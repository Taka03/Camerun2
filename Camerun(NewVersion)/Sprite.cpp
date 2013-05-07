//*============================================================================
//Sprite.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Sprite.h"


//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	pName:�f�[�^��
//	vPos:�\���ʒu
//	DivNum:������
//===========================================================================
CSprite::CSprite( const char *pName, Math::Vector2D vPos, Math::Point2DI DivNum )  
:m_pTex(NULL),
 m_pSpr(NULL),
 CDraw2DObject( pName, vPos ),
 m_DivNum( DivNum ),
 m_AnimTime( 30 ),
 m_AnimCount( 0 ),
 m_Anim( 0, 0 ),
 m_fSize( 0, 0 ),
 m_HitRect( 0, 0, 0, 0 ),
 m_DstRect( 0, 0, 0, 0 ),
 m_SrcRect( 0, 0, 0, 0 ),
 m_IsAnim( false )
{
	/*�G���[�h�~*/
	if( DivNum.x < 0 || DivNum.y < 0 )
	{
		m_DivNum.x = 1;
		m_DivNum.y = 1;
	}
}


//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	pName:�f�[�^��
//	vPos:�\���ʒu
//===========================================================================
CSprite::CSprite( const char *pName, Math::Vector2D vPos )  
:m_pTex(NULL),
 m_pSpr(NULL),
 CDraw2DObject( pName, vPos ),
 m_DivNum( 1, 1 ),
 m_AnimTime( 60 ),
 m_AnimCount( 0 ),
 m_Anim( 0, 0 ),
 m_fSize( 0, 0 ),
 m_HitRect( 0, 0, 0, 0 ),
 m_DstRect( 0, 0, 0, 0 ),
 m_SrcRect( 0, 0, 0, 0 ),
 m_IsAnim( false )
{

}

//============================================================================
//�f�X�g���N�^
//============================================================================
CSprite::~CSprite(void)
{
	SAFE_RELEASE( m_pSpr );
	SAFE_RELEASE( m_pTex );
}

//============================================================================
//�t�@�C���ǂݍ���
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//	pFileMgr:�t�@�C���Ǘ��p�f�o�C�X
//===========================================================================
void CSprite::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	pFileMgr->SetCurrentPath("Texture");
	
	printf("LOAD TEXTURE[%s]", m_strFileName.c_str() );
	
	m_pTex = pRender->CreateTextureFromFile( m_strFileName.c_str() );
	
	printf( "                 : -> %s\n", m_pTex->IsInvalid() ? "Failed" : "Succeeded" );
	
	/*�T�C�Y�̐ݒ�*/
	m_fSize.x = toF( m_pTex->GetOriginalSize().x / m_DivNum.x );
	m_fSize.y = toF( m_pTex->GetOriginalSize().y / m_DivNum.y );
	
	m_SrcRect.Set( 0, 0, m_fSize.x, m_fSize.y ),
	
	/*�X�v���C�g�̐���*/
	CreateSprite( pRender, 1000 );
	
}

//============================================================================
//�t�@�C���ǂݍ���
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//	Num:�X�v���C�g��
//===========================================================================
void CSprite::CreateSprite( Renderer::IRender *pRender, Uint32 Num )
{
	if( m_pTex != NULL )
	{	
		m_pSpr = pRender->CreateSprite2D( Num, m_pTex ); 
	}
}

//============================================================================
//����
//============================================================================
void CSprite::Exec()
{
	if( m_pSpr != NULL )
	{
		/*�A�j���[�V�����̐ݒ�*/
		SetAnimation();
		
		/*�`���*/
		m_DstRect.Set( m_vPos.x, m_vPos.y, m_fSize.x, m_fSize.y );
		
		/*�`�挳*/
		m_SrcRect.Set( m_Anim.x * m_fSize.x, m_Anim.y * m_fSize.y, m_fSize.x, m_fSize.y );
		
		/*�`��*/
		Draw();

	}
}

//============================================================================
//�`��
//============================================================================
void CSprite::Draw()
{
	/*�`��J�n*/
	m_pSpr->Begin();

	/*��]�t���`��*/
	m_pSpr->DrawSquareRotate( m_DstRect, m_SrcRect, CColor(255, 255, 255), toI( m_Rot.x ) ); 
	
	/*�`��I��*/
	m_pSpr->End();
}

//============================================================================
//�����_�����O
//============================================================================
void CSprite::Rendering( )
{
	if( GetVisibleFlag() )
	{	
		m_pSpr->Rendering();
	}
}


//============================================================================
//�O���[�X�P�[���`��
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//===========================================================================
void CSprite::DrawGrayScale( Renderer::IRender *pRender )
{
	Math::Rect2DF Dst( m_vPos.x, m_vPos.y, m_fSize.x, m_fSize.y );
	
	Math::Rect2DF Src( 0, 0, m_fSize.x, m_fSize.y );
	
	pRender->DrawGrayscale( Dst, CColor( 255, 255, 255 ), Src, m_pTex );
}

//============================================================================
//�A�j���[�V�����̐ݒ�
//============================================================================
void CSprite::SetAnimation()
{
	static int Counter = 0;//�����J�E���^�[
	
	/*�����蔻��̈�̃Z�b�g*/
	m_HitRect.Set( m_vPos.x, m_vPos.y, m_fSize.x, m_fSize.y );
	
	if( m_IsAnim )
	{
		/*�A�j���[�V�����J�E���^�̑���*/
		Counter++;
		
		if( Counter % m_AnimTime == 0 )
		{
			m_AnimCount ++;
		}
		
		m_Anim.x = m_AnimCount % m_DivNum.x;
		m_Anim.y = m_AnimCount % m_DivNum.y;
		
	}
	
}


//============================================================================
//�Q�ƃJ�E���^�̑���
//============================================================================
void CSprite::AddRef()
{
	m_pTex->AddRef();
	m_pSpr->AddRef();
}



