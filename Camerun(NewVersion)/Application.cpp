//*============================================================================
//Application.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Application.h"
#include "Game.h"
#include "CommonObject.h"


//=============================================================================
//variable
//=============================================================================
//ICore *CApplication::m_pCore = NULL;
//IGraphicCard *CApplication::m_pGraphicCard = NULL;
//File::IFileManager *CApplication::m_pFileMgr = NULL;
//Renderer::IRender *CApplication::m_pRender = NULL;


//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	Width:��ʕ�
//	Height:��ʍ���
//=============================================================================
CApplication::CApplication( Uint32 Width, Uint32 Height ) 
 :m_ScreenWidth( Width ),
  m_ScreenHeight( Height ),
  m_pCore( NULL ),
  m_pGraphicCard( NULL ),
  m_pFileMgr( NULL ),
  m_pRender( NULL ),
  m_strAppName( "�L����RUN" )
{
	
}



//=============================================================================
//�f�X�g���N�^
//=============================================================================
CApplication::~CApplication(void)
{
	SAFE_RELEASE( m_pRender );
	SAFE_RELEASE( m_pFileMgr );
	SAFE_RELEASE( m_pGraphicCard );
	SAFE_RELEASE( m_pCore );
	
}

//=============================================================================
//�R�A�̐���
//=============================================================================
void CApplication::CreateCore()
{
	
	#if defined(DEBUG) | defined(_DEBUG)
	
		/*�V�X�e���̏�����*/
		System::Initialize();
		
	#else
	
		System::Initialize( true, false );
		
	#endif
	
	/*�R�A�̐���*/
	m_pCore = System::CreateCore();
	
}

//=============================================================================
//������
//=============================================================================
bool CApplication::Initialize( )
{
	//-----------------------------------------------------------------
	// �^�C�g���o�[�ɏ���\��
	//-----------------------------------------------------------------
	#if defined(DEBUG) | (_DEBUG) 
	
		m_pCore->EnableDrawTitleInformation( true );
		
	#endif

	//-----------------------------------------------------------------
	// �t�@�C���o�^
	//-----------------------------------------------------------------
	// �t�@�C���}�l�[�W���[�𐶐�
	m_pFileMgr = m_pCore->CreateFileManager();
	// �R�A�ɐݒ�
	m_pCore->SetFileManager( m_pFileMgr );
	
	// ���[�g�f�B���N�g����ݒ�
	#if defined(DEBUG) | (_DEBUG)
		
		m_pFileMgr->SetRootPath( 0, "../data" );
		
	#else
	
		m_pFileMgr->SetRootPath( 0, "./data" );
	
	#endif

	//-----------------------------------------------------------------
	// �O���t�B�b�N�J�[�h���擾
	//-----------------------------------------------------------------
	// �O���t�B�b�N�J�[�h�Ɋւ��Ă̏��������s���܂��B
	// IGraphicCard�C���^�[�t�F�C�X����͐ڑ����ꂽ
	// �O���t�B�b�N�J�[�h�̔\�͂��擾���鎖���\�ł��B
	// IGraphicCard�C���^�[�t�F�C�X��1��ICore�C���^�[�t�F�C�X�ɑ΂���1�������݂��܂���B
	m_pGraphicCard = m_pCore->CreateGraphicCard( GRAPHIC_CARD_DEFAULT_NO );
	
	if( m_pGraphicCard == NULL )
	{
		_ASSERT( !m_pGraphicCard );
		
		return false;
	}

	//-----------------------------------------------------------------
	// �E�B���h�E�쐬
	//-----------------------------------------------------------------
	// ICore�C���^�[�t�F�C�X���̏��ɏ]���ăA�v���P�[�V����
	// �E�B���h�E�𐶐����܂��B
	// IGraphicCard����̏������ɉ�ʉ𑜓x�Ȃǂ�ύX����ꍇ�́A
	// ICore::Start()���Ăяo���O�ɍs���Ă��������B

	m_pCore->Start( m_ScreenWidth, m_ScreenHeight, true );

	//-----------------------------------------------------------------
	// �����_���[���擾
	//-----------------------------------------------------------------
	// �쐬�����O���t�B�b�N�J�[�h�����ʕ`��p�̃����_���[���擾���܂��B
	// Renderer::IRender�C���^�[�t�F�C�X��1��IGraphicCard�C���^�[�t�F�C�X�ɑ΂���1�������݂��܂���B
	m_pRender = m_pGraphicCard->CreateRender();
	
	if( m_pRender == NULL ) 
	{
		_ASSERT( !m_pRender );
		return false;
	}
	
	//�e�N�X�`���t�H�[�}�b�g�̐ݒ�
	SetTextureFormat();
	
	return true;

}

//=============================================================================
//�N��
//=============================================================================
void CApplication::Run()
{
	//�R�A�̐���
	CreateCore();
	
	//����������
	CCommonObject::Initialize();
	
	CGame Game;
	
	/*������*/
	if( m_pCore->Initialize( m_strAppName.c_str() , FRAME_RATE_60 ) )
	{
		Initialize();
		
		while( GetCore()->Run() )
		{
			Game.Run();
		}
		
	}
	
	//�I������
	CCommonObject::Finalize();
	

}

//=============================================================================
//�e�N�X�`���t�H�[�}�b�g�̐ݒ�
//=============================================================================
void CApplication::SetTextureFormat()
{
	Renderer::CTextureConfig Config;
	
	// �e�N�X�`���t�H�[�}�b�g
	Config.SetColorKey( CColor(0,0,0, 0) );
	Config.SetFormat( FORMAT_TEXTURE_32BIT );
	Config.SetMipmapEnable( true );
	m_pRender->SetTextureConfig( Config );
}

//=============================================================================
//�e�N�X�`���t�B���^�̐ݒ�
//=============================================================================
void CApplication::SetTextureFilter()
{
	// �t�B���^�����O   
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_COLOR, TEXTURE_FILTER_3D_LOW );
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_LIGHT, TEXTURE_FILTER_3D_LOW );
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_ENVIRONMENT, TEXTURE_FILTER_3D_LOW );
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_SPECULAR, TEXTURE_FILTER_3D_LOW );
	m_pRender->SetTextureFilterType( TEXTURE_STAGE_NORMAL, TEXTURE_FILTER_3D_LOW );
}

//=============================================================================
//�Q�ƃJ�E���^����
//=============================================================================
void CApplication::AddRef()
{
	m_pRender->AddRef();
	m_pGraphicCard->AddRef();
	m_pFileMgr->AddRef();
	m_pCore->AddRef();
}
	



