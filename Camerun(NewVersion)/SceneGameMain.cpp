//*============================================================================
//SceneGameMain.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneGameMain.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>

//=============================================================================
//using
//=============================================================================
using namespace std;

//=============================================================================
//namespace
//=============================================================================
namespace 
{
	int time = 0;
	float fMoveDistance = 0.0f;//矢印の距離
	Sint32 MoveAngle = 0;//矢印の向いている位置	
	Math::Vector3D vMousePos( 0, 0, 0 );
	Math::Vector3D vOldMousePos( 0, 0, 0 );
	Math::Vector3D vMovePos( 0, 0, 0 );//移動位置
	Math::Vector3D vTargetPos( 0, 0, 0 );
	Uint32 TutorialCount = 0;
	const int TIME_MAX = 60 * 3;
	int TotalScore = 0;//合計スコア
	int count = 0;//内部カウンター
	int MarkerIdx = 0;//マーカーカウンター
	int ShowEnemyCount = 0;//敵表示カウント
	int AddFuncCount = 0;//追加機能カウント
	int ShootEnemyCount = 0;//敵の写真に映っている数
	vector< CPhoto::PhotoCheckData > vecPhotoData;//写真判定データ
	
	const int LOCKON_MAX = 3;//ロックオンの最大数
	bool IsAddEnemy[CSceneGameMain::ELEM_MAX - 2];
	
	vector< string > vecStr;
	
	int CamCnt = 0;//カメラ用カウンタ

}

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	strFileName:ファイル名
//=============================================================================
CSceneGameMain::CSceneGameMain( string strFileName )
: m_eNextScene( SCENE_PHOTOCHECK ),
  m_eTrlScene( SCENE_START ),
  CSceneTemplate( strFileName ),
  m_pPlayer(NULL),
  m_pTrlField(NULL),
  m_pField(NULL),
  m_pTrain(NULL),
  m_pAmeus(NULL),
  m_pManta(NULL),
  m_pMarkerSpr(NULL),
  m_pMenuBtnSpr(NULL),
  m_pTargetArrow(NULL),
  m_pArrow(NULL),
  m_pReleaseBtnSpr(NULL),
  m_pMouseSpr( NULL ),
  m_pFountObj( NULL ),
  m_pIsLand( NULL ),
  m_eMouseSprState( MOUSE_PUSHNONE )
  
{
	
	#if defined (CAM_TOOL)
	
	m_vecMarker.clear();
		
	for( int i = 0;i < MARKER_MAX;++i )
	{	
		char Temp[20];
		
		sprintf_s( Temp, 20, "VecMarker%d", i );
		
		CCommonObject::GetResMgr()->Push( new CFileData( "pointa.bmp", Temp, "SPRITE3D", Math::Vector3D( 0, 0, 0 ) ) );
		
	}
	
	#else
	
	#endif
	
	memset( IsAddEnemy, false, sizeof( bool ) * ( ELEM_MAX - 2 ) );
	
	//フォントの設定
	CCommonObject::GetAppli()->GetRenderer()->SetDrawTextFont( "MS ゴシック", 60, 2 );
}

//=============================================================================
//デストラクタ
//=============================================================================
CSceneGameMain::~CSceneGameMain(void)
{
}

//=============================================================================
//オブジェクトデータの初期化
//=============================================================================
//[input]
//	dt:時間の増加間隔
//=============================================================================
void CSceneGameMain::InitObjectData( Uint32 dt )
{
	if( !CCommonObject::GetResMgr()->IsLoading() )
	{
		#if defined( CAM_TOOL )
		
			SetFirstGameFlag( false );
		
		#endif
		
		string strObjList[] =
		{
			"Player",
			"Train",
			"Ameus",
			"Arrow",
			"FountObj",
			"IsLand",
			"Manta1",
			"Manta2",
			"Manta3",
			"Bird1",
			"Bird2",
			"Rabbit1",
			"Rabbit2",
			"Rabbit3",
			"Rabbit4",
			"Rabbit5",
			"Rabbit6",
			"Rabbit7",
			"Rabbit8",
			"Rabbit9",
			"Rabbit10",
			"Car1",
			"Car2",
			"Car3",
			"Car4",
		};
		
		const int OBJ_NUM = 24;
		
		for( int i = 0;i < OBJ_NUM;++i )
		{
			
			CDraw3DObject *pObj = dynamic_cast<CDraw3DObject *>( 
								  CCommonObject::GetResMgr()->FindObject( strObjList[i].c_str() ) );
			
			m_vec3DList.push_back( pObj );
		}
		
		
		
		m_pPlayer = dynamic_cast<CPlayer *>( CCommonObject::GetResMgr()->FindObject("Player") );
		m_pTrlField	= dynamic_cast<CField *>( CCommonObject::GetResMgr()->FindObject("TutorialMap") );
		
		m_pTrain = dynamic_cast<CTrain *>( CCommonObject::GetResMgr()->FindObject("Train") );		
		m_pAmeus = dynamic_cast<CEnemyAmeus *>( CCommonObject::GetResMgr()->FindObject("Ameus") );
		//m_pManta = dynamic_cast<CEnemyManta *>( CCommonObject::GetResMgr()->FindObject("Manta") );	
		m_pRabbit = dynamic_cast<CEnemyRabbit *>( CCommonObject::GetResMgr()->FindObject("Rabbit1") );	
		
		m_pArrow = dynamic_cast<CCharacter *>( CCommonObject::GetResMgr()->FindObject("Arrow") );		
		//m_pTargetArrow = dynamic_cast<CCharacter *>( CCommonObject::GetResMgr()->FindObject("Target") );
		m_pFountObj = dynamic_cast<CCharacter *>( CCommonObject::GetResMgr()->FindObject("FountObj") );
		m_pIsLand = dynamic_cast<CCharacter *>( CCommonObject::GetResMgr()->FindObject("IsLand") );
		
		
		m_pMiniMap = dynamic_cast<CMiniMap *>( CCommonObject::GetResMgr()->FindObject("MiniMap") );	
		m_pMiniTarget = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("MiniTarget") );	
		
		m_pMouseSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("MouseBtn") );	
		
		m_pMarkerSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("Marker") );	
		m_pMoveArrowSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("MoveArrow") );
		m_pReleaseBtnSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("Release") );				
		m_pMenuBtnSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("MenuBtn") );
		m_pArrowExpSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("ArrowExp") );
		m_pReadySpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("Ready") );
		m_pGoSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("Go") );
		m_pEndSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("EndPhoto") );
		
		const char *strFont[] =
		{
			"ScoreFont",
			"FilmFont",
		};
		
		m_pMissionWinSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("MissionWindow") );	
		
		for( int i = 0;i < OPTION_MAX;++i )
		{	
			m_pNumFont[i] = dynamic_cast<CFontSprite *>( CCommonObject::GetResMgr()->FindObject( strFont[i] ) );
		}
		
		m_pCamPointaSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("CamPointa") );
		
		m_pGameMusic = dynamic_cast<CBGM *>( CCommonObject::GetResMgr()->FindSoundObj("GameBGM") );
		m_pTrlMusic =  dynamic_cast<CBGM *>( CCommonObject::GetResMgr()->FindSoundObj("TrlBGM") );
		
		#if defined( CAM_TOOL )
			for( int i = 0;i < MARKER_MAX;++i )
			{	
				char Temp[20];
				
				sprintf_s( Temp, 20, "VecMarker%d", i );
				
				MarkData mark;
				
				mark.m_pMarker = dynamic_cast<CSprite3D *>( CCommonObject::GetResMgr()->FindObject( Temp ) );
				mark.m_IsSet = false;
				
				m_vecMarker.push_back( mark );
			}
		#else
		
		#endif
		
		CSprite *pCloud = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("Cloud") );
		
		for( int i = 0;i < SCREEN_MAX;++i )
		{
			/*スカイドームの作成*/
			CCommonObject::GetSceneMgr(i)->CreateSkyDoom( pCloud->GetTexture() );
		}
		
		CCommonObject::GetResMgr()->RemoveObject( pCloud );
		
		/*2Dオブジェクトの追加*/
		Push2DObject();
		
		//レンダラーの設定
		m_pMiniMap->SetRenderer( CCommonObject::GetAppli()->GetRenderer() );
		
		/*分割数の設定*/
		m_pMouseSpr->SetDivNumX( 4 );
		
		m_pCamPointaSpr->SetVisibleFlag( false );
		
		//m_pCamPointaSpr->SetDivNumX( 2 );
		
		m_pReleaseBtnSpr->SetDivNumX( 3 );
		
		m_pMenuBtnSpr->SetDivNumX( 2 );
		
		CFileLoader FileLoader;
		
		CCommonObject::GetAppli()->GetFileMgr()->SetCurrentPath( "Text" );
		
		File::IResourceFile *pResFile = CCommonObject::GetAppli()->GetFileMgr()->FileOpen( "ShowEnemy.txt" );
		
		FileLoader.Load( pResFile->GetNamePointer() );
		
		SAFE_RELEASE( pResFile );
		
		vector< string > strList = FileLoader.GetStrList();
		
		vector< string >::iterator it = strList.begin();
		
		for( it = strList.begin(); it != strList.end();++it )
		{
			string strEnemyName = *it;
			
			CEnemy *pEnemy = dynamic_cast<CEnemy *>
							( CCommonObject::GetResMgr()->FindObject( strEnemyName.c_str() ) );
			
			m_pVecCatchEnemy.push_back( pEnemy );
		}
		
		SetTargetEnemy();
		
		
		/*チュートリアル用の敵*/
		CEnemy *pTrlEnemy[] =
		{
			m_pRabbit,//マンタ(本当はうさぎ)
			m_pAmeus,//アメウス
		};
		
		memcpy( m_pTrlEnemy, pTrlEnemy, sizeof( CEnemy *) * TRL_ENEMY_NUM );	
		
		m_pReadySpr->SetVisibleFlag( false );
		m_pGoSpr->SetVisibleFlag( false );
		m_pEndSpr->SetVisibleFlag( false );
		m_pMiniTarget->SetVisibleFlag( false );
		
		SetTargetExistFlag( false );
		
		SetState( &CSceneTemplate::Init );
	}
}


//=============================================================================
//初期化
//=============================================================================
//[input]
//	dt:時間の増加間隔
//=============================================================================
void CSceneGameMain::Init( Uint32 dt )
{
	printf("[GameMain]::Init\n");
	
	m_eSceneState = STATE_CONTINUE;
	
	m_pEndSpr->SetVisibleFlag( false );

	m_pField = dynamic_cast<CField *>( CCommonObject::GetResMgr()->FindObject("Field") );
	
	m_pTrlField->SetVisibleFlag( false );
	
	m_IsDemo = true;
	
	m_pPlayer->SetStopFlag( true );
	
	SetStopFlagAll( true );
	
	//オブジェクトの初期化
	InitAll();
	
	/*オブジェクトの初期化*/
	//CCommonObject::GetResMgr()->Get3DObject()->Init();
	//
	//CCommonObject::GetResMgr()->Get2DObject()->Init();
	//
	/*カメラの初期化*/
	for( int i = 0;i < SCREEN_MAX;++i )
	{
		CCommonObject::GetCamera( i )->Init();
	}
	
	/*フィルム枚数の初期化*/
	SetFilmCount( 0 );
	
	SetTotalScore( 0 );
	
	m_pField->SetRotate( Math::Point3DI( 0, 0, 0 ) );
	
	SetFingState( FING_NONE );
	
	LoadMission();//ミッションのロード	
	
	/*チュートリアルモードの場合*/
	if( GetTutorialFlag() )
	{
		InitTutorial();
	}
	
	else
	{
		InitMain();
	}
	
	vecPhotoData.clear();
	
	TotalScore = 0;
	
	time = 0;
	
	CamCnt = 0;
	
	m_pReadySpr->SetVisibleFlag( false );
	m_pGoSpr->SetVisibleFlag( false );

	
		
	SetState( &CSceneTemplate::Idle );
}

