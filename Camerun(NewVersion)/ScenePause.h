//*============================================================================
//ScenePause.h
//*============================================================================
//[history]
//	08/11/27  作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "SceneTemplate.h"

//=============================================================================
//const
//=============================================================================
const int SKILL_MAX = 5;//スキルの最大数

//=============================================================================
//class
//=============================================================================
//[Desc]
//	ポーズ画面
//=============================================================================
class CScenePause :	public CSceneTemplate
{

	public:
	
		/*メニュー項目*/
		enum eSelectScene
		{
			SCENE_RETURNGAME,//ゲームに戻る
			SCENE_RETRY,//リトライ
			SCENE_RETURNTITLE,//タイトルに戻る
		};
		
		enum ePauseScene
		{
			SCENE_CHECK,
			SCENE_NONE,
		};
		
	
	private:
	
		// メニューフォント用スプライト
		//CFontSprite *m_pMenuFontSpr;
		
		/*ポーズメニュー*/
		CMenu *m_pPauseMenu;
		
		/*確認メニュー*/
		CMenu *m_pCheckMenu;
		
		// セレクトシーン
		eSelectScene m_eSelectScene;
		
		/*メニューの表示の有無*/
		bool m_IsShowMenu;
		
		CSprite *m_pNextBtnSpr;//写真を次に送るボタン
		
		CSprite *m_pSkillSpr[SKILL_MAX];//スキル表示スプライト
		
		CSprite *m_pClearSpr;//クリアポイントスプライト
		
		CFontSprite *m_pFontSpr;//フォントスプライト
		
		CFontSprite *m_pClrPntFontSpr;//フォントスプライト
		
		CSprite *m_pSkillExpSpr;//スキル説明
		CSprite *m_pTargetSpr;//ターゲットスプライト
		
		Uint32 m_PhotoIdx;//写真のインデックス
		
		

	public:
	
		CScenePause( string strFileName );//コンストラクタ
		virtual ~CScenePause(void);//デストラクタ
		
	public:
	
		/*オブジェクトデータの初期化*/
		void InitObjectData( Uint32 dt );
		
		/*初期化*/
		void Init( Uint32 dt );
		
		/*待機中*/
		void Idle( Uint32 dt );
		
		/*レンダリング*/
		void Rendering();
		
		// ポーズメニューの設定
		void SetPauseMenu(void);
		
		/*確認画面の処理*/
		void CheckMenuExec();
		
		/*写真の描画*/
		void DrawPhoto();
		
		/*ネクストボタンの処理*/
		void NextBtnExec();
		
		// シーンの移動
		void MoveScene(eSelectScene eScene);
		
		/*ポーズメニュー表示スクリプト*/
		void PauseMenuScript();
		
		//ターゲットの表示
		void DrawTarget();
		
		//スキル説明の表示
		void DrawSkillExp( int no );
		
		//スキルの描画
		void DrawSkill();
		
	public:
	
		/*セレクトシーンの設定*/
		void SetSelectScene( eSelectScene eScene )
		{
			m_eSelectScene = eScene;
		} 
		
	public:
	
		/*セレクトシーンの取得*/
		eSelectScene GetSelectScene() const
		{
			return m_eSelectScene;
		}
		
};
