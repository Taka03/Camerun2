//*============================================================================
//DrawObject.h
//*============================================================================
//[history]
//	08/03/03 修正開始
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "gameobject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	描画用オブジェクト
//=============================================================================
class CDrawObject :public CGameObject
{
	protected:
		
		bool m_IsStop;//静止判定フラグ
		bool m_IsVisible;//表示判定フラグ
		
	public:
	
		//コンストラクタ
		CDrawObject( const char *pName );
		
		//デストラクタ
		virtual ~CDrawObject(void){};
		
		//初期化
		virtual void Init();
		
		//処理
		virtual void Exec(){};
		
		//ファイル読み込み
		virtual void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr ) = 0;
		
		//レンダリング
		virtual void Rendering() = 0;
		
	/*Set系*/
	public:
	
		/*表示フラグの設定*/
		void SetVisibleFlag( bool IsVisible )
		{
			m_IsVisible = IsVisible;
		}
		
		/*静止フラグの設定*/
		void SetStopFlag( bool IsStop )
		{
			m_IsStop = IsStop;
		}
		
	public:
		
		//表示フラグの取得
		bool GetVisibleFlag() const
		{
			return m_IsVisible;
		}
		
		//静止フラグの取得		
		bool GetStopFlag() const
		{
			return m_IsStop;
		}
		
		
};