//=============================================================================
//待機中
//=============================================================================
//[input]
//	dt:時間の増加間隔
//=============================================================================
void CSceneGameMain::Idle( Uint32 dt )
{
	m_eSceneState = STATE_CONTINUE;
	
	/*写真判定ボックスの生成*/
	m_pPlayer->CreateShootBox( CCommonObject::GetCamera( SCREEN_MAIN ), CCommonObject::GetSceneMgr( SCREEN_MAIN ) );
	
	if( GetTutorialFlag() )
	{
		m_eSceneState = STATE_CONTINUE;
	}
	
	vMousePos.Set( toF( CCommonObject::GetMouse()->GetMouse()->GetPosX() ), 
				   toF( CCommonObject::GetMouse()->GetMouse()->GetPosY() ),
				   0 );
	
	printf("[GameMain]::Idle %d\n", time );
	
	const int WAIT_TIME = 60 * 3;
	
	if( !m_IsDemo )
	{
		if( !GetTutorialFlag() )
		{
			if( time < WAIT_TIME )
			{
				Demo();
			}
			
			else if( time > WAIT_TIME && GetFilmCount() == FILM_MAX )
			{
				GameEnd();
			}

			else if( time > WAIT_TIME )
			{
				Game();
			}
			
		}
		
		else
		{
			Game();
		}
		
	}
	
	else
	{
		m_pReadySpr->SetVisibleFlag( false );
		m_pGoSpr->SetVisibleFlag( false );
		
		if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
		{
			m_IsDemo = false;
		}
	}
	

	///*ポーズ画面への移行*/
	//MovePauseMenu();
	

	
	/*地面チェック*/
	#if defined(CAM_TOOL)	
	
	#else
		m_pPlayer->GroundCheck( m_pField );
		
	#endif
	
	for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
	{
		CEnemy *pEnemy = *i;
		
		//if( m_pPlayer->HitCheck( pEnemy ) && m_pPlayer->GetState() == CPlayer::STATE_CAPSTART )
		//{
		//	m_pPlayer->SetState( CPlayer::STATE_CAPTURE );
		//}
		//
		if( !GetTutorialFlag() && pEnemy->GetStTypeName().compare("フンスイ") != 0 )
		{	
			pEnemy->GroundCheck( m_pField );
		}
	}
	
	/*レンダリング*/	
	Rendering();
	
	//----------------------------------------------
	//画面設定
	//----------------------------------------------
	/*パラメータ設定*/
	SetScreenParam();
	
	/*設定のレンダリング*/
	RenderingSetting();
		
	/*地面補正*/
	m_pPlayer->GroundAdjust();
	
	if( !GetBGM()->GetBGMDevice()->IsPlay() )
	{	
		GetBGM()->Exec();
	}
	
	if( !m_IsDemo )
	{	
		time += dt;
	}
	
}

//=============================================================================
//デモ
//=============================================================================
void CSceneGameMain::Demo()
{
	m_pMissionWinSpr->SetVisibleFlag( false );
	
	
	static int count = 0;
	
	const int TIME_MAX = 60 * 3;
	
	m_pPlayer->SetStopFlag( true );
	//CCommonObject::GetResMgr()->Get3DObject()->SetStopFlag( true );
	
	++count;
	
	if( count > 0 && count <= TIME_MAX / 2 )
	{
		m_pReadySpr->SetVisibleFlag( true );
	}
	
	else if( count > TIME_MAX / 2 && count < TIME_MAX )
	{
		m_pReadySpr->SetVisibleFlag( false );
		m_pGoSpr->SetVisibleFlag( true );
	}
	
	else if( count >= TIME_MAX )
	{
		m_pGoSpr->SetVisibleFlag( false );
		count = 0;
	}
	
}

//=============================================================================
//ゲーム中
//=============================================================================
void CSceneGameMain::Game()
{
	m_pReadySpr->SetVisibleFlag( false );
	m_pGoSpr->SetVisibleFlag( false );
	
	m_pPlayer->SetStopFlag( false );
	
	//CCommonObject::GetResMgr()->Get3DObject()->SetStopFlag( false );
	
	if( !GetTutorialFlag() )
	{
		if( GetFilmCount() == FILM_MAX )
		{
			SetNextScene( SCENE_RESULT );
			
			SetState( &CSceneTemplate::End );
		}
	}
	
	#if defined( CAM_TOOL )
	
		SavePos();
				
	#endif
	
	if( GetTutorialFlag() )
	{	
		/*マウススプライト状態処理*/
		MouseSprExec();
		
	}
	
	/*ターゲット矢印の処理*/
	TargetArrowExec();
	
	for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
	{
		CEnemy *pEnemy = *i;
		
		//敵とプレイヤーとの判定
		if( !m_pPlayer->GetCaptureFlag() )
		{
			if( m_pPlayer->HitCheck( pEnemy ) && 
				( m_pPlayer->GetState() == CPlayer::STATE_NONE || 
				  m_pPlayer->GetState() == CPlayer::STATE_MOVING ) )
			{
				m_pPlayer->SetState( CPlayer::STATE_HIT_ENEMY );
			}
		}
			
		else
		{	
			if( m_pPlayer->GetCapedEnemy()->HitCheck( pEnemy ) &&
				( m_pPlayer->GetState() == CPlayer::STATE_NONE || 
				  m_pPlayer->GetState() == CPlayer::STATE_MOVING ) )
			{
				
			}
		}
		
	}
	
	static bool IsHitTrain = false;
	
	if( m_pTrain->HitCheck( m_pPlayer ) && 
		( m_pPlayer->GetState() == CPlayer::STATE_NONE || 
		  m_pPlayer->GetState() == CPlayer::STATE_MOVING ) )
	{
		m_pPlayer->SetState( CPlayer::STATE_HIT_TRAIN );
	}
	
	float fDistance = ( m_pPlayer->GetPosition() - m_pTrain->GetPosition() ).Length();
	
	if( !GetTutorialFlag() )
	{	
		m_pTrain->PlaySnd( fDistance );
	}

}

//=============================================================================
//ゲーム終了
//=============================================================================
void CSceneGameMain::GameEnd()
{
	static int count = 0;
	
	m_pEndSpr->SetVisibleFlag( true );
	
	memset( m_IsAddFunc, false, sizeof( bool ) * FUNC_MAX );
	
	/*移動機能だけ残す*/
	m_IsAddFunc[0] = true;

	
	//m_pPlayer->SetStopFlag( f
	
	//CCommonObject::GetResMgr()->Get3DObject()->SetStopFlag( true );

	++count;
	
	CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_EXIT );
	
	if( count > 60 * 2 )
	{
		SetNextScene( SCENE_RESULT );

		m_pGameMusic->GetBGMDevice()->Stop();
		
		SetState( &CSceneTemplate::End );
		
		count = 0;
	}
}


//=============================================================================
//ポーズ画面への移行
//=============================================================================
void CSceneGameMain::MovePauseMenu()
{
	Math::Vector2D vPos = Math::Vector2D( vMousePos.x, vMousePos.y );
	
	if( Collision::Point_Rect( vPos, m_pMenuBtnSpr->GetHitRect() ) )
	{
		if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
		{
			SetNextScene( SCENE_PAUSE );
			
			SetSceneState( STATE_FINISH );
			
			CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_CHANGE );
			
			//SetState( &CSceneTemplate::End );
		}
		
		else
		{
			m_pMenuBtnSpr->SetAnimXID( 1 );
		}
	}
	
	else
	{
		m_pMenuBtnSpr->SetAnimXID( 0 );
	}
}

//=============================================================================
//スコアの描画
//=============================================================================
void CSceneGameMain::DrawScore()
{
	char Temp[10];
	
	sprintf_s( Temp, 10, "%d", GetTotalScore() );
	
	string strTemp = Temp;
	
	string strScore;
	
	const int SCORE_MAX = 3;
	
	strScore += "Score ";
	
	for( Uint32 i = 0;i < SCORE_MAX - strTemp.length();++i )
	{
		strScore += "0";
	}
	
	strScore += Temp;
	
	m_pNumFont[OPTION_SCORE]->SetDrawString( strScore );
	
	if( GetTotalScore() > GetClearPoint() )
	{
		m_pNumFont[OPTION_SCORE]->SetFontColor( CColor( 255, 0, 0 ) );
	}
	
	else
	{
		m_pNumFont[OPTION_SCORE]->SetFontColor( CColor( 255, 255, 255 ) );
	}
		
		m_pNumFont[OPTION_SCORE]->Exec();
	
	/*レンダリング*/
	m_pNumFont[OPTION_SCORE]->Rendering();
	
}

//=============================================================================
//フィルム枚数の描画
//=============================================================================
void CSceneGameMain::DrawFilmNum()
{
	char Temp[10];
	
	sprintf_s( Temp, 10, "%d", FILM_MAX - GetFilmCount() );
	
	m_pNumFont[OPTION_FILM]->SetDrawString( Temp );
	
	m_pNumFont[OPTION_FILM]->Exec();
	
	/*レンダリング*/
	m_pNumFont[OPTION_FILM]->Rendering();
	
}



//=============================================================================
//終了
//=============================================================================
//[input]
//	dt:時間の増加間隔
//=============================================================================
void CSceneGameMain::End( Uint32 dt )
{
	printf("[CSceneGameMain]::End\n");
	
	m_eSceneState = STATE_FINISH;
	
	SetState( &CSceneTemplate::Init );
	
	
}


