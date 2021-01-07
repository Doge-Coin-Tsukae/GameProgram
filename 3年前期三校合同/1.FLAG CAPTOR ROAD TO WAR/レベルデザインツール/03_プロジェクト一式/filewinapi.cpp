//--------------------------------------
//windowsapiを使ってファイルの参照を行う
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
	case BFFM_INITIALIZED:  //      ダイアログボックス初期化時
		SendMessage(hWnd, BFFM_SETSELECTION, (WPARAM)TRUE, lpData);     //      コモンダイアログの初期ディレクトリ
		break;
	case BFFM_VALIDATEFAILED:       //      無効なフォルダー名が入力された
		MessageBox(hWnd, (TCHAR*)lParam, _TEXT("無効なフォルダー名が入力されました"), MB_OK);
		hEdit = FindWindowEx(hWnd, NULL, _TEXT("EDIT"), NULL);     //      エディットボックスのハンドルを取得する
		SetWindowText(hEdit, _TEXT(""));
		return 1;       //      ダイアログボックスを閉じない
		break;
	case BFFM_IUNKNOWN:
		break;
	case BFFM_SELCHANGED:   //      選択フォルダーが変化した場合
		lpid = (ITEMIDLIST *)lParam;
		SHGetPathFromIDList(lpid, dir);
		hEdit = FindWindowEx(hWnd, NULL, _TEXT("EDIT"), NULL);     //      エディットボックスのハンドルを取得する
		SetWindowText(hEdit, dir);
		break;
	}
	return 0;
}

bool GetDir(HWND hWnd, TCHAR* def_dir, TCHAR* path) {
	BROWSEINFO bInfo;
	LPITEMIDLIST pIDList;

	memset(&bInfo, 0, sizeof(bInfo));
	bInfo.hwndOwner = hWnd; // ダイアログの親ウインドウのハンドル 
	bInfo.pidlRoot = NULL; // ルートフォルダをデスクトップフォルダとする 
	bInfo.pszDisplayName = path; //フォルダ名を受け取るバッファへのポインタ 
	bInfo.lpszTitle = TEXT("フォルダの選択"); // ツリービューの上部に表示される文字列 
	bInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_VALIDATE | BIF_NEWDIALOGSTYLE; // 表示されるフォルダの種類を示すフラグ 
	bInfo.lpfn = BrowseCallbackProc; // BrowseCallbackProc関数のポインタ 
	bInfo.lParam = (LPARAM)def_dir;
	pIDList = SHBrowseForFolder(&bInfo);
	if (pIDList == NULL) {
		path[0] = _TEXT('\0');
		return false; //何も選択されなかった場合 
	}
	else {
		if (!SHGetPathFromIDList(pIDList, path))
			return false;//変換に失敗 
		CoTaskMemFree(pIDList);// pIDListのメモリを開放 
		return true;
	}
}