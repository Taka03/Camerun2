//*============================================================================
//GameSceneManager.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "GameSceneManager.h"
#include <fstream>

//=============================================================================
//namespace
//=============================================================================
namespace
{
	Math::Rect2DF ScreenRect( 0.0f, 0.0f, toF( SCREEN_WIDTH ), toF( SCREEN_HEIGHT ) );
}

//=============================================================================
//コンストラクタ
//=============================================================================
CGameSceneManager::CGameSceneManager( ) 
:   m_eSceneState( STATE_FADEOUT ),
	m_Color		( 0, 0, 0, 0 ),
	m_Time		( 0 ),
	m_TimeLast	( 0 ),
	m_pGameTitle( NULL ),
	m_pGameMain( NULL ),
	m_pPhotoCheck( NULL ),
	m_pResult( NULL ),
	m_pPause( NULL ),
	m_pNewComp( NULL )
{
	
	
	m_pGameTitle = new CSceneGameTitle( "SceneTitle.csv" );
	
	m_pGameMain = new CSceneGameMain( "SceneMain.csv" );
	
	m_pPhotoCheck = new CScenePhoto("ScenePhoto.csv");
	m_pResult = new CSceneResult("SceneResult.csv");
	m_pPause = new CScenePause( "ScenePause.csv" );
	
	m_pShowMission = new CSceneShowMission( "SceneShowMission.csv" );
	m_pNewComp = new CSceneNewComponent( "SceneNewComp.csv" );
	
	/*ステータスの読み込み*/
	LoadStatus();
	
	SetStateFunc( &CGameSceneManager::Title );
	SetRenderFunc( &CGameSceneManager::Title );
}

//=============================================================================
//デストラクタ
//=============================================================================
CGameSceneManager::~CGameSceneManager()
{
	SAFE_DELETE( m_pNewComp );
	SAFE_DELETE( m_pPause );
	SAFE_DELETE( m_pResult );
	SAFE_DELETE( m_pPhotoCheck );
	SAFE_DELETE( m_pGameMain );
	SAFE_DELETE( m_pGameTitle );

}

//=============================================================================
//タイトル関数
//=============================================================================
void CGameSceneManager::Title()
{
	if( m_pGameTitle->UpDate() == STATE_FINISH )
	{
		/*ゲームプレイの場合*/
		if( m_pGameTitle->GetSelectScene() == CSceneGameTitle::SELECT_GAME )
		{
			
			//CCommonObject::GetResMgr()->Get3DObject()->Init();
			//
			//GetWindowSpr()->Init();
			//
			//CCommonObject::GetResMgr()->Get2DObject()->Init();
			//
			
			SetFadeIn( 60, CColor( 255, 255, 255 ), &CGameSceneManager::GameMain );	
	
			GetBGM()->GetBGMDevice()->Stop();

				
			
		}
		
		/*チュートリアルの場合*/
		else if( m_pGameTitle->GetSelectScene() == CSceneGameTitle::SELECT_TUTORIAL )
		{
			/*チュートリアルフラグを立て直す*/
			SetTutorialFlag( true );
			
			//CCommonObject::GetResMgr()->Get3DObject()->Init();
			
			GetWindowSpr()->Init();
			
			//CCommonObject::GetResMgr()->Get2DObject()->Init();
			
	
			SetFadeIn( 60, CColor( 255, 255, 255 ), &CGameSceneManager::GameMain );		
			
			GetBGM()->GetBGMDevice()->Stop();

			
			
			//SetStateFunc( &CGameSceneManager::GameMain );
			//SetRenderFunc( &CGameSceneManager::GameMain );
		}
		
		/*終了の場合*/
		else
		{
			SetFadeOut( 60, CColor( 255, 255, 255 ), &CGameSceneManager::Exit );		
		
		}
	}
}


//=============================================================================
//ミッション表示関数
//=============================================================================
void CGameSceneManager::ShowMission()
{
	if( m_pShowMission->UpDate() == STATE_FINISH )
	{
		SetFadeIn( 60, CColor( 255, 255, 255 ), &CGameSceneManager::GameMain );

	}
}