//=============================================================================
//レンダリング
//=============================================================================
void CSceneGameMain::Rendering()
{
	/*シーンのレンダリング*/
	for( int ScreenNum = 0;ScreenNum < SCREEN_MAX;++ScreenNum )
	{	
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->Rendering( false );
	}
	
	m_pReadySpr->Exec();
	m_pReadySpr->Rendering();
	
	m_pGoSpr->Exec();
	m_pGoSpr->Rendering();
	
	m_pEndSpr->Exec();
	
	m_pEndSpr->Rendering();
	
	//ミニマップの表示
	if( !GetTutorialFlag() )
	{	
		ShowMiniMap();

		
	}
	
		

	if( !m_pPlayer->GetStopFlag() )
	{
		
		/*移動マーカーの表示*/
		ShowMarker();
		
		/*2Dリストの処理*/
		Exec2DList();
		
		
		/*移動カーソルの表示*/
		DrawMoveCursor();
		

		/*2Dリストのレンダリング*/
		Rendering2DList();
		
		/*スコアの描画*/
		DrawScore();
		
		/*フィルム枚数の描画*/
		DrawFilmNum();
		
		/*指アイコンの処理*/
		FingIcoExec();
		
		/*追加機能の処理*/
		AddFuncExec();
		
		/*チュートリアルの場合のレンダリング*/
		RenderingTutorial();
		
		/*機能のレンダリング処理*/
		RenderFuncExec();
		
	}
	
	if( !GetTutorialFlag() )
	{
		CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
		
		m_pMissionWinSpr->Exec();
		m_pMissionWinSpr->Rendering();
		
		CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_NORMAL );
		

	}
	
	
	//マウスアイコンのレンダリング
	RenderMouseIco();
	
	#if defined( CAM_TOOL )
	
		for( vector< MarkData >::iterator i = m_vecMarker.begin();i != m_vecMarker.end();++i )
		{
			MarkData Markdat = *i;
			
			if( Markdat.m_IsSet == true )
			{
				Markdat.m_pMarker->Exec();
				
				Markdat.m_pMarker->Rendering();
			}
		}
	
	#endif
	
	if( m_IsDemo )
	{	
		//ミッションの描画
		DrawMission();
	}
	
	
	/*デバッグ情報の表示*/
	#if defined( DEBUG ) | ( _DEBUG )	
		ShowDebugInfo();
	#endif
	
}


//=============================================================================
//メイン時の初期化
//=============================================================================
void CSceneGameMain::InitMain()
{
	const int CLEAR_OBJECT = 4;//非表示にするオブジェクト数
	
	/*消していたオブジェクトを表示するように*/
	CDraw3DObject *pClearObj[] =
	{
		m_pField,
		m_pTrain,
		m_pFountObj,
		m_pIsLand,
	};
	
	/*全機能の追加*/
	memset( m_IsAddFunc, true, sizeof( bool ) * FUNC_MAX );
	
	for( int i = 0;i < CLEAR_OBJECT;++i )
	{
		pClearObj[i]->SetVisibleFlag( true );
	}
		
	for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
	{
		CEnemy *pEnemy = *i;
		
		pEnemy->SetVisibleFlag( true );
		
		pEnemy->SetSeed( CCommonObject::GetAppli()->GetCore() );
	}
	
	//クリア時のオブジェクトの設定
	//SetClearObject();
	
	/*マウス表示スプライトの設定*/
	m_pMouseSpr->SetVisibleFlag( false );
	
	m_pArrowExpSpr->SetVisibleFlag( false );
	
	SetTutorialFlag( false );
	
	//ターゲットの設定
	LoadMission();
	
	m_pMissionWinSpr->SetVisibleFlag( true );
	
	
	SetBGM( m_pGameMusic );
	
	
}

//=============================================================================
//チュートリアルの初期化
//=============================================================================
void CSceneGameMain::InitTutorial()
{
	const int CLEAR_OBJECT = 4;//非表示にするオブジェクト数
	
	/*余計なオブジェクトを非表示にする*/
	CDraw3DObject *pClearObj[] =
	{
		m_pField,
		m_pTrain,
		m_pFountObj,
		m_pIsLand,
		
	};
	
	for( int i = 0;i < CLEAR_OBJECT;++i )
	{
		pClearObj[i]->SetVisibleFlag( false );
	}
		
	
	for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
	{
		CEnemy *pEnemy = *i;
		
		pEnemy->SetVisibleFlag( false );
		
		pEnemy->SetSeed( CCommonObject::GetAppli()->GetCore() );
		
	}
	
	/*その他の機能は、最初は機能させない*/
	/*全機能の追加*/
	memset( m_IsAddFunc, false, sizeof( bool ) * FUNC_MAX );
	
	m_pArrowExpSpr->SetVisibleFlag( false );
	
	m_pTrlField->SetVisibleFlag( true );
	
	GetWindowSpr()->Init();
	
	ShowEnemyCount = 0;
	
	AddFuncCount = 0;
	
	m_pField = m_pTrlField;
	
	SetTarget( m_pTrlEnemy[ShowEnemyCount] );
	
	for( int i = 0;i < TRL_ENEMY_NUM;++i )
	{
		m_pTrlEnemy[i]->SetVisibleFlag( false );
	}
	
	m_pMissionWinSpr->SetVisibleFlag( false );
	
	m_IsDemo = false;
	
	SetBGM( m_pTrlMusic );
	
}

//=============================================================================
//チュートリアルのレンダリング
//=============================================================================
void CSceneGameMain::RenderingTutorial()
{
	if( GetTutorialFlag() )
	{
		GetWindowSpr()->SetVisibleFlag( true );
	}
	
	else
	{
		GetWindowSpr()->SetVisibleFlag( false );

	}
	
	GetWindowSpr()->Exec();
	
	GetWindowSpr()->Rendering();
	
}


//=================================================================================================
/*ここからスクリプトの個別処理*/
//=================================================================================================

//=============================================================================
//左クリックを押したときの処理
//=============================================================================
void CSceneGameMain::LeftClickScript()
{
	if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH && !m_pCamBtnSpr->GetCamMoveFlag() )
	{
		GetWindowSpr()->AddStrCount( 1 );
		
		m_eMouseSprState = MOUSE_PUSHNONE;
	}
	
	/*マウス左ボタンクリック画像の表示*/
	else 
	{
		m_eMouseSprState = MOUSE_PUSHLEFT;
	
	}
}

//=============================================================================
//右クリックを押したときの処理
//=============================================================================
void CSceneGameMain::RightClickScript()
{
	if( CCommonObject::GetMouse()->GetMouse()->GetStateR() == MOUSE_PUSH && !m_pCamBtnSpr->GetCamMoveFlag() )
	{
		GetWindowSpr()->AddStrCount( 1 );
		
		m_eMouseSprState = MOUSE_PUSHNONE;
	}
	
	/*マウス右ボタンクリック画像の表示*/
	else 
	{
		m_eMouseSprState = MOUSE_PUSHRIGHT;
	}

}

//=============================================================================
//ドラッグしたときの処理
//=============================================================================
void CSceneGameMain::DragScript()
{
	bool IsMoveMouse = ( CCommonObject::GetMouse()->GetMouse()->GetMoveX() != 0 || CCommonObject::GetMouse()->GetMouse()->GetMoveY() != 0 );//マウスが動いているか
	
	if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_HOLD && IsMoveMouse
		&& !m_pCamBtnSpr->GetCamMoveFlag()  )
	{
		GetWindowSpr()->AddStrCount( 1 );
		
		m_eMouseSprState = MOUSE_PUSHNONE;
		

	}
	
	/*マウスドラッグ画像の表示*/
	else
	{
		m_eMouseSprState = MOUSE_DRAG;
	}

}

//=============================================================================
//カメラ回転時の処理
//=============================================================================
void CSceneGameMain::CameraRotScript()
{
	Math::Vector2D vPos = Math::Vector2D( vMousePos.x, vMousePos.y );
	
	/*カメラが移動してたら会話を進める*/
	if( m_pCamBtnSpr->GetCamMoveFlag() )
	{
		m_eMouseSprState = MOUSE_PUSHNONE;
		
		/*矢印を非表示*/
		SetFingState( CSceneBase::FING_NONE );
		
		GetWindowSpr()->AddStrCount( 1 );
		m_pCamBtnSpr->SetVisibleFlag( true );
		
	}
	
	/*点滅画像の表示*/
	else
	{
		m_eMouseSprState = MOUSE_PUSHLEFT;
		
		/*右方向の矢印表示*/
		SetFingState( CSceneBase::FING_RIGHT );
		
		
		GetFingerSpr()->SetInitPosition( m_pCamBtnSpr->GetPosition() + Math::Vector2D( 120.0f, 90.0f ) );
		
		
		
	}

}

//=============================================================================
//カメラリセット時の処理
//=============================================================================
void CSceneGameMain::CameraResetScript()
{
	Math::Vector2D vPos = Math::Vector2D( vMousePos.x, vMousePos.y );
	
	/*カメラが移動してたら会話を進める*/
	if( m_pCamBtnSpr->GetCamResetFlag() )
	{
		m_eMouseSprState = MOUSE_PUSHNONE;
		
		/*矢印を非表示*/
		SetFingState( CSceneBase::FING_NONE );
		
		GetWindowSpr()->AddStrCount( 1 );
		m_pCamBtnSpr->GetResetButton()->SetVisibleFlag( true );
		
	}
	
	/*点滅画像の表示*/
	else
	{
		m_eMouseSprState = MOUSE_PUSHLEFT;
		
		/*右方向の矢印表示*/
		SetFingState( CSceneBase::FING_RIGHT );
		
		GetFingerSpr()->SetInitPosition( m_pCamBtnSpr->GetResetButton()->GetPosition() - 
										 Math::Vector2D( 110.0f, 0 ) );
		
		
	}

}

//=============================================================================
//矢印説明時の処理
//=============================================================================
void CSceneGameMain::ArrowExpScript()
{
	if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
	{
		m_eMouseSprState = MOUSE_PUSHNONE;
		
	//	m_pArrowExpSpr->SetVisibleFlag( false );
		
		GetWindowSpr()->AddStrCount( 1 );
	}
		
	else 
	{
		m_eMouseSprState = MOUSE_PUSHLEFT;
	}
}

//=============================================================================
//スコア説明時スクリプト
//=============================================================================
void CSceneGameMain::ScoreExpScript()
{
	if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
	{
		GetWindowSpr()->AddStrCount( 1 );
		m_pNumFont[OPTION_SCORE]->SetVisibleFlag( true );
		
		/*矢印を非表示*/
		SetFingState( CSceneBase::FING_NONE );
		
		m_eMouseSprState = MOUSE_PUSHNONE;
		
	}
	
	else
	{
		m_eMouseSprState = MOUSE_PUSHLEFT;
		
		/*上方向の矢印表示*/
		SetFingState( CSceneBase::FING_UP );
		
		GetFingerSpr()->SetInitPosition( m_pNumFont[OPTION_SCORE]->GetPosition() 
										 + Math::Vector2D( 150.0f, 90.0f ) );
		
	}
}

//=============================================================================
//フィルム説明時スクリプト
//=============================================================================
void CSceneGameMain::FilmExpScript()
{
	if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
	{
		GetWindowSpr()->AddStrCount( 1 );
		m_pNumFont[OPTION_FILM]->SetVisibleFlag( true );
		m_eMouseSprState = MOUSE_PUSHNONE;
		
		/*矢印を非表示*/
		SetFingState( CSceneBase::FING_NONE );
		
		
		
	}
	
	else
	{
		m_eMouseSprState = MOUSE_PUSHLEFT;

		
		/*上方向の矢印表示*/
		SetFingState( CSceneBase::FING_UP );
		
		GetFingerSpr()->SetInitPosition( m_pNumFont[OPTION_FILM]->GetPosition() +
										 Math::Vector2D( 0, 100.0f ) );
		
	}
	

}

