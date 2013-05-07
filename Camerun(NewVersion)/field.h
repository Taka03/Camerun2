//*============================================================================
//field.h
//*============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Draw3DObject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	フィールド用クラス
//=============================================================================
class CField :public CDraw3DObject
{
	private:
	
		Renderer::Object::IMapModel *m_pMapModel;//マップのモデルデータ
		Scene::IMapActor			*m_pActorMap[SCREEN_MAX];//マップアクター
		Renderer::Object::ILine3D   *m_pLine3D;//デバッグライン
		
	public:
	
		CField( const char *pName, Math::Vector3D vPos );//コンストラクタ
		~CField();//デストラクタ
		
		void Init();//初期化
		void Exec();//処理
		void Rendering( );//レンダリング
		void Rendering( int index );//レンダリング
		
		void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//ファイル読み込み
		void SetActorIndex( int index );//アクターインデックスのセット
		
	public:
		
		void	CreateActor( int index, Scene::ISceneManager *pSceneMgr );//アクターの生成
		
		/*衝突判定用ライン*/
		void SetCollisionLine( Renderer::Object::ILine3D *pLine )
		{
			m_pLine3D = pLine;
		}
	
	/*Get系*/
	public:
	
		/*マップモデルデータの取得*/
		Renderer::Object::IMapModel *GetMapModel() const
		{
			return m_pMapModel;
		}
		
		/*マップアクターの取得*/
		Scene::IMapActor *GetMapActor( int index ) const
		{
			return m_pActorMap[index];
		}

		
	
		
		
};