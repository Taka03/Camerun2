//*============================================================================
//FontSprite3D.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "FontSprite3D.h"
#include "SceneManager.h"

//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	pName:�f�[�^��
//===========================================================================
CFontSprite3D::CFontSprite3D( const char *pName, Math::Vector3D vPos ) 
 :m_pFontSpr3D(NULL),
  CDraw3DObject( pName, vPos )
{
	m_Str = "����������";
	
	for( int i = 0;i < SCREEN_MAX;++i )
	{
		m_pActorFont[i] = NULL;
	}
	
	m_fSize.x = 1.0f;
	m_fSize.y = -11.0f;
}


//============================================================================
//�f�X�g���N�^
//============================================================================
CFontSprite3D::~CFontSprite3D(void)
{
	for( int i = 0;i < SCREEN_MAX;++i )
	{	
		SAFE_RELEASE( m_pActorFont[i] );
	}
	
	SAFE_RELEASE( m_pFontSpr3D );
	
	SAFE_RELEASE( m_pRender ); 
}

//============================================================================
//�t�@�C���ǂݍ���
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//	pFileMgr:�t�@�C���Ǘ��p�f�o�C�X
//===========================================================================
void CFontSprite3D::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	pFileMgr->SetCurrentPath("Font");
	
	m_pFontSpr3D = pRender->CreateFontSprite3DFromFile( m_strFileName.c_str(), "tga", 1024 );
	
	m_pRender = pRender;
	
	m_pRender->AddRef();
	
	//�A�N�^�[�̐���
	for( int i = 0;i < SCREEN_MAX;++i )
	{
		CreateActor( i, CCommonObject::GetSceneMgr( i )->GetSceneMgr() );
	}
}

//============================================================================
//�t�@�C���ǂݍ���
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//===========================================================================
void CFontSprite3D::CreateActor( int index, Scene::ISceneManager *pSceneMgr )
{
	m_pActorFont[index] = pSceneMgr->CreateActor( m_pFontSpr3D );
}

//============================================================================
//����
//============================================================================
void CFontSprite3D::Exec()
{
	if( m_pFontSpr3D != NULL )
	{
		// ������`��p�̃X�e�[�g
		m_pRender->SetDrawType( DRAW_TYPE_BLEND );
		m_pRender->SetAlphaTestEnable( true );
		m_pRender->SetDepthTestEnable( true );
		m_pRender->SetDepthWriteEnable( true );
		m_pRender->SetCullType( CULL_FRONT );
		
		/*�`��J�n*/
		m_pFontSpr3D->Begin();
		
		/*�`��L���[�ɒǉ�*/
		m_pFontSpr3D->DrawString( m_Str.c_str(), m_vPos, m_fSize, CColor(255, 255, 255) );
		
		/*�`��I��*/
		m_pFontSpr3D->End();
	}	
}

//============================================================================
//�����_�����O
//============================================================================
void CFontSprite3D::Rendering()
{
	if( GetVisibleFlag() )
	{	
		m_pActorFont[m_ActorIndex]->RenderingRequest();
	}
}

//============================================================================
//�A�N�^�[�C���f�b�N�X�̃Z�b�g
//============================================================================
void CFontSprite3D::SetActorIndex( int index )
{
	m_ActorIndex = index;
}