//=============================================================================
//ターゲット表示用スクリプト
//=============================================================================
void CSceneGameMain::TargetShowScript()
{
	
	m_pTrlEnemy[ShowEnemyCount]->SetVisibleFlag( true );
	
	m_pTrlEnemy[ShowEnemyCount]->SetPosition( Math::Vector3D( 31, 0, -46 ) );
	
	if( m_pTrlEnemy[ShowEnemyCount]->GetVisibleFlag() )
	{
		GetWindowSpr()->AddStrCount( 1 );
	}
	
	/*TODO:エフェクト表示*/
	
}

//=============================================================================
//ターゲット消去用スクリプト
//=============================================================================
void CSceneGameMain::TargetClearScript()
{
	m_pRabbit->SetVisibleFlag( false );
	
	ShowEnemyCount++;
	
	SetTarget( m_pTrlEnemy[ShowEnemyCount] );
	
	GetWindowSpr()->AddStrCount( 1 );
	
	/*TODO:エフェクト表示*/
	
	
}

//=============================================================================
//ターゲットポイント表示用スクリプト
//=============================================================================
void CSceneGameMain::TargetPlaceScript()
{
	static bool IsReachPlace = false;//ターゲットの場所にたどり着いたか
	
	if( m_pPlayer->GetPosition().x < 0 && m_pPlayer->GetCaptureFlag() )
	{
		IsReachPlace = true;
		
	}
	
	if( IsReachPlace )
	{
		GetWindowSpr()->AddStrCount( 1 );	
		IsReachPlace = false;
		
		/*矢印を表示*/
	}
}

//=============================================================================
//ターゲットの撮影
//=============================================================================
void CSceneGameMain::ShootTargetScript()
{
	if( CCommonObject::GetMouse()->GetMouse()->GetStateR() == MOUSE_PUSH )
	{
		m_eMouseSprState = MOUSE_PUSHNONE;
	}
	
	else
	{
		m_eMouseSprState = MOUSE_PUSHRIGHT;
	}
}

//=============================================================================
//キャッチ説明スクリプト
//=============================================================================
void CSceneGameMain::CatchExpScript()
{
	if( GetTarget()->GetCapedFlag() && m_pPlayer->GetState() == CPlayer::STATE_CAPTURE )
	{
		//ShowEnemyCount++;
		//
		//SetTarget( m_pTrlEnemy[ShowEnemyCount] );
		
		GetWindowSpr()->AddStrCount( 1 );
		
		m_eMouseSprState = MOUSE_PUSHNONE;
		
	}	
	
	else
	{
		m_eMouseSprState = MOUSE_PUSHLEFT;
	}
}

//=============================================================================
//機能追加スクリプト
//=============================================================================
void CSceneGameMain::AddFuncScript()
{
	m_IsAddFunc[AddFuncCount] = true;
	
	if( AddFuncCount > FUNC_MAX - 1 )
	{
		AddFuncCount = FUNC_MAX - 1;
	}
	
	if( m_IsAddFunc[AddFuncCount] )
	{	
		AddFuncCount++;
	
		GetWindowSpr()->AddStrCount( 1 );
	}
	
}

//=============================================================================
//リリースボタンスクリプト
//=============================================================================
void CSceneGameMain::ReleaseBtnScript()
{
	Math::Vector2D vPos = CCommonObject::GetMouse()->GetMousePos();
	
	static bool IsClick = false;
	
	if( Collision::Point_Rect( vPos, m_pReleaseBtnSpr->GetHitRect() ) )
	{
		if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
		{		
			IsClick = true;
			m_eMouseSprState = MOUSE_PUSHNONE;
			CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_CHANGE );
			
			
		}
		
		else
		{
			m_eMouseSprState = MOUSE_PUSHLEFT;
		}
	
	}
	
	if( IsClick && m_pPlayer->GetState() == CPlayer::STATE_NONE )
	{
		GetWindowSpr()->AddStrCount( 1 );	
		IsClick = false;
		
		/*矢印を非表示*/
		SetFingState( CSceneBase::FING_NONE );
		
	}
	
	else
	{
		m_eMouseSprState = MOUSE_PUSHLEFT;
		
		/*右方向の矢印表示*/
		SetFingState( CSceneBase::FING_RIGHT );
		
		GetFingerSpr()->SetInitPosition( m_pReleaseBtnSpr->GetPosition() -
										 Math::Vector2D( 110.0f, 0.0f ) );
	}

}

//=============================================================================
//メニュー表示用スクリプト
//=============================================================================
void CSceneGameMain::MenuScript()
{
	Math::Vector2D vPos = CCommonObject::GetMouse()->GetMousePos();
	
	if( Collision::Point_Rect( vPos, m_pMenuBtnSpr->GetHitRect() )
		 && CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
	{
		GetWindowSpr()->AddStrCount( 1 );				
		m_eMouseSprState = MOUSE_PUSHNONE;
		
		/*矢印非表示*/
		SetFingState( CSceneBase::FING_NONE );
		
		CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_CHANGE );
		
	}
	
	else
	{
		m_eMouseSprState = MOUSE_PUSHLEFT;
		
		/*右方向の矢印表示*/
		SetFingState( CSceneBase::FING_DOWN );
		
		GetFingerSpr()->SetInitPosition( m_pMenuBtnSpr->GetPosition() - 
										 Math::Vector2D( 20.0f, 80.0f ) );
	}

}

//=============================================================================
//終了スクリプト
//=============================================================================
void CSceneGameMain::EndScript()
{
	
	//一回だけ新要素表示画面に移る
	if( GetFirstGameFlag() )
	{	
		SetNextScene( SCENE_NEWELEM );
		
		/*プレイ済みフラグを立てる*/
		SetFirstGameFlag( false );
	
	}
	
	else
	{
		SetNextScene( SCENE_TITLE );
	}
	
	/*チュートリアルを終了する*/
	SetTutorialFlag( false );
	
	m_pAmeus->SetVisibleFlag( false );	
	
	m_pTrlMusic->GetBGMDevice()->Stop();
	
	for( Uint32 i = 0;i < GetFilmCount();++i )
	{
		char Temp[10];
		
		sprintf_s( Temp, 10, "Photo%d", i );
		
		CPhoto *pPhoto = dynamic_cast<CPhoto *>( CCommonObject::GetResMgr()->FindObject(Temp) );
		
		/*次回写真撮影できるように削除*/
		CCommonObject::GetResMgr()->RemoveObject( pPhoto );
	}
	
	
	
	
	SetState( &CSceneTemplate::End );	
}

//=============================================================================
//その他のスクリプト
//=============================================================================
void CSceneGameMain::OtherScript()
{
	if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
	{
		GetWindowSpr()->AddStrCount( 1 );				
		
	}
	
	else
	{
		m_eMouseSprState = MOUSE_PUSHLEFT;
	
	}
	
}

//=================================================================================================
/*ここまでスクリプトの個別処理*/
//=================================================================================================

//=============================================================================
//追加関数処理
//=============================================================================
void CSceneGameMain::AddFuncExec()
{
	/*関数テーブル*/
	AddFunc FuncTbl[] = 
	{
		&CSceneGameMain::MoveFunc,//移動機能
		&CSceneGameMain::CameraRotFunc,//カメラ回転機能
		&CSceneGameMain::CameraResetFunc,//カメラリセット機能
		&CSceneGameMain::ShootTargetFunc,//写真撮影機能
		&CSceneGameMain::MenuFunc,//メニュー機能
		&CSceneGameMain::CaptureFunc,//捕獲機能
		&CSceneGameMain::ReleaseFunc,//解放機能

	};
	
	for( int i = 0;i < FUNC_MAX;++i )
	{	
		/*機能解放していたら実行*/
		if(	m_IsAddFunc[i] )
		{
			(this->*FuncTbl[i])();
		}
	}
	
}


//=================================================================================================
/*ここから追加関数の個別処理*/
//=================================================================================================

//=============================================================================
//移動機能
//=============================================================================
void CSceneGameMain::MoveFunc()
{
	#if defined( CAM_TOOL )
	
		m_pPlayer->Move( CCommonObject::GetCamera(SCREEN_MAIN), CCommonObject::GetMouse()->GetMouse(), m_pField, CCommonObject::GetSceneMgr( SCREEN_MAIN )->GetSceneMgr() );
		
	
	#else
	
		/*移動マークが表示されていて、カメラ回転していないとき移動処理*/
		if( m_pPlayer->GetState() != CPlayer::STATE_CAPSTART &&
			m_pPlayer->GetState() != CPlayer::STATE_RELSTART &&
			m_pPlayer->GetState() != CPlayer::STATE_HIT_ENEMY )
		{	
			if( !m_pCamBtnSpr->GetCamMoveFlag() )
			{
				/*捕獲していないときは、プレイヤー。捕獲しているときは捕獲した敵を動かす*/
				if( m_pPlayer->GetCaptureFlag() )
				{	
					/*捕獲中のときは、敵の角度と連動*/
					m_pPlayer->SetRotate( m_pPlayer->GetCapedEnemy()->GetRotate() );
					
					m_pPlayer->GetCapedEnemy()->Move( vTargetPos, CCommonObject::GetCamera( SCREEN_MAIN ), 
													  m_pField,  m_pMarkerSpr->GetVisibleFlag() );
													  
					if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
					{
						m_pPlayer->GetCapedEnemy()->SetGravityCnt( 0 );
					}
					
					else if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PULL )
					{
						m_pPlayer->GetCapedEnemy()->SetGravityCnt( 0 );
					}
					
					//m_pPlayer->SetRotate( Math::Vector3D( m_pPlayer->GetCapedEnemy()->GetRotate().x,
					//									  m_pPlayer->GetRotate().y,
					//									  m_pPlayer->GetRotate().z ) );
					
				}
				
				else
				{
					
					m_pPlayer->Move( vTargetPos, CCommonObject::GetCamera( SCREEN_MAIN ), m_pField, m_pMarkerSpr->GetVisibleFlag() );
					
				}
			}
			
		}
		
		
		
		/*敵に噛み付いている最中の時は、モーションを変化させない*/
		//if( m_pPlayer->GetState() != CPlayer::STATE_CAPSTART && 
		//	m_pPlayer->GetState() != CPlayer::STATE_CAPTURE  &&
		//	m_pPlayer->GetState() != CPlayer::STATE_RELSTART &&
		//	m_pPlayer->GetState() != CPlayer::STATE_RELEASE &&
		//	m_pPlayer->GetState() != CPlayer::STATE_HIT_ENEMY &&
		//	m_pPlayer->GetState() != CPlayer::stat)
		if( m_pPlayer->GetState() == CPlayer::STATE_NONE ||
			m_pPlayer->GetState() == CPlayer::STATE_MOVING )
		{
			
			/*移動ベクトルが大きさを持っていたら移動、いなかったら立ち状態*/
			if( m_pMoveArrowSpr->GetVisibleFlag() && vTargetPos.Length() > 0.0f )
			{
				m_pPlayer->SetState( CPlayer::STATE_MOVING );
			
			}
			
			else
			{
				m_pPlayer->SetState( CPlayer::STATE_NONE );
			}
		}
		
	#endif
	
}

