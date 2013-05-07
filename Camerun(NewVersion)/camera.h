//*============================================================================
//camera.h
//*============================================================================
//[history]
//	08/03/11�@�C��
//[author]
//	Taka
//============================================================================

//��d�C���N���[�h�h�~
#pragma once

//=============================================================================
//include
//=============================================================================
#include "gameobject.h"

//=============================================================================
//enum
//=============================================================================
//�J�����̉�]�^�C�v
enum eRollType
{
	ROLL_LEFT,
	ROLL_RIGHT,
	ROLL_UP,
	ROLL_DOWN,
};

//=============================================================================
//variable
//=============================================================================
class CPlayer;
class CEnemy;

//=============================================================================
//class
//=============================================================================
//[desc]
//	�J�����p�N���X
//=============================================================================
class CCamera
{
	private:
	
		Scene::ICamera *m_pCamera;//�J�����f�o�C�X
		
	private:
	
		Math::Vector3D m_vPos;//�ʒu
		Math::Vector3D m_vInitPos;//�ʒu(�o�b�N�A�b�v�p)
		Math::Vector3D m_vTarget;//�^�[�Q�b�g
		Math::Point3DI m_Rot;//��]�p�x
		Math::Point3DI m_InitRot;//��]�p�x(�o�b�N�A�b�v�p)
		Math::Style	   m_Style;//�p���f�[�^
		
		Math::Vector3D m_vDirection;//�J�����̖ڐ����W
		
		Math::Vector3D m_vUp;//�J�����̏��
		Math::Vector3D m_vFront;//�J�����̐���
		Math::Vector3D m_vRight;//�J�����̉E��
		
		Math::Vector3D m_vInitFront;//�J�����̐���
		Math::Vector3D m_vInitRight;//�J�����̑���
		
		::Collision::CLine3D m_vRay;//���C
		
		bool m_IsChangeTopView;//�g�b�v�r���[�؂�ւ�����t���O
		
		Sint32 m_CamCnt;//�J�����J�E���g
	
	public:
	

		CCamera();//�R���X�g���N�^
		~CCamera();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
		
		void RotateCamera( eRollType Type );//�J�����̉�]
		void RotateAdjust();//�J�����̉�]�␳
		
	public:
	
		void SetCamera( Scene::ISceneManager *pScene );//�J�����̃Z�b�g
		//void SetCamera( Scene::ICustomizedSceneManager *pScene );//�J�����̃Z�b�g
		
		void SetProjection( float fNear, float fFar, Sint32 fov, Sint32 Width, Sint32 Height );//�v���W�F�N�V�����̐ݒ�
		void SetTransform( Math::Style style );//�ό`�̓K�p	
		void SetTransform( );//�ό`�̓K�p
		void SetTransform( CPlayer *pPlayer );
		void SetTransform( Sint32 Angle, bool IsCamMove );
		void SetTransform2();//�ό`�̓K�p
		void SetTransform3();//�ό`�̓K�p
		void SetTransformCap( CPlayer *pPlayer, CEnemy *pTarget );//�L���v�`���[���̃J�����ό`
		void SetTransformDemo( CEnemy *pEnemy );//�f���p�̃J�����ړ�
		void SetTransformBird( Sint32 Angle, bool IsCamMove);//�g���p�̃J�����ړ�
		void SetPosition( Math::Vector3D vPos );//�ʒu�̐ݒ�
		void SetAngle( Sint32 Angle );//�p�x�̐ݒ�
		void SetTargetPos( Math::Vector3D vTarget );//�^�[�Q�b�g�̈ʒu�Z�b�g
		void SetStyle( Math::Style style );//�p���f�[�^�ݒ�		
		void SetRotate( Math::Point3DI Rot );//�p�x�̐ݒ�
		
		/*�g�b�v�r���[�t���O�̐ݒ�*/
		void SetTopViewFlag( bool flag )
		{
			m_IsChangeTopView = flag;
		}
		
		/*�J�����̕����̐ݒ�*/
		void SetDirection( Math::Vector3D vDir )
		{
			m_vDirection = vDir;
		}
		
		/*��]�����̑���*/
		void AddRotate( Math::Point3DI Add )
		{
			m_Rot += Add;	
			
		}
	
		
	/*Get�n*/
	public:
	
		//�J�����f�o�C�X�̎擾
		Scene::ICamera *GetCamera()
		{
			return m_pCamera;
		}
		
		//�ʒu�̎擾		
		Math::Vector3D GetPosition()
		{
			return m_vPos;
		}
		//�^�[�Q�b�g�̎擾
		Math::Vector3D GetTarget() const
		{
			return m_vTarget;
		}
		
		//�p���f�[�^�̎擾		
		Math::Style GetStyle() const
		{
			return m_Style;
		}
		
		/*�J�����̐��ʂ̎擾*/
		Math::Vector3D GetFront() const
		{
			return m_vFront;
		}
		
		/*�J�����̑��ʂ̎擾*/
		Math::Vector3D GetRight() const
		{
			return m_vRight;
		}
		
		//�J�����̏�ʂ̎擾
		Math::Vector3D GetUp() const
		{
			return m_vUp;
		}
		
		//��]�p�x�̐ݒ�
		Math::Point3DI GetRotate() const
		{
			return m_Rot;
		}
		
		/*�g�b�v�r���[����t���O�̎擾*/
		bool GetTopViewFlag() const
		{
			return m_IsChangeTopView;
		}

		
		
		
		
		
};