//****************************************************
//�Ə����o���v���O����
//****************************************************

#include "point.h"
#include "camera.h"
#include "texture.h"
#include "sprite.h"
#include "xfile.h"

DRAWOBJECT static g_en[MAX_PLAYER];		//�~���

//�e�̃N���X
class POINTER {
private:
	D3DXVECTOR3		PosPoint;				//�e�̃|�W�V����
	D3DXVECTOR3		RotPoint;				// �e�̌���(��])
	D3DXVECTOR3		SclPoint;				//�e�̑傫��


public:
	//�e�̏�������
	void PointInit(int index)
	{
		g_en[index].InitCircle(index);	//�~�̏��L����
		PosPoint = GetPos(index);
		RotPoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SclPoint = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	}

	//�e�̍��W���X�V����
	void Update(int index)
	{
		float radius = g_en[index].GetAngle() * 3.14f / 180.0f;

		// �O�p�֐����g�p���A�~�̈ʒu������o���B
		float add_x = cos(radius) * g_en[index].GetLength();
		float add_z = sin(radius) * g_en[index].GetLength();

		// ���ʂłł��ʒu�𒆐S�ʒu�ɉ��Z���A�����`��ʒu�Ƃ���
		PosPoint.x = GetPos(index).x + add_x;
		PosPoint.z = GetPos(index).z + add_z;
		/*�����܂�*/

		/*�c�̉~������o��*/
		float radius2 = g_en[index].GetAngle2() * 3.14f / 180.0f;

		// �O�p�֐����g�p���A�~�̈ʒu������o���B
		float add_y = sin(radius2) * g_en[index].GetLength();
		PosPoint.y = (GetPos(index).y +150.0f) + add_y;
	}

	void changepoint(int type, int index,float cameraspeed)
	{
		switch (type) {
			//�O�ړ�
		case UP:
			PosPoint.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//���ړ�
		case DOWN:
			PosPoint.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//�E�ړ�
		case RIGHT:
			PosPoint.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//���ړ�
		case LEFT:
			PosPoint.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//�E�O
		case RIGHTUP:
			PosPoint.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;

			PosPoint.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//�E���
		case RIGHTDOWN:
			PosPoint.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;

			PosPoint.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//���O
		case LEFTUP:
			PosPoint.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;

			PosPoint.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//�����
		case LEFTDOWN:
			PosPoint.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;

			PosPoint.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

		case FLY:
			break;

			//�d�͂Ɉ���������
		case GRAVITY:

			//����ȊO
		default:
			break;
		}
	}

	//���W�̊m�F
	D3DXVECTOR3 CheckPos()
	{
		return PosPoint;
	}

	//�傫���̊m�F
	D3DXVECTOR3 CheckScl()
	{
		return SclPoint;
	}

	//��]�̊m�F
	D3DXVECTOR3 CheckRot()
	{
		return RotPoint;
	}

};

POINTER  point[MAX_PLAYER];

//*****************************************************************************
//�֐�
//*****************************************************************************

/*��������*/
HRESULT Point_Initialize(void)
{
	for (int i = 0 ; i < MAX_PLAYER; i++)
	{
		point[i].PointInit(i);
	}

	SetTexture(TEXTURE_INDEX_SIGHT);

	return S_OK;
}

/*�I������*/
void Point_Finalize(void)
{
	ReleaseTexture(TEXTURE_INDEX_SIGHT);
}

/*�X�V����*/
void Point_Update(void)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		point[i].Update(i);		//�e�̍X�V����
	}
}

/*�`�揈��*/
void Point_Draw(void)
{
	Sprite_Draw(TEXTURE_INDEX_SIGHT,
		SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4 - 60, SCREEN_HEIGHT / 2);

	Sprite_Draw(TEXTURE_INDEX_SIGHT,
		SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4 - 60, SCREEN_HEIGHT / 2);
}

D3DXVECTOR3 Get_Pos(int index)
{
	return point[index].CheckPos();
}

void ChangePointVer(int num, int index)
{
	g_en[index].ChangeCameraRotVertical(num);
}

void ChangePoint(int num, int index,float cameraspeed)
{
	point[index].changepoint(num,index,cameraspeed);
}

void ChangePointAngle(int num,int index)
{
	g_en[index].ChangeCameraRot(num);
}