//=============================================================================
//カメラ回転機能
//=============================================================================
void CSceneGameMain::CameraRotFunc()
{
	CCamera *pSetCam[] =
	{
		CCommonObject::GetCamera( SCREEN_MAIN ),
		CCommonObject::GetCamera( SCREEN_SUB ),
	};
	
	/*カメラ移動*/
	if( m_pPlayer->GetState() != CPlayer::STATE_MOVING )
	{
			m_pCamBtnSpr->Move( pSetCam, CCommonObject::GetResMgr(), m_pPlayer );
	}
	
}

//=============================================================================
//カメラリセット機能
//=============================================================================
void CSceneGameMain::CameraResetFunc()
{
	CCamera *pSetCam[] =
	{
		CCommonObject::GetCamera( SCREEN_MAIN ),
		CCommonObject::GetCamera( SCREEN_SUB ),
	};
	
	/*カメラリセット*/
	m_pCamBtnSpr->Reset( pSetCam, m_pPlayer );
}

//=============================================================================
//写真撮影機能
//=============================================================================
void CSceneGameMain::ShootTargetFunc()
{
	#if defined ( CAM_TOOL )
	
	#else
		/*写真撮影*/
		ShootPhoto();
	#endif
	
}


//=============================================================================
//捕獲機能
//=============================================================================
void CSceneGameMain::CaptureFunc()
{
	/*キャッチマークの表示*/
	if( !m_pPlayer->GetCaptureFlag() )
	{	
		ShowCatchMark();
	}
	
	/*噛み付き移動位置の設定*/
	for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
	{	
		CEnemy *pEnemy = *i;
		/*捕獲対象範囲内で、敵が捕獲されてない状態*/
		if( pEnemy->GetCatchSpr3D()->GetVisibleFlag() 
		    && !m_pPlayer->GetCaptureFlag() )
		{
			m_pPlayer->SetTargetPos( CCommonObject::GetMouse()->GetMouse(), pEnemy, CCommonObject::GetSceneMgr( SCREEN_MAIN )->GetSceneMgr() );
		}
	}
	
	
}

//=============================================================================
//解放機能
//=============================================================================
void CSceneGameMain::ReleaseFunc()
{
	Math::Vector2D vPos = CCommonObject::GetMouse()->GetMousePos();
	
	/*解放ボタンが押されていて、捕獲状態の時解放する*/
	if( ::Collision::Point_Rect( vPos, m_pReleaseBtnSpr->GetHitRect() ) )
	{
		if( m_pPlayer->GetCaptureFlag() )
		{	
			if(	CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
			{
				m_pPlayer->ReleaseEnemy();	
			}
			
			else
			{
				m_pReleaseBtnSpr->SetAnimXID( 2 );
			}	
			
		}
		
	}
	
	else
	{
		m_pReleaseBtnSpr->SetAnimXID( 1 );
	}
	
	/*捕獲時は普通に表示*/
	if( m_pPlayer->GetCaptureFlag() )
	{
	}
	
	/*移動時はグレースケール表示*/
	else
	{
		m_pReleaseBtnSpr->SetAnimXID( 0 );
	}
	
	m_pReleaseBtnSpr->Rendering();
	
	
}

//=============================================================================
//メニュー機能
//=============================================================================
void CSceneGameMain::MenuFunc()
{
	/*メニューに移動*/
	MovePauseMenu();
}

//=================================================================================================
/*ここまで追加関数の個別処理*/
//=================================================================================================

//=================================================================================================
/*ここから機能のレンダリングの個別処理*/
//=================================================================================================
//[input]
//	flag:true→通常通り表示
//		 false→グレースケール表示
//=================================================================================================

//=============================================================================
//レンダリング関数の処理
//=============================================================================
void CSceneGameMain::RenderFuncExec()
{
	/*関数テーブル*/
	FuncRender FuncTbl[] = 
	{
		&CSceneGameMain::RenderMove,//移動機能
		&CSceneGameMain::RenderCameraRot,//カメラ回転機能
		&CSceneGameMain::RenderCameraReset,//カメラリセット機能
		&CSceneGameMain::RenderShootTarget,//写真撮影機能
		&CSceneGameMain::RenderMenu,//メニュー機能
		&CSceneGameMain::RenderCapture,//捕獲機能
		&CSceneGameMain::RenderRelease,//解放機能

	};
	
	for( int i = 0;i < FUNC_MAX;++i )
	{	
		(this->*FuncTbl[i])(m_IsAddFunc[i]);
	}


}

//=============================================================================
//移動時の表示
//=============================================================================
void CSceneGameMain::RenderMove( bool flag )
{
}

//=============================================================================
//カメラ回転時の表示
//=============================================================================
void CSceneGameMain::RenderCameraRot( bool flag )
{
	if( flag )
	{
		
	}
	
	else
	{
		m_pCamBtnSpr->DrawGrayScale( CCommonObject::GetAppli()->GetRenderer() );
	}
	
	
}

//=============================================================================
//カメラリセット時の表示
//=============================================================================
void CSceneGameMain::RenderCameraReset( bool flag )
{
	if( flag )
	{
		
	}
	
	else
	{
		m_pCamBtnSpr->GetResetButton()->SetAnimXID( 0 );
	}
}

//=============================================================================
//写真撮影時の表示
//=============================================================================
void CSceneGameMain::RenderShootTarget( bool flag )
{
	if( flag )
	{
		//m_pCamPointaSpr->SetVisibleFlag( true );
	}
	
	else
	{
		//m_pCamPointaSpr->SetVisibleFlag( false );
	}
}

//=============================================================================
//捕獲時の表示
//=============================================================================
void CSceneGameMain::RenderCapture( bool flag )
{
	if( flag )
	{
		
	}
	
	else
	{
	
	}
}

//=============================================================================
//解放時の表示
//=============================================================================
void CSceneGameMain::RenderRelease( bool flag )
{
	if( flag )
	{
	}
	
	else
	{
		m_pReleaseBtnSpr->SetAnimXID( 0 );
	}
	
	m_pReleaseBtnSpr->Rendering();
	
}

//=============================================================================
//メニュー時の表示
//=============================================================================
void CSceneGameMain::RenderMenu( bool flag )
{
	if( flag )
	{
		m_pMenuBtnSpr->Rendering();
	}
	
	else
	{
		m_pMenuBtnSpr->DrawGrayScale( CCommonObject::GetAppli()->GetRenderer() );
	}
}

//=================================================================================================
/*ここまで機能のレンダリングの個別処理*/
//=================================================================================================



//=============================================================================
//アクターの生成
//=============================================================================
void CSceneGameMain::CreateActor()
{
	//for( int i = 0;i < SCREEN_MAX;++i )
	//{
	//	CCommonObject::GetResMgr()->get->CreateActor( i, CCommonObject::GetSceneMgr(i)->GetSceneMgr() );
	//}
}

//=============================================================================
//写真評価
//=============================================================================
void CSceneGameMain::GradePhoto()
{
	int Score = 0;
	
	for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
	{
		CEnemy *pEnemy = *i;
		
		CPhoto::PhotoCheckData datPhoto;
		
		Score = pEnemy->CalcScore( m_pPlayer );
		
		/*撮影が終わってなくて、ロックオン状態のときのみ点数加算*/
		if( pEnemy->GetLockOnFlag() && !pEnemy->GetShootEndFlag() )
		{
			datPhoto.m_Score = Score;
			datPhoto.m_strTargetName = pEnemy->GetTypeName();
			
			vecPhotoData.push_back( datPhoto );
			
			char Temp[16];
			
			sprintf_s( Temp, 16, "Photo%d", GetFilmCount() );
			
			CPhoto *pPhoto =  dynamic_cast<CPhoto *>( CCommonObject::GetResMgr()->FindObject(Temp) );
			
			pPhoto->SetPhotoData( vecPhotoData );
			
			//写真情報のセット
			pPhoto->SetPhotoInfo();
			
			/*リストのクリア*/
			vecPhotoData.clear();
			
			/*撮影終了フラグの設定*/
			pEnemy->SetShootEndFlag( true );
			
			//ターゲットが存在していたらフラグを立てる
			if( pEnemy == GetTarget() )
			{
				SetTargetExistFlag( true );	
			}
			
			TotalScore += Score;
			
		}
		
	}	
	
	const int MAX_SCORE = 999;
	
	if( TotalScore > MAX_SCORE )
	{
		TotalScore = MAX_SCORE;
	}
	
	SetTotalScore( TotalScore );
	
	AddFilmCount();
	
	SetPhotoSaveFlag( false );
	
}

//=============================================================================
//デバッグ情報の表示
//=============================================================================
void CSceneGameMain::ShowDebugInfo()
{
	Renderer::IRender *pRender = CCommonObject::GetAppli()->GetRenderer();
	
	pRender->DebugPrint( Math::Point2DI( 0, 0 ), CColor( 255, 255, 255 ), 
						 "Player:Pos.x:%f, y:%f, z:%f", 
						 m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z );
	
	
	pRender->DebugPrint( Math::Point2DI( 0, 10 ), CColor( 255, 255, 255 ), 
						 "Player:Rot.x:%d, y:%d, z:%d", 
						 m_pPlayer->GetRotate().x, m_pPlayer->GetRotate().y, m_pPlayer->GetRotate().z );
						 
	pRender->DebugPrint( Math::Point2DI( 0, 20 ), CColor( 255, 255, 255 ),
						 "Camera:Rot.x:%d, y:%d, z:%d",
						 CCommonObject::GetCamera( SCREEN_MAIN )->GetRotate().x, 
						 CCommonObject::GetCamera( SCREEN_MAIN )->GetRotate().y,
						 CCommonObject::GetCamera( SCREEN_MAIN )->GetRotate().z );
						 
						 
	pRender->DebugPrint( Math::Point2DI( 0, 30 ), CColor( 255, 255, 255 ),
						 "Camera:Pos.x:%f, y:%f, z:%f",
						 CCommonObject::GetCamera( SCREEN_MAIN )->GetCamera()->Position().x, 
						 CCommonObject::GetCamera( SCREEN_MAIN )->GetCamera()->Position().y,
						 CCommonObject::GetCamera( SCREEN_MAIN )->GetCamera()->Position().z );
						 
						 
						 
	pRender->DebugPrint( Math::Point2DI( 0, 40 ), CColor( 255, 255, 255 ),
						 "Ameus:Pos.x:%f, y:%f, z:%f",
						 m_pAmeus->GetPosition().x, m_pAmeus->GetPosition().y,
						 m_pAmeus->GetPosition().z );
						 
	pRender->DebugPrint( Math::Point2DI( 0, 100 ), CColor( 255, 255, 255 ),
						 "Ameus:Exist:%d",
						 m_pAmeus->GetVisibleFlag() );
						 
						 
	//pRender->DebugPrint( Math::Point2DI( 0, 60 ), CColor( 255, 255, 255 ),
	//					 "Manta:Pos.x:%f, y:%f, z:%f",
	//					 m_pManta->GetPosition().x, m_pManta->GetPosition().y,
	//					 m_pManta->GetPosition().z );
						 
	pRender->DebugPrint( Math::Point2DI( 0, 70 ), CColor( 255, 255, 255 ),
						 "Ameus:CatchPos.x:%f, y:%f, z:%f",
						 m_pAmeus->GetCatchPos().x, m_pAmeus->GetCatchPos().y,
						 m_pAmeus->GetCatchPos().z );
						 
	pRender->DebugPrint( Math::Point2DI( 0, 110 ), CColor( 255, 255, 255 ),
						 "Mouse.x:%f, y:%f",
						vOldMousePos.x, vOldMousePos.y );

						 

	pRender->DebugPrint( Math::Point2DI( 0, 80 ), CColor( 255, 255, 255 ),
						 "TotalScore:%d",
						 GetTotalScore() );
						 
						 
	pRender->DebugPrint( Math::Point2DI( 0, 50 ), CColor( 255, 255, 255 ),
						 "Ameus:KeySpeed:%f",
						 m_pAmeus->GetKeyTime() );
						 
	pRender->DebugPrint( Math::Point2DI( 0, 90 ), CColor( 255, 255, 255 ),
						 "MoveAngle:%d",
						 DEG_TO_ANGLE( 90 ) );
						 
	pRender->DebugPrint( Math::Point2DI( 0, 120 ), CColor( 255, 255, 255 ),
						 "Count:%d",
						 ShootEnemyCount );

	pRender->DebugPrint( Math::Point2DI( 0, 130 ), CColor( 255, 255, 255 ),
						 "Rab:Exist:%d",
						 m_pRabbit->GetVisibleFlag() );
						 
						 
	
						 
}
//=============================================================================
//ターゲットへの矢印の処理
//=============================================================================
void CSceneGameMain::TargetArrowExec()
{
	Math::Vector3D vArrowPos = CCommonObject::GetSceneMgr( SCREEN_MAIN )->GetSceneMgr()->TransformToScreen
								( Math::Vector3D( m_pPlayer->GetPosition().x, 
												  m_pPlayer->GetPosition().y + 10.0f, 
												  m_pPlayer->GetPosition().z ) ); 
	
	
	m_pArrow->SetPosition( m_pPlayer->GetPosition() + Math::Vector3D( 0, 5, 0 ) );
	
	Math::Vector3D vDirection = GetTarget()->GetPosition() - m_pArrow->GetPosition();
	
	/*ターゲットとの距離によって色を変更*/
	Sint32 MeshCount = m_pArrow->GetModelActor(SCREEN_MAIN)->GetMeshCount();
	
	for( int MeshIndex = 0; MeshIndex < MeshCount;++MeshIndex )
	{
		Sint32 MateCount = m_pArrow->GetModelActor(SCREEN_MAIN)->GetMeshMaterialCount( MeshIndex );
		
		for( int MateIndex = 0; MateIndex < MateCount;++MateIndex )
		{
			/*近かったら赤色に*/
			if( vDirection.Length() >= 0.0 && vDirection.Length() < 10.0 )
			{
				m_pArrow->GetModelActor(SCREEN_MAIN)->MeshMaterial_SetMaterialColor( MeshIndex, MateIndex, Math::Vector4D( 255, 0, 0, 255 ) );
			}
			
			/*ほどほど近かったら黄色に*/
			else if( vDirection.Length() >= 10.0 && vDirection.Length() < 30.0 )
			{
				m_pArrow->GetModelActor(SCREEN_MAIN)->MeshMaterial_SetMaterialColor( MeshIndex, MateIndex, Math::Vector4D( 255, 255, 0, 255 ) );
			}
			
			/*遠かったら青色*/
			else
			{
				m_pArrow->GetModelActor(SCREEN_MAIN)->MeshMaterial_SetMaterialColor( MeshIndex, MateIndex, Math::Vector4D( 0, 0, 255, 255 ) );
			}

		}
	}

	
	/*ターゲットの位置によって、方向を変える*/
	Sint32 RotX = Math::ATan2( -vDirection.z, vDirection.x );
	Sint32 RotY = Math::ATan2( -vDirection.z, vDirection.y );
	
	if( GetTarget()->GetStTypeName().compare( "テイエン" ) == 0 )
	{
		RotY = Math::ATan2( -vDirection.x, vDirection.y );		
		
		m_pArrow->SetRotate( Math::Point3DI( RotX, RotY, 0 ) );
	}
	
	else
	{	
		m_pArrow->SetRotate( Math::Point3DI( -RotX, RotY, 0 ) );
	}
}

//=============================================================================
//移動マーカーの表示
//=============================================================================
void CSceneGameMain::ShowMarker()
{
	Math::Vector2D vPos( vMousePos.x, vMousePos.y );
	
	Math::Vector2D vCenterPos( toF( m_pMarkerSpr->GetSize().x / 2 ), toF( m_pMarkerSpr->GetSize().y / 2 ) );


	if( m_pCamBtnSpr->GetCamMoveFlag() )
	{
		GetMouseCursor()->SetVisibleFlag( true );
		m_pMarkerSpr->SetVisibleFlag( false );
	}
	
	else
	{
		if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
		{
			vOldMousePos = Math::Vector3D( CCommonObject::GetMouse()->GetMousePos().x,
											CCommonObject::GetMouse()->GetMousePos().y,
											0.0f );
		}
		
		else if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_HOLD )
		{
			
			m_pMarkerSpr->SetPosition( vPos - vCenterPos );
			//m_pMarkerSpr->SetPosition( vOldMousePos );
			m_pMarkerSpr->SetVisibleFlag( true );
			GetMouseCursor()->SetVisibleFlag( false );
			
		}
		
		else
		{
			m_pMarkerSpr->SetVisibleFlag( false );
			GetMouseCursor()->SetVisibleFlag( true );
			
		}
	}	
}