//=============================================================================
//ゲームメイン関数
//=============================================================================
void CGameSceneManager::GameMain()
{
	
	if( m_pGameMain->UpDate() == STATE_FINISH )
	{
		/*それぞれの画面に移行*/
		switch( m_pGameMain->GetNextScene() )
		{
			/*写真確認画面の時*/
			case CSceneGameMain::SCENE_PHOTOCHECK:
			{
				SetFadeIn( 60, CColor( 255, 255, 255 ), &CGameSceneManager::PhotoCheck );		
				break;
			}
			
			/*ポーズ画面*/
			case CSceneGameMain::SCENE_PAUSE:
			{
				SetStateFunc( &CGameSceneManager::Pause );
				SetRenderFunc( &CGameSceneManager::Pause );
			
				break;
			}
			
			/*タイトル画面*/
			case CSceneGameMain::SCENE_TITLE:
			{
				SetFadeIn( 30, CColor( 255, 255, 255 ), &CGameSceneManager::Title );		
				break;
			}
			
			/*リザルト画面*/
			case CSceneGameMain::SCENE_RESULT:
			{
				SetFadeIn( 10, CColor( 255, 255, 255 ), &CGameSceneManager::Result );		
				GetBGM()->GetBGMDevice()->Stop();
				break;
			}
			
			//新要素追加画面
			case CSceneGameMain::SCENE_NEWELEM:
			{
				SetFadeIn( 10, CColor( 255, 255, 255 ), &CGameSceneManager::NewComp );	
				break;	
			}
		}
	}
	
}

//=============================================================================
//写真確認画面関数
//=============================================================================
void CGameSceneManager::PhotoCheck()
{
	if( m_pPhotoCheck->UpDate() == STATE_FINISH )
	{
		SetFadeIn( 10, CColor( 255, 255, 255 ), &CGameSceneManager::GameMain );		
		
		m_pPhotoCheck->SelectFuncExec();
		
		//SetStateFunc( &CGameSceneManager::GameMain );
		//SetRenderFunc( &CGameSceneManager::GameMain );
		
	}
}

//=============================================================================
//リザルト画面関数
//=============================================================================
void CGameSceneManager::Result()
{
	if( m_pResult->UpDate() == STATE_FINISH )
	{
		SetFadeIn( 10, CColor( 255, 255, 255 ), &CGameSceneManager::NewComp );		
		
	}
}

//=============================================================================
//新要素表示
//=============================================================================
void CGameSceneManager::NewComp()
{
	if( m_pNewComp->UpDate() == STATE_FINISH )
	{
		/*ステータスのセーブ*/
		SaveStatus();
		
		SetFadeIn( 60, CColor( 255, 255, 255 ), &CGameSceneManager::Title );
	}
}

//=============================================================================
// スタートメニュー
//=============================================================================
void CGameSceneManager::Pause(void)
{
	if( m_pPause->UpDate() == STATE_FINISH )
	{
		/*ゲームに戻るの場合*/
		if( m_pPause->GetSelectScene() == CScenePause::SCENE_RETURNGAME )
		{
			SetStateFunc( &CGameSceneManager::GameMain );
			SetRenderFunc( &CGameSceneManager::GameMain );
		}
		
		/*リトライの場合*/
		else if( m_pPause->GetSelectScene() == CScenePause::SCENE_RETRY )
		{
			m_pGameMain->SetState( &CSceneTemplate::Init );
			
			SetFadeIn( 10, CColor( 255, 255, 255 ), &CGameSceneManager::GameMain );		
		
		}
		
		/*タイトルに戻る場合*/
		else if( m_pPause->GetSelectScene() == CScenePause::SCENE_RETURNTITLE )
		{
			m_pGameMain->SetState( &CSceneTemplate::Init );
			
			SetFadeIn( 10, CColor( 0, 0, 0 ), &CGameSceneManager::Title );		
		}
	}
}

//=============================================================================
//終了
//=============================================================================
void CGameSceneManager::Exit()
{
	if( !IsFade())
	{
		/*終了*/
		CCommonObject::GetAppli()->GetCore()->Exit();
	}
}



//=============================================================================
//レンダリング
//=============================================================================
void CGameSceneManager::Rendering()
{
	/*描画処理*/
	( this->*m_pRenderFunc )();
	
}

//=============================================================================
//シーンの更新
//=============================================================================
//[return]
//	シーンの状態
//=============================================================================
eSceneState CGameSceneManager::UpDate()
{
	
	/*チュートリアル処理*/
	if( GetTutorialFlag() && !IsFade() )
	{
		TutorialExec();
	}
	
	/*ゲームの更新*/
	( this->*m_pStateFunc )();
	
	FadeExec();
	
	return m_eSceneState;
	
	
}

