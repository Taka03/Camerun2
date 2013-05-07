//*============================================================================
//SceneMissionSelect.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneMissionSelect.h"
#include <fstream>

//=============================================================================
//namespace
//=============================================================================
namespace
{
	int time = 0;
	int MissionClrCount = 0;//ミッションのクリア数カウント
	int Cursor = 0;
}

//=============================================================================
//コンストラクタ
//=============================================================================
CSceneMissionSelect::CSceneMissionSelect( )
{
	//const string MissionPicture[] =
	//{
	//	"train.png",
	//	"ameus.png",
	//	"funsui.png",
	//	"oashisu.png",
	//	"manta.png",
	//};
	//
	//const Math::Vector3D vPicturePos[] =
	//{
	//	Math::Vector3D( 280, 150, 0 ),
	//	Math::Vector3D( 125, 240, 0 ),
	//	Math::Vector3D( 480, 70, 0 ),
	//	Math::Vector3D( 75, 80, 0 ),
	//	Math::Vector3D( 440, 260, 0 ),

	//};
	//
	//const Math::Vector3D vMissionSprPos[] =
	//{
	//	Math::Vector3D( 270, 208, 0 ),
	//	Math::Vector3D( 115, 298, 0 ),
	//	Math::Vector3D( 452, 128, 0 ),
	//	Math::Vector3D( 65, 138, 0 ),
	//	Math::Vector3D( 426, 318, 0 ),
	//};
	//
	//for( int i = 0;i < MISSION_MAX;++i )
	//{
	//	char Temp[256];
	//	char Temp2[256];
	//	
	//	sprintf( Temp, "Mission%d", i + 1 );
	//	sprintf( Temp2, "mission%d.dds", i + 1 );
	//	
	//	GetResMgr()->Push( new CFileData( Temp2, Temp, SPRITE, vMissionSprPos[i] ) );
	//	
	//	sprintf( Temp, "Picture%d", i + 1 );
	//	
	//	GetResMgr()->Push( new CFileData( MissionPicture[i], Temp, SPRITE, vPicturePos[i] ) );
	//	
	//}
	//
	//
	//GetResMgr()->Push( new CFileData( "missionselect.png", "MissionSelect", SPRITE, Math::Vector3D( 0, 0, 0 ) ) );
	//GetResMgr()->Push( new CFileData( "pin.dds", "Pin", SPRITE, Math::Vector3D( 0, 0, 0 ) ) );
	//
	//
	//GetResMgr()->Push( new CFileData( "NumFont.sff", "NumFont", FONT, Math::Vector3D( 80, 520, 0 ) ) );
	//GetResMgr()->Push( new CFileData( "MiContFont.sff", "ContentFont", FONT, Math::Vector3D( 340, 490, 0 ) ) );
	//
	//
	//SetState( &CSceneMissionSelect::Init );
	//
}

//=============================================================================
//デストラクタ
//=============================================================================
CSceneMissionSelect::~CSceneMissionSelect(void)
{

}

//=============================================================================
//初期化
//=============================================================================
void CSceneMissionSelect::Init( Uint32 dt )
{
	printf("[GameMissionSelect]::Init\n");
	
	if( !GetResMgr()->IsLoading() )
	{
		m_pMissionSelSpr = dynamic_cast<CSprite *>( GetResMgr()->Get2DObject()->FindObjectFromName("MissionSelect") );
		m_pPinSpr = dynamic_cast<CSprite *>( GetResMgr()->Get2DObject()->FindObjectFromName("Pin") );
		
		m_pNumFont = dynamic_cast<CFontSprite *>( GetResMgr()->Get2DObject()->FindObjectFromName("NumFont") );
	
		m_pMiContFont = dynamic_cast<CFontSprite *>( GetResMgr()->Get2DObject()->FindObjectFromName("ContentFont") );
		
		/*分割数の設定*/
		m_pPinSpr->SetDivNum( Math::Point2DI( 2, 1 ) );
		
		/*ミッションの追加*/
		AppendMission();
		
		SetState( &CSceneMissionSelect::Idle );
	}
}

