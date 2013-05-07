//*============================================================================
//ResourceManager.h
//*============================================================================
//[history]
//	08/10/01　作成
//[author]
//	Taka
//[ref]
//	SeleneSampleコード
//=============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Application.h"
#include "SceneManager.h"
#include "FileData.h"

#include <list>

//=============================================================================
//const
//=============================================================================
const int QUE_MAX = 2;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	リソース管理クラス
//============================================================================
class CResourceManager
{
	public:
	
		//リストデータ
		struct ListData
		{
			Uint32 m_Priority;//順番
			string m_strDataName;//管理名称
			CGameObject *m_pGameobj;//オブジェクトのポインタ
		};
		
		//オブジェクトタイプ
		enum eObjType
		{
			OBJ_DRAW,//描画オブジェクト
			OBJ_SND,//サウンドオブジェクト
		};
	
	private:
		
		CGameObject *m_pGameObj;//ゲーム用オブジェクト
		CDraw3DObject *m_p3DObj;//3Dオブジェクト
		CDraw2DObject *m_p2DObj;//2Dオブジェクト
		CSoundObject	*m_pSoundObj;//サウンド用オブジェクト
		
		Thread::CThread m_Thread;
		Thread::CCriticalSection m_CS;
		Thread::CEvent m_Event;
		
		CFileData *m_pQueTop[QUE_MAX];
		Sint32 m_Page;
		
		eObjType m_eObjType;//オブジェクトタイプ
		
		//描画リスト
		static list< ListData > m_DrawList;
		
		//効果音リスト
		static list< ListData > m_SoundList;
		
	private:
	
		/*生成メソッド*/
		typedef void (CResourceManager::*CreateFunc)( CFileData *pFile );
	
	
		//起動
		virtual void Run();
		
		//ロード用スレッド
		static void LoadProc( void *pData );
	
	public:	
	
		//コンストラクタ
		CResourceManager( );
		
		//デストラクタ
		virtual ~CResourceManager();
		
		/*リソースの追加*/
		virtual void Push( CFileData *pFile );
		
		//オブジェクトの取得
		CGameObject *FindObject( const char *pName );
		
		//音オブジェクトの取得
		CGameObject *FindSoundObj( const char *pName );
		
		//オブジェクトの削除
		void RemoveObject( const char *pDataName );
		
		//オブジェクトの削除
		void RemoveObject( CGameObject *pRemObj );
		
		//サウンドオブジェクトの消去
		void RemoveSound( const char *pDataName );
		
		/*ロード中*/
		virtual Bool IsLoading();
		
		
	private:
	
		
		//リストへ追加
		void AppendList( string strDataName, CGameObject *pGameObj );
		
		/*タイプの判定*/
		void CheckType( CFileData *pFile );
		
	private:
	
		//スプライトの生成
		void CreateSprite( CFileData *pFile );
		
		//写真スプライトの生成
		void CreatePhoto( CFileData *pFile );
		
		//ミニマップの生成
		void CreateMiniMap( CFileData *pFile );
		
		//カメラボタンの生成
		void CreateCamButton( CFileData *pFile );
		
		//メニューの生成
		void CreateMenu( CFileData *pFile );
		
		//ウィンドウの生成
		void CreateExpWindow( CFileData *pFile );
		
		//フォントスプライトの生成
		void CreateFontSprite( CFileData *pFile );
		
		//効果音の生成
		void CreateSound( CFileData *pFile );
		
		//BGMの生成
		void CreateBGM( CFileData *pFile );
		
		//フィールドの生成
		void CreateField( CFileData *pFile );
		
		//3Dフォントスプライトの生成
		void CreateFontSprite3D( CFileData *pFile );
		
		//3Dスプライトの生成
		void CreateSprite3D( CFileData *pFile );
		
		//キャラクターの生成
		void CreateCharacter( CFileData *pFile );
		
		//プレイヤーの生成
		void CreatePlayer( CFileData *pFile );
		
		//電車の生成
		void CreateTrain( CFileData *pFile );
		
		//アメウスの生成
		void CreateAmeus( CFileData *pFile );
		
		//マンタの生成
		void CreateManta( CFileData *pFile );
		
		//トリの生成
		void CreateBird( CFileData *pFile );
		
		//ネズミの生成
		void CreateMouse( CFileData *pFile );
		
		//ウサギの生成
		void CreateRabbit( CFileData *pFile );
		
		//トカゲの生成
		void CreateLizard( CFileData *pFile );
		
		//車の生成
		void CreateCar( CFileData *pFile );
		
		//噴水の生成
		void CreateFount( CFileData *pFile );
		
		//空中庭園の生成
		void CreateSkyObj( CFileData *pFile );
	
	public:		
		
		/*ゲーム用オブジェクトの取得*/
		CGameObject *GetGameObject() const
		{
			return m_pGameObj;
		}
		
		/*2D用オブジェクトの取得*/
		CDraw2DObject *Get2DObject() const
		{
			return m_p2DObj;
		}
		
		/*3D用オブジェクトの取得*/
		CDraw3DObject *Get3DObject() const
		{
			return m_p3DObj;
		}

		/*サウンド用オブジェクトの取得*/
		CSoundObject *GetSoundObject() const
		{
			return m_pSoundObj;
		}
		
		//描画リストの取得
		list< ListData > GetDrawList()
		{
			return m_DrawList;
		}
		
};

