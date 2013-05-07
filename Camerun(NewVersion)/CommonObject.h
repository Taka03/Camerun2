//*============================================================================
//CommonObject.h
//*============================================================================
//[history]
//	08/12/27 作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Application.h"

//=============================================================================
//variable
//=============================================================================
class CGameSceneManager;
class CSoundManager;
class CResourceManager;
class CApplication;
class CSceneManager;
class CCamera;
class CMouse;


//=============================================================================
//class
//=============================================================================
//[Desc]
//	共通オブジェクト用クラス
//=============================================================================
class CCommonObject
{
	public:
	
		//コンストラクタ
		CCommonObject(void);
		
		//デストラクタ
		~CCommonObject(void);
		
	private:
	
		static CApplication *m_pApp;//アプリケーションクラス
		static CResourceManager *m_pResMgr;//リソース管理クラス
		static CSoundManager *m_pSndMgr;//サウンド管理クラス
		static CGameSceneManager *m_pGameSceneMgr;//ゲームシーン管理クラス
		static CSceneManager *m_pSceneMgr[SCREEN_MAX];//シーン(3D)管理
		static CCamera *m_pCamera[SCREEN_MAX];//シーンのカメラ
		static CMouse *m_pMouse;//マウス管理クラス
		
	public:
	
		static void Initialize();//初期化処理
		static void Finalize();//終了処理
	
	public:
	
		/*サウンド管理クラスの取得*/
		static CSoundManager *GetSoundMgr(); 
		
		//リソース管理クラスの取得
		static CResourceManager *GetResMgr();
		
		//シーン(3D)管理クラスの取得
		static CSceneManager *GetSceneMgr( int index );
		
		//カメラの取得
		static CCamera *GetCamera( int index );
		
		//アプリケーションクラスの取得
		static CApplication *GetAppli();
		
		//マウスクラスの取得
		static CMouse *GetMouse();
		
		//ゲームシーンマネージャの取得
		static CGameSceneManager *GetGameSceneMgr();
};