//=============================================================================
//キャッチマークの表示
//=============================================================================
void CSceneGameMain::ShowCatchMark()
{
	/*キャッチマーク表示範囲*/
	Collision::CBox HitBox = m_pPlayer->GetCapCheckBox();
	
	/*カメラのビュー→ワールド変換を取得*/
	Math::Matrix matViewToWorld = CCommonObject::GetCamera( SCREEN_SUB )->GetCamera()->ViewToWorld();
	
	for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
	{	
		CEnemy *pEnemy = *i;
		
		/*ワールド行列の設定*/
		pEnemy->GetCatchSpr3D()->SetMatWorld( matViewToWorld );
		
		/*キャッチマーク表示範囲かチェック*/
		pEnemy->CheckCatch( HitBox );
	}
	
}

//=============================================================================
//移動カーソルの表示
//=============================================================================
void CSceneGameMain::DrawMoveCursor()
{
	
	m_pMoveArrowSpr->SetVisibleFlag( m_pMarkerSpr->GetVisibleFlag() );
	
	Math::Vector3D vPos( vOldMousePos.x, vOldMousePos.y, 0.0f );
	
	vTargetPos = vMousePos - vPos;
	
	fMoveDistance = vTargetPos.Length();
	
	Math::Matrix matWorld;
	Math::Matrix matTemp;
	
	matWorld.Identity();
	matTemp.Identity();
	
	//原点に重ね合わせる平行移動
	matTemp.Translation( -m_pMoveArrowSpr->GetSize().x / 2, 
						 -m_pMoveArrowSpr->GetSize().y / 3,
						 0.0f );
	matWorld *= matTemp;

	MoveAngle = Math::ATan2( -vTargetPos.y, vTargetPos.x );
	
	//拡大行列と合成
	matTemp.Scaling( 1.0f, fMoveDistance * 0.01f, 1.0f );
	matWorld *= matTemp;
	
	//回転行列と合成
	matTemp.RotationZ( MoveAngle );
	//matTemp.RotationAxis( MoveAngle, vPos );
	matWorld *= matTemp;
	//
	////指定の場所へと移動する行列との合成
	matTemp.Translation( vOldMousePos.x, vOldMousePos.y, 0.0f );
	
	matWorld *= matTemp;
	
	Math::Rect2DF SrcRect( 0, 0, toF( m_pMoveArrowSpr->GetSize().x ), toF( m_pMoveArrowSpr->GetSize().y ) );
	
	m_pMoveArrowSpr->GetSprite()->Begin();
	
	m_pMoveArrowSpr->GetSprite()->DrawSquareMatrix( matWorld, SrcRect, CColor( 255, 255, 255 ) );
	
	
	m_pMoveArrowSpr->GetSprite()->End();
	
}

//=============================================================================
//写真撮影
//=============================================================================
void CSceneGameMain::ShootPhoto()
{
	/*カメラポインタとの当たり判定*/
	HitCheckCamPointa();
	
	if( GetPhotoSaveFlag() )
	{
		/*写真評価*/
		GradePhoto();

	}
	
	/*右クリックの時*/
	if( CCommonObject::GetMouse()->GetMouse()->GetStateR() == MOUSE_PUSH )
	{
	
		string name = "file";
		char Temp[16];
		
		sprintf_s( Temp, 16,  "%d.tga", GetFilmCount() );
		
		name += Temp;
		
		/*写真を一時的に保存して、そのデータを読み込んですぐ破棄*/								
		CCommonObject::GetSceneMgr( SCREEN_SUB )->GetRenderTex()->SaveToTGA( name.c_str() );
		
		sprintf_s( Temp, 16,  "Photo%d", GetFilmCount() );
		
		
		if( GetTutorialFlag() )
		{
			if( GetTarget()->GetLockOnFlag() )
			{	
				
				CCommonObject::GetResMgr()->Push( new CFileData( name.c_str(), Temp, "PHOTO", Math::Vector3D( 0, 0, 0 ),
																 vecPhotoData ) );
				
				CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_SHUTTER );

				/*写真チェック画面に遷移*/
				SetNextScene( SCENE_PHOTOCHECK );
				
				//ターゲットだったら進める
				if( GetTarget() == m_pRabbit )
				{	
					GetWindowSpr()->AddStrCount( 1 );
				}
			
				
				/*シーンを終了*/
				SetSceneState( STATE_FINISH );
			
			}
			
			else
			{
				CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_PROHIBIT );
			}
			
		}
		
		else
		{
			CPhoto *pPhoto = NULL;
				
			CCommonObject::GetResMgr()->Push( new CFileData( name.c_str(), Temp, "PHOTO", 
												  Math::Vector3D( 0, 0, 0 ), vecPhotoData ) );
			
			/*リストのクリア*/
			vecPhotoData.clear();
			
			CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_SHUTTER );
			
			
			/*写真チェック画面に遷移*/
			SetNextScene( SCENE_PHOTOCHECK );
			
			/*シーンを終了*/
			SetSceneState( STATE_FINISH );
		
		
		}
		
	}

}

