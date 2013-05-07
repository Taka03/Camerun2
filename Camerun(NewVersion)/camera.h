//*============================================================================
//camera.h
//*============================================================================
//[history]
//	08/03/11　修正
//[author]
//	Taka
//============================================================================

//二重インクルード防止
#pragma once

//=============================================================================
//include
//=============================================================================
#include "gameobject.h"

//=============================================================================
//enum
//=============================================================================
//カメラの回転タイプ
enum eRollType
{
	ROLL_LEFT,
	ROLL_RIGHT,
	ROLL_UP,
	ROLL_DOWN,
};

//=============================================================================
//variable
//=============================================================================
class CPlayer;
class CEnemy;

//=============================================================================
//class
//=============================================================================
//[desc]
//	カメラ用クラス
//=============================================================================
class CCamera
{
	private:
	
		Scene::ICamera *m_pCamera;//カメラデバイス
		
	private:
	
		Math::Vector3D m_vPos;//位置
		Math::Vector3D m_vInitPos;//位置(バックアップ用)
		Math::Vector3D m_vTarget;//ターゲット
		Math::Point3DI m_Rot;//回転角度
		Math::Point3DI m_InitRot;//回転角度(バックアップ用)
		Math::Style	   m_Style;//姿勢データ
		
		Math::Vector3D m_vDirection;//カメラの目線座標
		
		Math::Vector3D m_vUp;//カメラの上面
		Math::Vector3D m_vFront;//カメラの正面
		Math::Vector3D m_vRight;//カメラの右面
		
		Math::Vector3D m_vInitFront;//カメラの正面
		Math::Vector3D m_vInitRight;//カメラの側面
		
		::Collision::CLine3D m_vRay;//レイ
		
		bool m_IsChangeTopView;//トップビュー切り替え判定フラグ
		
		Sint32 m_CamCnt;//カメラカウント
	
	public:
	

		CCamera();//コンストラクタ
		~CCamera();//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		
		void RotateCamera( eRollType Type );//カメラの回転
		void RotateAdjust();//カメラの回転補正
		
	public:
	
		void SetCamera( Scene::ISceneManager *pScene );//カメラのセット
		//void SetCamera( Scene::ICustomizedSceneManager *pScene );//カメラのセット
		
		void SetProjection( float fNear, float fFar, Sint32 fov, Sint32 Width, Sint32 Height );//プロジェクションの設定
		void SetTransform( Math::Style style );//変形の適用	
		void SetTransform( );//変形の適用
		void SetTransform( CPlayer *pPlayer );
		void SetTransform( Sint32 Angle, bool IsCamMove );
		void SetTransform2();//変形の適用
		void SetTransform3();//変形の適用
		void SetTransformCap( CPlayer *pPlayer, CEnemy *pTarget );//キャプチャー時のカメラ変形
		void SetTransformDemo( CEnemy *pEnemy );//デモ用のカメラ移動
		void SetTransformBird( Sint32 Angle, bool IsCamMove);//トリ用のカメラ移動
		void SetPosition( Math::Vector3D vPos );//位置の設定
		void SetAngle( Sint32 Angle );//角度の設定
		void SetTargetPos( Math::Vector3D vTarget );//ターゲットの位置セット
		void SetStyle( Math::Style style );//姿勢データ設定		
		void SetRotate( Math::Point3DI Rot );//角度の設定
		
		/*トップビューフラグの設定*/
		void SetTopViewFlag( bool flag )
		{
			m_IsChangeTopView = flag;
		}
		
		/*カメラの方向の設定*/
		void SetDirection( Math::Vector3D vDir )
		{
			m_vDirection = vDir;
		}
		
		/*回転方向の増加*/
		void AddRotate( Math::Point3DI Add )
		{
			m_Rot += Add;	
			
		}
	
		
	/*Get系*/
	public:
	
		//カメラデバイスの取得
		Scene::ICamera *GetCamera()
		{
			return m_pCamera;
		}
		
		//位置の取得		
		Math::Vector3D GetPosition()
		{
			return m_vPos;
		}
		//ターゲットの取得
		Math::Vector3D GetTarget() const
		{
			return m_vTarget;
		}
		
		//姿勢データの取得		
		Math::Style GetStyle() const
		{
			return m_Style;
		}
		
		/*カメラの正面の取得*/
		Math::Vector3D GetFront() const
		{
			return m_vFront;
		}
		
		/*カメラの側面の取得*/
		Math::Vector3D GetRight() const
		{
			return m_vRight;
		}
		
		//カメラの上面の取得
		Math::Vector3D GetUp() const
		{
			return m_vUp;
		}
		
		//回転角度の設定
		Math::Point3DI GetRotate() const
		{
			return m_Rot;
		}
		
		/*トップビュー判定フラグの取得*/
		bool GetTopViewFlag() const
		{
			return m_IsChangeTopView;
		}

		
		
		
		
		
};