//*============================================================================
//ScreenController.h
//*============================================================================
//[history]
//	08/11/23　作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Selene.h"
#include "setting.h"

//=============================================================================
//using
//=============================================================================
using namespace Selene;

//=============================================================================
//class
//=============================================================================
//[desc]
//	スクリーン制御用クラス
//=============================================================================
class CScreenController
{
	public:
		
		
		enum eScreenState
		{
			STATE_STANDBY,
			STATE_FADEIN,
			STATE_FADEOUT,
		};
		
	private:
	
		Renderer::IRender *m_pRender;//レンダー用デバイス
		CColor			  m_Color;//色
		eScreenState	  m_eScreenState;//スクリーンの状態
		Sint32			  m_Time;//タイムカウンター
		Sint32			  m_TimeLast;//最大タイム
		
	private:
	
		void FadeIn();//フェードイン
		void FadeOut();//フェードアウト

		
	public:
	
		CScreenController(){};//コンストラクタ
		CScreenController( Renderer::IRender *pRender );//コンストラクタ
		virtual ~CScreenController();//デストラクタ
		
		virtual void Exec();//処理
		
		virtual void SetFadeIn( Sint32 Time, CColor Color );//フェードインの設定
		virtual void SetFadeOut( Sint32 Time, CColor Color );//フェードアウトの設定
		virtual Bool IsFade( void );//フェード中かどうか
		
	public:
	
		
		
	
	
};


