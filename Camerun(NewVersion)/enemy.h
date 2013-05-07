//*============================================================================
//enemy.h
//*============================================================================
//[history]
//	08/03/09　修正開始
//[author]
//	Taka
//=============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "character.h"
#include "Sprite3D.h"
#include "FontSprite3D.h"
#include "Sprite.h"
#include "SceneManager.h"
#include <vector>
#include <fstream>
#include <string>

//=============================================================================
//const
//=============================================================================
const float fCHECK_DISTANCE = 30.0f;//写真判定可能距離

using namespace std;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	敵用クラス
//=============================================================================
class CEnemy :public CCharacter
{
	public:
	
		/*敵の状態*/
		enum eEnemyState
		{
			STATE_NONE,
			STATE_RELEASE,
			STATE_HITENEMY,
		};
		
		//マスクの状態
		enum eFieldMask
		{
			MASK_UNIVERSAL,//汎用
			MASK_LAKE = 2,//湖
			MASK_MOUSE,//ネズミ
			MASK_LIZARD,//トカゲ
			MASK_OUT,//外壁
			
		};
	
	protected:
	
		int m_PhotoPoint;//写真撮影時ポイント
		bool m_IsEndPhoto;//写真撮影を終えているかどうか
		bool m_IsLockOn;//ロックオンされているかどうか
		bool m_IsHitWall;//壁に接触していた場合
		bool m_IsCatchable;//キャッチできるかどうか
		
		string m_TypeName;//タイプ名
		string m_StTypeName;//タイプ名(汎用)
		
		CSprite3D *m_pCatchSpr3D;//キャッチマーク
		CSprite3D *m_pLockOnSpr3D;//ロックオンマーク
		CFontSprite3D *m_pPntFontSpr3D;//ポイント表示スプライト
		
		CSprite *m_pMinSpr;//ミニマップ用スプライト
		
		Math::Vector3D m_vCatchPos;//噛み付かれ位置
		Math::Vector3D m_vCatchMrkPos;//キャッチマークの位置
		Math::Vector3D m_vLockMrkPos;//ロックオンマークの位置
		
		Math::Vector3D m_vCatchBefPos;//噛み付かれる前の位置
		
		eEnemyState m_eState;//敵の状態
		
		float m_fKeyTime;//キー時間
		float m_fMaxKeyTime;//最大キー時間
		
		vector< Math::Vector3D > m_vecKey;//キーデータ
		
		Math::Vector3D m_vNextPoint;//次の移動ポイント
		Math::Vector3D m_vInitPoint;//現在の移動ポイント
		int m_RootSpeed;//ルートの移動速度
		int m_ReleaseCnt;//リリースカウント
		int m_GravityCnt;//重力カウント
		
		bool m_IsCaptured;//捕獲判定フラグ
		
		Collision::CLine3D m_HitRay;//当たり判定用レイ
		
		Math::CRandom m_Rand;//ランダム値
		
		//Math::Point3D< Math::Animation *> m_pPntAnim;//アニメーションポイント
		Math::Animation *m_pAnimX;//アニメーションポイントX
		Math::Animation *m_pAnimZ;//アニメーションポイントZ
		
		Uint32 m_RootCount;//ルートカウント
		
	public:
	
		CEnemy( const char *pName, Math::Vector3D vPos, Selene::File::IResourceFile *pResFile );//コンストラクタ
		~CEnemy();//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		void Rendering();//レンダリング
		
		void ShowMiniChara();//ミニキャラの表示

		void StateExec();//状態毎の処理
		void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//読み込み
		void SetActorIndex( int index );
		
		virtual void MoveExec();//移動処理
		virtual bool Move( Selene::Math::Vector3D vTargetPos, CCamera *pCam, CField *pField, bool IsShowMark );//移動
		void MoveRoot();//ルートでの移動
		void MoveRandom();//ランダムウォーク
		
		void SetNextPoint( );//次の移動ポイントの設定
		
		virtual bool HitCheckWall( CField *pField );//壁との接触判定
		
