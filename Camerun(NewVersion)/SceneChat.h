//*============================================================================
//SceneChat.h
//*============================================================================
//[history]
//	08/05/23　作成
//	08/11/01  修正
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "SceneBase.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	会話画面クラス
//=============================================================================
class CSceneChat : public CSceneBase
{
	private:
	
		/*ステートメソッドポインタ*/
		void ( CSceneChat::*m_pStateFunc )( Uint32 );
		
		//シーンの状態
		eSceneState m_eSceneState;
		
	private:
	
		CSprite *m_pBG;//背景
		CFontSprite *m_pChatFont;//会話フォント
		CBGM *m_pMusic;//BGM
	
	public:
	
		CSceneChat();//コンストラクタ
		CSceneChat( CResourceManager *pResMgr, CMissionManager *pMissionMgr );//コンストラクタ
		~CSceneChat(void);//デストラクタ
		
		/*初期化*/
		void Init( Uint32 dt );
		
		/*待機中*/
		void Idle( Uint32 dt );
		
		/*終了*/
		void End( Uint32 dt );
		
		/*レンダリング*/
		void Rendering();
		
		/*更新*/
		virtual eSceneState UpDate();
		
	public:
	
		/*状態のセット*/
		void SetState( void ( CSceneChat::*pState_Func )( Uint32 ) )
		{
			m_pStateFunc = pState_Func;
		}

};
