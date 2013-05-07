//*============================================================================
//ResourceManager.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "ResourceManager.h"
#include "LuaScript.h"

//=============================================================================
//variable
//=============================================================================
list< CResourceManager::ListData > CResourceManager::m_DrawList;
list< CResourceManager::ListData > CResourceManager::m_SoundList;



//============================================================================
//コンストラクタ
//============================================================================
CResourceManager::CResourceManager( ) 
: m_Page(0),
  m_eObjType( OBJ_DRAW )
{
	//m_pGameObj = new CGameObject();
	//m_pSoundObj = new CSoundObject();
	//m_p3DObj = new CDraw3DObject();
	//m_p2DObj = new CDraw2DObject();
	
	//memset( m_pQueTop, NULL, QUE_MAX );
	
	for( int i = 0;i < QUE_MAX;++i )
	{
		m_pQueTop[i] = NULL;
	}
	
	m_DrawList.clear();
	
	/*スレッドの作成*/
	m_Thread.Create( LoadProc, (void*)this );
	
	
	printf("BOOT ResourceManager\n");
}	

//============================================================================
//デストラクタ
//============================================================================
CResourceManager::~CResourceManager()
{
	printf("ABORT ResourceManager\n");
	
	/*終了*/
	m_Event.Set();
	
	/*スレッドの終了待ち*/
	while( !m_Thread.WaitForExit() )
	{
		Sleep( 100 );
	}
	
	vector< string > strRemoveObj;
	vector< string > strRemoveSound;
	
	//消去オブジェクトリストの取得
	for( list< ListData >::iterator it = m_DrawList.begin();it != m_DrawList.end();++it )
	{
		string strTemp = it->m_strDataName;
		
		strRemoveObj.push_back( strTemp );
	}
	
	//消去サウンドオブジェクトの取得
	for( list< ListData >::iterator it = m_SoundList.begin();it != m_SoundList.end();++it )
	{
		string strTemp = it->m_strDataName;
		
		strRemoveSound.push_back( strTemp );
	}
	
	//描画リストの消去
	for( Uint32 i = 0;i < strRemoveObj.size();++i )
	{
		RemoveObject( strRemoveObj.at( i ).c_str() );
	}
	
	//サウンドリストの消去
	for( Uint32 i = 0;i < strRemoveSound.size();++i )
	{
		RemoveSound( strRemoveSound.at( i ).c_str() );
	}
	
	printf("EXIT ResourceManager\n");
	
}

//============================================================================
//オブジェクトの取得
//============================================================================
//[input]
//	pName:データ名
//[return]
//	取得したオブジェクト
//===========================================================================
CGameObject *CResourceManager::FindObject( const char *pName )
{
	for( list< ListData >::iterator it = m_DrawList.begin();it != m_DrawList.end();++it )
	{
		string strName = it->m_strDataName;
		
		//一致したらそのオブジェクトを返す
		if( strName.compare( pName ) == 0 )
		{
			return it->m_pGameobj;
		}
	}
		 
	//_ASSERT(
	//
	return NULL;
}

//============================================================================
//音オブジェクトの取得
//============================================================================
//[input]
//	pName:データ名
//[return]
//	取得した音オブジェクト
//===========================================================================
CGameObject *CResourceManager::FindSoundObj( const char *pName )
{
	for( list< ListData >::iterator it = m_SoundList.begin();it != m_SoundList.end();++it )
	{
		string strName = it->m_strDataName;
		
		//一致したらそのオブジェクトを返す
		if( strName.compare( pName ) == 0 )
		{
			return it->m_pGameobj;
		}
	}
		 
	//_ASSERT(
	//
	return NULL;
}



