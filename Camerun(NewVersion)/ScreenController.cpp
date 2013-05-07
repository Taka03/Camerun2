//*============================================================================
//ScreenController.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "ScreenController.h"

namespace
{
	Math::Rect2DF ScreenRect( 0.0f, 0.0f, toF( SCREEN_WIDTH ), toF( SCREEN_HEIGHT ) );
}

//=============================================================================
//コンストラクタ
//=============================================================================
CScreenController::CScreenController( Renderer::IRender *pRender )
	: m_pRender		( pRender ),
	  m_eScreenState( STATE_STANDBY ),
	  m_Color		( 0, 0, 0, 0 ),
	  m_Time		( 0 ),
	  m_TimeLast	( 0 )
{
	m_pRender->AddRef();
}

//=============================================================================
//デストラクタ
//=============================================================================
CScreenController::~CScreenController()
{
	SAFE_RELEASE( m_pRender );
}

//=============================================================================
//処理
//=============================================================================
void CScreenController::Exec()
{
	switch( m_eScreenState )
	{
		case STATE_STANDBY:
		{
			break;
		}
		
		/*フェードイン*/
		case STATE_FADEIN:
		{
			FadeIn();
			break;
		}
		
		/*フェードアウト*/
		case STATE_FADEOUT:
		{
			FadeOut();
			break;
		}
	}
}

//=============================================================================
//フェードイン
//=============================================================================
void CScreenController::FadeIn()
{
	m_Color.a = (Uint8)( ::Interpolation::Flat( 255L, 0L, m_TimeLast, m_Time ) );
	
	m_pRender->SetDrawType( DRAW_TYPE_BLEND );
	
	/*画面全体を覆う*/
	m_pRender->FillRect( ScreenRect, m_Color );
	
	// タイマー＋
	if ( ++m_Time > m_TimeLast )
	{
		m_eScreenState = STATE_STANDBY;
	}
	
}

//=============================================================================
//フェードアウト
//=============================================================================
void CScreenController::FadeOut()
{
	m_Color.a = (Uint8)( ::Interpolation::Flat( 0L, 255L, m_TimeLast, m_Time ) );
	
	m_pRender->SetDrawType( DRAW_TYPE_BLEND );
	
	/*画面全体を覆う*/
	m_pRender->FillRect( ScreenRect, m_Color );
	
	// タイマー＋
	if ( ++m_Time > m_TimeLast )
	{
		m_eScreenState = STATE_STANDBY;
	}
}

//=============================================================================
//フェードインの設定
//=============================================================================
//[input]
//	Time:フェードイン時間
//	Color:描画する色
//=============================================================================
void CScreenController::SetFadeIn( Sint32 Time, CColor Color )
{
	m_eScreenState = STATE_FADEIN;
	m_Color = Color;
	m_TimeLast = Time;
	m_Time = 0;
}

//=============================================================================
//フェードアウトの設定
//=============================================================================
//[input]
//	Time:フェードアウト時間
//	Color:描画する色
//=============================================================================
void CScreenController::SetFadeOut( Sint32 Time, CColor Color )
{
	m_eScreenState = STATE_FADEOUT;
	m_TimeLast = Time;
	m_Time = 0;
}

//=============================================================================
//フェード中かどうか
//=============================================================================
Bool CScreenController::IsFade()
{
	return m_eScreenState != STATE_STANDBY;
}









