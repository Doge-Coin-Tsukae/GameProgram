//--------------------------------------
//windowsapi���g���ăt�@�C���̎Q�Ƃ��s��
//--------------------------------------
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <tchar.h>
#include <shlobj.h>

int __stdcall BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData) {
	TCHAR dir[MAX_PATH];
	ITEMIDLIST *lpid;
	HWND hEdit;

	switch (uMsg) {
	case BFFM_INITIALIZED:  //      �_�C�A���O�{�b�N�X��������
		SendMessage(hWnd, BFFM_SETSELECTION, (WPARAM)TRUE, lpData);     //      �R�����_�C�A���O�̏����f�B���N�g��
		break;
	case BFFM_VALIDATEFAILED:       //      �����ȃt�H���_�[�������͂��ꂽ
		MessageBox(hWnd, (TCHAR*)lParam, _TEXT("�����ȃt�H���_�[�������͂���܂���"), MB_OK);
		hEdit = FindWindowEx(hWnd, NULL, _TEXT("EDIT"), NULL);     //      �G�f�B�b�g�{�b�N�X�̃n���h�����擾����
		SetWindowText(hEdit, _TEXT(""));
		return 1;       //      �_�C�A���O�{�b�N�X����Ȃ�
		break;
	case BFFM_IUNKNOWN:
		break;
	case BFFM_SELCHANGED:   //      �I���t�H���_�[���ω������ꍇ
		lpid = (ITEMIDLIST *)lParam;
		SHGetPathFromIDList(lpid, dir);
		hEdit = FindWindowEx(hWnd, NULL, _TEXT("EDIT"), NULL);     //      �G�f�B�b�g�{�b�N�X�̃n���h�����擾����
		SetWindowText(hEdit, dir);
		break;
	}
	return 0;
}

bool GetDir(HWND hWnd, TCHAR* def_dir, TCHAR* path) {
	BROWSEINFO bInfo;
	LPITEMIDLIST pIDList;

	memset(&bInfo, 0, sizeof(bInfo));
	bInfo.hwndOwner = hWnd; // �_�C�A���O�̐e�E�C���h�E�̃n���h�� 
	bInfo.pidlRoot = NULL; // ���[�g�t�H���_���f�X�N�g�b�v�t�H���_�Ƃ��� 
	bInfo.pszDisplayName = path; //�t�H���_�����󂯎��o�b�t�@�ւ̃|�C���^ 
	bInfo.lpszTitle = TEXT("�t�H���_�̑I��"); // �c���[�r���[�̏㕔�ɕ\������镶���� 
	bInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_VALIDATE | BIF_NEWDIALOGSTYLE; // �\�������t�H���_�̎�ނ������t���O 
	bInfo.lpfn = BrowseCallbackProc; // BrowseCallbackProc�֐��̃|�C���^ 
	bInfo.lParam = (LPARAM)def_dir;
	pIDList = SHBrowseForFolder(&bInfo);
	if (pIDList == NULL) {
		path[0] = _TEXT('\0');
		return false; //�����I������Ȃ������ꍇ 
	}
	else {
		if (!SHGetPathFromIDList(pIDList, path))
			return false;//�ϊ��Ɏ��s 
		CoTaskMemFree(pIDList);// pIDList�̃��������J�� 
		return true;
	}
}