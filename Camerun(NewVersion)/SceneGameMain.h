//*============================================================================
//SceneGameMain.h
//*============================================================================
//[history]
//	08/03/11　作成
//	08/11/02  修正
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "SceneTemplate.h"
#include "MiniMap.h"
#include <vector>

//=============================================================================
//const
//=============================================================================
const int TRL_ENEMY_NUM = 2;//チューリアルの敵の数
const int MARKER_MAX = 99;//マーカー数


//=============================================================================
//struct
//=============================================================================
struct MarkData
{
	CSprite3D *m_pMarker;//マーカースプライト
	bool m_IsSet;//設置されているかどうか
	
	MarkData()
	{
		m_pMarker = NULL;
		m_IsSet = false;
	}
};

class CDraw3DObject;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	ゲームシーンメインクラス
//=============================================================================
class CSceneGameMain :	public CSceneTemplate
{
	public:
	
		/*次のシーン*/
		enum eNextScene
		{
			SCENE_PHOTOCHECK,//写真確認画面
			SCENE_TITLE,//タイトル画面
			SCENE_RESULT,//リザルト画面	
			SCENE_PAUSE,//ポーズ画面
			SCENE_NEWELEM,//新要素画面
		};
		
		/*チュートリアルのシーン*/
		enum eTutorialScene
		{
			SCENE_START,//チュートリアルの始まり
			SCENE_MOVEEXP,//移動説明
			SCENE_CAMMOVEEXP,//カメラ移動説明
			SCENE_SHOOTTARGET,//ターゲット撮影
			SCENE_CAPTURETARGET,//ターゲット捕獲
			SCENE_RELEASETARGET,//ターゲットリリース
			SCENE_FINISH,//終了
		};
		
		/*マウススプライトの状態*/
		enum eMouseSprState
		{
			MOUSE_PUSHNONE,//何もしてない状態
			MOUSE_PUSHLEFT,//左クリック
			MOUSE_PUSHRIGHT,//右クリック
			MOUSE_DRAG,//ドラッグ
			MOUSE_MAX,
		};
		
		/*追加する機能*/
		enum eAddFunc
		{
			FUNC_MOVE,//移動
			FUNC_CAMROT,//カメラ回転
			FUNC_CAMRESET,//カメラリセット
			FUNC_SHOOTTARGET,//写真撮影
			FUNC_MENU,//メニュー
			FUNC_CAPTURE,//捕獲
			FUNC_RELEASE,//解放
			FUNC_MAX,//追加機能の最大値
		};
		
		/*オプション*/
		enum eOption
		{
			OPTION_SCORE,//スコア
			OPTION_FILM,//フィルム
			OPTION_MAX,//オプション最大数
		};
		
		//新要素
		enum eNewElement
		{
			ELEM_TUTORIAL,//チュートリアル追加
			ELEM_ADDMOUSE,//ねずみの追加
			ELEM_ADDLIZARD,//とかげの追加
			ELEM_ADDOLDCAM,//旧キャメの追加
			ELEM_ADDFREE,//フリーミッションの追加
			ELEM_MAX,
		};
		
	private:
	
		
		eNextScene m_eNextScene;//次のシーン
		eTutorialScene m_eTrlScene;//チュートリアルシーン
		bool m_IsTutorialEnd;//チュートリアル終了したか
		
		bool m_IsDemo;//デモ中
		
		std::vector<CDraw3DObject *> m_vec3DList;//3DList
		
	private:
	
		CPlayer *m_pPlayer;//プレイヤーオブジェクト
		CField  *m_pField;//フィールドオブジェクト
		CTrain  *m_pTrain;//電車オブジェクト
		CEnemyMouse *m_pMouse;//ねずみオブジェクト
		CEnemyAmeus *m_pAmeus;//アメウスオブジェクト		
		CEnemyManta *m_pManta;//マンタオブジェクト
		CEnemyRabbit *m_pRabbit;//うさぎオブジェクト
		
