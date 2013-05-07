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
	int MissionClrCount = 0;//�~�b�V�����̃N���A���J�E���g
	int Cursor = 0;
}

//=============================================================================
//�R���X�g���N�^
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
//�f�X�g���N�^
//=============================================================================
CSceneMissionSelect::~CSceneMissionSelect(void)
{

}

//=============================================================================
//������
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
		
		/*�������̐ݒ�*/
		m_pPinSpr->SetDivNum( Math::Point2DI( 2, 1 ) );
		
		/*�~�b�V�����̒ǉ�*/
		AppendMission();
		
		SetState( &CSceneMissionSelect::Idle );
	}
}

//=============================================================================
//�ҋ@��
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
				
		/*�~�b�V�����N���A���̃J�E���g�A�b�v*/
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
	
	/*�����_�����O*/	
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
	
	/*�~�b�V�����I��*/
	SelectMission( pMouse );
	
	time += dt;
	
	
}

//=============================================================================
//�I��
//=============================================================================
void CSceneMissionSelect::End( Uint32 dt )
{
	printf("[GameMissionSelect]::End\n");
	
	m_eSceneState = STATE_FINISH;
	
	SetState( &CSceneMissionSelect::Init );
	
}

//=============================================================================
//�X�V
//=============================================================================
eSceneState CSceneMissionSelect::UpDate()
{
	( this->*m_pStateFunc )( 1 );
	return m_eSceneState;
}



//=============================================================================
//�����_�����O
//=============================================================================
void CSceneMissionSelect::Rendering()
{
	/*�w�i�̕\��*/
	m_pMissionSelSpr->Rendering();
	
	/*�I���O�̎ʐ^�̕\��*/
	for( int i = 0; i < MissionClrCount+1; ++i )
	{
		CMission *pMission = GetMissionMgr()->GetMission(i);
		
		/*�I���O�̓O���[�X�P�[����*/
		pMission->GetMissionData().m_pPhotoSpr->DrawGrayScale( GetResMgr()->GetRenderer() );
		
	}
	
	/*�I������Ă���ʐ^�̕\��*/
	for( int i = 0;i < MISSION_MAX;++i )
	{
		CMission *pMission = GetMissionMgr()->GetMission(i);
		
		if( Cursor == i )
		{
			/*�I������Ă���̂̓J���[�\��*/
			pMission->GetMissionData().m_pPhotoSpr->Rendering();
			
			char Temp[10];
			
			sprintf( Temp, "%d", pMission->GetHiScore() );
			
			/*������̐ݒ�*/
			m_pMiContFont->SetVecTextChat( pMission->GetMissionData().m_vecMissionContent );
			
			/*�n�C�X�R�A�̕�����ݒ�*/
			m_pNumFont->SetDrawString( Temp ) ;
		}
		
	}
	
	/*�~�b�V�����^�C�g���̕\��*/
	for( int i = 0; i < MissionClrCount+1; ++i )
	{	
		CMission *pMission = GetMissionMgr()->GetMission(i);
		
		if( Cursor == i )
		{
			pMission->GetMissionData().m_pFontSpr->Rendering();
		}
		
	}
	
	/*�s���\���pID*/
	Math::Point2DF Anim[] =
	{
		Math::Point2DF( 0, 0 ),
		Math::Point2DF( 0, 0 ),
		Math::Point2DF( 0, 0 ),
		Math::Point2DF( 0, 0 ),
		Math::Point2DF( 0, 0 ),
	};
	
	/*�s���̕`��*/
	m_pPinSpr->Rendering();
	
	/*�~�b�V�������e�̕`��*/
	m_pMiContFont->Rendering();
	
	/*�n�C�X�R�A�̕`��*/
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
//�~�b�V�����̒ǉ�
//=============================================================================
void CSceneMissionSelect::AppendMission()
{
	File::IResourceFile *pResFile = NULL;
	
	/*�ǂݍ��݃f�B���N�g���̐ݒ�*/
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
		// �~�b�V������b�e�L�X�g�̓ǂݍ���
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
		// �~�b�V�������e�̓ǂݍ���
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
		// �~�b�V�����f�[�^����C�ɓǂݍ���
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
		
		/*�~�b�V�����̒ǉ�*/
		GetMissionMgr()->AppendMission( count, new CMission( dynamic_cast<CDraw3DObject *>( GetResMgr()->Get2DObject()->FindObjectFromName( datMission.m_TargetName ) ), datMission ) );
		
		count++;
	}
		
	ifsMission.close();
	

}

//=============================================================================
//�~�b�V�����̑I��
//=============================================================================
//[input]
//	pMouse:�ݒ肷��}�E�X�f�o�C�X
//=============================================================================
void CSceneMissionSelect::SelectMission( Peripheral::IMouse *pMouse )
{
	Math::Vector2D vMousePos( (float)( pMouse->GetPosX() ), (float)( pMouse->GetPosY() ) );
	
	for( int i = 0;i < MissionClrCount+1; ++i )
	{
		CMission *pMission = GetMissionMgr()->GetMission(i);
		
		Math::Rect2DF HitRect = pMission->GetMissionData().m_pPhotoSpr->GetHitRect();
		
		/*�����蔻��*/
		if( Collision::Point_Rect( vMousePos, HitRect ) )
		{
			Cursor = i;	
			
			/*�~�b�V��������*/
			DecideMission( pMouse );
		}
	}
	

}


//=============================================================================
//�~�b�V�����̌���
//=============================================================================
//[input]
//	pMouse:�ݒ肷��}�E�X�f�o�C�X
//=============================================================================
void CSceneMissionSelect::DecideMission( Peripheral::IMouse *pMouse )
{
	if( pMouse->GetStateL() == MOUSE_PUSH )
	{
		/*�~�b�V�����ԍ��̌���*/
		GetMissionMgr()->SetMissionNo( Cursor );
		
		/*�V�[���؂�ւ�*/
		SetState( &CSceneMissionSelect::End );
	}

}


//=============================================================================
//����
//=============================================================================
//[input]
//	pScene:�ݒ肷��V�[��
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
//	/*��������̕����`��*/
//	//pScene->GetAppDevice()->GetRenderer()->DrawTextA( Math::Point2DI( 600, 10 ), CColor( 255, 255, 255 ), "R2�{�^���@�~�b�V��������" );
//	
//	
//	/*�~�b�V�����T�v�̕`��*/
//	
//	/*�`��I��*/
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
//	/*�~�b�V�����̌���*/
//	if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_R2 ) )
//	{
//		pTitleMusic->GetBGMDevice()->Stop();
//		
//		/*�~�b�V�����ԍ��̐ݒ�*/
//		pScene->GetMissionMgr()->SetMissionNo( Cursor );
//		
//		CSoundEffect *sndDecide	= dynamic_cast<CSoundEffect *>( pScene->GetSoundObj()->FindObjectFromName("Decide") );
//			
//			
//		/*�~�j�L�����̍ő�*/
//		const int FLASH_CHARA = 9;
//		
//		/*�~�j�L�����̃I�u�W�F�N�g��*/
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
//		/*��U�S�~�j�L�������\���ɂ���*/
//		for( int i = 0;i < FLASH_CHARA;++i )
//		{	
//			CSprite *objMiniSpr = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName(MiniObjName[i]) ); 
//			objMiniSpr->SetVisibleFlag( false );
//			objMiniSpr->SetMissionVisible( false );
//		}
//		
//		/*�~�b�V�����ɂ���āA�\��������~�j�L������ς���*/
//			
//		/*���g���~�b�V����*/
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
//		/*�˂��݂����~�b�V����*/
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
