//*============================================================================
//CommonObject.h
//*============================================================================
//[history]
//	08/12/27 �쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Application.h"

//=============================================================================
//variable
//=============================================================================
class CGameSceneManager;
class CSoundManager;
class CResourceManager;
class CApplication;
class CSceneManager;
class CCamera;
class CMouse;


//=============================================================================
//class
//=============================================================================
//[Desc]
//	���ʃI�u�W�F�N�g�p�N���X
//=============================================================================
class CCommonObject
{
	public:
	
		//�R���X�g���N�^
		CCommonObject(void);
		
		//�f�X�g���N�^
		~CCommonObject(void);
		
	private:
	
		static CApplication *m_pApp;//�A�v���P�[�V�����N���X
		static CResourceManager *m_pResMgr;//���\�[�X�Ǘ��N���X
		static CSoundManager *m_pSndMgr;//�T�E���h�Ǘ��N���X
		static CGameSceneManager *m_pGameSceneMgr;//�Q�[���V�[���Ǘ��N���X
		static CSceneManager *m_pSceneMgr[SCREEN_MAX];//�V�[��(3D)�Ǘ�
		static CCamera *m_pCamera[SCREEN_MAX];//�V�[���̃J����
		static CMouse *m_pMouse;//�}�E�X�Ǘ��N���X
		
	public:
	
		static void Initialize();//����������
		static void Finalize();//�I������
	
	public:
	
		/*�T�E���h�Ǘ��N���X�̎擾*/
		static CSoundManager *GetSoundMgr(); 
		
		//���\�[�X�Ǘ��N���X�̎擾
		static CResourceManager *GetResMgr();
		
		//�V�[��(3D)�Ǘ��N���X�̎擾
		static CSceneManager *GetSceneMgr( int index );
		
		//�J�����̎擾
		static CCamera *GetCamera( int index );
		
		//�A�v���P�[�V�����N���X�̎擾
		static CApplication *GetAppli();
		
		//�}�E�X�N���X�̎擾
		static CMouse *GetMouse();
		
		//�Q�[���V�[���}�l�[�W���̎擾
		static CGameSceneManager *GetGameSceneMgr();
};
