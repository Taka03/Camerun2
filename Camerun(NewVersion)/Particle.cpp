//*============================================================================
//Particle.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Particle.h"
#include "SceneManager.h"


//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	pName:�f�[�^��
//	vPos:�\���ʒu
//===========================================================================
CParticle::CParticle( const char *pName, Math::Vector3D vPos ) 
:m_pTex(NULL), 
 m_pParticle(NULL),
 CDraw3DObject( pName, vPos ),
 m_Alpha( 255, 255, 255 )
{
	memset( m_pActorParticle, NULL, SCREEN_MAX );
	
	
}

//============================================================================
//�f�X�g���N�^
//============================================================================
CParticle::~CParticle(void)
{
	for( int i = 0;i < SCREEN_MAX;++i )
	{	
		SAFE_RELEASE( m_pActorParticle[i] );
	}
	
	SAFE_RELEASE( m_pParticle );
	SAFE_RELEASE( m_pTex );
	
	
}

//============================================================================
//�t�@�C���ǂݍ���
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//	pFileMgr:�t�@�C���Ǘ��p�f�o�C�X
//===========================================================================
void CParticle::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	pFileMgr->SetCurrentPath("Texture");
	
	m_pTex = pRender->CreateTextureFromFile( m_strFileName.c_str() );
	
	m_Width = m_pTex->GetOriginalSize().x;
	m_Height = m_pTex->GetOriginalSize().y;
	
	/*�p�[�e�B�N���̐���*/
	m_pParticle = pRender->CreateParticle( 128, m_pTex, PARTICLE_TYPE_VOLUME, true ); 
	
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
void CParticle::CreateActor( int index, Scene::ISceneManager *pSceneMgr )
{
	m_pActorParticle[index] = pSceneMgr->CreateActor( m_pParticle );
}

//============================================================================
//����
//============================================================================
void CParticle::Exec()
{
	static int count = 0;
	
	if( m_pParticle != NULL )
	{
		if( m_IsVisible )
		{
			
			m_pParticle->Begin();
			
			//m_Alpha.x = Interpolation::Flat( m_Alpha.y, m_Alpha.z, BOMB_ALIVE_TIME, count );
			//m_Rot.x = DEG_TO_ANGLE(0);
			//m_Alpha.x = 255;
			//m_vScale.x = Interpolation::Flat( m_vScale.y, m_vScale.z, BOMB_ALIVE_TIME, count );
			
			//m_vPos.z = Interpolation::Flat( m_vPos.z, m_vPos.z + 1, BOMB_ALIVE_TIME, count );
		
			Math::Rect2DI SrcRect( 0, 0, m_Width, m_Height );
			
			m_pParticle->DrawRotate( m_vPos, Math::Point2DF( m_vScale.x, m_vScale.y ), SrcRect, CColor( 255, 255, 255, m_Alpha.x ), toI( m_Rot.x ) );
			
			m_pParticle->End();
		}
	}
}

//============================================================================
//�����_�����O
//============================================================================
void CParticle::Rendering( int index )
{
	m_pRender->SetDrawType( DRAW_TYPE_BLEND );	// �`�惂�[�h�i���Z
	m_pRender->SetAlphaTestEnable( true );		// �A���t�@�e�X�gON
	m_pRender->SetDepthTestEnable( true );		// �[�x�e�X�gON
	m_pRender->SetDepthWriteEnable( false );		// �[�x��������OFF
	
	m_pActorParticle[index]->RenderingRequest();
	
	m_pRender->SetDrawType( DRAW_TYPE_NORMAL );	
	
}
