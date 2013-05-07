//*============================================================================
//ScenePhoto.h
//*============================================================================
//[history]
//	08/03/11　作成
//	08/11/11  修正
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "SceneTemplate.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	ゲームシーン(写真)クラス
//=============================================================================
class CScenePhoto :	public CSceneTemplate
{
	public:
	
		/*写真確認*/
		enum eSelectPhoto
		{
			SELECT_REGIST,//写真を残す
			SELECT_DESTROY,//写真を捨てる
			SELECT_MAX,
		};
	
	private:
	
		CPhoto *m_pPhoto;//写真用オブジェクト
		CMenu  *m_pCheckMenu;//写真保存確認メニュー
		CSprite *m_pBG;//背景
		CFontSprite *m_pScoreFont;//スコアフォント
		
		eSelectPhoto m_eSelPhoto;//写真確認
		
		bool m_IsShowMenu;//メニューが表示されているか
		
	private:
		
		/*写真確認メソッド*/
		typedef void (CScenePhoto::*SelectFunc)();
		
		void RegistPhoto();//写真の登録
		void RemovePhoto();//写真の破棄
	
	public:
	
		CScenePhoto( string strFileName );//コンストラクタ
		virtual ~CScenePhoto(void);//デストラクタ
		
	public:
		
		/*オブジェクトデータの初期化*/
		void InitObjectData( Uint32 dt );
		
		/*初期化*/
		void Init( Uint32 dt );
		
		/*待機中*/
		void Idle( Uint32 dt );
		
		/*レンダリング*/
		void Rendering();
		
	public:
	
		void SelectFuncExec();//セレクトの処理
		void SetCheckMenu();//写真確認メニューの設定
		void MoveScene( eSelectPhoto eScene );//シーンの移動
		
	public:
	
		void PhotoSaveScript();//写真撮影スクリプト
		void RenderMenu();//メニューのレンダリング
		
	public:
	
		//表示する写真のセット	
		void SetPhoto( CPhoto *pPhoto )
		{
			m_pPhoto = pPhoto;
		}
		
		//写真確認画面の設定
		void SetSelectScene( eSelectPhoto eSelect )
		{
			m_eSelPhoto = eSelect;
		}
		
	public:
	
		/*次のシーンの取得*/
		eSelectPhoto GetSelectScene() const
		{
			return m_eSelPhoto;
		}

		
		
		
};
