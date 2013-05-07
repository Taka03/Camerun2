//*============================================================================
//ResourceManager.h
//*============================================================================
//[history]
//	08/10/01�@�쐬
//[author]
//	Taka
//[ref]
//	SeleneSample�R�[�h
//=============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Application.h"
#include "SceneManager.h"
#include "FileData.h"

#include <list>

//=============================================================================
//const
//=============================================================================
const int QUE_MAX = 2;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	���\�[�X�Ǘ��N���X
//============================================================================
class CResourceManager
{
	public:
	
		//���X�g�f�[�^
		struct ListData
		{
			Uint32 m_Priority;//����
			string m_strDataName;//�Ǘ�����
			CGameObject *m_pGameobj;//�I�u�W�F�N�g�̃|�C���^
		};
		
		//�I�u�W�F�N�g�^�C�v
		enum eObjType
		{
			OBJ_DRAW,//�`��I�u�W�F�N�g
			OBJ_SND,//�T�E���h�I�u�W�F�N�g
		};
	
	private:
		
		CGameObject *m_pGameObj;//�Q�[���p�I�u�W�F�N�g
		CDraw3DObject *m_p3DObj;//3D�I�u�W�F�N�g
		CDraw2DObject *m_p2DObj;//2D�I�u�W�F�N�g
		CSoundObject	*m_pSoundObj;//�T�E���h�p�I�u�W�F�N�g
		
		Thread::CThread m_Thread;
		Thread::CCriticalSection m_CS;
		Thread::CEvent m_Event;
		
		CFileData *m_pQueTop[QUE_MAX];
		Sint32 m_Page;
		
		eObjType m_eObjType;//�I�u�W�F�N�g�^�C�v
		
		//�`�惊�X�g
		static list< ListData > m_DrawList;
		
		//���ʉ����X�g
		static list< ListData > m_SoundList;
		
	private:
	
		/*�������\�b�h*/
		typedef void (CResourceManager::*CreateFunc)( CFileData *pFile );
	
	
		//�N��
		virtual void Run();
		
		//���[�h�p�X���b�h
		static void LoadProc( void *pData );
	
	public:	
	
		//�R���X�g���N�^
		CResourceManager( );
		
		//�f�X�g���N�^
		virtual ~CResourceManager();
		
		/*���\�[�X�̒ǉ�*/
		virtual void Push( CFileData *pFile );
		
		//�I�u�W�F�N�g�̎擾
		CGameObject *FindObject( const char *pName );
		
		//���I�u�W�F�N�g�̎擾
		CGameObject *FindSoundObj( const char *pName );
		
		//�I�u�W�F�N�g�̍폜
		void RemoveObject( const char *pDataName );
		
		//�I�u�W�F�N�g�̍폜
		void RemoveObject( CGameObject *pRemObj );
		
		//�T�E���h�I�u�W�F�N�g�̏���
		void RemoveSound( const char *pDataName );
		
		/*���[�h��*/
		virtual Bool IsLoading();
		
		
	private:
	
		
		//���X�g�֒ǉ�
		void AppendList( string strDataName, CGameObject *pGameObj );
		
		/*�^�C�v�̔���*/
		void CheckType( CFileData *pFile );
		
	private:
	
		//�X�v���C�g�̐���
		void CreateSprite( CFileData *pFile );
		
		//�ʐ^�X�v���C�g�̐���
		void CreatePhoto( CFileData *pFile );
		
		//�~�j�}�b�v�̐���
		void CreateMiniMap( CFileData *pFile );
		
		//�J�����{�^���̐���
		void CreateCamButton( CFileData *pFile );
		
		//���j���[�̐���
		void CreateMenu( CFileData *pFile );
		
		//�E�B���h�E�̐���
		void CreateExpWindow( CFileData *pFile );
		
		//�t�H���g�X�v���C�g�̐���
		void CreateFontSprite( CFileData *pFile );
		
		//���ʉ��̐���
		void CreateSound( CFileData *pFile );
		
		//BGM�̐���
		void CreateBGM( CFileData *pFile );
		
		//�t�B�[���h�̐���
		void CreateField( CFileData *pFile );
		
		//3D�t�H���g�X�v���C�g�̐���
		void CreateFontSprite3D( CFileData *pFile );
		
		//3D�X�v���C�g�̐���
		void CreateSprite3D( CFileData *pFile );
		
		//�L�����N�^�[�̐���
		void CreateCharacter( CFileData *pFile );
		
		//�v���C���[�̐���
		void CreatePlayer( CFileData *pFile );
		
		//�d�Ԃ̐���
		void CreateTrain( CFileData *pFile );
		
		//�A���E�X�̐���
		void CreateAmeus( CFileData *pFile );
		
		//�}���^�̐���
		void CreateManta( CFileData *pFile );
		
		//�g���̐���
		void CreateBird( CFileData *pFile );
		
		//�l�Y�~�̐���
		void CreateMouse( CFileData *pFile );
		
		//�E�T�M�̐���
		void CreateRabbit( CFileData *pFile );
		
		//�g�J�Q�̐���
		void CreateLizard( CFileData *pFile );
		
		//�Ԃ̐���
		void CreateCar( CFileData *pFile );
		
		//�����̐���
		void CreateFount( CFileData *pFile );
		
		//�󒆒뉀�̐���
		void CreateSkyObj( CFileData *pFile );
	
	public:		
		
		/*�Q�[���p�I�u�W�F�N�g�̎擾*/
		CGameObject *GetGameObject() const
		{
			return m_pGameObj;
		}
		
		/*2D�p�I�u�W�F�N�g�̎擾*/
		CDraw2DObject *Get2DObject() const
		{
			return m_p2DObj;
		}
		
		/*3D�p�I�u�W�F�N�g�̎擾*/
		CDraw3DObject *Get3DObject() const
		{
			return m_p3DObj;
		}

		/*�T�E���h�p�I�u�W�F�N�g�̎擾*/
		CSoundObject *GetSoundObject() const
		{
			return m_pSoundObj;
		}
		
		//�`�惊�X�g�̎擾
		list< ListData > GetDrawList()
		{
			return m_DrawList;
		}
		
};

