//*============================================================================
//MiniMap.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "MiniMap.h"

//=============================================================================
//const
//=============================================================================

//�~�j�}�b�v�̈ړ����\��
const int MAP_ZMIN = -528;//�}�b�vZ�ʒu�̍ŏ��ʒu
const int MAP_ZMAX = 0;//�}�b�vZ�ʒu�̍ő�ʒu
const int MAP_XMIN = -359;//�}�b�vX�ʒu�̍ŏ��ʒu
const int MAP_XMAX = 359*2;//�}�b�vX�ʒu�̍ő�ʒu

const int MINI_PLAYER_WIDTH = 16;
const int MINI_PLAYER_HEIGHT = 16;

//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	pName:�f�[�^��
//	vPos:�\���ʒu
//===========================================================================
CMiniMap::CMiniMap( const char *pName, Math::Vector2D vPos ) :CSprite( pName, vPos ),
m_pRender( NULL )
{
	m_Scroll.x = 0;
	m_Scroll.y = 0;
	
	m_DrawSize.x = 240;
	m_DrawSize.y = 180;
	
}

//============================================================================
//�f�X�g���N�^
//============================================================================
CMiniMap::~CMiniMap()
{
	SAFE_RELEASE( m_pRender )
}


//============================================================================
//����
//============================================================================
void CMiniMap::Exec()
{
	if( m_pSpr != NULL )
	{
		Math::Rect2DF Dst( m_vPos.x, m_vPos.y, m_DrawSize.x, m_DrawSize.y );
		
		Math::Rect2DF Src( m_Scroll.x , m_Scroll.y , m_DrawSize.x, m_DrawSize.y  );
		
		m_pSpr->Begin();
		
		m_pSpr->DrawSquare( Dst, Src, CColor(255, 255, 255) ); 
		
		m_pSpr->End();
	}
}

//============================================================================
//����
//============================================================================
void CMiniMap::Rendering()
{
	if( m_pRender != NULL )
	{
		/*�g�̕`��*/
		m_pRender->SetDrawType( DRAW_TYPE_ADD );
		
		const int SUB_X = 0;
		const int SUB_Y = 0;
		
		m_pRender->FillRect( Math::Rect2DF( toF( m_vPos.x ), toF( m_vPos.y ), m_DrawSize.x, m_DrawSize.y ), 
		                     CColor( 189, 140, 191, 128) );
		
		m_pRender->SetDrawType( DRAW_TYPE_BLEND );
		
		m_pSpr->Rendering();
		
		m_pRender->SetDrawType( DRAW_TYPE_NORMAL );
		
	}
	
}



//============================================================================
//�ړ�
//============================================================================
//[input]
//	pChara:�ݒ肷��L�����N�^�[
//============================================================================
void CMiniMap::Move( CCharacter *pChara )
{
	
	m_Scroll.x = ( ( pChara->GetPosition().x - MAP_XMIN) / MAP_XMAX ) * (m_fSize.x) - m_DrawSize.x/2;
	m_Scroll.y = ( (pChara->GetPosition().z /MAP_ZMIN ) )  * (m_fSize.y) - m_DrawSize.y/2;
	
}

//============================================================================
//�X�N���[���␳
//============================================================================
void CMiniMap::ScrollAdjust()
{
	
	if( m_Scroll.x <= 0)
	{
		m_Scroll.x = 0;
	}
	
	if( m_Scroll.x >= m_fSize.x - m_DrawSize.x + MINI_PLAYER_WIDTH )
	{
		m_Scroll.x = m_fSize.x - m_DrawSize.x + MINI_PLAYER_WIDTH;	
	}
	
	if( m_Scroll.y <=  -m_DrawSize.y / 2 )
	{
		m_Scroll.y = -m_DrawSize.y / 2;	
	}
	
	if( m_Scroll.y >= m_fSize.y - m_DrawSize.y / 2 + MINI_PLAYER_HEIGHT)
	{
		m_Scroll.y = m_fSize.y - m_DrawSize.y / 2 + MINI_PLAYER_HEIGHT;
	}
}

