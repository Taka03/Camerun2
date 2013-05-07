//*============================================================================
//CommonObject.cpp
//*============================================================================


//=============================================================================
//include
//=============================================================================
#include "CommonObject.h"
#include "GameSceneManager.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "Application.h"
#include "camera.h"
#include "SceneManager.h"
#include "Mouse.h"

//=============================================================================
//variable
//=============================================================================
CApplication *CCommonObject::m_pApp = NULL;
CSoundManager *CCommonObject::m_pSndMgr = NULL;
CResourceManager *CCommonObject::m_pResMgr = NULL;
CCamera *CCommonObject::m_pCamera[SCREEN_MAX];
CSceneManager *CCommonObject::m_pSceneMgr[SCREEN_MAX];
CGameSceneManager *CCommonObject::m_pGameSceneMgr = NULL;
CMouse *CCommonObject::m_pMouse = NULL;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CCommonObject::CCommonObject(void) 
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CCommonObject::~CCommonObject(void)
{

}

//=============================================================================
//����������
//=============================================================================
void CCommonObject::Initialize()
{
	memset( m_pSceneMgr, NULL, SCREEN_MAX );
	memset( m_pCamera, NULL, SCREEN_MAX );
}


//=============================================================================
//�I������
//=============================================================================
void CCommonObject::Finalize()
{
	SAFE_DELETE( m_pGameSceneMgr );
	
	
	SAFE_DELETE( m_pSndMgr );
	
	SAFE_DELETE( m_pResMgr );
	
	for( int i = 0;i < SCREEN_MAX;++i )
	{	
		SAFE_DELETE( m_pCamera[i] );
		SAFE_DELETE( m_pSceneMgr[i] );
	}
	
	
	SAFE_DELETE( m_pMouse );
	
	SAFE_DELETE( m_pApp );
}


//=============================================================================
//�A�v���P�[�V�����N���X�̎擾
//=============================================================================
//[return]
//	�A�v���P�[�V�����N���X
//=============================================================================
CApplication *CCommonObject::GetAppli()
{
	if( m_pApp == NULL )
	{
		m_pApp = new CApplication( SCREEN_WIDTH, SCREEN_HEIGHT );
	}
	
	return m_pApp;
}

//=============================================================================
//�}�E�X�N���X�̎擾
//=============================================================================
//[return]
//	�}�E�X�N���X
//=============================================================================
CMouse *CCommonObject::GetMouse()
{
	if( m_pMouse == NULL )
	{
		m_pMouse = new CMouse( GetAppli()->GetCore() );
		
	}
	
	return m_pMouse;
}



//=============================================================================
//���\�[�X�}�l�[�W���[�̎擾
//=============================================================================
//[return]
//	���\�[�X�}�l�[�W���[
//=============================================================================
CResourceManager *CCommonObject::GetResMgr()
{
	if( m_pResMgr == NULL )
	{
		m_pResMgr = new CResourceManager( );
	}
	
	return m_pResMgr;
}

//=============================================================================
//�V�[���}�l�[�W���[�̎擾
//=============================================================================
//[input]
//	index:�擾����V�[���ԍ�
//[return]
//	�V�[���}�l�[�W���[
//=============================================================================
CSceneManager *CCommonObject::GetSceneMgr( int index )
{
	static bool IsFirst = true;//����Ăяo���t���O
	
	if( IsFirst )
	{
		//�e�N�X�`���ɕ`�悷�邩
		bool IsRenderTex[] =
		{
			false,
			true,	
		};
	
		for( int i = 0;i < SCREEN_MAX;++i )
		{	
			m_pSceneMgr[i] = new CSceneManager( GetAppli()->GetRenderer() );
			
			//�f�o�C�X�̐���
			m_pSceneMgr[i]->CreateDevice( IsRenderTex[i] );
			
			m_pSceneMgr[i]->SetInitParameter();
		
		}
		
		IsFirst = false;
				
	}
	
	return m_pSceneMgr[index];
}

//=============================================================================
//�J�����̎擾
//=============================================================================
//[input]
//	index:�擾����J�����ԍ�
//[return]
//	�J����
//=============================================================================
CCamera *CCommonObject::GetCamera( int index )
{
	static bool IsFirst = true;//����Ăяo���t���O
	
	if( IsFirst )
	{
		for( int i = 0;i < SCREEN_MAX;++i )
		{	
			m_pCamera[i] = new CCamera();
			
			//�f�o�C�X�̐���
			m_pCamera[i]->SetCamera( GetSceneMgr( i )->GetSceneMgr() );
			
			//�v���W�F�N�V�����̐ݒ�
			m_pCamera[i]->SetProjection( 1.0f, 300.0f, 45, SCREEN_WIDTH, SCREEN_HEIGHT ); 
			
		}
		
		IsFirst = false;
				
	}
	
	return m_pCamera[index];
	
}

//=============================================================================
//�T�E���h�}�l�[�W���[�̎擾
//=============================================================================
//[return]
//	�T�E���h�}�l�[�W���[
//=============================================================================
CSoundManager *CCommonObject::GetSoundMgr() 
{
	if( m_pSndMgr == NULL )
	{
		m_pSndMgr = new CSoundManager();
	}
	
	return m_pSndMgr;
}

//=============================================================================
//�Q�[���V�[���}�l�[�W���[�̎擾
//=============================================================================
//[return]
//	�Q�[���V�[���}�l�[�W���[
//=============================================================================
CGameSceneManager *CCommonObject::GetGameSceneMgr()
{
	if( m_pGameSceneMgr == NULL )
	{
		m_pGameSceneMgr = new CGameSceneManager( );
	}

	return m_pGameSceneMgr;
}