//============================================================================
//オブジェクトのリスト追加
//============================================================================
//[input]
//	pDataName:データ名
//	pGameObj:ゲームオブジェクト
//===========================================================================
void CResourceManager::AppendList( string strDataName, CGameObject *pGameObj )
{
	static Uint32 priority = 0;
	
	ListData liData;
	
	liData.m_strDataName = strDataName;
	liData.m_pGameobj = pGameObj;
	liData.m_Priority = priority;
	
	//描画オブジェクトのとき
	if( m_eObjType == OBJ_DRAW )
	{	
		m_DrawList.push_back( liData );
	}
	
	//音オブジェクトのとき
	else if( m_eObjType == OBJ_SND )
	{
		m_SoundList.push_back( liData );
	}
	
	pGameObj->Init();
	
	
	
	priority++;
	
}


//============================================================================
//オブジェクトの消去
//============================================================================
//[input]
//	pDataName:データ名
//============================================================================
void CResourceManager::RemoveObject( const char *pDataName )
{
	list< ListData >::iterator it = m_DrawList.begin();
	
	for( it = m_DrawList.begin();it != m_DrawList.end(); )
	{
		//一致したらそのオブジェクトを消去
		if( it->m_strDataName.compare( pDataName ) == 0 )
		{
			SAFE_DELETE( it->m_pGameobj );
			
			//リストから消去
			it = m_DrawList.erase( it );
			
			continue;
		}
		
		++it;
	}
}

//============================================================================
//サウンドオブジェクトの消去
//============================================================================
//[input]
//	pDataName:データ名
//============================================================================
void CResourceManager::RemoveSound( const char *pDataName )
{
	list< ListData >::iterator it = m_SoundList.begin();
	
	for( it = m_SoundList.begin();it != m_SoundList.end(); )
	{
		//一致したらそのオブジェクトを消去
		if( it->m_strDataName.compare( pDataName ) == 0 )
		{
			SAFE_DELETE( it->m_pGameobj );
			
			//リストから消去
			it = m_SoundList.erase( it );
			
			continue;
		}
		
		++it;
	}
}


//============================================================================
//オブジェクトの消去
//============================================================================
//[input]
//	pRemObj:消去対象オブジェクト
//============================================================================
void CResourceManager::RemoveObject( CGameObject *pRemObj )
{
	list< ListData >::iterator it = m_DrawList.begin();
	
	for( it = m_DrawList.begin();it != m_DrawList.end(); )
	{
		//一致したらそのオブジェクトを消去
		if( it->m_pGameobj == pRemObj )
		{
			SAFE_DELETE( it->m_pGameobj );
			
			//リストから消去
			it = m_DrawList.erase( it );
			
			continue;
		}
		
		++it;
	}
}




//============================================================================
//オブジェクトの追加
//============================================================================
//[input]
//	pFile:追加するデータ
//===========================================================================
void CResourceManager::Push ( CFileData *pFile )
{
	/*終了処理発生した?*/
	if( m_Event.IsSignal() )
	{
		return;
	}
	
	//オートロック
	Thread::CAutoLock Lock( m_CS );
	
	/*先頭*/
	if( m_pQueTop[m_Page] == NULL )
	{
		m_pQueTop[m_Page] = pFile;
	}
	
	/*リストの追加*/
	else
	{
		CFileData *pData = m_pQueTop[m_Page];
		
		while( pData->GetNext() != NULL )
		{
			pData = pData->GetNext();
		}
		
		pData->SetNext( pFile );
	}
	
	pFile->SetNext( NULL );
	
	printf("CResourceManager :PUSH [%s]\n", pFile->GetFileName().c_str() );
	
}



//============================================================================
//読み込み中かどうか判定
//============================================================================
Bool CResourceManager::IsLoading()
{
	//オートロック
	Thread::CAutoLock Lock( m_CS );
	
	if( m_pQueTop[0] != NULL )
	{
		return true;
	}
	
	if( m_pQueTop[1] != NULL )
	{
		return true;
	}
	
	return false;
}