//=============================================================================
//待機中
//=============================================================================
void CSceneMissionSelect::Idle( Uint32 dt )
{
	Peripheral::IMouse *pMouse = GetResMgr()->GetCore()->GetMouse();
	
	GetMouseCursor()->SetPosition( Math::Vector3D( toF( pMouse->GetPosX() ), 
												   toF( pMouse->GetPosY() ),
												   0.0f ) );
	
	
	printf("[GameMissionSelect]::Idle %d\n", time );
	
	#if defined(DEBUG) | (_DEBUG)  
	
		MissionClrCount = 4;
	
	#else
				
		/*ミッションクリア数のカウントアップ*/
		for( int i = 0; i < GetMissionMgr()->GetMissionNum(); ++i )
		{
			CMission *pMission = GetMissionMgr()->GetMission(i);
			
			if( pMission->GetGameClearFlag() )
			{
				MissionClrCount++;
				
			}
		}
		
		//MissionClrCount = 4;
		
		if( MissionClrCount >= 4 )
		{
			MissionClrCount = 4;
		}
				
				
	#endif
	
	/*レンダリング*/	
	Rendering();
	
	m_pMissionSelSpr->Exec();
	
	m_pNumFont->Exec();
	
	GetMouseCursor()->Exec();
	
	
	m_pMiContFont->DrawMultiLine();
	
	for( int i = 0; i < MissionClrCount+1; ++i )
	{
		CMission *pMission = GetMissionMgr()->GetMission(i);
		
		pMission->Exec();
	}
	
	/*ミッション選択*/
	SelectMission( pMouse );
	
	time += dt;
	
	
}

//=============================================================================
//終了
//=============================================================================
void CSceneMissionSelect::End( Uint32 dt )
{
	printf("[GameMissionSelect]::End\n");
	
	m_eSceneState = STATE_FINISH;
	
	SetState( &CSceneMissionSelect::Init );
	
}

//=============================================================================
//更新
//=============================================================================
eSceneState CSceneMissionSelect::UpDate()
{
	( this->*m_pStateFunc )( 1 );
	return m_eSceneState;
}



//=============================================================================
//レンダリング
//=============================================================================
void CSceneMissionSelect::Rendering()
{
	/*背景の表示*/
	m_pMissionSelSpr->Rendering();
	
	/*選択外の写真の表示*/
	for( int i = 0; i < MissionClrCount+1; ++i )
	{
		CMission *pMission = GetMissionMgr()->GetMission(i);
		
		/*選択外はグレースケールで*/
		pMission->GetMissionData().m_pPhotoSpr->DrawGrayScale( GetResMgr()->GetRenderer() );
		
	}
	
	/*選択されている写真の表示*/
	for( int i = 0;i < MISSION_MAX;++i )
	{
		CMission *pMission = GetMissionMgr()->GetMission(i);
		
		if( Cursor == i )
		{
			/*選択されているのはカラー表示*/
			pMission->GetMissionData().m_pPhotoSpr->Rendering();
			
			char Temp[10];
			
			sprintf( Temp, "%d", pMission->GetHiScore() );
			
			/*文字列の設定*/
			m_pMiContFont->SetVecTextChat( pMission->GetMissionData().m_vecMissionContent );
			
			/*ハイスコアの文字列設定*/
			m_pNumFont->SetDrawString( Temp ) ;
		}
		
	}
	
	/*ミッションタイトルの表示*/
	for( int i = 0; i < MissionClrCount+1; ++i )
	{	
		CMission *pMission = GetMissionMgr()->GetMission(i);
		
		if( Cursor == i )
		{
			pMission->GetMissionData().m_pFontSpr->Rendering();
		}
		
	}
	
	/*ピン表示用ID*/
	Math::Point2DF Anim[] =
	{
		Math::Point2DF( 0, 0 ),
		Math::Point2DF( 0, 0 ),
		Math::Point2DF( 0, 0 ),
		Math::Point2DF( 0, 0 ),
		Math::Point2DF( 0, 0 ),
	};
	
	/*ピンの描画*/
	m_pPinSpr->Rendering();
	
	/*ミッション内容の描画*/
	m_pMiContFont->Rendering();
	
	/*ハイスコアの描画*/
	m_pNumFont->Rendering();
	
	
	for( int i = 0; i < MissionClrCount+1; ++i )
	{	
		Math::Point2DF Pos[] =
		{
			Math::Point2DI( 383, 142 ),
			Math::Point2DI( 228, 232 ),
			Math::Point2DI( 583, 62 ),
			Math::Point2DI( 178, 72 ),
			Math::Point2DI( 543, 252 ),
		};

		CMission *pMission = GetMissionMgr()->GetMission(i);
	
		if( pMission->GetGameClearFlag() )	
		{
			Anim[i].x = 1;
			
		}
		
		else
		{
			Anim[i].x = 0;
		}
		
		//m_pPinSpr->DrawMultiGraph( Pos, Anim,  MissionClrCount + 1 );		
		
	}
	
	GetMouseCursor()->Rendering();
	
	
}

