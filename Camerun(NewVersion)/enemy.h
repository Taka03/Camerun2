//*============================================================================
//enemy.h
//*============================================================================
//[history]
//	08/03/09�@�C���J�n
//[author]
//	Taka
//=============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "character.h"
#include "Sprite3D.h"
#include "FontSprite3D.h"
#include "Sprite.h"
#include "SceneManager.h"
#include <vector>
#include <fstream>
#include <string>

//=============================================================================
//const
//=============================================================================
const float fCHECK_DISTANCE = 30.0f;//�ʐ^����\����

using namespace std;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�G�p�N���X
//=============================================================================
class CEnemy :public CCharacter
{
	public:
	
		/*�G�̏��*/
		enum eEnemyState
		{
			STATE_NONE,
			STATE_RELEASE,
			STATE_HITENEMY,
		};
		
		//�}�X�N�̏��
		enum eFieldMask
		{
			MASK_UNIVERSAL,//�ėp
			MASK_LAKE = 2,//��
			MASK_MOUSE,//�l�Y�~
			MASK_LIZARD,//�g�J�Q
			MASK_OUT,//�O��
			
		};
	
	protected:
	
		int m_PhotoPoint;//�ʐ^�B�e���|�C���g
		bool m_IsEndPhoto;//�ʐ^�B�e���I���Ă��邩�ǂ���
		bool m_IsLockOn;//���b�N�I������Ă��邩�ǂ���
		bool m_IsHitWall;//�ǂɐڐG���Ă����ꍇ
		bool m_IsCatchable;//�L���b�`�ł��邩�ǂ���
		
		string m_TypeName;//�^�C�v��
		string m_StTypeName;//�^�C�v��(�ėp)
		
		CSprite3D *m_pCatchSpr3D;//�L���b�`�}�[�N
		CSprite3D *m_pLockOnSpr3D;//���b�N�I���}�[�N
		CFontSprite3D *m_pPntFontSpr3D;//�|�C���g�\���X�v���C�g
		
		CSprite *m_pMinSpr;//�~�j�}�b�v�p�X�v���C�g
		
		Math::Vector3D m_vCatchPos;//���ݕt����ʒu
		Math::Vector3D m_vCatchMrkPos;//�L���b�`�}�[�N�̈ʒu
		Math::Vector3D m_vLockMrkPos;//���b�N�I���}�[�N�̈ʒu
		
		Math::Vector3D m_vCatchBefPos;//���ݕt�����O�̈ʒu
		
		eEnemyState m_eState;//�G�̏��
		
		float m_fKeyTime;//�L�[����
		float m_fMaxKeyTime;//�ő�L�[����
		
		vector< Math::Vector3D > m_vecKey;//�L�[�f�[�^
		
		Math::Vector3D m_vNextPoint;//���̈ړ��|�C���g
		Math::Vector3D m_vInitPoint;//���݂̈ړ��|�C���g
		int m_RootSpeed;//���[�g�̈ړ����x
		int m_ReleaseCnt;//�����[�X�J�E���g
		int m_GravityCnt;//�d�̓J�E���g
		
		bool m_IsCaptured;//�ߊl����t���O
		
		Collision::CLine3D m_HitRay;//�����蔻��p���C
		
		Math::CRandom m_Rand;//�����_���l
		
		//Math::Point3D< Math::Animation *> m_pPntAnim;//�A�j���[�V�����|�C���g
		Math::Animation *m_pAnimX;//�A�j���[�V�����|�C���gX
		Math::Animation *m_pAnimZ;//�A�j���[�V�����|�C���gZ
		
		Uint32 m_RootCount;//���[�g�J�E���g
		
	public:
	
		CEnemy( const char *pName, Math::Vector3D vPos, Selene::File::IResourceFile *pResFile );//�R���X�g���N�^
		~CEnemy();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
		void Rendering();//�����_�����O
		
		void ShowMiniChara();//�~�j�L�����̕\��

		void StateExec();//��Ԗ��̏���
		void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//�ǂݍ���
		void SetActorIndex( int index );
		
		virtual void MoveExec();//�ړ�����
		virtual bool Move( Selene::Math::Vector3D vTargetPos, CCamera *pCam, CField *pField, bool IsShowMark );//�ړ�
		void MoveRoot();//���[�g�ł̈ړ�
		void MoveRandom();//�����_���E�H�[�N
		
		void SetNextPoint( );//���̈ړ��|�C���g�̐ݒ�
		
		virtual bool HitCheckWall( CField *pField );//�ǂƂ̐ڐG����
		
