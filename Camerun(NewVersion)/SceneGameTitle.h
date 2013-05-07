//*============================================================================
//SceneGameTitle.h
//*============================================================================
//[history]
//	08/10/14  �쐬
//[author]
//	Taka
//============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneTemplate.h"

//=============================================================================
//const
//=============================================================================
/*���j���[��*/
const int MENU_MAX = 3;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�Q�[���^�C�g���N���X
//============================================================================
class CSceneGameTitle :public CSceneTemplate
{
	public:
	
		/*�Z���N�g�V�[��*/
		enum eSelectScene
		{
			SELECT_GAME,
			SELECT_TUTORIAL,
			SELECT_EXIT,
		};

	
	private:
	
		
		/*�^�C�g���̏��*/
		enum eTitleState
		{
			STATE_DEMO,
			STATE_STANDBY,
		};
		
		eSelectScene m_eSelectScene;//�Z���N�g�V�[��
		
	private:
	
		CBGM *m_pTitleBGM;//�^�C�g��BGM
		
		CMenu *m_pTitleMenu;//�^�C�g�����j���[
		
		CSprite *m_pBG;
		
		CFontSprite *m_pHiScoreFont;//�n�C�X�R�A�t�H���g
		CSprite *m_pHiScoreSpr;//�n�C�X�R�A
		
					
	public:
	
		
		/*�R���X�g���N�^*/
		CSceneGameTitle( string strFileName );
		
		/*�f�X�g���N�^*/
		~CSceneGameTitle();
		
		/*�I�u�W�F�N�g�f�[�^�̏�����*/
		void InitObjectData( Uint32 dt );
	
		/*������*/
		void Init( Uint32 dt );
		
		/*�ҋ@��*/
		void Idle( Uint32 dt );
		
		/*�t�F�[�h�A�E�g*/
		void FadeOut( Uint32 dt );
		
		/*�����_�����O*/
		void Rendering();
		
	public:
	
		void SetTitleMenu();//�^�C�g�����j���[�̐ݒ�
		void MoveScene( eSelectScene eScene );//�V�[���̈ړ�
		
	public:
	
		//�Z���N�g�V�[���̐ݒ�
		void SetSelectScene( eSelectScene eScene )
		{
			m_eSelectScene = eScene;
		}
		
	public:
	
		
		/*�Z���N�g�V�[���̎擾*/
		eSelectScene GetSelectScene() const
		{
			return m_eSelectScene;
		}
		
};