		vector<CEnemy *> m_pVecCatchEnemy;//捕獲対象の敵
		vector<CEnemy *> m_pVecTarget;//ターゲット対象の敵
		CEnemy *m_pTrlEnemy[TRL_ENEMY_NUM];//チュートリアルの敵
		
		CCharacter *m_pFountObj;//噴水オブジェクト
		CCharacter *m_pIsLand;//空中庭園オブジェクト
		CCharacter *m_pTargetArrow;//ターゲット矢印オブジェクト
		CCharacter *m_pArrow;//矢印オブジェクト
		
		CSprite	   *m_pReleaseBtnSpr;//憑依解除ボタン

		CSprite	   *m_pFilmSpr;//フィルムオブジェクト
		CSprite    *m_pMoveArrowSpr;//移動矢印
		CSprite	   *m_pCamPointaSpr;//カメラポインタ
		
		CSprite	   *m_pMarkerSpr;//移動マーカ
		
		CSprite	   *m_pMissionWinSpr;//ミッションウィンドウスプライト
			
		CSprite	   *m_pMenuBtnSpr;// メニューボタンスプライト
		CSprite    *m_pReadySpr;//ゲーム開始スプライト
		CSprite	   *m_pGoSpr;//ゴースプライト
		CSprite	   *m_pEndSpr;//ゲーム終了スプライト
		
		CMiniMap   *m_pMiniMap;//ミニマップ用オブジェクト	
		CSprite	   *m_pMiniTarget;//ミニマップターゲット用スプライト	
		
		CBGM	*m_pGameMusic;//ゲーム音楽オブジェクト
		
		vector< MarkData > m_vecMarker;//ツール用マーカー
				
		CFontSprite *m_pNumFont[OPTION_MAX];//共通フォント
		
		
		//チュートリアルモード用
	private:
	
		eMouseSprState m_eMouseSprState;//マウスの状態
		CSprite	   *m_pMouseSpr;//マウス状態表示アイコン
		CSprite    *m_pArrowExpSpr;//矢印説明用画像
		CField  *m_pTrlField;//チュートリアルフィールドオブジェクト
		
		CBGM	*m_pTrlMusic;//チュートリアル音楽
		
		bool m_IsAddFunc[FUNC_MAX];//機能追加されたかどうか
		
	public:
	
		void SetActorIndexAll( int index );//アクターインデックスの一括設定
		void Rendering3DObject();//3Dオブジェクトのレンダリング
		void Exec3DObject();//3Dオブジェクトの処理
		void MoveExec3DObject();//3Dオブジェクトの移動処理
		void SetStopFlagAll( bool flag );//停止フラグの一括設定
		void SetVisibleFlagAll( bool flag );//表示フラグの一括設定
		void InitAll();//一括初期化
		
	/*スクリプト関数*/
	public:
	
		void LeftClickScript();//左クリックを押したときのスクリプト
		void RightClickScript();//右クリックを押したときのスクリプト
		void DragScript();//ドラッグしたときのスクリプト
		void CameraRotScript();//カメラ回転時のスクリプト
		void CameraResetScript();//カメラリセット時のスクリプト
		void ArrowExpScript();//矢印説明時のスクリプト
		void FilmExpScript();//フィルム説明時のスクリプト
		void ScoreExpScript();//スコア説明時スクリプト
		void CatchExpScript();//キャッチ用スクリプト
		void AddFuncScript();//機能追加スクリプト
		void TargetShowScript();//ターゲット表示用スクリプト
		void TargetClearScript();//ターゲット消去用スクリプト
		void ShootTargetScript();//最初のターゲットの撮影
		void TargetPlaceScript();//ターゲットポイント表示用スクリプト
		void ReleaseBtnScript();//リリースボタンスクリプト
		void MenuScript();//メニュー表示用スクリプト
		void EndScript();//終了スクリプト
		void OtherScript();//その他の場合のスクリプト
	
