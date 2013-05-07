//*============================================================================
//Sprite3D.h
//*============================================================================
//[history]
//	08/03/19　作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Draw3DObject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	スプライト描画用オブジェクト
//=============================================================================
class CSprite3D :	public CDraw3DObject
{
	protected:
	
		Selene::Renderer::ITexture *m_pTex;//テクスチャ用ハンドル
		Selene::Renderer::Object::ISprite3D *m_pSpr;//スプライト用ハンドル
		Selene::Scene::ISpriteActor *m_pActorSprite[SCREEN_MAX];//スプライトアクター
	
	protected:
	
		Math::Matrix m_matWorld;//ローカル行列
		
		Math::Point2DI m_DivNum;//分割数
		Math::Point2DI m_Anim;//アニメID
	
		Sint32 m_Width;//幅
		Sint32 m_Height;//高さ
	
	public:
	
		CSprite3D( const char *pName, Math::Vector3D vPos );//コンストラクタ
		~CSprite3D(void);//デストラクタ
		
		virtual void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//ファイル読み込み
		void CreateActor( int index, Scene::ISceneManager *pSceneMgr );//アクターの生成

		void Init(){};//初期化
		void Exec();//処理
		void Rendering( );//レンダリング
		
		void AddRef();//参照カウンタの増加
		
		void SetActorIndex( int index );//アクターインデックスの設定
		
	/*Set系*/
	public:
	
		/*ローカル行列の設定*/
		void SetMatWorld( Math::Matrix &mat )
		{
			m_matWorld = mat;
		}
		
		/*分割数の設定*/
		void SetDivNum( Math::Point2DI Divnum )
		{
			m_DivNum = Divnum;
		}
		
		/*アニメーションIDの設定*/
		void SetAnimID( Math::Point2DI animID )
		{
			m_Anim = animID;
		}
		
	/*Get系*/
	public:

		//テクスチャ用ハンドルの取得
		Selene::Renderer::ITexture *GetTexture() const
		{
			return m_pTex;
		}
		
		//スプライト用ハンドルの取得
		Selene::Renderer::Object::ISprite3D *GetSprite() const
		{
			return m_pSpr;
		}
		
};
