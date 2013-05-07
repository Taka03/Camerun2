//*============================================================================
//SceneGameTitle.h
//*============================================================================
//[history]
//	08/10/14  作成
//[author]
//	Taka
//============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneTemplate.h"

//=============================================================================
//const
//=============================================================================
/*メニュー数*/
const int MENU_MAX = 3;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	ゲームタイトルクラス
//============================================================================
class CSceneGameTitle :public CSceneTemplate
{
	public:
	
		/*セレクトシーン*/
		enum eSelectScene
		{
			SELECT_GAME,
			SELECT_TUTORIAL,
			SELECT_EXIT,
		};

	
	private:
	
		
		/*タイトルの状態*/
		enum eTitleState
		{
			STATE_DEMO,
			STATE_STANDBY,
		};
		
		eSelectScene m_eSelectScene;//セレクトシーン
		
	private:
	
		CBGM *m_pTitleBGM;//タイトルBGM
		
		CMenu *m_pTitleMenu;//タイトルメニュー
		
		CSprite *m_pBG;
		
		CFontSprite *m_pHiScoreFont;//ハイスコアフォント
		CSprite *m_pHiScoreSpr;//ハイスコア
		
					
	public:
	
		
		/*コンストラクタ*/
		CSceneGameTitle( string strFileName );
		
		/*デストラクタ*/
		~CSceneGameTitle();
		
		/*オブジェクトデータの初期化*/
		void InitObjectData( Uint32 dt );
	
		/*初期化*/
		void Init( Uint32 dt );
		
		/*待機中*/
		void Idle( Uint32 dt );
		
		/*フェードアウト*/
		void FadeOut( Uint32 dt );
		
		/*レンダリング*/
		void Rendering();
		
	public:
	
		void SetTitleMenu();//タイトルメニューの設定
		void MoveScene( eSelectScene eScene );//シーンの移動
		
	public:
	
		//セレクトシーンの設定
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




