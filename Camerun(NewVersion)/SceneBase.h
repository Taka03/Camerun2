//*============================================================================
//SceneBase.h
//*============================================================================
//[history]
//	08/03/11�@�쐬
//	08/10/08  ���O��SceneBase.h�ɕύX
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "ResourceManager.h"
#include "ScreenController.h"
#include "FileLoader.h"
#include "SceneManager.h"
#include "MissionManager.h"
#include "Draw3DObject.h"
#include "camera.h"
#include "BGM.h"
#include "SoundManager.h"
#include "mouse.h"

#include <list>


//=============================================================================
//enum
//=============================================================================

//�V�[�����
enum eSceneState
{
	STATE_LOADING,//���[�h��
	STATE_CONTINUE,//�J�ڒ�
	STATE_STANDBY,//�X�^���o�C���
	STATE_FADEIN,//�t�F�[�h�C��
	STATE_FADEOUT,//�t�F�[�h�A�E�g
	STATE_FINISH,//�J�ڏI��
};

//=============================================================================
//const
//=============================================================================
const int FILM_MAX = 5;//�t�B�����̍ő喇��

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�Q�[���V�[���p�N���X
//=============================================================================
class CSceneBase
{
	public:
	
		struct StringList
		{
			string m_DataName;//�f�[�^��
		};
		
		/*�w�A�C�R���̏��*/
		enum eFingState
		{
			FING_NONE,//��\�����
			FING_UP,//�����
			FING_DOWN,//������
			FING_LEFT,//������
			FING_RIGHT,//�E����
		};
		
	private:
	
	private:
	
		static CSprite *m_pCursorSpr;//�J�[�\��

		static Uint32 m_FilmCount;//�t�B�����J�E���g
		static int m_TotalScore;//���v�X�R�A
		static int m_ClearCount;//�N���A�J�E���g
		static int m_ClearPoint;//�N���A�|�C���g
		
		static int m_HiScore;//�n�C�X�R�A
		
		static float m_fTargetDis;//�^�[�Q�b�g�Ƃ̋���
		static Math::Vector3D m_vTargetPos;//�^�[�Q�b�g�Ƃ̈ʒu
		
		static CBGM *m_pBGM;//BGM
		
		static bool m_IsFirstGame;//�����v���C���ǂ���
		
		/*�`���[�g���A���p*/
		static bool m_IsTutorial;//�`���[�g���A�����[�h���ǂ���
		static CExpWindow *m_pWindowSpr;//�E�B���h�E�X�v���C�g
		static CSprite *m_pFingIcoSpr;//�w�A�C�R���X�v���C�g
		
		static eFingState m_eFingState;//�w�A�C�R���̏��
		
		static CEnemy *m_pTarget;//�ʐ^�̃^�[�Q�b�g
		
		static bool m_IsTargetExist;//�^�[�Q�b�g�����݂��邩
		
		static bool m_IsSavePhoto;//�ʐ^���Z�[�u������
		
		
	protected:
	
		list<StringList> m_DataNameList;//�f�[�^�����X�g
		list<CDraw2DObject *> m_Draw2DList;//2D�`�惊�X�g
		list< CResourceManager::ListData > m_DataList;//�f�[�^���X�g
				
		static CCamButton *m_pCamBtnSpr;//�J�����{�^��
		

		
	public:
	
		CSceneBase();//�R���X�g���N�^
		CSceneBase( string strFileName );//�R���X�g���N�^
		virtual ~CSceneBase(void);//�f�X�g���N�^
		
		void Init();//������
		virtual eSceneState UpDate() = 0;//�X�V
		virtual void Rendering() = 0;//�����_�����O
		
		void LoadResource( string strFileName );//���\�[�X�̓ǂݍ���
		void Push2DObject();//2D�I�u�W�F�N�g�̃��X�g�ǉ�
		void Rendering2DList();//2D���X�g�̃����_�����O
		void Exec2DList();//2D���X�g�̏���
		
		void FingIcoExec();//�w�A�C�R���̏���
		void RenderMouseIco();//�}�E�X�A�C�R���̃����_�����O
		
	/*Set�n*/
	public:
	
		
		
		/*�}�E�X�J�[�\���̃Z�b�g*/
		void SetMouseCursor( CSprite *pSpr )
		{
			m_pCursorSpr = pSpr;
		}
		
		/*�t�B�����J�E���^�̃Z�b�g*/
		void SetFilmCount( int count )
		{
			m_FilmCount = count;
		}
		
		/*���v�_�̃Z�b�g*/
		void SetTotalScore( int Score )
		{
			m_TotalScore = Score;
		}
		
		//�n�C�X�R�A�̐ݒ�
		void SetHiScore( int Score )
		{
			m_HiScore = Score;
		}
		
		/*�t�B�����J�E���^�̑���*/
		void AddFilmCount()
		{
			m_FilmCount++;
		}
		
		/*�N���A�J�E���g�̐ݒ�*/
		void SetClearCount( int count )
		{
			m_ClearCount = count;
		}
		
		//�N���A�|�C���g�̐ݒ�
		void SetClearPoint( int point )
		{
			m_ClearPoint = point;
		}
		
		/*�N���A�J�E���g�̑���*/
		void AddClearCount()
		{
			++m_ClearCount;
		}
		
		/*�`���[�g���A���t���O�̐ݒ�*/
		void SetTutorialFlag( bool flag )
		{
			m_IsTutorial = flag;
		}
		
		/*�����v���C�t���O�̐ݒ�*/
		void SetFirstGameFlag( bool flag )
		{
			m_IsFirstGame = flag;
		}
		
		/*�^�[�Q�b�g�Ƃ̋����̐ݒ�*/
		void SetTargetDistance( float fDis )
		{
			m_fTargetDis = fDis;
		}
		
		/*�^�[�Q�b�g�Ƃ̈ʒu�̐ݒ�*/
		void SetTargetPos( Math::Vector3D vPos )
		{
			m_vTargetPos = vPos;
		}
		
		/*�E�B���h�E�X�v���C�g�̐ݒ�*/
		void SetWindowSpr( CExpWindow *pWindow )
		{
			m_pWindowSpr = pWindow;
		}
		
		/*�w�A�C�R���̐ݒ�*/
		void SetFingIcoSpr( CSprite *pFing )
		{
			m_pFingIcoSpr = pFing;
		}
		
		/*�w�A�C�R����Ԃ̐ݒ�*/
		void SetFingState( eFingState eState )
		{
			m_eFingState = eState;
		}
		
		//BGM�̐ݒ�
		void SetBGM( CBGM *pBGM )
		{
			m_pBGM = pBGM;
		}
		
		/*�^�[�Q�b�g�̐ݒ�*/
		void SetTarget( CEnemy *pTarget )
		{
			m_pTarget = pTarget;
		}
		
		//�^�[�Q�b�g���݃t���O�̐ݒ�
		void SetTargetExistFlag( bool flag )
		{
			m_IsTargetExist = flag;
		}
		
		//�ʐ^��ۑ�����t���O�̐ݒ�
		void SetPhotoSaveFlag( bool flag )
		{
			m_IsSavePhoto = flag;
		}
		
	/*Get�n*/
	public:
		
		/*�}�E�X�J�[�\���̎擾*/
		CSprite *GetMouseCursor() const
		{
			return m_pCursorSpr;
		}
		
		/*�t�B�����J�E���g�̎擾*/
		Uint32 GetFilmCount() const
		{
			return m_FilmCount;
		}
		
		/*���v���_�̎擾*/
		int GetTotalScore() const
		{
			return m_TotalScore;
		}
		
		//�n�C�X�R�A�̎擾
		int GetHiScore() const
		{
			return m_HiScore;
		}
		
		/*�N���A�J�E���g�̎擾*/
		int GetClearCount() const
		{
			return m_ClearCount;
		}
		
		//�N���A�|�C���g�̎擾
		int GetClearPoint() const
		{	
			return m_ClearPoint;
		}
		
		
		/*�`���[�g���A���t���O�̎擾*/
		static bool GetTutorialFlag()
		{
			return m_IsTutorial;
		}
		
		/*�����v���C�t���O�̐ݒ�*/
		bool GetFirstGameFlag() const
		{
			return m_IsFirstGame;
		}
		
		/*�^�[�Q�b�g�Ƃ̋����̎擾*/
		float GetTargetDistance() const
		{
			return m_fTargetDis;
		}
		
		/*�^�[�Q�b�g�Ƃ̈ʒu�̎擾*/
		Math::Vector3D GetTargetPos() const
		{
			return m_vTargetPos;
		}
		
		/*�E�B���h�E�X�v���C�g�̎擾*/
		CExpWindow *GetWindowSpr() const
		{
			return m_pWindowSpr;
		}
		
		/*�w�A�C�R���̎擾*/
		CSprite *GetFingerSpr() const
		{
			return m_pFingIcoSpr;
		}
		
		/*�w�A�C�R����Ԃ̎擾*/
		eFingState GetFingState() const
		{
			return m_eFingState;
		}
		
		//�^�[�Q�b�g�ƂȂ�I�u�W�F�N�g�̎擾
		CEnemy *GetTarget() const
		{
			return m_pTarget;
		}
		
		//�^�[�Q�b�g���݃t���O�̎擾
		bool GetTargetExistFlag() const
		{
			return m_IsTargetExist;
		}
		
		//�ʐ^�ۑ�����t���O�̎擾
		bool GetPhotoSaveFlag() const
		{
			return m_IsSavePhoto;
		}
		
		/*BGM�̎擾*/
		CBGM *GetBGM()
		{
			return m_pBGM;
		}
		
};