//=============================================================================
//画面の設定
//=============================================================================
void CSceneGameMain::SetScreenParam()
{
	for( int ScreenNum = 0;ScreenNum < SCREEN_MAX;++ScreenNum )
	{	
		/*パラメータの設定*/
		CCommonObject::GetSceneMgr( ScreenNum )->SetParameter();
		
		// 平行光源
		//   シーンに対して平行光源を設定します。
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->SetLightParameter_Directional(
			Math::Vector3D( 0.5f, -0.5f, 0.7f ),		// ライトの方向
			Math::Vector3D( 1.0f, 1.0f, 1.0f ) );		// ライトの色

		// アンビエント
		// 半球ライティングを行っているので、天球と地表の照り返しの色を設定します。
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->SetLightParameter_Ambient(
			Math::Vector3D( 0.2f, 0.2f, 0.2f ),			// 天球の色
			Math::Vector3D( 0.5f, 0.5f, 0.5f ) );		// 地表の色
			
		// カメラの注視目標
		#if defined( DEBUG_MAP_SEE )
		
			ifstream ifs("target.txt");
			
			if( ifs.fail() )
			{
				ofstream out("target.txt");
				
				out << "Ameus" << std::endl;
				
				out.close();
			}
			
			char TargetStr[20] = "";
			
			ifs >> TargetStr;
			
			CEnemy *m_pTarget = dynamic_cast<CEnemy *>( GetResMgr()->FindObject(TargetStr) );
			
			
			GetCamera(ScreenNum)->SetTargetPos( m_pTarget->GetPosition() + Math::Vector3D(0.0f, 3.0f, 0.0f ) );
			
			ifs.close();
		
		#else
		
			/*捕獲中の敵にフォーカスを合わせる*/
			if( m_pPlayer->GetCaptureFlag() )
			{
				CCommonObject::GetCamera( ScreenNum )->SetTargetPos( m_pPlayer->GetCapedEnemy()->GetPosition()
													  + Math::Vector3D(0.0f, 3.0f, 0.0f) );
			}
			
			else
			{	
				CCommonObject::GetCamera( ScreenNum )->SetTargetPos( m_pPlayer->GetPosition() + Math::Vector3D(0.0f, 3.0f, 0.0f) );
			}
			
		
		#endif

		/*カメラの回転補正*/
		CCommonObject::GetCamera( ScreenNum )->RotateAdjust();
		
		/*カメラの変形*/
		#if defined(CAM_TOOL)
			
			CCommonObject::GetCamera( ScreenNum )->SetTransform3();
				
		#else
			
			if( m_IsDemo )
			{
				
				++CamCnt;
				
				const int TIME_MAX = 60 * 6;
				
				CEnemy *pTarget = GetTarget();
				
				if( GetTarget()->GetStTypeName().compare( "テイエン" ) == 0 )
				{
					if( CamCnt > 0 && CamCnt <= TIME_MAX / 2 )
					{
						pTarget = GetTarget();
					}
					
					else if( CamCnt > TIME_MAX / 2 && CamCnt <= TIME_MAX )
					{
						pTarget = dynamic_cast<CEnemy *>( CCommonObject::GetResMgr()->FindObject("Bird1") );
					}
					
				}
				
				else if( GetTarget()->GetStTypeName().compare( "フンスイ" ) == 0 )
				{
					if( CamCnt > 0 && CamCnt <= TIME_MAX / 2 )
					{
						pTarget = GetTarget();
					}
					
					else if( CamCnt > TIME_MAX / 2 && CamCnt <= TIME_MAX )
					{
						pTarget = dynamic_cast<CEnemy *>( CCommonObject::GetResMgr()->FindObject("Manta1") );
					}
				}
				
				else if( GetTarget()->GetStTypeName().compare( "アメウス" ) == 0 )
				{
					if( CamCnt > 0 && CamCnt <= TIME_MAX / 2 )
					{
						pTarget = GetTarget();
					}
					
					else if( CamCnt > TIME_MAX / 2 && CamCnt <= TIME_MAX )
					{
						pTarget = dynamic_cast<CEnemy *>( CCommonObject::GetResMgr()->FindObject("Mouse1") );
					}
				}
				
				else
				{
					pTarget = GetTarget();
				}
				
				if( CamCnt > TIME_MAX )
				{
					CamCnt = 0;
				}
				
				CCommonObject::GetCamera( ScreenNum )->SetTransformDemo( pTarget );
				
			}
			
			else
			{
			
				if( m_pPlayer->GetCapedEnemy() != NULL && 
					m_pPlayer->GetCapedEnemy()->GetStTypeName().compare("トリ") == 0 )
				{	
					CCommonObject::GetCamera( ScreenNum )->SetTransformBird( MoveAngle, m_pMarkerSpr->GetVisibleFlag() );
				}
				
				else
				{
					CCommonObject::GetCamera( ScreenNum )->SetTransform( MoveAngle, m_pMarkerSpr->GetVisibleFlag() );
				}
			}
			
		#endif
		
		// シーンにシャドウマップ用カメラ設定t
		//   シャドウマップのレンダリングに使うカメラを設定
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->SetParameter_Shadow(
			Math::Vector3D( -3.0f, 20.0f, -30.0f ),	// カメラ位置
			Math::Vector3D( 0, 10.0, 0 ),
			//objPlayer->GetPosition(),									// カメラ注視点
			100.0f,								// レンダリングサイズ
			10.0f,								// 近クリップ面
			30.0f,								// 遠クリップ面
			0.0f,								// Z値バイアス（実際に見ていい感じに調整
			0.7f );								// 影の強さ（SHADING_NORMALの時のみ有効）
			
		// ハッチング用のパラメーター
		//GetSceneMgr(ScreenNum)->GetSceneMgr()->SetParameter_Toon( Math::Vector3D(0.5, 0.5, 0.5 ), 0.1f );
		//GetSceneMgr(ScreenNum)->GetSceneMgr()->SetParameter_ToonEdge( 3.0f, 10.0f, false );
			
		// 雲の移動
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->SceneSkydoom_SetCloudOffset( Math::Vector2D( 0.0002f, 0.0005f ) );
	}
	
}

//=============================================================================
//設定のレンダリング
//=============================================================================
void CSceneGameMain::RenderingSetting( )
{
	for( int ScreenNum = 0;ScreenNum < SCREEN_MAX;++ScreenNum )
	{
		/*アクターインデックスの切り替え*/
		m_pField->SetActorIndex( ScreenNum );
		
		SetActorIndexAll( ScreenNum );
		
		//m_pPlayer->SetActorIndex( ScreenNum );
		//CCommonObject::GetResMgr()->Get3DObject()->SetActorIndex( ScreenNum );
		
		
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->Begin( false );
		
		// スカイドームのレンダリング
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->SceneSkydoom_Rendering();
		
		// 影の影響を受けるように設定
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->SetActorParameter_ProjectionShadow( PROJECTION_SHADOW_DROP_SHAPE, PROJECTION_SHADOW_PRIORITY_0 );
		
		m_pField->SetVisibleFlag( true );
		
		/*フィールドのレンダリング*/
		m_pField->Rendering();
		
		/*2重レンダリングを防ぐ*/
		m_pField->SetVisibleFlag( false );

		// 影を落とすように設定
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->SetActorParameter_ProjectionShadow( PROJECTION_SHADOW_DROP_SHAPE, PROJECTION_SHADOW_PRIORITY_1 );
		
		

		/*写真に写って欲しくないものの設定*/
		if( ScreenNum == SCREEN_SUB )
		{
			
			/*サブ画面にはプレイヤーを表示させない*/
			m_pPlayer->SetVisibleFlag( false );
			
			m_pArrow->SetVisibleFlag( false );
			
			//m_pTargetArrow->SetVisibleFlag( false ); 
			
			for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
			{
				CEnemy *pEnemy = *i;
				
				pEnemy->GetCatchSpr3D()->SetVisibleFlag( false );
				
				pEnemy->GetPntSpr3D()->SetVisibleFlag( false );
				
				//pEnemy->GetLockOnSpr3D()->SetVisibleFlag( false );
			}
			
			/*捕獲時には、捕獲中の敵も表示させない*/
			if( m_pPlayer->GetCaptureFlag() )
			{
				m_pPlayer->GetCapedEnemy()->SetVisibleFlag( false );
			}
			
			
		}
		
		/*メイン画面時*/
		else
		{
			m_pPlayer->SetVisibleFlag( true );
			
			//m_pArrow->SetVisibleFlag( true );
			
			//m_pTargetArrow->SetVisibleFlag( true ); 
			
			if( m_pPlayer->GetCapedEnemy() != NULL )
			{	
				m_pPlayer->GetCapedEnemy()->SetVisibleFlag( true );
			}

			
		}
		
		
		
		/*写真判定用レイの設定*/
		m_pPlayer->CreateShootRay( CCommonObject::GetSceneMgr( SCREEN_MAIN )->GetSceneMgr() );
		
		/*移動処理*/
		if( !GetTutorialFlag() )
		{
			if( m_pPlayer->GetState() != CPlayer::STATE_CAPSTART || 
				m_pPlayer->GetState() != CPlayer::STATE_RELSTART )
			{
				MoveExec3DObject();
			}
		}
		
		
		
		/*処理*/
		Exec3DObject();
		
		//レンダリング
		Rendering3DObject();
		
		for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
		{
			CEnemy *pEnemy = *i;
			
			if( pEnemy->GetVisibleFlag() )
			{
				/*キャッチマークのレンダリング*/
				pEnemy->RenderingCatchMark();
				
			}
		}
		
		// シーン管理を終了
		//   ここまでで構築されたシーン情報を元に実際に描画用データの構築を行います。
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->End();
	}

}

//=============================================================================
//電車との当たり判定
//=============================================================================
void CSceneGameMain::HitCheckTrain( )
{
	
	Collision::CLine3D vRay;
	Renderer::SCollisionResult Ret;
	
	vRay.vStart = m_pPlayer->GetPosition() + Math::Vector3D( 0, 3, 0 );
	
	vRay.vEnd = vRay.vStart + Math::Vector3D( 0, 0, 3 );
	
	static int count = 0;

	/*当たり判定*/
	if( m_pPlayer->HitCheck( vRay, Ret ) )
	{
		if( Ret.Attribute == 1 )
		{
			#if defined (DEBUG) | (_DEBUG) 
				//pRender->DebugPrint( Math::Point2DI( 200, 100 ), CColor( 255, 255, 255 ), "電車に接触中" );
			#endif
			
			m_pPlayer->SetDeadFlag( true );
			
			m_pPlayer->SetState( CPlayer::STATE_HIT_TRAIN );
		}
		
		else
		{
			m_pPlayer->SetState( CPlayer::STATE_HIT_ENEMY );
		}
	
	}	
	
	if( count > 200 )
	{
		count = 0;
		
		SetState( &CSceneTemplate::End );
		
	}
	
}

//=============================================================================
//位置の保存
//=============================================================================
void CSceneGameMain::SavePos()
{
	Math::Matrix mat = CCommonObject::GetCamera( SCREEN_MAIN )->GetCamera()->ViewToWorld();
	
	if( MarkerIdx > MARKER_MAX )
	{
		MarkerIdx = MARKER_MAX;
	}
	
	m_vecMarker.at(MarkerIdx).m_pMarker->SetMatWorld( mat );
	
	/*位置の設定*/
	m_vecMarker.at(MarkerIdx).m_pMarker->SetPosition( m_pPlayer->GetMouseTarget() );
	
	ofstream out( "data.csv", ios::out | ios::trunc );
	
	bool IsClick = false;
	
	if( CCommonObject::GetMouse()->GetMouse()->GetStateR() == MOUSE_PUSH )
	{
		m_vecMarker.at(MarkerIdx).m_IsSet = true;
		
		MarkerIdx ++;			
		
		IsClick = true;
	
	}
	
	for( vector<MarkData>::iterator i = m_vecMarker.begin();i != m_vecMarker.end();++i )
	{
		MarkData markdat = *i;
		
		if( markdat.m_IsSet && IsClick )
		{	
			out << markdat.m_pMarker->GetPosition().x << "," << markdat.m_pMarker->GetPosition().z << std::endl;
		}
	}

}