//=============================================================================
//ミッションの追加
//=============================================================================
void CSceneMissionSelect::AppendMission()
{
	File::IResourceFile *pResFile = NULL;
	
	/*読み込みディレクトリの設定*/
	GetResMgr()->GetFileMgr()->SetCurrentPath("CSV");
	
	pResFile = GetResMgr()->GetFileMgr()->FileOpen("mission.csv");
	
	ifstream ifsMission( pResFile->GetNamePointer() );
	
	SAFE_RELEASE( pResFile );
	
	char MissionTemp[256];
	
	ifsMission.getline( MissionTemp, 256 );
	
	GetResMgr()->GetFileMgr()->SetCurrentPath("Text");
	
	while( !ifsMission.eof() )
	{
		char Temp[20] = "";
		
		static int count = 0;
		
		MissionData datMission;
		char TempMissionName[256];
		char TempTargetName[256];
		char TempChat[1024];
		
		//-----------------------------------------------------------------
		// ミッション会話テキストの読み込み
		//-----------------------------------------------------------------
		sprintf( Temp, "Mission%d.txt", count+1);
		
		pResFile = 	GetResMgr()->GetFileMgr()->FileOpen(Temp);
		
		ifstream ifs( pResFile->GetNamePointer() );
		
		SAFE_RELEASE( pResFile );
		
		#if defined (DEBUG) | (_DEBUG)
		#endif
		
		while( !ifs.eof() )
		{	
			ifs >> TempChat;
			datMission.m_vecChat.push_back( TempChat );
		}
		
		ifs.close();
		
		//-----------------------------------------------------------------
		// ミッション内容の読み込み
		//-----------------------------------------------------------------
		sprintf( Temp, "MissionContent%d.txt", count+1 );
		
		pResFile = 	GetResMgr()->GetFileMgr()->FileOpen(Temp);
		
		ifstream ifsContent( pResFile->GetNamePointer() );
		
		char TempMiCont[256] = "";
		
		SAFE_RELEASE( pResFile );
		
		while( !ifsContent.eof() )
		{
			ifsContent >> TempMiCont;
			datMission.m_vecMissionContent.push_back( TempMiCont );
		}
		
		ifsContent.close();
		
		//-----------------------------------------------------------------
		// ミッションデータを一気に読み込む
		//-----------------------------------------------------------------
		ifsMission >> TempMissionName >> TempTargetName >> datMission.m_ClearPoint >> datMission.m_FilmNum 
		>> datMission.m_LimitTime.Min >> datMission.m_LimitTime.Sec >> datMission.m_TimeBorder.Min >> datMission.m_TimeBorder.Sec
		>> datMission.m_TargetPosMin >> datMission.m_TargetPosMax >> datMission.m_DistanceMin >> datMission.m_DistanceMax ;
		
		datMission.m_MissionName = TempMissionName;
		datMission.m_TargetName = TempTargetName;
		
		sprintf( Temp, "Mission%d", count+1 );
		
		datMission.m_pFontSpr = dynamic_cast<CSprite *>( GetResMgr()->Get2DObject()->FindObjectFromName(Temp) );		
		
		sprintf( Temp, "Picture%d", count+1 );
		
		datMission.m_pPhotoSpr = dynamic_cast<CSprite *>( GetResMgr()->Get2DObject()->FindObjectFromName(Temp) );	
		
		/*ミッションの追加*/
		GetMissionMgr()->AppendMission( count, new CMission( dynamic_cast<CDraw3DObject *>( GetResMgr()->Get2DObject()->FindObjectFromName( datMission.m_TargetName ) ), datMission ) );
		
		count++;
	}
		
	ifsMission.close();
	

}

//=============================================================================
//ミッションの選択
//=============================================================================
//[input]
//	pMouse:設定するマウスデバイス
//=============================================================================
void CSceneMissionSelect::SelectMission( Peripheral::IMouse *pMouse )
{
	Math::Vector2D vMousePos( (float)( pMouse->GetPosX() ), (float)( pMouse->GetPosY() ) );
	
	for( int i = 0;i < MissionClrCount+1; ++i )
	{
		CMission *pMission = GetMissionMgr()->GetMission(i);
		
		Math::Rect2DF HitRect = pMission->GetMissionData().m_pPhotoSpr->GetHitRect();
		
		/*当たり判定*/
		if( Collision::Point_Rect( vMousePos, HitRect ) )
		{
			Cursor = i;	
			
			/*ミッション決定*/
			DecideMission( pMouse );
		}
	}
	

}


//=============================================================================
//ミッションの決定
//=============================================================================
//[input]
//	pMouse:設定するマウスデバイス
//=============================================================================
void CSceneMissionSelect::DecideMission( Peripheral::IMouse *pMouse )
{
	if( pMouse->GetStateL() == MOUSE_PUSH )
	{
		/*ミッション番号の決定*/
		GetMissionMgr()->SetMissionNo( Cursor );
		
		/*シーン切り替え*/
		SetState( &CSceneMissionSelect::End );
	}

}


