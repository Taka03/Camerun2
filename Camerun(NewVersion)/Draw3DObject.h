//*============================================================================
//Draw3DObject.h
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
#include "drawobject.h"
#include "setting.h"

//=============================================================================
//class
//=============================================================================
//[desc]
//	3Dオブジェクト描画用クラス
//=============================================================================
class CDraw3DObject :public CDrawObject
{
	public:
	
		//オブジェクトタイプ
		enum e3DObjectType
		{
			OBJ_PLAYER,
			OBJ_ENEMY,
			OBJ_FIELD,
			OBJ_OTHER,
		};

	
	protected:
	
		Math::Vector3D m_vPos; //座標
		Math::Vector3D m_vInitPos;//位置のバックアップ用
		Math::Point3DI m_Rot;//角度
		Math::Point3DI m_InitRot;//角度のバックアップ用
		Math::Vector3D m_vScale;//拡縮
		Math::Vector3D m_vInitScale;//拡縮のバックアップ用
	
		int m_ActorIndex;//アクターインデックス
		
	public:
	
		CDraw3DObject( const char *pName, Math::Vector3D vPos );//コンストラクタ
		virtual ~CDraw3DObject(void);//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		virtual void MoveExec();//移動処理
		virtual void Rendering();//レンダリング
		
		virtual void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//ファイル読み込み
		void LoadShader( Renderer::IRender *pRender, const char *pName );//シェーダーの読み込み
		
		virtual void CreateActor( int index,  Scene::ISceneManager *pSceneMgr );//アクターの生成
		
		virtual bool HitCheck( CDraw3DObject **ppChara );//当たり判定
		virtual bool HitCheck( Selene::Collision::CLine3D &vRay );//当たり判定
		virtual bool HitCheck( Selene::Collision::CLine3D &vRay, CDraw3DObject **ppHitObj );//当たり判定
		virtual bool HitCheck( Selene::Collision::CLine3D &vRay, Renderer::SCollisionResult &Out );
		virtual bool HitCheck( Selene::Collision::CLine3D &vRay, Renderer::SCollisionResult &Out, CDraw3DObject **ppHitObj );
		
		virtual void SetActorIndex( int index );//アクターインデックスの設定
		
	/*Set系*/
	public:
	
		//位置の設定
		void SetPosition( Math::Vector3D vPos )
		{
			m_vPos = vPos;
		}
		
		/*初期位置の設定*/
		void SetInitPosition( Math::Vector3D vPos )
		{
			m_vInitPos = vPos;
		}
		
		/*X位置の設定*/
		void SetXPosition( float x )
		{
			m_vPos.x = x;
		}
		
		/*Y位置の設定*/
		void SetYPosition( float y )
		{
			m_vPos.y = y;
		}
		
		/*Z位置の設定*/
		void SetZPosition( float z )
		{
			m_vPos.z = z;
		}
		
		//回転角度の設定
		void SetRotate( Math::Point3DI Rot )
		{
			m_Rot = Rot;
		}
		
		//X回転角度の設定
		void SetXRotate( Sint32 x )
		{
			m_Rot.x = x;
		}
		
		//Y回転角度の設定
		void SetYRotate( Sint32 y )
		{
			m_Rot.y = y;
		}

		//Z回転角度の設定
		void SetZRotate( Sint32 z )
		{
			m_Rot.z = z;
		}
		
		//拡縮の取得
		void SetScale( Math::Vector3D vScale )
		{
			m_vScale = vScale;
		}
		
	/*Get系*/
	public:
	
		//位置の取得
		Math::Vector3D GetPosition() const
		{
			return m_vPos;
		}
		
		/*初期座標の取得*/
		Math::Vector3D GetInitPos() const
		{
			return m_vInitPos;
		}
		
		//回転角度の取得
		Math::Point3DI GetRotate() const
		{
			return m_Rot;
		}
		
		//拡縮の取得
		Math::Vector3D GetScale() const
		{
			return m_vScale;
		}
		
		/*アクターインデックスの取得*/
		int GetActorIndex() const
		{
			return m_ActorIndex;
		}
		
};
