//*============================================================================
//SceneBase.h
//*============================================================================
//[history]
//	08/03/11　作成
//	08/10/08  名前をSceneBase.hに変更
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "ResourceManager.h"
#include "ScreenController.h"
#include "FileLoader.h"
#include "SceneManager.h"
#include "MissionManager.h"
#include "Draw3DObject.h"
#include "camera.h"
#include "BGM.h"
#include "SoundManager.h"
#include "mouse.h"

#include <list>


//=============================================================================
//enum
//=============================================================================

//シーン状態
enum eSceneState
{
	STATE_LOADING,//ロード中
	STATE_CONTINUE,//遷移中
	STATE_STANDBY,//スタンバイ状態
	STATE_FADEIN,//フェードイン
	STATE_FADEOUT,//フェードアウト
	STATE_FINISH,//遷移終了
};

//=============================================================================
//const
//=============================================================================
const int FILM_MAX = 5;//フィルムの最大枚数

//=============================================================================
//class
//=============================================================================
//[Desc]
//	ゲームシーン用クラス
//=============================================================================
class CSceneBase
{
	public:
	
		struct StringList
		{
			string m_DataName;//データ名
		};
		
		/*指アイコンの状態*/
		enum eFingState
		{
			FING_NONE,//非表示状態
			FING_UP,//上方向
			FING_DOWN,//下方向
			FING_LEFT,//左方向
			FING_RIGHT,//右方向
		};
		
	private:
	
	private:
	
		static CSprite *m_pCursorSpr;//カーソル

		static Uint32 m_FilmCount;//フィルムカウント
		static int m_TotalScore;//合計スコア
		static int m_ClearCount;//クリアカウント
		static int m_ClearPoint;//クリアポイント
		
		static int m_HiScore;//ハイスコア
		
		static float m_fTargetDis;//ターゲットとの距離
		static Math::Vector3D m_vTargetPos;//ターゲットとの位置
		
		static CBGM *m_pBGM;//BGM
		
		static bool m_IsFirstGame;//初期プレイかどうか
		
		/*チュートリアル用*/
		static bool m_IsTutorial;//チュートリアルモードかどうか
		static CExpWindow *m_pWindowSpr;//ウィンドウスプライト
		static CSprite *m_pFingIcoSpr;//指アイコンスプライト
		
		static eFingState m_eFingState;//指アイコンの状態
		
		static CEnemy *m_pTarget;//写真のターゲット
		
		static bool m_IsTargetExist;//ターゲットが存在するか
		
		static bool m_IsSavePhoto;//写真をセーブしたか
		
		
	protected:
	
		list<StringList> m_DataNameList;//データ名リスト
		list<CDraw2DObject *> m_Draw2DList;//2D描画リスト
		list< CResourceManager::ListData > m_DataList;//データリスト
				
		static CCamButton *m_pCamBtnSpr;//カメラボタン
		

		
	public:
	
		CSceneBase();//コンストラクタ
		CSceneBase( string strFileName );//コンストラクタ
		virtual ~CSceneBase(void);//デストラクタ
		
		void Init();//初期化
		virtual eSceneState UpDate() = 0;//更新
		virtual void Rendering() = 0;//レンダリング
		
		void LoadResource( string strFileName );//リソースの読み込み
		void Push2DObject();//2Dオブジェクトのリスト追加
		void Rendering2DList();//2Dリストのレンダリング
		void Exec2DList();//2Dリストの処理
		
		void FingIcoExec();//指アイコンの処理
		void RenderMouseIco();//マウスアイコンのレンダリング
		
	/*Set系*/
	public:
	
		
		
		/*マウスカーソルのセット*/
		void SetMouseCursor( CSprite *pSpr )
		{
			m_pCursorSpr = pSpr;
		}
		
		/*フィルムカウンタのセット*/
		void SetFilmCount( int count )
		{
			m_FilmCount = count;
		}
		
		/*合計点のセット*/
		void SetTotalScore( int Score )
		{
			m_TotalScore = Score;
		}
		
		//ハイスコアの設定
		void SetHiScore( int Score )
		{
			m_HiScore = Score;
		}
		
		/*フィルムカウンタの増加*/
		void AddFilmCount()
		{
			m_FilmCount++;
		}
		