//=============================================================================
//処理
//=============================================================================
//[input]
//	pScene:設定するシーン
//=============================================================================
//void CSceneMissionSelect::Exec( CScene *pScene )
//{
//	
//	
//	//pExpFont->Rendering();
//	
//	pNumFont->Exec();
//	
//	pMiContFont->DrawMultiLine();
//	
//	pExpFont->DrawMultiLine( vPos );
//	//pMiContFont->Exec();
//	
//	/*操作説明の文字描画*/
//	//pScene->GetAppDevice()->GetRenderer()->DrawTextA( Math::Point2DI( 600, 10 ), CColor( 255, 255, 255 ), "R2ボタン　ミッション決定" );
//	
//	
//	/*ミッション概要の描画*/
//	
//	/*描画終了*/
//	pRender->End();
//	
//	for( int i = 0; i < MissionClrCount+1; ++i )
//	{
//		CMission *pMission = pScene->GetMissionMgr()->GetMission(i);
//		
//		pMission->Exec();
//	}
//	
//	pBG->Exec();
//	
//	static bool IsFade = false;
//	
//	/*ミッションの決定*/
//	if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_R2 ) )
//	{
//		pTitleMusic->GetBGMDevice()->Stop();
//		
//		/*ミッション番号の設定*/
//		pScene->GetMissionMgr()->SetMissionNo( Cursor );
//		
//		CSoundEffect *sndDecide	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Decide") );
//			
//			
//		/*ミニキャラの最大*/
//		const int FLASH_CHARA = 9;
//		
//		/*ミニキャラのオブジェクト名*/
//		const char *MiniObjName[] =
//		{
//			"Mini_Bird1",
//			"Mini_Bird2",
//			"Mini_Bird3",
//			"Mini_Bird4",
//			"Mini_Bird5",
//			"Mini_Bird6",
//			"Mini_Mouse1",
//			"Mini_Mouse2",
//			"Mini_Mouse3",
//		};
//			
//		/*一旦全ミニキャラを非表示にする*/
//		for( int i = 0;i < FLASH_CHARA;++i )
//		{	
//			CSprite *objMiniSpr = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName(MiniObjName[i]) ); 
//			objMiniSpr->SetVisibleFlag( false );
//			objMiniSpr->SetMissionVisible( false );
//		}
//		
//		/*ミッションによって、表示させるミニキャラを変える*/
//			
//		/*鳥使うミッション*/
//		if( Cursor == 2 )
//		{
//			for( int BirdNum = 0;BirdNum < BIRD_MAX;++BirdNum )
//			{
//				CSprite *objMiniSpr = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName(MiniObjName[BirdNum]) ); 
//				
//				objMiniSpr->SetMissionVisible( true );
//			}
//		}
//		
//		/*ねずみつかうミッション*/
//		else if( Cursor == 3 )
//		{
//			for( int MouseNum = BIRD_MAX; MouseNum < FLASH_CHARA;++MouseNum )
//			{
//				CSprite *objMiniSpr = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName(MiniObjName[MouseNum]) ); 
//				
//				objMiniSpr->SetMissionVisible( true );
//				
//			}
//		}
//			
//		pBG->SetVisibleFlag( false );
//		
//		for( int i = 0; i < MISSION_MAX; ++i )
//		{
//			CMission *pMission = pScene->GetMissionMgr()->GetMission(i);
//			
//			pMission->GetMissionData().m_pFontSpr->SetVisibleFlag( false );
//			
//			pMission->GetMissionData().m_pPhotoSpr->SetVisibleFlag( false );
//			
//			pPin->SetVisibleFlag( false );
//			
//			
//		}
//		
//		pScene->SetNextScene( SCENE_CHAT );
//		
//		
//		//if( pScene->GetSceneState() == STATE_FADEOUT )
//		//{
//		//	pTitleMusic->FadeOut();
//		//}
//		//
//		//else
//		//{
//		//	pTitleMusic->GetBGMDevice()->SetVolume( 100 );
//		//}
//		
//		
//		vecText.clear();
//		
//		pExpFont->SetVecTextChat( vecText );
//		
//		pScene->SetSceneState( STATE_FADEOUT );	
//		
//		if( pScene->GetSceneState() == STATE_STANDBY )
//		{	
//			sndDecide->GetSEDevice()->Play( 0 );
//		}
//		
//			
//	}
//	
//	
//	eInputButtonType eButtonUpDown = pScene->GetJoyPad()->GetController()->CursorRepeatUpDown( 0, Cursor, MissionClrCount+1 );
//	
//	if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, eButtonUpDown ) )
//	{
//		CSoundEffect *sndSelect	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Select") );
//		sndSelect->GetSEDevice()->Play( 0 );
//	}
//	
//	//eInputButtonType eButtonUpDown = pScene->GetJoyPad()->GetController()->CursorRepeatUpDown( 0, Cursor, 4 );
//
//}