//============================================================================
//起動
//============================================================================
void CResourceManager::Run()
{
	for(;;)
	{
		CFileData *pFile = NULL;
		Sint32 ActivePage = -1;
		
		/*終了チェック*/
		if( m_Event.IsSignal() )
		{
			break;
		}
		
		/*今回取得するリストを取得*/
		m_CS.Enter();
		
		/*これから処理するページ*/
		ActivePage = m_Page;
		
		/*ページ切り替え*/
		m_Page = 1 - m_Page;
		
		/*先頭を取得*/
		pFile = m_pQueTop[ActivePage];
		
		m_CS.Leave();
		
		if( pFile == NULL )
		{
			::Sleep( 250 );
			
			continue;
		}
		
		while( pFile != NULL )
		{
			/*リソースタイプを判別*/
			CheckType( pFile );
			
			/*次を取得*/
			CFileData *pNext = pFile->GetNext();
			
			/*現在のものを削除*/
			delete pFile;
			
			pFile = pNext;
			
		}
		
		/*ゲームデータの読み込み*/
		//m_pGameObj->Load( m_pRender, m_pFileMgr );
		
		/*2Dデータの読み込み*/
		//m_p2DObj->Load( m_pRender, m_pFileMgr );
		
		/*3Dデータの読み込み*/
		//m_p3DObj->Load( m_pRender, m_pFileMgr );
		
		/*音声の読み込み*/
		//m_pSoundObj->LoadSound( m_pCore, m_pFileMgr );
		
		/*リスト初期化*/
		m_pQueTop[ActivePage] = NULL;
		
	}
	
	//----------------------------------------------------------------------------
	//キューの中身をクリア
	//----------------------------------------------------------------------------
	for( Sint32 i = 0;i < QUE_MAX;++i )
	{
		CFileData *pFile = m_pQueTop[i];
		
		while( pFile != NULL )
		{
			CFileData *pNext = pFile->GetNext();
			delete pFile ;
			pFile = pNext;
		}
		
		m_pQueTop[i] = NULL;
	}

	
}

//============================================================================
//タイプの判別
//============================================================================
//[input]
//	pFile:判定するデータ
//===========================================================================
void CResourceManager::CheckType( CFileData *pFile )
{
	string strDataName[] =
	{
		"SPRITE",
		"PHOTO",
		"MINIMAP",
		"CAMBUTTON",
		"MENU",
		"WINDOW",
		"FONT",
		"SOUND",
		"BGM",
		"FIELD",
		"FONT3D",
		"SPRITE3D",
		"CHARACTER",
		"PLAYER",
		"TRAIN",
		"AMEUS",
		"MANTA",
		"BIRD",
		"MOUSE",
		"RABBIT",
		"LIZARD",
		"CAR",
		"FOUNT",
		"SKY",
	};
	
	CreateFunc CreateTbl[] =
	{
		&CResourceManager::CreateSprite,
		&CResourceManager::CreatePhoto,
		&CResourceManager::CreateMiniMap,
		&CResourceManager::CreateCamButton,
		&CResourceManager::CreateMenu,
		&CResourceManager::CreateExpWindow,
		&CResourceManager::CreateFontSprite,
		&CResourceManager::CreateSound,
		&CResourceManager::CreateBGM,
		&CResourceManager::CreateField,
		&CResourceManager::CreateFontSprite3D,
		&CResourceManager::CreateSprite3D,
		&CResourceManager::CreateCharacter,
		&CResourceManager::CreatePlayer,
		&CResourceManager::CreateTrain,
		&CResourceManager::CreateAmeus,
		&CResourceManager::CreateManta,
		&CResourceManager::CreateBird,
		&CResourceManager::CreateMouse,
		&CResourceManager::CreateRabbit,
		&CResourceManager::CreateLizard,
		&CResourceManager::CreateCar,
		&CResourceManager::CreateFount,
		&CResourceManager::CreateSkyObj,
	};		
	
	
	int Count = 0;

	for( int i = 0;i < CFileData::RESOURCE_MAX;++i )
	{
		
		string strTemp = pFile->GetTypeName();
		
		string strData = strDataName[i];
		
		if( strTemp.compare( strDataName[i] ) == 0 )
		{
			(this->*CreateTbl[i])( pFile );
			
			break;
		}
		
	}
	
}