		void RenderingCatchMark();//�L���b�`�}�[�N�̃����_�����O
		void RenderingPoint();//�|�C���g�̃����_�����O
		void RenderingLockOn();//���b�N�I���}�[�N�̃����_�����O
		
		/*�����̎�̐ݒ�*/
		void SetSeed( ICore *pCore );
		
		
		//���[�g�̈ړ��ӏ��L�[�̐ݒ�
		void SetRootKey();
		
	
		
	public:
	
		void ChangeAnimation( );//�A�j���[�V�����̕ύX
		
		void CheckCatch( Collision::CBox Box );//�ߊl�Ώۂ��`�F�b�N
		int CalcScore( CPlayer *pPlayer );//�X�R�A�v�Z
		int CheckPosScore();//�ʐ^�̎ʂ��Ă���ʒu�̃X�R�A
		bool CheckShoot( CSceneManager *pSceneMgr );//�ʐ^�B�e�\���`�F�b�N
		bool CheckShoot( CPlayer *pPlayer );//�ʐ^�B�e�\���`�F�b�N

		
	public:
	
		/*�ߊl����t���O�̐ݒ�*/
		void SetCapdFlag( bool IsCaped )
		{
			m_IsCaptured = IsCaped;
		} 
		
		/*���ݕt����ʒu�̐ݒ�*/
		void SetCatchPos( Math::Vector3D vPos )
		{
			m_vCatchPos = vPos;
		}
		
		/*��Ԃ̐ݒ�*/
		void SetState( eEnemyState eState )
		{
			m_eState = eState;
		}
		
		/*���b�N�I������t���O�̐ݒ�*/
		void SetLockOnFlag( bool flag )
		{
			m_IsLockOn = flag;
		}
		
		/*�ߊl�O�̍��W�̐ݒ�*/
		void SetCatchBeforePos( Math::Vector3D vPos )
		{
			m_vCatchBefPos = vPos;
		}
		
		/*�B�e�I���t���O�̐ݒ�*/
		void SetShootEndFlag( bool flag )
		{
			m_IsEndPhoto = flag;
		}
		
		//�L���b�`�X�v���C�g�̃Z�b�g
		void SetCatchSpr3D( CSprite3D *pSpr3D )
		{
			m_pCatchSpr3D = pSpr3D;
		}
		
		//�d�̓J�E���^�̐ݒ�
		void SetGravityCnt( Sint32 Cnt )
		{
			m_GravityCnt = Cnt;
		}

	public:
	
		/*�L�[�A�j���[�V�������Ԃ̎擾*/
		float GetKeyTime( ) const
		{
			return m_fKeyTime;
		}
		
		/*���ݕt����ʒu�̎擾*/
		Math::Vector3D GetCatchPos() const
		{
			return m_vCatchPos;
		}
		
		/*�L���b�`�X�v���C�g�̎擾*/
		CSprite3D *GetCatchSpr3D() const
		{
			return m_pCatchSpr3D;
		}
		
		/*�|�C���g�t�H���g�̎擾*/
		CFontSprite3D *GetPntSpr3D() const
		{
			return m_pPntFontSpr3D;
		}
		
		/*���b�N�I���X�v���C�g�̎擾*/
		CSprite3D *GetLockOnSpr3D() const
		{
			return m_pLockOnSpr3D;
		}
		
		/*���b�N�I������t���O�̎擾*/
		bool GetLockOnFlag() const
		{
			return m_IsLockOn;
		}
		
		/*�B�e�I���t���O�̎擾*/
		bool GetShootEndFlag() const
		{
			return m_IsEndPhoto;
		}
		
		/*�ߊl���ꂽ�t���O�̎擾*/
		bool GetCapedFlag() const
		{
			return m_IsCaptured;
		}
		
		/*�ߊl�\����t���O*/
		bool GetCatchableFlag() const
		{
			return m_IsCatchable;
		}
		
		/*�ߊl�O�̍��W�̎擾*/
		Math::Vector3D GetCatchBeforePos() const
		{
			return m_vCatchBefPos;
		}
		
		//���b�N�I���}�[�N�̈ʒu�̎擾
		Math::Vector3D GetLockSprPos() const
		{
			return m_vLockMrkPos;
		}
		
		/*�^�C�v���̎擾*/
		string GetTypeName() const
		{
			return m_TypeName;
		}
		
		//�^�C�v���̎擾
		string GetStTypeName() const
		{
			return m_StTypeName;
		}
		
		//�~�j�L�����̎擾
		CSprite *GetMinSpr() const
		{
			return m_pMinSpr;
		}

	
	
};