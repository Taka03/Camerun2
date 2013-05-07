//*============================================================================
//SceneTemplate.h
//*============================================================================
//[history]
//	08/11/11  作成
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
//	ゲームシーンテンプレートクラス
//=============================================================================
class CSceneTemplate :	public CSceneBase
{
	protected:
	
		/*ステートメソッドポインタ*/
		void ( CSceneTemplate::*m_pStateFunc )( Uint32 );
		
		//シーンの状態
		eSceneState m_eSceneState;
		
	public:
	
		CSceneTemplate();//コンストラクタ
		CSceneTemplate( string strFileName );//コンストラクタ
		virtual ~CSceneTemplate(void);//デストラクタ
		
	public:
	
		/*オブジェクトデータの初期化*/
		virtual void InitObjectData( Uint32 dt ) = 0;
		
		/*初期化*/
		virtual void Init( Uint32 dt ) = 0;
		
		/*待機中*/
		virtual void Idle( Uint32 dt ) = 0;
		
		/*停止中*/
		//virtual void Resume( Uint32 dt );
		
		/*レンダリング*/
		virtual void Rendering() = 0;
		
		/*終了*/
		virtual void End( Uint32 dt );
		
		/*更新*/
		virtual eSceneState UpDate();
		
		/*処理*/
		void Exec();
			

	public:
		
		/*状態のセット*/
		void SetState( void ( CSceneTemplate::*pState_Func )( Uint32 ) )
		{
			m_pStateFunc = pState_Func;
		}
		
		/*シーンの状態の設定*/
		void SetSceneState( eSceneState eState )
		{
			m_eSceneState = eState;
		}
	
		// フェード処理
		void FadeExec(void);
	};
