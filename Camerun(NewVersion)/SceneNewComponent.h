//*============================================================================
//SceneNewComponent.h
//*============================================================================
//[history]
//	08/12/26  作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "SceneTemplate.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	新要素表示画面
//=============================================================================
class CSceneNewComponent :	public CSceneTemplate
{
	public:
	
	private:
	
		CFontSprite *m_pClearFont;//クリア文字フォント
		
		CSprite *m_pBGSpr;//背景
		CSprite *m_pClearSpr;//ゲームクリア
		CSprite *m_pFailSpr;//ゲーム失敗
	
	public:
	
		CSceneNewComponent( string strFileName );//コンストラクタ
		virtual ~CSceneNewComponent(void);//デストラクタ
		
	public:
	
		/*オブジェクトデータの初期化*/
		void InitObjectData( Uint32 dt );
		
		/*初期化*/
		void Init( Uint32 dt );
		
		/*待機中*/
		void Idle( Uint32 dt );
		
		/*レンダリング*/
		void Rendering();
		
	public:
	
		void DrawMessage();//メッセージの描画
	
};
