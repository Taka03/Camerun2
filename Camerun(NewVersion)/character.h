//*============================================================================
//character.h
//*============================================================================
//[history]
//	08/03/03�@�C���J�n
//[author]
//	Taka
//=============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Draw3DObject.h"
#include "camera.h"
#include "field.h"
#include "LuaManager.h"

//=============================================================================
//enum
//=============================================================================
//�A�j���[�V�����^�C�v
enum eAnimType
{
	ANIM_NOW,
	ANIM_NEXT,
	ANIM_MAX,
};

//�A�j���[�V�����̏��
enum eAnimState
{
	ANIM_STANDBY,//�ҋ@��
	ANIM_CHANGESTART,//�؂�ւ��J�n
	ANIM_CHANGE,//�؂�ւ���
	ANIM_CHANGEEND,//�؂�ւ��I��
};

//#define DEBUG_MAP


//=============================================================================
//class
//=============================================================================
//[Desc]
//	�L�����N�^�[�p�N���X
//=============================================================================
class CCharacter :public CDraw3DObject
{
	protected:
	
		Renderer::Object::IModel *m_pModel;//���f���f�[�^	
		Scene::IModelActor		 *m_pActorModel[SCREEN_MAX];//���f���A�N�^�[
		
		Renderer::Object::ILine3D *m_pLine3D;//�f�o�b�O�p���C��
		Scene::IPrimitiveActor *m_pActorLine[SCREEN_MAX];//���C���A�N�^�[
		
	protected:
	
		Math::Vector3D m_vFront;//�L�����̐��ʃx�N�g��
		Math::Vector3D m_vRight;//�L�����̉E�ʃx�N�g��
		
		Math::Vector3D m_vDirection;//�L�����̌����Ă������
		
		bool m_IsExistAnim;//�A�j���[�V���������݂��邩
		bool m_IsMoving;//�L�����������Ă��邩�ǂ���
		
		eAnimState m_eAnimState;//�A�j���[�V�������
		
		float m_fWeight;//�d��
		float m_fSpeed;//�ړ����x
		float m_fStSpeed;//��{���x
		
		float   m_fGravity;//�d��
		
		bool m_IsFly;//��s�����ǂ���
		
		int m_AnimID[ANIM_MAX];//�A�j���[�V����ID
		float m_fAnimTime[ANIM_MAX];//���݂̃A�j���[�V��������
		
	public:
	
		CCharacter( const char *pName, Math::Vector3D vPos );//�R���X�g���N�^
		
		~CCharacter(); //�f�X�g���N�^
	
		void Init();//������
		void Exec();//����
		void SetActorSetting();//�A�N�^�[�̐ݒ�̃Z�b�g
		void Rendering( );//�����_�����O
		virtual void MoveExec(){};
		
		virtual bool Move( Selene::Math::Vector3D vTargetPos, CCamera *pCam, CField *pField );//�ړ�
		
		
		virtual void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//�t�@�C���ǂݍ���
		virtual void CreateActor( int index, Scene::ISceneManager *pSceneMgr );//�A�N�^�[�̐���
		void CreateCollision( int index );//�R���W�����f�[�^�̍쐬
		
		bool HitCheck( CCharacter *pChara );
		bool HitCheck( CDraw3DObject **ppChara );//�����蔻��
		bool HitCheck( Selene::Collision::CLine3D &vRay );//�����蔻��
		bool HitCheck( Selene::Collision::CLine3D &vRay, Renderer::SCollisionResult &Out );
		
		Bool MoveCheck( CField *pField );//�ړ��`�F�b�N
		bool MoveCheck( CCharacter *pChara );//�ړ��`�F�b�N

		bool GroundCheck( CCharacter *pChara );//�n�ʃ`�F�b�N
		virtual bool GroundCheck( CField *pField );//�n�ʃ`�F�b�N

		void SetActorIndex( int index );//�A�N�^�[�C���f�b�N�X�̃Z�b�g
		
		float CheckDistance( CCharacter *pChara );//�L���������𑪂�
		
		void SetAlphaColor( Sint32 alpha );//�A���t�@�l�̐ݒ�
		
		void AddRef();//�Q�ƃJ�E���^�̑���
		
		/*�{�b�N�X�̕`��*/
		void DrawBox( Collision::CBox Box[], int num );
		
	/*Set�n*/
	public:
	

		
	/*Get�n*/
	public:
	
		/*���f���f�[�^�̎擾*/
		Renderer::Object::IModel *GetModel() const
		{
			return m_pModel;
		}
		
		/*���f���A�N�^�[�̎擾*/
		Scene::IModelActor *GetModelActor( int index ) const
		{
			return m_pActorModel[index];
		}
		
		/*�ړ����x�̎擾*/
		float GetSpeed() const
		{
			return m_fSpeed;
		}
		
		/*���ʃx�N�g���̎擾*/
		Math::Vector3D GetFront() const
		{
			return m_vFront;
		}
		
		/*�E�ʃx�N�g���̎擾*/
		Math::Vector3D GetRight() const
		{
			return m_vRight;
		}
		
		/*�����̎擾*/
		Math::Vector3D GetDirection() const
		{
			return m_vDirection;
		}
		

		
};