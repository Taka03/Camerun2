//*============================================================================
//FontSprite3D.h
//*============================================================================
//[history]
//	08/03/16 作成
//	08/11/19 修正開始
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Draw3DObject.h"

#include <string>

//=============================================================================
//class
//=============================================================================
//[Desc]
//	フォントスプライト描画用オブジェクト
//=============================================================================
class CFontSprite3D :	public CDraw3DObject
{
	private:
		
		Renderer::Object::IFontSprite3D *m_pFontSpr3D;//フォントスプライト用ハンドル
		Scene::IParticleActor *m_pActorFont[SCREEN_MAX];//フォントアクター
		Math::Point2DF m_fSize;//サイズ
		std::string m_Str;//表示する文字
		
		Renderer::IRender *m_pRender;//レンダラー
	
	public:
	
		CFontSprite3D( const char *pName, Math::Vector3D vPos );//コンストラクタ
		
		virtual ~CFontSprite3D(void);//デストラクタ
		
		void Init(){};//初期化
		void Exec();//処理
		void Rendering();//レンダリング
		
		void CreateActor( int index, Scene::ISceneManager *pSceneMgr );//アクターの生成
		void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//読み込み
		void SetActorIndex( int index );//アクターインデックスのセット
		
	/*Set系*/
	public:
	
		//描画する文字の設定
		void SetDrawString( std::string str )
		{
			m_Str = str;
		}
		
	/*Get系*/	
	public:
	
		//フォントスプライト用ハンドルの取得
		Renderer::Object::IFontSprite3D *GetFontSprite() const
		{
			return m_pFontSpr3D;
		}
		
		/*フォントアクターの取得*/
		Scene::IParticleActor *GetFontActor( int index ) const
		{
			return m_pActorFont[index];
		}	
		
	
};