//****************************************************************************
//ここからリソースの作成
//****************************************************************************

//============================================================================
//スプライトの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//===========================================================================
void CResourceManager::CreateSprite( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	Math::Vector2D vPos( pFile->GetPosition().x, pFile->GetPosition().y );
	
	CSprite *pSpr = new CSprite( pFile->GetFileName().c_str(), vPos, pFile->GetDivNum() );
	
	pSpr->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pSpr );
}

//============================================================================
//写真スプライトの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//===========================================================================
void CResourceManager::CreatePhoto( CFileData *pFile )
{
	
	m_eObjType = OBJ_DRAW;
	
	Math::Vector2D vPos( pFile->GetPosition().x, pFile->GetPosition().y );
	
	CPhoto *pPhoto = new CPhoto( pFile->GetFileName().c_str(), vPos, pFile->GetVecPhotoData() );
	
	pPhoto->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pPhoto );
}

//============================================================================
//ミニマップの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//===========================================================================
void CResourceManager::CreateMiniMap( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	
	Math::Vector2D vPos( pFile->GetPosition().x, pFile->GetPosition().y );
	
	CMiniMap *pMiniMap =  new CMiniMap( pFile->GetFileName().c_str(), vPos );
	
	pMiniMap->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pMiniMap );
}

//============================================================================
//カメラボタンの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//===========================================================================
void CResourceManager::CreateCamButton( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	
	Math::Vector2D vPos( pFile->GetPosition().x, pFile->GetPosition().y );
	
	CCamButton *pCamBtn = new CCamButton( pFile->GetFileName().c_str(), vPos );
	
	pCamBtn->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pCamBtn );	
}

//============================================================================
//メニューの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//===========================================================================
void CResourceManager::CreateMenu( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	Math::Vector2D vPos( pFile->GetPosition().x, pFile->GetPosition().y );
	
	CMenu *pMenu = new CMenu( pFile->GetFileName().c_str(), vPos, CCommonObject::GetAppli()->GetCore()->GetMouse() );
	
	pMenu->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pMenu );	
}

//============================================================================
//ウィンドウの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//===========================================================================
void CResourceManager::CreateExpWindow( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	
	Math::Vector2D vPos( pFile->GetPosition().x, pFile->GetPosition().y );
	
	CExpWindow *pExpWindow = new CExpWindow( pFile->GetFileName().c_str(), vPos );
	
	pExpWindow->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pExpWindow );	
}

//============================================================================
//フォントスプライトの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//===========================================================================
void CResourceManager::CreateFontSprite( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	Math::Vector2D vPos( pFile->GetPosition().x, pFile->GetPosition().y );
	
	CFontSprite *pFontSpr = new CFontSprite( pFile->GetFileName().c_str(), vPos );
	
	pFontSpr->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pFontSpr );	
}

//============================================================================
//効果音の生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//===========================================================================
void CResourceManager::CreateSound( CFileData *pFile )
{
	m_eObjType = OBJ_SND;
	
	CSoundEffect *pSnd = new CSoundEffect( pFile->GetFileName().c_str() );
	
	pSnd->LoadSound( CCommonObject::GetAppli()->GetCore(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pSnd );	
}

//============================================================================
//BGMの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//===========================================================================
void CResourceManager::CreateBGM( CFileData *pFile )
{
	m_eObjType = OBJ_SND;
	
	CBGM *pSnd = new CBGM( pFile->GetFileName().c_str() );
	
	pSnd->LoadSound( CCommonObject::GetAppli()->GetCore(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pSnd );	
}

//============================================================================
//フィールドの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//===========================================================================
void CResourceManager::CreateField( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CField *pField = new CField( pFile->GetFileName().c_str(), pFile->GetPosition() );
	
	pField->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pField );	

}

//============================================================================
//3Dフォントスプライトの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//===========================================================================
void CResourceManager::CreateFontSprite3D( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CFontSprite3D *pFontSpr3D = new CFontSprite3D( pFile->GetFileName().c_str(), pFile->GetPosition() );
	
	pFontSpr3D->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pFontSpr3D );	

}

