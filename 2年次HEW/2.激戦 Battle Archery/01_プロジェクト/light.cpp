
#include "light.h"
#include "myDirect3D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_LIGHT		(5)		// ���C�g�̐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DLIGHT9 g_aLight[NUM_LIGHT];		// ���C�g���

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void Light_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice(); 
	D3DXVECTOR3 vecDir;

	// **********************************************************************************
	// �^�ォ��Ƃ炷���C�g
	// **********************************************************************************
	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&g_aLight[0], sizeof(D3DLIGHT9));

	// ���C�g�̃^�C�v�̐ݒ�
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// �g�U��
	g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ����
	g_aLight[0].Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0].Direction, &vecDir);

	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(0, &g_aLight[0]);

	// ���C�g��L����
	pDevice->LightEnable(0, TRUE);


	// **********************************************************************************
	// �E�ǂ��Ƃ炷���C�g
	// **********************************************************************************
	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&g_aLight[1], sizeof(D3DLIGHT9));

	// ���C�g�̃^�C�v�̐ݒ�
	g_aLight[1].Type =D3DLIGHT_DIRECTIONAL;

	// �g�U��
	g_aLight[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ����
	g_aLight[1].Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

    // ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[1].Direction, &vecDir);

	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(1, &g_aLight[1]);

	// ���C�g��L����
	pDevice->LightEnable(1, TRUE);


	// **********************************************************************************
	// �������Ƃ炷���C�g
	// **********************************************************************************
	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&g_aLight[2], sizeof(D3DLIGHT9));

	// ���C�g2�̃^�C�v�̐ݒ�
	g_aLight[2].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g2�̊g�U���̐ݒ�
	g_aLight[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g2�̋��ʔ��ˌ��̐ݒ�
	g_aLight[2].Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

    // ���C�g2�̕����̐ݒ�
	vecDir = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[2].Direction, &vecDir);

	// ���C�g2�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(2, &g_aLight[2]);

	// ���C�g2��L����
	pDevice->LightEnable(2, TRUE);


	// **********************************************************************************
	// ���ǂ��Ƃ炷���C�g
	// **********************************************************************************
	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&g_aLight[3], sizeof(D3DLIGHT9));

	// ���C�g3�̃^�C�v�̐ݒ�
	
	g_aLight[3].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g3�̊g�U���̐ݒ�
	g_aLight[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g3�̋��ʔ��ˌ��̐ݒ�
	g_aLight[3].Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	// ���C�g3�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[3].Direction, &vecDir);

	// ���C�g3�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(3, &g_aLight[3]);

	// ���C�g3��L����
	pDevice->LightEnable(3, TRUE);


	// **********************************************************************************
	// �O�ǂ��Ƃ炷���C�g
	// **********************************************************************************
	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&g_aLight[4], sizeof(D3DLIGHT9));

	// ���C�g4�̃^�C�v�̐ݒ�

	g_aLight[4].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g4�̊g�U���̐ݒ�
	g_aLight[4].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g4�̋��ʔ��ˌ��̐ݒ�
	g_aLight[4].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

	// ���C�g4�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.0f, -1.0f, -1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[4].Direction, &vecDir);

	// ���C�g4�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(4, &g_aLight[4]);

	// ���C�g4��L����
	pDevice->LightEnable(4, TRUE);


	// ���C�e�B���O���[�h�L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);	//TRUE�ɂ���Ǝ����I�Ƀ��C�e�B���O
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void Light_Finalize(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void Light_Update(void)
{
}

