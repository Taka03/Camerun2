//*============================================================================
//character.h
//*============================================================================
//[history]
//	08/03/03　修正開始
//[author]
//	Taka
//=============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Draw3DObject.h"
#include "camera.h"
#include "field.h"
#include "LuaManager.h"

//=============================================================================
//enum
//=============================================================================
//アニメーションタイプ
enum eAnimType
{
	ANIM_NOW,
	ANIM_NEXT,
	ANIM_MAX,
};

//アニメーションの状態
enum eAnimState
{
	ANIM_STANDBY,//待機中
	ANIM_CHANGESTART,//切り替え開始
	ANIM_CHANGE,//切り替え中
	ANIM_CHANGEEND,//切り替え終了
};

//#define DEBUG_MAP


//=============================================================================
//class
//=============================================================================
//[Desc]
//	キャラクター用クラス
//=============================================================================
class CCharacter :public CDraw3DObject
{
	protected:
	
		Renderer::Object::IModel *m_pModel;//モデルデータ	
		Scene::IModelActor		 *m_pActorModel[SCREEN_MAX];//モデルアクター
		
		Renderer::Object::ILine3D *m_pLine3D;//デバッグ用ライン
		Scene::IPrimitiveActor *m_pActorLine[SCREEN_MAX];//ラインアクター
		
	protected:
	
		Math::Vector3D m_vFront;//キャラの正面ベクトル
		Math::Vector3D m_vRight;//キャラの右面ベクトル
		
		Math::Vector3D m_vDirection;//キャラの向いている方向
		
		bool m_IsExistAnim;//アニメーションが存在するか
		bool m_IsMoving;//キャラが動いているかどうか
		
		eAnimState m_eAnimState;//アニメーション状態
		
		float m_fWeight;//重み
		float m_fSpeed;//移動速度
		float m_fStSpeed;//基本速度
		
		float   m_fGravity;//重力
		
		bool m_IsFly;//飛行中かどうか
		
		int m_AnimID[ANIM_MAX];//アニメーションID
		float m_fAnimTime[ANIM_MAX];//現在のアニメーション時間
		
	public:
	
		CCharacter( const char *pName, Math::Vector3D vPos );//コンストラクタ
		
		~CCharacter(); //デストラクタ
	
		void Init();//初期化
		void Exec();//処理
		void SetActorSetting();//アクターの設定のセット
		void Rendering( );//レンダリング
		virtual void MoveExec(){};
		
		virtual bool Move( Selene::Math::Vector3D vTargetPos, CCamera *pCam, CField *pField );//移動
		
		
		virtual void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//ファイル読み込み
		virtual void CreateActor( int index, Scene::ISceneManager *pSceneMgr );//アクターの生成
		void CreateCollision( int index );//コリジョンデータの作成
		
		bool HitCheck( CCharacter *pChara );
		bool HitCheck( CDraw3DObject **ppChara );//当たり判定
		bool HitCheck( Selene::Collision::CLine3D &vRay );//当たり判定
		bool HitCheck( Selene::Collision::CLine3D &vRay, Renderer::SCollisionResult &Out );
		
		Bool MoveCheck( CField *pField );//移動チェック
		bool MoveCheck( CCharacter *pChara );//移動チェック

		bool GroundCheck( CCharacter *pChara );//地面チェック
		virtual bool GroundCheck( CField *pField );//地面チェック

		void SetActorIndex( int index );//アクターインデックスのセット
		
		float CheckDistance( CCharacter *pChara );//キャラ距離を測る
		
		void SetAlphaColor( Sint32 alpha );//アルファ値の設定
		
		void AddRef();//参照カウンタの増加
		
		/*ボックスの描画*/
		void DrawBox( Collision::CBox Box[], int num );
		
	/*Set系*/
	public:
	

		
	/*Get系*/
	public:
	
		/*モデルデータの取得*/
		Renderer::Object::IModel *GetModel() const
		{
			return m_pModel;
		}
		
		/*モデルアクターの取得*/
		Scene::IModelActor *GetModelActor( int index ) const
		{
			return m_pActorModel[index];
		}
		
		/*移動速度の取得*/
		float GetSpeed() const
		{
			return m_fSpeed;
		}
		
		/*正面ベクトルの取得*/
		Math::Vector3D GetFront() const
		{
			return m_vFront;
		}
		
		/*右面ベクトルの取得*/
		Math::Vector3D GetRight() const
		{
			return m_vRight;
		}
		
		/*方向の取得*/
		Math::Vector3D GetDirection() const
		{
			return m_vDirection;
		}
		

		
};