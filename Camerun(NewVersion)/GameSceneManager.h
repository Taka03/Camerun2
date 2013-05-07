//*============================================================================
//GameSceneManager.h
//*============================================================================
//[history]
//	08/03/05　作成
//	08/10/08  修正開始	
//[author]
//	Taka
//[ref]
// ○×つくろーどっとコム　http://marupeke296.com/
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "gameobject.h"
#include "SceneBase.h"
#include "SceneGameTitle.h"
#include "SceneGameMain.h"
#include "ScenePhoto.h"
#include "SceneResult.h"
#include "ScenePause.h"
#include "SceneTutorial.h"
#include "SceneShowMission.h"
#include "SceneNewComponent.h"

//=============================================================================
//define
//=============================================================================


//=============================================================================
//using
//=============================================================================
using namespace std;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	ゲームシーン管理用クラス
//=============================================================================
class CGameSceneManager :public CSceneBase
{
	public:
	
	private:
	
		CSceneGameTitle *m_pGameTitle;//ゲームタイトル
		CSceneGameMain *m_pGameMain;//ゲームメイン
		CScenePhoto *m_pPhotoCheck;//写真確認画面
		CSceneResult *m_pResult;//結果画面
		CScenePause *m_pPause;//ポーズ画面
		CSceneShowMission *m_pShowMission;//ミッション表示
		CSceneNewComponent *m_pNewComp;//新要素表示
	
	private:
	
		eSceneState m_eSceneState;//シーンの状態
		
	public:
	
		CColor			  m_Color;//色
		Sint32			  m_Time;//タイムカウンター
		Sint32			  m_TimeLast;//最大タイム
		
		
	private:
	
		void Title();//タイトル
		void ShowMission();//ミッションスタート画面
		void GameMain();//ゲームメイン
		void PhotoCheck();//写真確認画面
		void Result();//結果画面
		void NewComp();//新要素表示画面
		void Pause(void);// スタートメニュー
		void Exit();//終了
		
		void DrawNowLoading();//読み込み画面の描画

	private:
	
		void LoadStatus( );//ステータスのロード
		void SaveStatus( );//ステータスのセーブ
		
	private:
	
		/*スクリプトメソッド*/
		typedef void (CSceneGameMain::*ScriptFunc)();

		string ScriptExec( string strSource );//スクリプト処理
		void TutorialExec();//チュートリアル処理
		
	private:
	
		virtual void SetFadeIn( Sint32 Time, CColor Color, void ( CGameSceneManager::*pStateFunc )() );//フェードインの設定
		virtual void SetFadeOut( Sint32 Time, CColor Color, void ( CGameSceneManager::*pStateFunc )() );//フェードアウトの設定
		virtual Bool IsFade( void );//フェード中かどうか
		void FadeIn();//フェードイン
		void FadeOut();//フェードアウト
		
		void FadeExec();//フェード処理
	
		
	public:
	
		CGameSceneManager( CSceneBase *pScene );//コンストラクタ
		
		CGameSceneManager( );//コンストラクタ

		~CGameSceneManager();//デストラクタ
		
		void Rendering();//レンダリング
		
		eSceneState UpDate();//更新
		
		/*シーンの設定*/
		void SetStateFunc( void ( CGameSceneManager::*pStateFunc )() )
		{
			m_pStateFunc = pStateFunc;
		}
		
		/*描画の設定*/
		void SetRenderFunc( void ( CGameSceneManager::*pRenderFunc )() )
		{
			m_pRenderFunc = pRenderFunc;
		}
		
	public:
	
		//ステートメソッドポインタ		
		void ( CGameSceneManager::*m_pStateFunc )();	
		
		//描画メソッドポインタ
		void ( CGameSceneManager::*m_pRenderFunc )();
		
		// チュートリアル画面
		void Tutorial(void);
		
};