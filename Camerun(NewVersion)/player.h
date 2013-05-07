//*============================================================================
//player.h
//*============================================================================
//[history]
//	08/03/03　修正開始
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "SoundEffect.h"
#include "Particle.h"
#include "Menu.h"
#include "field.h"
#include "Sprite3D.h"
#include "character.h"
#include "enemy.h"

//=============================================================================
//using
//=============================================================================
using namespace Selene;

struct MarkData;

//=============================================================================
//enum
//=============================================================================



//=============================================================================
//class
//=============================================================================
//[Desc]
//	プレイヤー用クラス
//=============================================================================
class CPlayer :public CCharacter
{
	public:
	
		//プレイヤーの状態
		enum eCharaState
		{
			STATE_NONE, //何もしていない状態
			STATE_MOVING, //移動中
			STATE_CAPSTART, //捕獲開始
			STATE_CAPTURE, //捕獲中
			STATE_RELSTART,//解放開始
			STATE_RELEASE, //解放中
			STATE_STOP,//停止中
			STATE_HIT_TRAIN, //電車に当たった場合
			STATE_HIT_ENEMY, //敵に当たった場合
			STATE_MAX,//プレイヤーの状態の最大数
		};
		
		//プレイヤーのアニメーションパターン
		enum eAnimPattern
		{
			ANIM_STAND,//立ち状態
			ANIM_WALK,//移動状態
			ANIM_CAPSTART,//噛み付き始め
			ANIM_CAPMOVE,//噛み付き移動
			ANIM_CAPEND,//噛み付き終わり
			ANIM_CAPING,//噛み付き中
		};
		
	private:
	
		Math::Vector3D m_vTargetPos;//キャラ移動位置
		Math::Vector3D m_vCapedPos;//キャッチした位置(保存用)
		
		bool	m_IsJumpFlag;//ジャンプ中かどうか
		bool	m_IsDead;//死亡フラグ
		bool	m_IsCapture;//捕獲フラグ
		
		float	m_fAccel;//加速度
		float	m_fMaxSpeed;//最大速度
		
		Uint32 m_RelCount;//リリースカウンター
		
		eCharaState m_eState;//キャラの状態
		
		CSprite *m_pMinSpr;//ミニマップ用スプライト
		CEnemy *m_pCapedEnemy;//捕獲対象の敵
		
		Collision::CBox m_CapChkBox;//捕獲判定ボックス
		Collision::CBox m_ShootChkBox;//写真撮影可能判定ボックス
		Collision::CLine3D m_ShootChkRay; //写真撮影判定レイ
		
	public:
	
		CPlayer( const char *pName, Math::Vector3D vPos );//コンストラクタ
		
		~CPlayer();//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		
		void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//ファイル読み込み

		void StateExec();//状態毎の処理
		void AnimExec();//アニメーション用処理
		void MoveExec(){};//移動処理
		
		void Rendering();//レンダリング
		
		void ShowMiniChara();//ミニキャラの表示
		
	public:
	
		void AdjustDirection();//方向補正
		bool Move( Selene::Math::Vector3D vTargetPos, CCamera *pCam, CField *pField, bool IsShowMark );//移動処理
		bool GroundCheck( CField *pField );	//地面チェック
		bool GroundCheck( CCharacter *pChara );//地面チェック(キャラ)
		
		void MoveAdjust();//移動補正
		void GroundAdjust();//地面補正
		
		void ChangeCameraMode( Sound::ISound *pSnd );//カメラモードの切り替え
		void UpdateAnimation( );//アニメーションの変更
		void ChangeAnimation( int animID );//アニメーションの切り替え
		
		void CreateCapBox();//捕獲判定用ボックスの生成
		void CreateShootBox( CCamera *pCam, CSceneManager *pSceneMgr );//写真撮影判定用ボックスの生成
		void CreateShootRay( Scene::ISceneManager *pSceneMgr );//写真撮影判定用レイの生成
		void ReleaseEnemy();//捕獲している敵の解放
		
	private:
	
		Math::Vector3D m_vTarget;//捕獲ターゲット位置
		
	public:
		
		void Move( CCamera *pCam, Peripheral::IMouse *pMouse, 
					CField *pField, Scene::ISceneManager *pSceneMgr);//移動処理(ツール用)
					

		
	/*Set系*/
	public:
	
		void SetTargetPos( Peripheral::IMouse *pMouse, CEnemy *pEnemy, Scene::ISceneManager *pSceneMgr );//移動位置の設定
		
		/*アニメーション状態の設定*/
		void SetAnimState( eAnimState state )
		{
			m_eAnimState = state;
		}
		
		/*死亡フラグの設定*/
		const void SetDeadFlag( bool flag ) 
		{
			m_IsDead = flag;
		}
		
		/*プレイヤーの状態のセット*/
		const void SetState( eCharaState eState )
		{
			m_eState = eState;
		}
		
		void AddRotate( Math::Point3DI Rot )
		{
			m_Rot += Rot;
		}
		
	/*Get系*/
	public:
	
		/*重力加速度の取得*/
		float GetGravity() const
		{
			return m_fGravity;									
		}

		
		/*死亡フラグの取得*/
		bool GetDeadFlag() const
		{
			return m_IsDead;
		}
		
		/*移動中判定フラグの取得*/
		bool GetMovingFlag() const
		{
			return m_IsMoving;
		}
		
		/*プレイヤーの状態の取得*/
		eCharaState GetState() const
		{
			return m_eState;
		}
		
		/*捕獲判定ボックスの取得*/
		Collision::CBox GetCapCheckBox() const
		{
			return m_CapChkBox;
		}	
		
		/*写真判定用のレイの取得*/
		Collision::CLine3D GetShootRay() const
		{
			return m_ShootChkRay;
		}
		
		/*写真判定可能ボックスの取得*/
		Collision::CBox GetShootChkBox() const
		{
			return m_ShootChkBox;
		} 
		
		/*捕獲対象の敵の取得*/
		CEnemy *GetCapedEnemy() const
		{
			return m_pCapedEnemy;
		}
		
		//捕獲位置の取得
		Math::Vector3D GetCapedPos() const
		{
			return m_vCapedPos;
		}
		
		/*捕獲フラグの設定*/
		bool GetCaptureFlag() const
		{
			return m_IsCapture;
		}
		
		/*マウスターゲットの取得*/
		Math::Vector3D GetMouseTarget() const
		{
			return m_vTarget;
		}
		
		//ミニキャラの取得
		CSprite *GetMinSpr() const
		{
			return m_pMinSpr;
		}
		
};