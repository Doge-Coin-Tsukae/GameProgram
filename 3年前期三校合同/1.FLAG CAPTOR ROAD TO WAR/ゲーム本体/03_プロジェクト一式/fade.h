#pragma once

#include "gameobject.h"

class CFADE :public CGameObject
{
private:
	static ID3D11Buffer*				m_VertexBuffer;		//�o�b�t�@
	static ID3D11ShaderResourceView*	m_Texture;			//�e�N�X�`��

	static D3DXCOLOR m_FadeColor;	//�F
	static float m_Alpha;			//�A���t�@�l
	static float m_AddAlpha;		//��x�ɑ������
	static bool m_bOut;				//�t�F�[�h�C�����t�F�[�h�A�E�g��
	static bool m_bIsFade;			//���݃t�F�[�h���Ă��邩

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static void Fade_Start(bool bOut, int frame, D3DCOLOR color);		//�t�F�[�h�X�^�[�g
	static bool Fade_IsFade(void);										//�t�F�[�h�����m�F
	static void SetTexture(char* SetTexture)							//�e�N�X�`���̃Z�b�g
	{
		//�e�N�X�`���ǂݍ���
		D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
			SetTexture,
			NULL,
			NULL,
			&m_Texture,
			NULL);
	}
};