//============================================================================
//�~�j�}�b�v�p�L�����ʒu�̐ݒ�
//============================================================================
//[input]
//	pChara:�ݒ肷��L�����N�^�[
//	pSpr:�ݒ肷��~�j�L�����X�v���C�g
//	IsPlayer:�v���C���[�L�������ǂ���
//============================================================================
void CMiniMap::SetMiniCharaPos( CCharacter *pChara, CSprite *pSpr, bool IsPlayer )
{
	if( IsPlayer )
	{
		if( pChara->GetPosition().x < 0 )
		{	
			pSpr->SetPosition( Math::Vector2D
			( m_DrawSize.x / 2 - pSpr->GetSize().x / 2, 
			m_DrawSize.y / 2 - pSpr->GetSize().y / 2 ) );
			
		}
		
		else
		{
			float XAxis = ( pChara->GetPosition().x ) / MAP_XMAX;
			float ZAxis = ( pChara->GetPosition().z ) / MAP_ZMIN;
			float AdjustWidth = m_DrawSize.x - pSpr->GetSize().x / 2;
			float AdjustHeight = m_DrawSize.y - pSpr->GetSize().y;
		
			//pSpr->SetPosition( Math::Vector3D(	XAxis  * AdjustWidth + m_DrawSize.x / 2 + m_vPos.x,
			//											ZAxis  * AdjustHeight + m_vPos.y ,
			//											 0 ) );
			//
			pSpr->SetPosition( Math::Vector2D( m_DrawSize.x / 2 - pSpr->GetSize().x / 2, 
											   m_DrawSize.y / 2 - pSpr->GetSize().y / 2 ) );
														 
		}	
		
		pSpr->SetRotate( Math::Point2DI( pChara->GetRotate().x, pChara->GetRotate().y ) );
		
		
	}
	
	else
	{
		if( pSpr->GetPosition().x < 0 )
		{	
			float XAxis = ( pChara->GetPosition().x + MAP_XMAX/2  ) / MAP_XMAX ;
			float ZAxis =( pChara->GetPosition().z ) / MAP_ZMIN;
			float AdjustHeight = m_fSize.x - pSpr->GetSize().y;
			
			pSpr->SetPosition( Math::Vector2D( ( XAxis * m_fSize.x + m_vPos.x ) -  m_Scroll.x, 
											   ( ZAxis * AdjustHeight + m_vPos.y ) - m_Scroll.y )  );
		}
		
		else
		{
			float XAxis = ( pChara->GetPosition().x ) / MAP_XMAX;
			float ZAxis = ( pChara->GetPosition().z ) / MAP_ZMIN;
			float AdjustWidth = m_fSize.x - pSpr->GetSize().x / 2.0f;
			float AdjustHeight =m_fSize.y - pSpr->GetSize().y ;
		
			pSpr->SetPosition( Math::Vector2D( (XAxis  * AdjustWidth + m_fSize.x / 2 + m_vPos.x ) 
												- m_Scroll.x - pSpr->GetSize().x/2,
											   (ZAxis  * AdjustHeight + m_vPos.y) - m_Scroll.y ) );
		}	
		
		/*�~�j�}�b�v�O�ɂ���Ƃ��́A�\�������Ȃ��悤�ɂ���*/
		if( pSpr->GetPosition().x >= m_vPos.x && pSpr->GetPosition().x <= m_vPos.x + m_DrawSize.x
			&& pSpr->GetPosition().y >= m_vPos.y && pSpr->GetPosition().y <= m_vPos.y + m_DrawSize.y )
		{
			//if( pSpr->GetMissionVisible() )
			//{	
				pSpr->SetVisibleFlag( pChara->GetVisibleFlag() );
			//}
		}
		
		else
		{
			pSpr->SetVisibleFlag( false );
		}
	
	}
	
	
}




