//*============================================================================
//SceneMissionSelect.h
//*============================================================================
//[history]
//	08/05/01　作成
//	08/10/21  修正
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
//	ミッションセレクト画面クラス
//=============================================================================
class CSceneMissionSelect : public CSceneBase
{
	private:
	
		/*ステートメソッドポインタ*/
		void ( CSceneMissionSelect::*m_pStateFunc )( Uint32 );
		
		//シーンの状態
		eSceneState m_eSceneState;
		
	private:
	
		CSprite *m_pMissionSelSpr;//ミッションセレクト画面
		CSprite *m_pPinSpr;//ピン
		CFontSprite *m_pNumFont;//数字フォント
		CFontSprite *m_pMiContFont;//ミッション内容表示フォント
		
		CBGM *m_pTitleMusic;//ゲームBGM
	
	
	public:
	
		CSceneMissionSelect();//コンストラクタ
		~CSceneMissionSelect(void);//デストラクタ
		
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
		
		/*ミッションの追加*/
		void AppendMission();
		
		/*ミッションの選択*/
		void SelectMission( Peripheral::IMouse *pMouse );
		
		/*ミッションの決定*/
		void DecideMission( Peripheral::IMouse *pMouse );
		
		
	public:
	
		/*状態のセット*/
		void SetState( void ( CSceneMissionSelect::*pState_Func )( Uint32 ) )
		{
			m_pStateFunc = pState_Func;
		}

	
		
		
			
};
