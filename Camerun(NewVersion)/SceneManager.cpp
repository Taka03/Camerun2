//*============================================================================
//SceneManager.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneManager.h"
#include "prehead.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//=============================================================================
CSceneManager::CSceneManager( Renderer::IRender *pRender ) 
 :m_pSceneMgr(NULL), 
  m_pRenderTex(NULL),
  m_pRender( pRender ),
  m_IsRenderTex( false )

{
	
	m_pRender->AddRef();
	
	m_RenderTargetWidth = SCREEN_WIDTH;
	m_RenderTargetHeight = SCREEN_HEIGHT;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneManager::~CSceneManager(void)
{
	SAFE_RELEASE( m_pRenderTex );
	SAFE_RELEASE( m_pSceneMgr );
	SAFE_RELEASE( m_pRender );
}

//=============================================================================
//�f�o�C�X�̐ݒ�
//=============================================================================
//[input]
//	IsRenderTex:�e�N�X�`���Ƀ����_�����O���邩
//=============================================================================
void CSceneManager::CreateDevice( bool IsRenderTex )
{
	m_pSceneMgr = m_pRender->CreateSceneManager( 512, false );
	
	if( IsRenderTex )
	{
		m_IsRenderTex = IsRenderTex;
		
		m_pRenderTex = m_pRender->CreateTextureRenderTarget( m_RenderTargetWidth, m_RenderTargetHeight, 
														   FORMAT_TARGET_32BIT );
	}
		
}

//=============================================================================
//�����p�����[�^�[�̐ݒ�
//=============================================================================
void CSceneManager::SetInitParameter( )
{
	if( m_pSceneMgr != NULL )
	{
		if( m_IsRenderTex )
		{

			m_pSceneMgr->InitParameter_RenderTargetData(
				m_pRenderTex,												// �����_�����O�^�[�Q�b�g�̃e�N�X�`���iNULL�Ńo�b�N�o�b�t�@�֒��ځj
				Math::Point2DI( m_RenderTargetWidth, m_RenderTargetHeight ),		// �`���̃����_�����O�^�[�Q�b�g�T�C�Y�i�����w�肳��Ă��鎞�́��̃e�N�X�`���T�C�Y�Ɏ����ϊ��j
				false );											// �`���̃e�N�X�`���T�C�Y���Q�̗ݏ�ɂ��邩�ǂ���
		}
		
		else
		{
			m_pSceneMgr->InitParameter_RenderTargetData(
				NULL,												// �����_�����O�^�[�Q�b�g�̃e�N�X�`���iNULL�Ńo�b�N�o�b�t�@�֒��ځj
				Math::Point2DI( m_RenderTargetWidth, m_RenderTargetHeight ),		// �`���̃����_�����O�^�[�Q�b�g�T�C�Y�i�����w�肳��Ă��鎞�́��̃e�N�X�`���T�C�Y�Ɏ����ϊ��j
				false );											// �`���̃e�N�X�`���T�C�Y���Q�̗ݏ�ɂ��邩�ǂ���
		
		}

		// �V�[���ɑ΂���G�t�F�N�g�̏�����
		//   �V�[���ɑ΂��čs���e�탌���_�����O�G�t�F�N�g�͂����ōs���܂��B
		m_pSceneMgr->InitParameter_Shading( SHADING_TYPE_NORMAL );							// �V�F�[�f�B���O
		//m_pSceneMgr->InitParameter_Fog( FOG_TYPE_DISABLE, FOG_EFFECT_LINEAR );				// �t�H�O
		//m_pSceneMgr->InitParameter_HighDynamicRange( HDR_TYPE_ENABLE, HDR_EFFECT_CROSS );		// HDR�����_�����O
	//		m_pSceneMgr->InitParameter_MotionBlur( MOTION_BLUR_TYPE_DISABLE );					// ���[�V�����u���[
	//		m_pSceneMgr->InitParameter_DepthOfField( DOF_TYPE_DISABLE );							// ��ʊE�[�x
		m_pSceneMgr->InitParameter_Shadow( SHADOW_TYPE_SHADOWMAP, SHADOW_QUARITY_MIDDLE );	// �e����
	//		m_pSceneMgr->InitParameter_AntiAliasType( AA_TYPE_DISABLE, 0.0f );					// �A���`�G�C���A�X

		// �V�[���̏������n�p�����[�^�[�̍X�V
		m_pSceneMgr->InitParameter_Update();
		
		
	}
}

//=============================================================================
//�X�J�C�h�[���̐���
//=============================================================================
//[input]
//	pTex:�e�N�X�`���n���h��
//=============================================================================
void CSceneManager::CreateSkyDoom( Renderer::ITexture *pTex )
{

	if( m_pSceneMgr != NULL && pTex != NULL )
	{
		// �X�J�C�h�[������
		//  ���\�����邽�߂̃X�J�C�h�[���𐶐����܂��B
		m_pSceneMgr->SceneSkydoom_Create(
			10.0f,						// ���a
			CColor(121,154,255),		// �n�\�F
			CColor(121,154,255),		// �V���F
			pTex );					// ��e�N�X�`��
	}
		
}

//=============================================================================
//�p�����[�^�[�̐ݒ�
//=============================================================================
void CSceneManager::SetParameter()
{
	if( m_pSceneMgr != NULL )
	{
		m_pSceneMgr->Reset();

		// �V�[���̔w�i�̐F
		m_pSceneMgr->SetParameter_BGColor( Math::Vector4D(0.0f,0.0f,0.0f,1.0f) );
		
		/*�`���̈�*/
		m_pSceneMgr->SetParameter_RenderRect( Math::Rect2DF( 0, 0,
															 toF( m_RenderTargetWidth ), toF( m_RenderTargetHeight ) ) );
		
		//m_pSceneMgr->SetParameter_Fog(
		//	Math::Vector3D( 0.8f, 0.8f, 0.8f ),		// �t�H�O�F
		//	50.0f,									// �t�H�O�J�n�ʒu
		//	300.0f );								// �t�H�O�I���ʒu
		//	
		
	}
}



//=============================================================================
//�`��̈�T�C�Y�̐ݒ�
//=============================================================================
//[input]
//	width:�ݒ肷�镝
//	height:�ݒ肷�鍂��
//=============================================================================
void CSceneManager::SetRenderSize( Sint32 width, Sint32 height )
{
	m_RenderTargetWidth = width;
	m_RenderTargetHeight = height;
}