//=============================================================================
//ステータスのロード
//=============================================================================
void CGameSceneManager::LoadStatus( )
{
	#if defined( DEBUG ) | ( _DEBUG )	
	
		ifstream ifs( "save.dat", ios::in );
		
		/*ファイルがなかったら生成*/
		if( ifs.fail() )
		{
			ofstream out( "save.dat" );
			
			/*ハイスコアの設定*/
			out << "0" << std::endl;
			
			/*ゲーム初期起動フラグの設定*/
			out << "1" << std::endl;
			
			/*クリアカウントの設定*/
			out << "0" << std::endl;
			
		}
	#else
	
		ifstream ifs( "save.dat", ios::in | ios::binary );
	
		/*ファイルがなかったら生成*/
		if( ifs.fail() )
		{
			ofstream out( "save.dat" , ios::out |ios::binary );
			
			/*ハイスコアの設定*/
			out << "0" << std::endl;
			
			/*ゲーム初期起動フラグの設定*/
			out << "1" << std::endl;
			
			/*クリアカウントの設定*/
			out << "0" << std::endl;
			
			
		}
	
		
	#endif
	
		//-------------------------------------------------------
		//データの読み込み
		//-------------------------------------------------------
		int Key = 0;
		
		ifs >> Key;
		
		SetHiScore( Key );
		
		bool IsFirstFlag = true;
		
		ifs >> IsFirstFlag;

		SetFirstGameFlag( IsFirstFlag );
		
		ifs >> Key;
		
		SetClearCount( Key );
		
}

//=============================================================================
//ステータスのセーブ
//=============================================================================
void CGameSceneManager::SaveStatus( )
{
	#if defined( DEBUG ) | ( _DEBUG )	
		ofstream out( "save.dat" );
	#else
		ofstream out( "save.dat" , ios::out |ios::binary );
	#endif
	
	out << GetHiScore() << std::endl;
	out << GetFirstGameFlag() << std::endl;
	out << GetClearCount() << std::endl;
}

//=============================================================================
//フェードイン
//=============================================================================
void CGameSceneManager::FadeIn()
{
	m_Color.a = (Uint8)( ::Interpolation::Flat( 255L, 0L, m_TimeLast, m_Time ) );
	
	CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
	
	/*画面全体を覆う*/
	CCommonObject::GetAppli()->GetRenderer()->FillRect( ScreenRect, m_Color );
	
	//シーンをセット
	SetStateFunc( m_pStateFunc );
	SetRenderFunc( m_pStateFunc );
	
	// タイマー
	if ( ++m_Time > m_TimeLast )
	{
		
		m_eSceneState = STATE_FADEOUT;
		
	}
	
}

//=============================================================================
//フェードアウト
//=============================================================================
void CGameSceneManager::FadeOut()
{
	
	
	m_Color.a = (Uint8)( ::Interpolation::Flat( 0L, 255L, m_TimeLast, m_Time ) );
	
	CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
	
	/*画面全体を覆う*/
	CCommonObject::GetAppli()->GetRenderer()->FillRect( ScreenRect, m_Color );
	

	
	// タイマー＋
	if ( ++m_Time > m_TimeLast )
	{
		
		/*フェードイン*/
		//SetFadeIn( m_TimeLast, m_Color, m_pStateFunc );
		

		m_eSceneState = STATE_CONTINUE;
	}
}

//=============================================================================
//フェードインの設定
//=============================================================================
//[input]
//	Time:フェードイン時間
//	Color:描画する色
//	pStateFunc:ステートメソッド
//=============================================================================
void CGameSceneManager::SetFadeIn( Sint32 Time, CColor Color, void ( CGameSceneManager::*pStateFunc )() )
{
	m_eSceneState = STATE_FADEIN;
	m_Color = Color;
	m_TimeLast = Time;
	m_Time = 0;
	m_pStateFunc = pStateFunc;
}

//=============================================================================
//フェードアウトの設定
//=============================================================================
//[input]
//	Time:フェードアウト時間
//	Color:描画する色
//	pStateFunc:ステートメソッド
//=============================================================================
void CGameSceneManager::SetFadeOut( Sint32 Time, CColor Color, void ( CGameSceneManager::*pStateFunc )() )
{
	m_eSceneState = STATE_FADEOUT;
	m_Color = Color;
	m_TimeLast = Time;
	m_Time = 0;
	m_pStateFunc = pStateFunc;
}