		/*クリアカウントの設定*/
		void SetClearCount( int count )
		{
			m_ClearCount = count;
		}
		
		//クリアポイントの設定
		void SetClearPoint( int point )
		{
			m_ClearPoint = point;
		}
		
		/*クリアカウントの増加*/
		void AddClearCount()
		{
			++m_ClearCount;
		}
		
		/*チュートリアルフラグの設定*/
		void SetTutorialFlag( bool flag )
		{
			m_IsTutorial = flag;
		}
		
		/*初期プレイフラグの設定*/
		void SetFirstGameFlag( bool flag )
		{
			m_IsFirstGame = flag;
		}
		
		/*ターゲットとの距離の設定*/
		void SetTargetDistance( float fDis )
		{
			m_fTargetDis = fDis;
		}
		
		/*ターゲットとの位置の設定*/
		void SetTargetPos( Math::Vector3D vPos )
		{
			m_vTargetPos = vPos;
		}
		
		/*ウィンドウスプライトの設定*/
		void SetWindowSpr( CExpWindow *pWindow )
		{
			m_pWindowSpr = pWindow;
		}
		
		/*指アイコンの設定*/
		void SetFingIcoSpr( CSprite *pFing )
		{
			m_pFingIcoSpr = pFing;
		}
		
		/*指アイコン状態の設定*/
		void SetFingState( eFingState eState )
		{
			m_eFingState = eState;
		}
		
		//BGMの設定
		void SetBGM( CBGM *pBGM )
		{
			m_pBGM = pBGM;
		}
		
		/*ターゲットの設定*/
		void SetTarget( CEnemy *pTarget )
		{
			m_pTarget = pTarget;
		}
		
		//ターゲット存在フラグの設定
		void SetTargetExistFlag( bool flag )
		{
			m_IsTargetExist = flag;
		}
		
		//写真を保存判定フラグの設定
		void SetPhotoSaveFlag( bool flag )
		{
			m_IsSavePhoto = flag;
		}
		
	/*Get系*/
	public:
		
		/*マウスカーソルの取得*/
		CSprite *GetMouseCursor() const
		{
			return m_pCursorSpr;
		}
		
		/*フィルムカウントの取得*/
		Uint32 GetFilmCount() const
		{
			return m_FilmCount;
		}
		
		/*合計得点の取得*/
		int GetTotalScore() const
		{
			return m_TotalScore;
		}
		
		//ハイスコアの取得
		int GetHiScore() const
		{
			return m_HiScore;
		}
		
		/*クリアカウントの取得*/
		int GetClearCount() const
		{
			return m_ClearCount;
		}
		
		//クリアポイントの取得
		int GetClearPoint() const
		{	
			return m_ClearPoint;
		}
		
		
		/*チュートリアルフラグの取得*/
		static bool GetTutorialFlag()
		{
			return m_IsTutorial;
		}
		
		/*初期プレイフラグの設定*/
		bool GetFirstGameFlag() const
		{
			return m_IsFirstGame;
		}
		
		/*ターゲットとの距離の取得*/
		float GetTargetDistance() const
		{
			return m_fTargetDis;
		}
		
		/*ターゲットとの位置の取得*/
		Math::Vector3D GetTargetPos() const
		{
			return m_vTargetPos;
		}
		
		/*ウィンドウスプライトの取得*/
		CExpWindow *GetWindowSpr() const
		{
			return m_pWindowSpr;
		}
		
		/*指アイコンの取得*/
		CSprite *GetFingerSpr() const
		{
			return m_pFingIcoSpr;
		}
		
		/*指アイコン状態の取得*/
		eFingState GetFingState() const
		{
			return m_eFingState;
		}
		
		//ターゲットとなるオブジェクトの取得
		CEnemy *GetTarget() const
		{
			return m_pTarget;
		}
		
		//ターゲット存在フラグの取得
		bool GetTargetExistFlag() const
		{
			return m_IsTargetExist;
		}
		
		//写真保存判定フラグの取得
		bool GetPhotoSaveFlag() const
		{
			return m_IsSavePhoto;
		}
		
		/*BGMの取得*/
		CBGM *GetBGM()
		{
			return m_pBGM;
		}
		
};