//============================================================================
//3Dスプライトの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//===========================================================================
void CResourceManager::CreateSprite3D( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CSprite3D *pSpr3D = new CSprite3D( pFile->GetFileName().c_str(), pFile->GetPosition() );
	
	pSpr3D->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pSpr3D );	

}

//============================================================================
//キャラクターの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//============================================================================
void CResourceManager::CreateCharacter( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CCharacter *pChara = new CCharacter( pFile->GetFileName().c_str(), pFile->GetPosition() );
	
	pChara->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pChara );	
}


//============================================================================
//プレイヤーの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//===========================================================================
void CResourceManager::CreatePlayer( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CPlayer *pPlayer = new CPlayer( pFile->GetFileName().c_str(), pFile->GetPosition() );
	
	pPlayer->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pPlayer );	
}

//============================================================================
//電車の生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//===========================================================================
void CResourceManager::CreateTrain( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CTrain *pTrain = new CTrain( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pTrain->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pTrain );	
}

//============================================================================
//アメウスの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//============================================================================
void CResourceManager::CreateAmeus( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemyAmeus *pAmeus = new CEnemyAmeus( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pAmeus->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pAmeus );	
}

//============================================================================
//マンタの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//============================================================================
void CResourceManager::CreateManta( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemyManta *pManta = new CEnemyManta( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pManta->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pManta );	
}

//============================================================================
//トリの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//============================================================================
void CResourceManager::CreateBird( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemyBird *pBird = new CEnemyBird( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pBird->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pBird );	
}

//============================================================================
//ネズミの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//============================================================================
void CResourceManager::CreateMouse( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemyMouse *pMouse = new CEnemyMouse( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pMouse->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pMouse );	
}

//============================================================================
//ウサギの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//============================================================================
void CResourceManager::CreateRabbit( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemyRabbit *pRabbit = new CEnemyRabbit( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pRabbit->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pRabbit );	
}

//============================================================================
//トカゲの生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//============================================================================
void CResourceManager::CreateLizard( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemyLizard *pLizard = new CEnemyLizard( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pLizard->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pLizard );	
}

//============================================================================
//車の生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//============================================================================
void CResourceManager::CreateCar( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemyCar *pCar = new CEnemyCar( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pCar->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pCar );	
}

//============================================================================
//噴水の生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//============================================================================
void CResourceManager::CreateFount( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemyFountObj *pFountObj = new CEnemyFountObj( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pFountObj->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pFountObj );	
}

//============================================================================
//空中庭園の生成
//============================================================================
//[input]
//	pFile:ファイルデータ
//============================================================================
void CResourceManager::CreateSkyObj( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemySkyObj *pSkyObj = new CEnemySkyObj( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pSkyObj->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//リストへの追加
	AppendList( pFile->GetDataName(), pSkyObj );	
}

//****************************************************************************
//ここまでリソースの作成
//****************************************************************************


//============================================================================
//ロード用スレッド
//============================================================================
//[input]
//	pData:
//===========================================================================
void CResourceManager::LoadProc( void *pData )
{
	//使用するCPU番号
	System::SetThreadCPUNo( 1 );
	
	//起動
	( (CResourceManager*)pData)->Run();
	
	//if( !m_IsLoading )
	//{
	//	::ExitThread( 0 );
	//}
}



					
									