		void RenderingCatchMark();//キャッチマークのレンダリング
		void RenderingPoint();//ポイントのレンダリング
		void RenderingLockOn();//ロックオンマークのレンダリング
		
		/*乱数の種の設定*/
		void SetSeed( ICore *pCore );
		
		
		//ルートの移動箇所キーの設定
		void SetRootKey();
		
	
		
	public:
	
		void ChangeAnimation( );//アニメーションの変更
		
		void CheckCatch( Collision::CBox Box );//捕獲対象かチェック
		int CalcScore( CPlayer *pPlayer );//スコア計算
		int CheckPosScore();//写真の写っている位置のスコア
		bool CheckShoot( CSceneManager *pSceneMgr );//写真撮影可能かチェック
		bool CheckShoot( CPlayer *pPlayer );//写真撮影可能かチェック

		
	public:
	
		/*捕獲判定フラグの設定*/
		void SetCapdFlag( bool IsCaped )
		{
			m_IsCaptured = IsCaped;
		} 
		
		/*噛み付かれ位置の設定*/
		void SetCatchPos( Math::Vector3D vPos )
		{
			m_vCatchPos = vPos;
		}
		
		/*状態の設定*/
		void SetState( eEnemyState eState )
		{
			m_eState = eState;
		}
		
		/*ロックオン判定フラグの設定*/
		void SetLockOnFlag( bool flag )
		{
			m_IsLockOn = flag;
		}
		
		/*捕獲前の座標の設定*/
		void SetCatchBeforePos( Math::Vector3D vPos )
		{
			m_vCatchBefPos = vPos;
		}
		
		/*撮影終了フラグの設定*/
		void SetShootEndFlag( bool flag )
		{
			m_IsEndPhoto = flag;
		}
		
		//キャッチスプライトのセット
		void SetCatchSpr3D( CSprite3D *pSpr3D )
		{
			m_pCatchSpr3D = pSpr3D;
		}
		
		//重力カウンタの設定
		void SetGravityCnt( Sint32 Cnt )
		{
			m_GravityCnt = Cnt;
		}

	public:
	
		/*キーアニメーション時間の取得*/
		float GetKeyTime( ) const
		{
			return m_fKeyTime;
		}
		
		/*噛み付かれ位置の取得*/
		Math::Vector3D GetCatchPos() const
		{
			return m_vCatchPos;
		}
		
		/*キャッチスプライトの取得*/
		CSprite3D *GetCatchSpr3D() const
		{
			return m_pCatchSpr3D;
		}
		
		/*ポイントフォントの取得*/
		CFontSprite3D *GetPntSpr3D() const
		{
			return m_pPntFontSpr3D;
		}
		
		/*ロックオンスプライトの取得*/
		CSprite3D *GetLockOnSpr3D() const
		{
			return m_pLockOnSpr3D;
		}
		
		/*ロックオン判定フラグの取得*/
		bool GetLockOnFlag() const
		{
			return m_IsLockOn;
		}
		
		/*撮影終了フラグの取得*/
		bool GetShootEndFlag() const
		{
			return m_IsEndPhoto;
		}
		
		/*捕獲されたフラグの取得*/
		bool GetCapedFlag() const
		{
			return m_IsCaptured;
		}
		
		/*捕獲可能判定フラグ*/
		bool GetCatchableFlag() const
		{
			return m_IsCatchable;
		}
		
		/*捕獲前の座標の取得*/
		Math::Vector3D GetCatchBeforePos() const
		{
			return m_vCatchBefPos;
		}
		
		//ロックオンマークの位置の取得
		Math::Vector3D GetLockSprPos() const
		{
			return m_vLockMrkPos;
		}
		
		/*タイプ名の取得*/
		string GetTypeName() const
		{
			return m_TypeName;
		}
		
		//タイプ名の取得
		string GetStTypeName() const
		{
			return m_StTypeName;
		}
		
		//ミニキャラの取得
		CSprite *GetMinSpr() const
		{
			return m_pMinSpr;
		}

	
	
};