//=============================================================================
//フェード中かどうか
//=============================================================================
Bool CGameSceneManager::IsFade()
{
	return m_eSceneState != STATE_CONTINUE;
}

//=============================================================================
//フェード処理
//=============================================================================
void CGameSceneManager::FadeExec()
{
	switch( m_eSceneState )
	{
		case STATE_CONTINUE:
		{
			break;
		}
		
		/*フェードイン*/
		case STATE_FADEIN:
		{
			FadeIn();
			break;
		}
		
		/*フェードアウト*/
		case STATE_FADEOUT:
		{
			FadeOut();
			break;
		}
	}
}

//=============================================================================
//スクリプトの処理
//=============================================================================
//[input]
//	strSource:分割対象の文字列
//[return]
//	strRet:表示させる文字列
//===========================================================================
string CGameSceneManager::ScriptExec( string strSource )
{
	
	string strRet;
	
	/*見つける文字列*/
	string strFind[] =
	{
		"Left",//左クリックの場合
		"Right",//右クリックの場合
		"Drag",//ドラッグの場合
		"Camera",//カメラ回転の場合
		"Reset",//カメラリセットの場合
		"Arrow",//矢印表示の場合
		"Score",//スコア説明の場合
		"Film",//フィルム説明の場合
		"TargetShow",//ターゲット表示の場合
		"DisTarget",//ターゲットの消去
		"Shoot",//ターゲットの撮影
		"Go",//ターゲットポイントに行く場合
		"Release",//リリースボタンを押した場合
		"Menu",//メニューボタンを押したとき
		"Catch",//キャッチマークを
		"End",//スクリプト終了
		"AddFunc",//カメラ回転機能追加
		"ReturnGame",//ゲームに戻る
		"Save",//写真保存時
		
	};
	
	ScriptFunc ScriptTbl[] = 
	{
		&CSceneGameMain::LeftClickScript,
		&CSceneGameMain::RightClickScript,
		&CSceneGameMain::DragScript,
		&CSceneGameMain::CameraRotScript,
		&CSceneGameMain::CameraResetScript,
		&CSceneGameMain::ArrowExpScript,
		&CSceneGameMain::ScoreExpScript,
		&CSceneGameMain::FilmExpScript,
		&CSceneGameMain::TargetShowScript,
		&CSceneGameMain::TargetClearScript,
		&CSceneGameMain::ShootTargetScript,
		&CSceneGameMain::TargetPlaceScript,
		&CSceneGameMain::ReleaseBtnScript,
		&CSceneGameMain::MenuScript,
		&CSceneGameMain::CatchExpScript,
		&CSceneGameMain::EndScript,
		&CSceneGameMain::AddFuncScript,
		
	};
	
	const int SCRIPT_MAX = 19;//スクリプト数
	
	int ScriptCount = 0;//スクリプトのカウント用
	
	for( int i = 0;i < SCRIPT_MAX;++i )
	{
		/*検索文字列*/
		string strSearch = strFind[i];
		
		/*検索文字列が現れる場所*/
		string::size_type index = strSource.rfind(strSearch);
		
		/*文字列一致*/
		if( index != string::npos )
		{
			/*余分な文字を消去*/
			strSource.erase( index, strSearch.length() );
			
			ScriptCount = 0;			
			
			/*写真保存時のとき*/
			if( i == SCRIPT_MAX - 1 )
			{ 
				m_pPhotoCheck->PhotoSaveScript();
			}
			
			/*ゲームに戻るのとき*/
			else if( i == SCRIPT_MAX - 2 )
			{
				m_pPause->PauseMenuScript();
			}
			
			/*その他の場合*/
			else
			{
				(m_pGameMain->*ScriptTbl[i])();
			}
		
		}
		
		else
		{
			ScriptCount++;
			
			if( ScriptCount == SCRIPT_MAX )
			{
				m_pGameMain->OtherScript();
			}
		}
		
		
	}
	
	strRet = strSource;
	
	
	return strRet;
}

//=============================================================================
//チュートリアル処理
//=============================================================================
void CGameSceneManager::TutorialExec()
{
	string strDraw;//描画文字列
	
	strDraw = ScriptExec( GetWindowSpr()->GetNowString() );
	
	GetWindowSpr()->GetTrlFont()->SetDrawString( strDraw );
	
}
