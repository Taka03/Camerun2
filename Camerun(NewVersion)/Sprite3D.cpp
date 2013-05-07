//*============================================================================
//Sprite3D.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Sprite3D.h"
#include "SceneManager.h"

//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	pName:�f�[�^��
//	vPos:�\���ʒu
//===========================================================================
CSprite3D::CSprite3D( const char *pName, Math::Vector3D vPos ) 
:CDraw3DObject( pName, vPos )
{
	for( int i = 0;i < SCREEN_MAX;++i )
	{
		m_pActorSprite[i] = NULL;
	}
	
	m_vScale.x = 2.0f;
	
	m_DivNum.x = 1;
	m_DivNum.y = 1;
	
	m_Anim.x = 0;
	m_Anim.y = 0;
	
	m_matWorld.Identity();
}

//============================================================================
//�f�X�g���N�^
//============================================================================
CSprite3D::~CSprite3D(void)
{
	for( int i = 0;i < SCREEN_MAX;++i )
	{	
		SAFE_RELEASE( m_pActorSprite[i] );
	}
	
	SAFE_RELEASE( m_pTex );
	SAFE_RELEASE( m_pSpr );
}

//============================================================================
//�t�@�C���ǂݍ���
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//	pFileMgr:�t�@�C���Ǘ��p�f�o�C�X
//===========================================================================
void CSprite3D::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	pFileMgr->SetCurrentPath("Texture");
	
	printf("LOAD TEXTURE[%s]", m_strFileName.c_str() );
	
	m_pTex = pRender->CreateTextureFromFile( m_strFileName.c_str() );
	
	printf( "                 : -> %s\n", m_pTex->IsInvalid() ? "Failed" : "Succeeded" );
	
	
	m_Width = m_pTex->GetOriginalSize().x / m_DivNum.x;
	m_Height = m_pTex->GetOriginalSize().y / m_DivNum.y;
	
	if( m_pTex != NULL )
	{	
		m_pSpr = pRender->CreateSprite3D( 1000, m_pTex ); 
	}
	
	//�A�N�^�[�̐���
	for( int i = 0;i < SCREEN_MAX;++i )
	{
		CreateActor( i, CCommonObject::GetSceneMgr( i )->GetSceneMgr() );
	}
}

//============================================================================
//�A�N�^�[����
//============================================================================
//[input]
//	index:�C���f�b�N�X
//	pSceneMgr:�V�[���}�l�[�W��
//===========================================================================
void CSprite3D::CreateActor( int index, Scene::ISceneManager *pSceneMgr )
{
	m_pActorSprite[index] = pSceneMgr->CreateActor( m_pSpr );
}

//=============================================================================
//�A�N�^�[�C���f�b�N�X�̃Z�b�g
//=============================================================================
//[input]
//	index:�ݒ肷��C���f�b�N�X
//=============================================================================
void CSprite3D::SetActorIndex( int index )
{
	m_ActorIndex = index;
}

//============================================================================
//����
//============================================================================
void CSprite3D::Exec()
{
	if( m_pSpr != NULL )
	{
		m_pSpr->Begin();
		
		Math::Rect2DI SrcRect( m_Anim.x*m_Width, m_Anim.y*m_Height, m_Width, m_Height );
		
		m_matWorld.w = m_vPos;
		
		/*�`��*/
		m_pSpr->Draw( m_matWorld, Math::Point2DF( m_vScale.x, m_vScale.x ), SrcRect, CColor( 255, 255, 255 ) );
		
		m_pSpr->End();
	}
	
	///*������*/
	//m_pActorSprite[i]->TransformReset();
	//
	//m_pActorSprite[i]->Translation( m_vPos );
	//
	///*�X�V*/
	//m_pActorSprite[i]->TransformUpdate();
}

//============================================================================
//�Q�ƃJ�E���^�̑���
//============================================================================
void CSprite3D::AddRef()
{
	m_pTex->AddRef();
	m_pSpr->AddRef();
	
	for( int actornum = 0;actornum < SCREEN_MAX;++actornum )
	{
		m_pActorSprite[actornum]->AddRef();
	}
}


//============================================================================
//�����_�����O
//============================================================================
void CSprite3D::Rendering()
{
	if( GetVisibleFlag() )
	{	
		m_pActorSprite[m_ActorIndex]->RenderingRequest();
	}
}
