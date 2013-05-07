//*============================================================================
//player.h
//*============================================================================
//[history]
//	08/03/03�@�C���J�n
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "SoundEffect.h"
#include "Particle.h"
#include "Menu.h"
#include "field.h"
#include "Sprite3D.h"
#include "character.h"
#include "enemy.h"

//=============================================================================
//using
//=============================================================================
using namespace Selene;

struct MarkData;

//=============================================================================
//enum
//=============================================================================



//=============================================================================
//class
//=============================================================================
//[Desc]
//	�v���C���[�p�N���X
//=============================================================================
class CPlayer :public CCharacter
{
	public:
	
		//�v���C���[�̏��
		enum eCharaState
		{
			STATE_NONE, //�������Ă��Ȃ����
			STATE_MOVING, //�ړ���
			STATE_CAPSTART, //�ߊl�J�n
			STATE_CAPTURE, //�ߊl��
			STATE_RELSTART,//����J�n
			STATE_RELEASE, //�����
			STATE_STOP,//��~��
			STATE_HIT_TRAIN, //�d�Ԃɓ��������ꍇ
			STATE_HIT_ENEMY, //�G�ɓ��������ꍇ
			STATE_MAX,//�v���C���[�̏�Ԃ̍ő吔
		};
		
		//�v���C���[�̃A�j���[�V�����p�^�[��
		enum eAnimPattern
		{
			ANIM_STAND,//�������
			ANIM_WALK,//�ړ����
			ANIM_CAPSTART,//���ݕt���n��
			ANIM_CAPMOVE,//���ݕt���ړ�
			ANIM_CAPEND,//���ݕt���I���
			ANIM_CAPING,//���ݕt����
		};
		
	private:
	
		Math::Vector3D m_vTargetPos;//�L�����ړ��ʒu
		Math::Vector3D m_vCapedPos;//�L���b�`�����ʒu(�ۑ��p)
		
		bool	m_IsJumpFlag;//�W�����v�����ǂ���
		bool	m_IsDead;//���S�t���O
		bool	m_IsCapture;//�ߊl�t���O
		
		float	m_fAccel;//�����x
		float	m_fMaxSpeed;//�ő呬�x
		
		Uint32 m_RelCount;//�����[�X�J�E���^�[
		
		eCharaState m_eState;//�L�����̏��
		
		CSprite *m_pMinSpr;//�~�j�}�b�v�p�X�v���C�g
		CEnemy *m_pCapedEnemy;//�ߊl�Ώۂ̓G
		
		Collision::CBox m_CapChkBox;//�ߊl����{�b�N�X
		Collision::CBox m_ShootChkBox;//�ʐ^�B�e�\����{�b�N�X
		Collision::CLine3D m_ShootChkRay; //�ʐ^�B�e���背�C
		
	public:
	
		CPlayer( const char *pName, Math::Vector3D vPos );//�R���X�g���N�^
		
		~CPlayer();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
		
		void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//�t�@�C���ǂݍ���

		void StateExec();//��Ԗ��̏���
		void AnimExec();//�A�j���[�V�����p����
		void MoveExec(){};//�ړ�����
		
		void Rendering();//�����_�����O
		
		void ShowMiniChara();//�~�j�L�����̕\��
		
	public:
	
		void AdjustDirection();//�����␳
		bool Move( Selene::Math::Vector3D vTargetPos, CCamera *pCam, CField *pField, bool IsShowMark );//�ړ�����
		bool GroundCheck( CField *pField );	//�n�ʃ`�F�b�N
		bool GroundCheck( CCharacter *pChara );//�n�ʃ`�F�b�N(�L����)
		
		void MoveAdjust();//�ړ��␳
		void GroundAdjust();//�n�ʕ␳
		
		void ChangeCameraMode( Sound::ISound *pSnd );//�J�������[�h�̐؂�ւ�
		void UpdateAnimation( );//�A�j���[�V�����̕ύX
		void ChangeAnimation( int animID );//�A�j���[�V�����̐؂�ւ�
		
		void CreateCapBox();//�ߊl����p�{�b�N�X�̐���
		void CreateShootBox( CCamera *pCam, CSceneManager *pSceneMgr );//�ʐ^�B�e����p�{�b�N�X�̐���
		void CreateShootRay( Scene::ISceneManager *pSceneMgr );//�ʐ^�B�e����p���C�̐���
		void ReleaseEnemy();//�ߊl���Ă���G�̉��
		
	private:
	
		Math::Vector3D m_vTarget;//�ߊl�^�[�Q�b�g�ʒu
		
	public:
		
		void Move( CCamera *pCam, Peripheral::IMouse *pMouse, 
					CField *pField, Scene::ISceneManager *pSceneMgr);//�ړ�����(�c�[���p)
					

		
	/*Set�n*/
	public:
	
		void SetTargetPos( Peripheral::IMouse *pMouse, CEnemy *pEnemy, Scene::ISceneManager *pSceneMgr );//�ړ��ʒu�̐ݒ�
		
		/*�A�j���[�V������Ԃ̐ݒ�*/
		void SetAnimState( eAnimState state )
		{
			m_eAnimState = state;
		}
		
		/*���S�t���O�̐ݒ�*/
		const void SetDeadFlag( bool flag ) 
		{
			m_IsDead = flag;
		}
		
		/*�v���C���[�̏�Ԃ̃Z�b�g*/
		const void SetState( eCharaState eState )
		{
			m_eState = eState;
		}
		
		void AddRotate( Math::Point3DI Rot )
		{
			m_Rot += Rot;
		}
		
	/*Get�n*/
	public:
	
		/*�d�͉����x�̎擾*/
		float GetGravity() const
		{
			return m_fGravity;									
		}

		
		/*���S�t���O�̎擾*/
		bool GetDeadFlag() const
		{
			return m_IsDead;
		}
		
		/*�ړ�������t���O�̎擾*/
		bool GetMovingFlag() const
		{
			return m_IsMoving;
		}
		
		/*�v���C���[�̏�Ԃ̎擾*/
		eCharaState GetState() const
		{
			return m_eState;
		}
		
		/*�ߊl����{�b�N�X�̎擾*/
		Collision::CBox GetCapCheckBox() const
		{
			return m_CapChkBox;
		}	
		
		/*�ʐ^����p�̃��C�̎擾*/
		Collision::CLine3D GetShootRay() const
		{
			return m_ShootChkRay;
		}
		
		/*�ʐ^����\�{�b�N�X�̎擾*/
		Collision::CBox GetShootChkBox() const
		{
			return m_ShootChkBox;
		} 
		
		/*�ߊl�Ώۂ̓G�̎擾*/
		CEnemy *GetCapedEnemy() const
		{
			return m_pCapedEnemy;
		}
		
		//�ߊl�ʒu�̎擾
		Math::Vector3D GetCapedPos() const
		{
			return m_vCapedPos;
		}
		
		/*�ߊl�t���O�̐ݒ�*/
		bool GetCaptureFlag() const
		{
			return m_IsCapture;
		}
		
		/*�}�E�X�^�[�Q�b�g�̎擾*/
		Math::Vector3D GetMouseTarget() const
		{
			return m_vTarget;
		}
		
		//�~�j�L�����̎擾
		CSprite *GetMinSpr() const
		{
			return m_pMinSpr;
		}
		
};