//*============================================================================
//SceneGameMain.h
//*============================================================================
//[history]
//	08/03/11�@�쐬
//	08/11/02  �C��
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "SceneTemplate.h"
#include "MiniMap.h"
#include <vector>

//=============================================================================
//const
//=============================================================================
const int TRL_ENEMY_NUM = 2;//�`���[���A���̓G�̐�
const int MARKER_MAX = 99;//�}�[�J�[��


//=============================================================================
//struct
//=============================================================================
struct MarkData
{
	CSprite3D *m_pMarker;//�}�[�J�[�X�v���C�g
	bool m_IsSet;//�ݒu����Ă��邩�ǂ���
	
	MarkData()
	{
		m_pMarker = NULL;
		m_IsSet = false;
	}
};

class CDraw3DObject;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�Q�[���V�[�����C���N���X
//=============================================================================
class CSceneGameMain :	public CSceneTemplate
{
	public:
	
		/*���̃V�[��*/
		enum eNextScene
		{
			SCENE_PHOTOCHECK,//�ʐ^�m�F���
			SCENE_TITLE,//�^�C�g�����
			SCENE_RESULT,//���U���g���	
			SCENE_PAUSE,//�|�[�Y���
			SCENE_NEWELEM,//�V�v�f���
		};
		
		/*�`���[�g���A���̃V�[��*/
		enum eTutorialScene
		{
			SCENE_START,//�`���[�g���A���̎n�܂�
			SCENE_MOVEEXP,//�ړ�����
			SCENE_CAMMOVEEXP,//�J�����ړ�����
			SCENE_SHOOTTARGET,//�^�[�Q�b�g�B�e
			SCENE_CAPTURETARGET,//�^�[�Q�b�g�ߊl
			SCENE_RELEASETARGET,//�^�[�Q�b�g�����[�X
			SCENE_FINISH,//�I��
		};
		
		/*�}�E�X�X�v���C�g�̏��*/
		enum eMouseSprState
		{
			MOUSE_PUSHNONE,//�������ĂȂ����
			MOUSE_PUSHLEFT,//���N���b�N
			MOUSE_PUSHRIGHT,//�E�N���b�N
			MOUSE_DRAG,//�h���b�O
			MOUSE_MAX,
		};
		
		/*�ǉ�����@�\*/
		enum eAddFunc
		{
			FUNC_MOVE,//�ړ�
			FUNC_CAMROT,//�J������]
			FUNC_CAMRESET,//�J�������Z�b�g
			FUNC_SHOOTTARGET,//�ʐ^�B�e
			FUNC_MENU,//���j���[
			FUNC_CAPTURE,//�ߊl
			FUNC_RELEASE,//���
			FUNC_MAX,//�ǉ��@�\�̍ő�l
		};
		
		/*�I�v�V����*/
		enum eOption
		{
			OPTION_SCORE,//�X�R�A
			OPTION_FILM,//�t�B����
			OPTION_MAX,//�I�v�V�����ő吔
		};
		
		//�V�v�f
		enum eNewElement
		{
			ELEM_TUTORIAL,//�`���[�g���A���ǉ�
			ELEM_ADDMOUSE,//�˂��݂̒ǉ�
			ELEM_ADDLIZARD,//�Ƃ����̒ǉ�
			ELEM_ADDOLDCAM,//���L�����̒ǉ�
			ELEM_ADDFREE,//�t���[�~�b�V�����̒ǉ�
			ELEM_MAX,
		};
		
	private:
	
		
		eNextScene m_eNextScene;//���̃V�[��
		eTutorialScene m_eTrlScene;//�`���[�g���A���V�[��
		bool m_IsTutorialEnd;//�`���[�g���A���I��������
		
		bool m_IsDemo;//�f����
		
		std::vector<CDraw3DObject *> m_vec3DList;//3DList
		
	private:
	
		CPlayer *m_pPlayer;//�v���C���[�I�u�W�F�N�g
		CField  *m_pField;//�t�B�[���h�I�u�W�F�N�g
		CTrain  *m_pTrain;//�d�ԃI�u�W�F�N�g
		CEnemyMouse *m_pMouse;//�˂��݃I�u�W�F�N�g
		CEnemyAmeus *m_pAmeus;//�A���E�X�I�u�W�F�N�g		
		CEnemyManta *m_pManta;//�}���^�I�u�W�F�N�g
		CEnemyRabbit *m_pRabbit;//�������I�u�W�F�N�g
		
		vector<CEnemy *> m_pVecCatchEnemy;//�ߊl�Ώۂ̓G
		vector<CEnemy *> m_pVecTarget;//�^�[�Q�b�g�Ώۂ̓G
		CEnemy *m_pTrlEnemy[TRL_ENEMY_NUM];//�`���[�g���A���̓G
		
		CCharacter *m_pFountObj;//�����I�u�W�F�N�g
		CCharacter *m_pIsLand;//�󒆒뉀�I�u�W�F�N�g
		CCharacter *m_pTargetArrow;//�^�[�Q�b�g���I�u�W�F�N�g
		CCharacter *m_pArrow;//���I�u�W�F�N�g
		
		CSprite	   *m_pReleaseBtnSpr;//�߈ˉ����{�^��

		CSprite	   *m_pFilmSpr;//�t�B�����I�u�W�F�N�g
		CSprite    *m_pMoveArrowSpr;//�ړ����
		CSprite	   *m_pCamPointaSpr;//�J�����|�C���^
		
		CSprite	   *m_pMarkerSpr;//�ړ��}�[�J
		
		CSprite	   *m_pMissionWinSpr;//�~�b�V�����E�B���h�E�X�v���C�g
			
		CSprite	   *m_pMenuBtnSpr;// ���j���[�{�^���X�v���C�g
		CSprite    *m_pReadySpr;//�Q�[���J�n�X�v���C�g
		CSprite	   *m_pGoSpr;//�S�[�X�v���C�g
		CSprite	   *m_pEndSpr;//�Q�[���I���X�v���C�g
		
		CMiniMap   *m_pMiniMap;//�~�j�}�b�v�p�I�u�W�F�N�g	
		CSprite	   *m_pMiniTarget;//�~�j�}�b�v�^�[�Q�b�g�p�X�v���C�g	
		
		CBGM	*m_pGameMusic;//�Q�[�����y�I�u�W�F�N�g
		
		vector< MarkData > m_vecMarker;//�c�[���p�}�[�J�[
				
		CFontSprite *m_pNumFont[OPTION_MAX];//���ʃt�H���g
		
		
		//�`���[�g���A�����[�h�p
	private:
	
		eMouseSprState m_eMouseSprState;//�}�E�X�̏��
		CSprite	   *m_pMouseSpr;//�}�E�X��ԕ\���A�C�R��
		CSprite    *m_pArrowExpSpr;//�������p�摜
		CField  *m_pTrlField;//�`���[�g���A���t�B�[���h�I�u�W�F�N�g
		
		CBGM	*m_pTrlMusic;//�`���[�g���A�����y
		
		bool m_IsAddFunc[FUNC_MAX];//�@�\�ǉ����ꂽ���ǂ���
		
	public:
	
		void SetActorIndexAll( int index );//�A�N�^�[�C���f�b�N�X�̈ꊇ�ݒ�
		void Rendering3DObject();//3D�I�u�W�F�N�g�̃����_�����O
		void Exec3DObject();//3D�I�u�W�F�N�g�̏���
		void MoveExec3DObject();//3D�I�u�W�F�N�g�̈ړ�����
		void SetStopFlagAll( bool flag );//��~�t���O�̈ꊇ�ݒ�
		void SetVisibleFlagAll( bool flag );//�\���t���O�̈ꊇ�ݒ�
		void InitAll();//�ꊇ������
		
	/*�X�N���v�g�֐�*/
	public:
	
		void LeftClickScript();//���N���b�N���������Ƃ��̃X�N���v�g
		void RightClickScript();//�E�N���b�N���������Ƃ��̃X�N���v�g
		void DragScript();//�h���b�O�����Ƃ��̃X�N���v�g
		void CameraRotScript();//�J������]���̃X�N���v�g
		void CameraResetScript();//�J�������Z�b�g���̃X�N���v�g
		void ArrowExpScript();//���������̃X�N���v�g
		void FilmExpScript();//�t�B�����������̃X�N���v�g
		void ScoreExpScript();//�X�R�A�������X�N���v�g
		void CatchExpScript();//�L���b�`�p�X�N���v�g
		void AddFuncScript();//�@�\�ǉ��X�N���v�g
		void TargetShowScript();//�^�[�Q�b�g�\���p�X�N���v�g
		void TargetClearScript();//�^�[�Q�b�g�����p�X�N���v�g
		void ShootTargetScript();//�ŏ��̃^�[�Q�b�g�̎B�e
		void TargetPlaceScript();//�^�[�Q�b�g�|�C���g�\���p�X�N���v�g
		void ReleaseBtnScript();//�����[�X�{�^���X�N���v�g
		void MenuScript();//���j���[�\���p�X�N���v�g
		void EndScript();//�I���X�N���v�g
		void OtherScript();//���̑��̏ꍇ�̃X�N���v�g
	
	/*�ǉ��@�\�֐�*/	
	private:
	
		typedef void (CSceneGameMain::*AddFunc)();
		
		void MoveFunc();//�ړ��@�\
		void CameraRotFunc();//�J������]�@�\
		void CameraResetFunc();//�J�������Z�b�g�@�\
		void ShootTargetFunc();//�ʐ^�B�e�@�\
		void CaptureFunc();//�ߊl�@�\
		void ReleaseFunc();//����@�\
		void MenuFunc();//���j���[�@�\
		
		
		
	/*�@�\�̃����_�����O�֐�*/
	private:
	
		typedef void (CSceneGameMain::*FuncRender)(bool flag);
		
		void RenderMove( bool flag );//�ړ����̕\��
		void RenderCameraRot( bool flag);//�J������]���̕\��
		void RenderCameraReset( bool flag );//�J�������Z�b�g���̕\��
		void RenderShootTarget( bool flag );//�ʐ^�B�e���̕\��
		void RenderCapture( bool flag);//�ߊl���̕\��
		void RenderRelease( bool flag);//������̕\��
		void RenderMenu( bool flag );//���j���[�@�\���̕\��
		
	private:
			
	public:
	
		CSceneGameMain( string strFileName );//�R���X�g���N�^
		virtual ~CSceneGameMain(void);//�f�X�g���N�^
		
		/*�I�u�W�F�N�g�f�[�^�̏�����*/
		void InitObjectData( Uint32 dt );
				
		/*������*/
		void Init( Uint32 dt );
		
		/*�ҋ@��*/
		void Idle( Uint32 dt );
		
		/*�I��*/
		void End( Uint32 dt );
		
		/*�����_�����O*/
		void Rendering();
		
	public:
	
		//�f�����
		void Demo();
		
		//���f�B�S�[���
		void ShowReadyGo();
		
		/*�Q�[����*/
		void Game();
		
		/*�Q�[���I��*/
		void GameEnd();
		
	public:		
	
		/*���̃V�[���̃Z�b�g*/
		void SetNextScene( eNextScene Scene )
		{
			m_eNextScene = Scene;
		}
		
		/*�`���[�g���A���V�[���̐ݒ�*/
		void SetTrlScene( eTutorialScene eScene )
		{
			m_eTrlScene = eScene;
		}
		
		
	public:
	
		/*���̃V�[���̎擾*/
		eNextScene GetNextScene() const
		{
			return m_eNextScene;
		}
		
	public:
	
		void AddFuncExec();//�@�\�̒ǉ�����
		void RenderFuncExec();//�����_�����O�֐��̏���
		
		void ShootPhoto();//�ʐ^�B�e
		void CreateActor();//�A�N�^�[�̐���
		
		void GradePhoto( );//�ʐ^�]��
		void HitCheckTrain(  );//�d�ԂƂ̓����蔻��
		void RenderingSetting();//�ݒ�̃����_�����O
		void SetScreenParam();//��ʃp�����[�^�̐ݒ�
		
		void ShowMarker();//�}�[�J�[�̕\��
		void DrawMoveCursor();//�ړ��J�[�\���̕\��
		void ShowCatchMark();//�L���b�`�}�[�N�̕\��
		
		void ShowMiniMap();//�~�j�}�b�v�̕\��
		
		void TargetArrowExec();//�^�[�Q�b�g�ւ̖��̏���
		
		void DrawScore();//�X�R�A�̕`��
		void DrawFilmNum();//�t�B���������̕`��
		
		void ShowDebugInfo();//�f�o�b�O���̕\��
		
		void MovePauseMenu();//�|�[�Y��ʂւ̈ڍs
		
		void HitCheckCamPointa();//�J�����|�C���^�Ƃ̓����蔻��
		
		void ReleaseEnemy();//�G�̉������
		
		void InitMain();//���C�����̏�����
		
		void SavePos();//�ۑ�
		
		//�N���A���ɒǉ�����I�u�W�F�N�g�̐ݒ�
		void SetClearObject();

		/*�`���[�g���A���p*/
		
		/*�`���[�g���A�����[�h���̏�����*/
		void InitTutorial();
		
		void MouseSprExec();//�}�E�X�X�v���C�g�̏���
		
		void RenderingTutorial();//�`���[�g���A���̃����_�����O
		
		void DrawMission();//�~�b�V�����̕`��
		
		void LoadMission();//�~�b�V�����̃��[�h
		
		void SetTargetEnemy();//�^�[�Q�b�g�Ώۂ̓G�̃Z�b�g
		
	
		
};