//=============================================================================
//マウススプライトの状態処理
//=============================================================================
void CSceneGameMain::MouseSprExec()
{
	int Anim[] =
	{
		0,
		1,
	};
	
	m_pMouseSpr->SetVisibleFlag( true );
	
	
	switch( m_eMouseSprState )
	{
		/*何もしてない状態のとき*/
		case MOUSE_PUSHNONE:
		{
			Anim[0] = 0;
			Anim[1] = 0;
			break;
		}
		
		/*左クリックを押す状態の時*/
		case MOUSE_PUSHLEFT:
		{
			Anim[0] = 0;
			Anim[1] = 1;			
			
			break;
		}
		
		/*右クリックを押す状態の時*/
		case MOUSE_PUSHRIGHT: 
		{
			Anim[0] = 0;
			Anim[1] = 2;
			
			break;
		}
		
		/*ドラッグ状態の時*/
		case MOUSE_DRAG:
		{
			Anim[0] = 1;
			Anim[1] = 3;
			
			break;
		}
	}
	
	++count;
	
	if( count > 0 && count < 30 )
	{ 	
		m_pMouseSpr->SetAnimXID( Anim[0] );
	}
	
	else if( count >= 30 && count < 60 )
	{
		m_pMouseSpr->SetAnimXID( Anim[1] );
	}
	
	else
	{
		count = 0;
	}

}

//=============================================================================
//ミニマップの表示
//=============================================================================
void CSceneGameMain::ShowMiniMap()
{
	
	m_pMiniMap->Rendering();
	
	m_pMiniMap->SetMiniCharaPos( m_pPlayer, m_pPlayer->GetMinSpr(), true );
	
	//プレイヤーの表示
	m_pMiniMap->Move( m_pPlayer );
	
	//ミニキャラの表示
	m_pPlayer->ShowMiniChara();
	
	for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
	{
		CEnemy *pEnemy = *i;
		
		if( GetTarget() == pEnemy )
		{	
			m_pMiniMap->SetMiniCharaPos( pEnemy, m_pMiniTarget, false );
		}
		
		else
		{
			m_pMiniMap->SetMiniCharaPos( pEnemy, pEnemy->GetMinSpr(), false );
		}
			
		
		pEnemy->ShowMiniChara();
	}
	
	m_pMiniMap->Exec();
}

//=============================================================================
//カメラポインタとの当たり判定
//=============================================================================
void CSceneGameMain::HitCheckCamPointa()
{
	/*ループ用カウント*/
	int EnemyCount = 0;
	
	/*ターゲットがカメラポインタに当たっているかどうか*/
	for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
	{
		CEnemy *pEnemy = *i;
		
		float fDistance = ( pEnemy->GetPosition() - m_pPlayer->GetPosition() ).Length();
		
		
		/*当たっていたら、カメラポインタのアニメーション番号変更*/
		if( pEnemy->CheckShoot( CCommonObject::GetSceneMgr( SCREEN_MAIN ) ) && !pEnemy->GetCapedFlag() && 
			fDistance < fCHECK_DISTANCE )
		{
			pEnemy->SetLockOnFlag( true );
		}
		
		else
		{
			pEnemy->SetLockOnFlag( false );
		}
		
		if( pEnemy->GetLockOnFlag() )
		{
			EnemyCount = 0;
			GetMouseCursor()->SetAnimXID( 2 );
			
			//m_pCamPointaSpr->SetAnimXID( 1 );
			
			ShootEnemyCount ++;
			
			if( ShootEnemyCount > LOCKON_MAX - 1 )
			{
				ShootEnemyCount = LOCKON_MAX - 1;
			}
			
			
		}
		
		else
		{
			EnemyCount++;
			
			if( EnemyCount == m_pVecCatchEnemy.size() )
			{	
			//	m_pCamPointaSpr->SetAnimXID( 0 );
			
				GetMouseCursor()->SetAnimXID( 1 );
			
				
				ShootEnemyCount = 0;
				
			}
		}
		
		/*敵が壁に当たっているかチェック*/
		//pEnemy->HitCheckWall( m_pField );
		
		//pEnemy->SetSeed( GetAppli()->GetCore() );
	}
	
}

//=============================================================================
//クリアオブジェクトの追加
//=============================================================================
void CSceneGameMain::SetClearObject()
{
	if( GetClearCount() < ELEM_ADDMOUSE + 1 )
	{
		const int ENEMOUSE_MAX = 3;	
		
		for( int i = 0;i < ENEMOUSE_MAX;++i )
		{
			char Temp[10];
			
			sprintf_s( Temp, 10, "Mouse%d", i + 1 );
			
			CEnemy *pEnemy = dynamic_cast<CEnemy *>( CCommonObject::GetResMgr()->FindObject( Temp ) );
			
			pEnemy->SetVisibleFlag( false );
		}
	}
}

//=============================================================================
//ミッションの描画
//=============================================================================
void CSceneGameMain::DrawMission()
{
	//ミッション名
	string strMissionName = vecStr[0];
	
	//ターゲット名
	string strTargetName = vecStr[1];
	
	//CCommonObject::GetAppli()->GetRenderer()->DrawTextLayer
	//( 2, Math::Point2DI( 0, 0 ), CColor( 255, 255, 255 ), strMissionName.c_str() );
	//
	CCommonObject::GetAppli()->GetRenderer()->DrawTextLayer
	( 2, Math::Point2DI( 40, 210 ), CColor( 0, 0, 0 ), "%sを撮れ", GetTarget()->GetStTypeName().c_str() );
	
	CCommonObject::GetAppli()->GetRenderer()->DrawTextLayer
	( 2, Math::Point2DI( 40, 260 ), CColor( 0, 0, 0 ), "クリアポイント:%dポイント", GetClearPoint() );
	
	static int count = 0;
	
	++count;
	
	if( count > 0 && count <= 30 )
	{
		CCommonObject::GetAppli()->GetRenderer()->DrawTextLayer
		( 2, Math::Point2DI( 100, 330 ), CColor( 255, 255, 255 ), "左クリックでスタート" );
	}
	
	else if( count > 30 && count < 60 )
	{
	
	}
	
	else if( count > 60 )
	{
		count = 0;
	}
	

}

//=============================================================================
//ミッションのロード
//=============================================================================
void CSceneGameMain::LoadMission()
{
	CFileLoader FileLoader;

	CCommonObject::GetAppli()->GetFileMgr()->SetCurrentPath("CSV");
	
	File::IResourceFile *pResFile = CCommonObject::GetAppli()->GetFileMgr()->FileOpen( "MissionTarget.csv" );
	
	FileLoader.Load( pResFile->GetNamePointer() );
	
	if( GetTutorialFlag() )
	{
		vecStr = FileLoader.SplitString( FileLoader.GetStrList().at( 0 ), "," );
	}
	
	else
	{	
		vecStr = FileLoader.SplitString( FileLoader.GetStrList().at( GetClearCount() ), "," );
	}
	
	Math::CRandom Rand( CCommonObject::GetAppli()->GetCore()->GetSyncCount());
	
	int TargetNo = Rand.GetInt( 0, m_pVecTarget.size() - 1 );
	
	//クリアポイント
	int ClearPoint = Rand.GetInt( 100, 500 );
	
	CEnemy *pEnemy = m_pVecTarget.at( TargetNo );

	//ターゲットの設定
	SetTarget( pEnemy );
	
	//クリアポイントの設定
	SetClearPoint( ClearPoint );
	
	SAFE_RELEASE( pResFile );
	
}

//=============================================================================
//ターゲット対象の敵の設定
//=============================================================================
void CSceneGameMain::SetTargetEnemy()
{
		
	CFileLoader FileLoader;
	
	File::IResourceFile *pResFile = CCommonObject::GetAppli()->GetFileMgr()->FileOpen( "TargetEnemy.txt" );
	
	string strFileName = pResFile->GetNamePointer();
	
	FileLoader.Load( strFileName );
	
	SAFE_RELEASE( pResFile );
	
	vector< string > strList = FileLoader.GetStrList();
	
	vector< string >::iterator it = strList.begin();
	
	for( it = strList.begin(); it != strList.end();++it )
	{
		string strEnemyName = *it;
		
		CEnemy *pEnemy = dynamic_cast<CEnemy *>
						( CCommonObject::GetResMgr()->FindObject( strEnemyName.c_str() ) );
		
		m_pVecTarget.push_back( pEnemy );
	}

}

//=============================================================================
//3Dオブジェクトの初期化
//=============================================================================
void CSceneGameMain::InitAll()
{
	for( Uint32 i = 0;i < m_vec3DList.size();++i )
	{
		CDraw3DObject *pObj = m_vec3DList.at( i );
		
		pObj->Init();
	}
}


//=============================================================================
//3Dオブジェクトのレンダリング
//=============================================================================
void CSceneGameMain::Rendering3DObject()
{
	for( int i = 0;i < m_vec3DList.size();++i )
	{
		CDraw3DObject *pObj = m_vec3DList.at( i );
		
		pObj->Rendering();
	}
}

//=============================================================================
//3Dオブジェクトの処理
//=============================================================================
void CSceneGameMain::Exec3DObject()
{
	for( int i = 0;i < m_vec3DList.size();++i )
	{
		CDraw3DObject *pObj = m_vec3DList.at( i );
		
		pObj->Exec();
	}
}

//=============================================================================
//3Dオブジェクトの処理
//=============================================================================
void CSceneGameMain::MoveExec3DObject()
{
	for( int i = 0;i < m_vec3DList.size();++i )
	{
		CDraw3DObject *pObj = m_vec3DList.at( i );
		
		pObj->MoveExec();
	}
}


//=============================================================================
//アクターインデックスの一括設定
//=============================================================================
//[input]
//	index:設定するインデックス
//=============================================================================
void CSceneGameMain::SetActorIndexAll( int index )
{
	for( int i = 0;i < m_vec3DList.size();++i )
	{
		CDraw3DObject *pObj = m_vec3DList.at( i );
		
		pObj->SetActorIndex( index );
	}
}

//=============================================================================
//表示フラグの一括設定
//=============================================================================
//[input]
//	flag:設定するフラグ
//=============================================================================
void CSceneGameMain::SetVisibleFlagAll( bool flag )
{
	for( int i = 0;i < m_vec3DList.size();++i )
	{
		CDraw3DObject *pObj = m_vec3DList.at( i );
		
		pObj->SetVisibleFlag( flag );
	}
}

//=============================================================================
//停止フラグの一括設定
//=============================================================================
//[input]
//	flag:設定するフラグ
//=============================================================================
void CSceneGameMain::SetStopFlagAll( bool flag )
{
	for( int i = 0;i < m_vec3DList.size();++i )
	{
		CDraw3DObject *pObj = m_vec3DList.at( i );
		
		pObj->SetStopFlag( flag );
	}
}