	/*追加機能関数*/	
	private:
	
		typedef void (CSceneGameMain::*AddFunc)();
		
		void MoveFunc();//移動機能
		void CameraRotFunc();//カメラ回転機能
		void CameraResetFunc();//カメラリセット機能
		void ShootTargetFunc();//写真撮影機能
		void CaptureFunc();//捕獲機能
		void ReleaseFunc();//解放機能
		void MenuFunc();//メニュー機能
		
		
		
	/*機能のレンダリング関数*/
	private:
	
		typedef void (CSceneGameMain::*FuncRender)(bool flag);
		
		void RenderMove( bool flag );//移動時の表示
		void RenderCameraRot( bool flag);//カメラ回転時の表示
		void RenderCameraReset( bool flag );//カメラリセット時の表示
		void RenderShootTarget( bool flag );//写真撮影時の表示
		void RenderCapture( bool flag);//捕獲時の表示
		void RenderRelease( bool flag);//解放時の表示
		void RenderMenu( bool flag );//メニュー機能時の表示
		
	private:
			
	public:
	
		CSceneGameMain( string strFileName );//コンストラクタ
		virtual ~CSceneGameMain(void);//デストラクタ
		
		/*オブジェクトデータの初期化*/
		void InitObjectData( Uint32 dt );
				
		/*初期化*/
		void Init( Uint32 dt );
		
		/*待機中*/
		void Idle( Uint32 dt );
		
		/*終了*/
		void End( Uint32 dt );
		
		/*レンダリング*/
		void Rendering();
		
	public:
	
		//デモ画面
		void Demo();
		
		//レディゴー画面
		void ShowReadyGo();
		
		/*ゲーム中*/
		void Game();
		
		/*ゲーム終了*/
		void GameEnd();
		
	public:		
	
		/*次のシーンのセット*/
		void SetNextScene( eNextScene Scene )
		{
			m_eNextScene = Scene;
		}
		
		/*チュートリアルシーンの設定*/
		void SetTrlScene( eTutorialScene eScene )
		{
			m_eTrlScene = eScene;
		}
		
		
	public:
	
		/*次のシーンの取得*/
		eNextScene GetNextScene() const
		{
			return m_eNextScene;
		}
		
	public:
	
		void AddFuncExec();//機能の追加処理
		void RenderFuncExec();//レンダリング関数の処理
		
		void ShootPhoto();//写真撮影
		void CreateActor();//アクターの生成
		
		void GradePhoto( );//写真評価
		void HitCheckTrain(  );//電車との当たり判定
		void RenderingSetting();//設定のレンダリング
		void SetScreenParam();//画面パラメータの設定
		
		void ShowMarker();//マーカーの表示
		void DrawMoveCursor();//移動カーソルの表示
		void ShowCatchMark();//キャッチマークの表示
		
		void ShowMiniMap();//ミニマップの表示
		
		void TargetArrowExec();//ターゲットへの矢印の処理
		
		void DrawScore();//スコアの描画
		void DrawFilmNum();//フィルム枚数の描画
		
		void ShowDebugInfo();//デバッグ情報の表示
		
		void MovePauseMenu();//ポーズ画面への移行
		
		void HitCheckCamPointa();//カメラポインタとの当たり判定
		
		void ReleaseEnemy();//敵の解放処理
		
		void InitMain();//メイン時の初期化
		
		void SavePos();//保存
		
		//クリア時に追加するオブジェクトの設定
		void SetClearObject();

		/*チュートリアル用*/
		
		/*チュートリアルモード時の初期化*/
		void InitTutorial();
		
		void MouseSprExec();//マウススプライトの処理
		
		void RenderingTutorial();//チュートリアルのレンダリング
		
		void DrawMission();//ミッションの描画
		
		void LoadMission();//ミッションのロード
		
		void SetTargetEnemy();//ターゲット対象の敵のセット
		
	
		
};
