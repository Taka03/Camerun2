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
	float fMoveDistance = 0.0f;//���̋���
	Sint32 MoveAngle = 0;//���̌����Ă���ʒu	
	Math::Vector3D vMousePos( 0, 0, 0 );
	Math::Vector3D vOldMousePos( 0, 0, 0 );
	Math::Vector3D vMovePos( 0, 0, 0 );//�ړ��ʒu
	Math::Vector3D vTargetPos( 0, 0, 0 );
	Uint32 TutorialCount = 0;
	const int TIME_MAX = 60 * 3;
	int TotalScore = 0;//���v�X�R�A
	int count = 0;//�����J�E���^�[
	int MarkerIdx = 0;//�}�[�J�[�J�E���^�[
	int ShowEnemyCount = 0;//�G�\���J�E���g
	int AddFuncCount = 0;//�ǉ��@�\�J�E���g
	int ShootEnemyCount = 0;//�G�̎ʐ^�ɉf���Ă��鐔
	vector< CPhoto::PhotoCheckData > vecPhotoData;//�ʐ^����f�[�^
	
	const int LOCKON_MAX = 3;//���b�N�I���̍ő吔
	bool IsAddEnemy[CSceneGameMain::ELEM_MAX - 2];
	
	vector< string > vecStr;
	
	int CamCnt = 0;//�J�����p�J�E���^

}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	strFileName:�t�@�C����
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
	
	//�t�H���g�̐ݒ�
	CCommonObject::GetAppli()->GetRenderer()->SetDrawTextFont( "MS �S�V�b�N", 60, 2 );
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneGameMain::~CSceneGameMain(void)
{
}

//=============================================================================
//�I�u�W�F�N�g�f�[�^�̏�����
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
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
			/*�X�J�C�h�[���̍쐬*/
			CCommonObject::GetSceneMgr(i)->CreateSkyDoom( pCloud->GetTexture() );
		}
		
		CCommonObject::GetResMgr()->RemoveObject( pCloud );
		
		/*2D�I�u�W�F�N�g�̒ǉ�*/
		Push2DObject();
		
		//�����_���[�̐ݒ�
		m_pMiniMap->SetRenderer( CCommonObject::GetAppli()->GetRenderer() );
		
		/*�������̐ݒ�*/
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
		
		
		/*�`���[�g���A���p�̓G*/
		CEnemy *pTrlEnemy[] =
		{
			m_pRabbit,//�}���^(�{���͂�����)
			m_pAmeus,//�A���E�X
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
//������
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
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
	
	//�I�u�W�F�N�g�̏�����
	InitAll();
	
	/*�I�u�W�F�N�g�̏�����*/
	//CCommonObject::GetResMgr()->Get3DObject()->Init();
	//
	//CCommonObject::GetResMgr()->Get2DObject()->Init();
	//
	/*�J�����̏�����*/
	for( int i = 0;i < SCREEN_MAX;++i )
	{
		CCommonObject::GetCamera( i )->Init();
	}
	
	/*�t�B���������̏�����*/
	SetFilmCount( 0 );
	
	SetTotalScore( 0 );
	
	m_pField->SetRotate( Math::Point3DI( 0, 0, 0 ) );
	
	SetFingState( FING_NONE );
	
	LoadMission();//�~�b�V�����̃��[�h	
	
	/*�`���[�g���A�����[�h�̏ꍇ*/
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
//�ҋ@��
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CSceneGameMain::Idle( Uint32 dt )
{
	m_eSceneState = STATE_CONTINUE;
	
	/*�ʐ^����{�b�N�X�̐���*/
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
	

	///*�|�[�Y��ʂւ̈ڍs*/
	//MovePauseMenu();
	

	
	/*�n�ʃ`�F�b�N*/
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
		if( !GetTutorialFlag() && pEnemy->GetStTypeName().compare("�t���X�C") != 0 )
		{	
			pEnemy->GroundCheck( m_pField );
		}
	}
	
	/*�����_�����O*/	
	Rendering();
	
	//----------------------------------------------
	//��ʐݒ�
	//----------------------------------------------
	/*�p�����[�^�ݒ�*/
	SetScreenParam();
	
	/*�ݒ�̃����_�����O*/
	RenderingSetting();
		
	/*�n�ʕ␳*/
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
//�f��
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
//�Q�[����
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
		/*�}�E�X�X�v���C�g��ԏ���*/
		MouseSprExec();
		
	}
	
	/*�^�[�Q�b�g���̏���*/
	TargetArrowExec();
	
	for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
	{
		CEnemy *pEnemy = *i;
		
		//�G�ƃv���C���[�Ƃ̔���
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
//�Q�[���I��
//=============================================================================
void CSceneGameMain::GameEnd()
{
	static int count = 0;
	
	m_pEndSpr->SetVisibleFlag( true );
	
	memset( m_IsAddFunc, false, sizeof( bool ) * FUNC_MAX );
	
	/*�ړ��@�\�����c��*/
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
//�|�[�Y��ʂւ̈ڍs
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
//�X�R�A�̕`��
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
	
	/*�����_�����O*/
	m_pNumFont[OPTION_SCORE]->Rendering();
	
}

//=============================================================================
//�t�B���������̕`��
//=============================================================================
void CSceneGameMain::DrawFilmNum()
{
	char Temp[10];
	
	sprintf_s( Temp, 10, "%d", FILM_MAX - GetFilmCount() );
	
	m_pNumFont[OPTION_FILM]->SetDrawString( Temp );
	
	m_pNumFont[OPTION_FILM]->Exec();
	
	/*�����_�����O*/
	m_pNumFont[OPTION_FILM]->Rendering();
	
}



//=============================================================================
//�I��
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CSceneGameMain::End( Uint32 dt )
{
	printf("[CSceneGameMain]::End\n");
	
	m_eSceneState = STATE_FINISH;
	
	SetState( &CSceneTemplate::Init );
	
	
}


//=============================================================================
//�����_�����O
//=============================================================================
void CSceneGameMain::Rendering()
{
	/*�V�[���̃����_�����O*/
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
	
	//�~�j�}�b�v�̕\��
	if( !GetTutorialFlag() )
	{	
		ShowMiniMap();

		
	}
	
		

	if( !m_pPlayer->GetStopFlag() )
	{
		
		/*�ړ��}�[�J�[�̕\��*/
		ShowMarker();
		
		/*2D���X�g�̏���*/
		Exec2DList();
		
		
		/*�ړ��J�[�\���̕\��*/
		DrawMoveCursor();
		

		/*2D���X�g�̃����_�����O*/
		Rendering2DList();
		
		/*�X�R�A�̕`��*/
		DrawScore();
		
		/*�t�B���������̕`��*/
		DrawFilmNum();
		
		/*�w�A�C�R���̏���*/
		FingIcoExec();
		
		/*�ǉ��@�\�̏���*/
		AddFuncExec();
		
		/*�`���[�g���A���̏ꍇ�̃����_�����O*/
		RenderingTutorial();
		
		/*�@�\�̃����_�����O����*/
		RenderFuncExec();
		
	}
	
	if( !GetTutorialFlag() )
	{
		CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
		
		m_pMissionWinSpr->Exec();
		m_pMissionWinSpr->Rendering();
		
		CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_NORMAL );
		

	}
	
	
	//�}�E�X�A�C�R���̃����_�����O
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
		//�~�b�V�����̕`��
		DrawMission();
	}
	
	
	/*�f�o�b�O���̕\��*/
	#if defined( DEBUG ) | ( _DEBUG )	
		ShowDebugInfo();
	#endif
	
}


//=============================================================================
//���C�����̏�����
//=============================================================================
void CSceneGameMain::InitMain()
{
	const int CLEAR_OBJECT = 4;//��\���ɂ���I�u�W�F�N�g��
	
	/*�����Ă����I�u�W�F�N�g��\������悤��*/
	CDraw3DObject *pClearObj[] =
	{
		m_pField,
		m_pTrain,
		m_pFountObj,
		m_pIsLand,
	};
	
	/*�S�@�\�̒ǉ�*/
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
	
	//�N���A���̃I�u�W�F�N�g�̐ݒ�
	//SetClearObject();
	
	/*�}�E�X�\���X�v���C�g�̐ݒ�*/
	m_pMouseSpr->SetVisibleFlag( false );
	
	m_pArrowExpSpr->SetVisibleFlag( false );
	
	SetTutorialFlag( false );
	
	//�^�[�Q�b�g�̐ݒ�
	LoadMission();
	
	m_pMissionWinSpr->SetVisibleFlag( true );
	
	
	SetBGM( m_pGameMusic );
	
	
}

//=============================================================================
//�`���[�g���A���̏�����
//=============================================================================
void CSceneGameMain::InitTutorial()
{
	const int CLEAR_OBJECT = 4;//��\���ɂ���I�u�W�F�N�g��
	
	/*�]�v�ȃI�u�W�F�N�g���\���ɂ���*/
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
	
	/*���̑��̋@�\�́A�ŏ��͋@�\�����Ȃ�*/
	/*�S�@�\�̒ǉ�*/
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
//�`���[�g���A���̃����_�����O
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
/*��������X�N���v�g�̌ʏ���*/
//=================================================================================================

//=============================================================================
//���N���b�N���������Ƃ��̏���
//=============================================================================
void CSceneGameMain::LeftClickScript()
{
	if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH && !m_pCamBtnSpr->GetCamMoveFlag() )
	{
		GetWindowSpr()->AddStrCount( 1 );
		
		m_eMouseSprState = MOUSE_PUSHNONE;
	}
	
	/*�}�E�X���{�^���N���b�N�摜�̕\��*/
	else 
	{
		m_eMouseSprState = MOUSE_PUSHLEFT;
	
	}
}

//=============================================================================
//�E�N���b�N���������Ƃ��̏���
//=============================================================================
void CSceneGameMain::RightClickScript()
{
	if( CCommonObject::GetMouse()->GetMouse()->GetStateR() == MOUSE_PUSH && !m_pCamBtnSpr->GetCamMoveFlag() )
	{
		GetWindowSpr()->AddStrCount( 1 );
		
		m_eMouseSprState = MOUSE_PUSHNONE;
	}
	
	/*�}�E�X�E�{�^���N���b�N�摜�̕\��*/
	else 
	{
		m_eMouseSprState = MOUSE_PUSHRIGHT;
	}

}

//=============================================================================
//�h���b�O�����Ƃ��̏���
//=============================================================================
void CSceneGameMain::DragScript()
{
	bool IsMoveMouse = ( CCommonObject::GetMouse()->GetMouse()->GetMoveX() != 0 || CCommonObject::GetMouse()->GetMouse()->GetMoveY() != 0 );//�}�E�X�������Ă��邩
	
	if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_HOLD && IsMoveMouse
		&& !m_pCamBtnSpr->GetCamMoveFlag()  )
	{
		GetWindowSpr()->AddStrCount( 1 );
		
		m_eMouseSprState = MOUSE_PUSHNONE;
		

	}
	
	/*�}�E�X�h���b�O�摜�̕\��*/
	else
	{
		m_eMouseSprState = MOUSE_DRAG;
	}

}

//=============================================================================
//�J������]���̏���
//=============================================================================
void CSceneGameMain::CameraRotScript()
{
	Math::Vector2D vPos = Math::Vector2D( vMousePos.x, vMousePos.y );
	
	/*�J�������ړ����Ă����b��i�߂�*/
	if( m_pCamBtnSpr->GetCamMoveFlag() )
	{
		m_eMouseSprState = MOUSE_PUSHNONE;
		
		/*�����\��*/
		SetFingState( CSceneBase::FING_NONE );
		
		GetWindowSpr()->AddStrCount( 1 );
		m_pCamBtnSpr->SetVisibleFlag( true );
		
	}
	
	/*�_�ŉ摜�̕\��*/
	else
	{
		m_eMouseSprState = MOUSE_PUSHLEFT;
		
		/*�E�����̖��\��*/
		SetFingState( CSceneBase::FING_RIGHT );
		
		
		GetFingerSpr()->SetInitPosition( m_pCamBtnSpr->GetPosition() + Math::Vector2D( 120.0f, 90.0f ) );
		
		
		
	}

}

//=============================================================================
//�J�������Z�b�g���̏���
//=============================================================================
void CSceneGameMain::CameraResetScript()
{
	Math::Vector2D vPos = Math::Vector2D( vMousePos.x, vMousePos.y );
	
	/*�J�������ړ����Ă����b��i�߂�*/
	if( m_pCamBtnSpr->GetCamResetFlag() )
	{
		m_eMouseSprState = MOUSE_PUSHNONE;
		
		/*�����\��*/
		SetFingState( CSceneBase::FING_NONE );
		
		GetWindowSpr()->AddStrCount( 1 );
		m_pCamBtnSpr->GetResetButton()->SetVisibleFlag( true );
		
	}
	
	/*�_�ŉ摜�̕\��*/
	else
	{
		m_eMouseSprState = MOUSE_PUSHLEFT;
		
		/*�E�����̖��\��*/
		SetFingState( CSceneBase::FING_RIGHT );
		
		GetFingerSpr()->SetInitPosition( m_pCamBtnSpr->GetResetButton()->GetPosition() - 
										 Math::Vector2D( 110.0f, 0 ) );
		
		
	}

}

//=============================================================================
//���������̏���
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
//�X�R�A�������X�N���v�g
//=============================================================================
void CSceneGameMain::ScoreExpScript()
{
	if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
	{
		GetWindowSpr()->AddStrCount( 1 );
		m_pNumFont[OPTION_SCORE]->SetVisibleFlag( true );
		
		/*�����\��*/
		SetFingState( CSceneBase::FING_NONE );
		
		m_eMouseSprState = MOUSE_PUSHNONE;
		
	}
	
	else
	{
		m_eMouseSprState = MOUSE_PUSHLEFT;
		
		/*������̖��\��*/
		SetFingState( CSceneBase::FING_UP );
		
		GetFingerSpr()->SetInitPosition( m_pNumFont[OPTION_SCORE]->GetPosition() 
										 + Math::Vector2D( 150.0f, 90.0f ) );
		
	}
}

//=============================================================================
//�t�B�����������X�N���v�g
//=============================================================================
void CSceneGameMain::FilmExpScript()
{
	if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
	{
		GetWindowSpr()->AddStrCount( 1 );
		m_pNumFont[OPTION_FILM]->SetVisibleFlag( true );
		m_eMouseSprState = MOUSE_PUSHNONE;
		
		/*�����\��*/
		SetFingState( CSceneBase::FING_NONE );
		
		
		
	}
	
	else
	{
		m_eMouseSprState = MOUSE_PUSHLEFT;

		
		/*������̖��\��*/
		SetFingState( CSceneBase::FING_UP );
		
		GetFingerSpr()->SetInitPosition( m_pNumFont[OPTION_FILM]->GetPosition() +
										 Math::Vector2D( 0, 100.0f ) );
		
	}
	

}

//=============================================================================
//�^�[�Q�b�g�\���p�X�N���v�g
//=============================================================================
void CSceneGameMain::TargetShowScript()
{
	
	m_pTrlEnemy[ShowEnemyCount]->SetVisibleFlag( true );
	
	m_pTrlEnemy[ShowEnemyCount]->SetPosition( Math::Vector3D( 31, 0, -46 ) );
	
	if( m_pTrlEnemy[ShowEnemyCount]->GetVisibleFlag() )
	{
		GetWindowSpr()->AddStrCount( 1 );
	}
	
	/*TODO:�G�t�F�N�g�\��*/
	
}

//=============================================================================
//�^�[�Q�b�g�����p�X�N���v�g
//=============================================================================
void CSceneGameMain::TargetClearScript()
{
	m_pRabbit->SetVisibleFlag( false );
	
	ShowEnemyCount++;
	
	SetTarget( m_pTrlEnemy[ShowEnemyCount] );
	
	GetWindowSpr()->AddStrCount( 1 );
	
	/*TODO:�G�t�F�N�g�\��*/
	
	
}

//=============================================================================
//�^�[�Q�b�g�|�C���g�\���p�X�N���v�g
//=============================================================================
void CSceneGameMain::TargetPlaceScript()
{
	static bool IsReachPlace = false;//�^�[�Q�b�g�̏ꏊ�ɂ��ǂ蒅������
	
	if( m_pPlayer->GetPosition().x < 0 && m_pPlayer->GetCaptureFlag() )
	{
		IsReachPlace = true;
		
	}
	
	if( IsReachPlace )
	{
		GetWindowSpr()->AddStrCount( 1 );	
		IsReachPlace = false;
		
		/*����\��*/
	}
}

//=============================================================================
//�^�[�Q�b�g�̎B�e
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
//�L���b�`�����X�N���v�g
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
//�@�\�ǉ��X�N���v�g
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
//�����[�X�{�^���X�N���v�g
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
		
		/*�����\��*/
		SetFingState( CSceneBase::FING_NONE );
		
	}
	
	else
	{
		m_eMouseSprState = MOUSE_PUSHLEFT;
		
		/*�E�����̖��\��*/
		SetFingState( CSceneBase::FING_RIGHT );
		
		GetFingerSpr()->SetInitPosition( m_pReleaseBtnSpr->GetPosition() -
										 Math::Vector2D( 110.0f, 0.0f ) );
	}

}

//=============================================================================
//���j���[�\���p�X�N���v�g
//=============================================================================
void CSceneGameMain::MenuScript()
{
	Math::Vector2D vPos = CCommonObject::GetMouse()->GetMousePos();
	
	if( Collision::Point_Rect( vPos, m_pMenuBtnSpr->GetHitRect() )
		 && CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
	{
		GetWindowSpr()->AddStrCount( 1 );				
		m_eMouseSprState = MOUSE_PUSHNONE;
		
		/*����\��*/
		SetFingState( CSceneBase::FING_NONE );
		
		CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_CHANGE );
		
	}
	
	else
	{
		m_eMouseSprState = MOUSE_PUSHLEFT;
		
		/*�E�����̖��\��*/
		SetFingState( CSceneBase::FING_DOWN );
		
		GetFingerSpr()->SetInitPosition( m_pMenuBtnSpr->GetPosition() - 
										 Math::Vector2D( 20.0f, 80.0f ) );
	}

}

//=============================================================================
//�I���X�N���v�g
//=============================================================================
void CSceneGameMain::EndScript()
{
	
	//��񂾂��V�v�f�\����ʂɈڂ�
	if( GetFirstGameFlag() )
	{	
		SetNextScene( SCENE_NEWELEM );
		
		/*�v���C�ς݃t���O�𗧂Ă�*/
		SetFirstGameFlag( false );
	
	}
	
	else
	{
		SetNextScene( SCENE_TITLE );
	}
	
	/*�`���[�g���A�����I������*/
	SetTutorialFlag( false );
	
	m_pAmeus->SetVisibleFlag( false );	
	
	m_pTrlMusic->GetBGMDevice()->Stop();
	
	for( Uint32 i = 0;i < GetFilmCount();++i )
	{
		char Temp[10];
		
		sprintf_s( Temp, 10, "Photo%d", i );
		
		CPhoto *pPhoto = dynamic_cast<CPhoto *>( CCommonObject::GetResMgr()->FindObject(Temp) );
		
		/*����ʐ^�B�e�ł���悤�ɍ폜*/
		CCommonObject::GetResMgr()->RemoveObject( pPhoto );
	}
	
	
	
	
	SetState( &CSceneTemplate::End );	
}

//=============================================================================
//���̑��̃X�N���v�g
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
/*�����܂ŃX�N���v�g�̌ʏ���*/
//=================================================================================================

//=============================================================================
//�ǉ��֐�����
//=============================================================================
void CSceneGameMain::AddFuncExec()
{
	/*�֐��e�[�u��*/
	AddFunc FuncTbl[] = 
	{
		&CSceneGameMain::MoveFunc,//�ړ��@�\
		&CSceneGameMain::CameraRotFunc,//�J������]�@�\
		&CSceneGameMain::CameraResetFunc,//�J�������Z�b�g�@�\
		&CSceneGameMain::ShootTargetFunc,//�ʐ^�B�e�@�\
		&CSceneGameMain::MenuFunc,//���j���[�@�\
		&CSceneGameMain::CaptureFunc,//�ߊl�@�\
		&CSceneGameMain::ReleaseFunc,//����@�\

	};
	
	for( int i = 0;i < FUNC_MAX;++i )
	{	
		/*�@�\������Ă�������s*/
		if(	m_IsAddFunc[i] )
		{
			(this->*FuncTbl[i])();
		}
	}
	
}


//=================================================================================================
/*��������ǉ��֐��̌ʏ���*/
//=================================================================================================

//=============================================================================
//�ړ��@�\
//=============================================================================
void CSceneGameMain::MoveFunc()
{
	#if defined( CAM_TOOL )
	
		m_pPlayer->Move( CCommonObject::GetCamera(SCREEN_MAIN), CCommonObject::GetMouse()->GetMouse(), m_pField, CCommonObject::GetSceneMgr( SCREEN_MAIN )->GetSceneMgr() );
		
	
	#else
	
		/*�ړ��}�[�N���\������Ă��āA�J������]���Ă��Ȃ��Ƃ��ړ�����*/
		if( m_pPlayer->GetState() != CPlayer::STATE_CAPSTART &&
			m_pPlayer->GetState() != CPlayer::STATE_RELSTART &&
			m_pPlayer->GetState() != CPlayer::STATE_HIT_ENEMY )
		{	
			if( !m_pCamBtnSpr->GetCamMoveFlag() )
			{
				/*�ߊl���Ă��Ȃ��Ƃ��́A�v���C���[�B�ߊl���Ă���Ƃ��͕ߊl�����G�𓮂���*/
				if( m_pPlayer->GetCaptureFlag() )
				{	
					/*�ߊl���̂Ƃ��́A�G�̊p�x�ƘA��*/
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
		
		
		
		/*�G�Ɋ��ݕt���Ă���Œ��̎��́A���[�V������ω������Ȃ�*/
		//if( m_pPlayer->GetState() != CPlayer::STATE_CAPSTART && 
		//	m_pPlayer->GetState() != CPlayer::STATE_CAPTURE  &&
		//	m_pPlayer->GetState() != CPlayer::STATE_RELSTART &&
		//	m_pPlayer->GetState() != CPlayer::STATE_RELEASE &&
		//	m_pPlayer->GetState() != CPlayer::STATE_HIT_ENEMY &&
		//	m_pPlayer->GetState() != CPlayer::stat)
		if( m_pPlayer->GetState() == CPlayer::STATE_NONE ||
			m_pPlayer->GetState() == CPlayer::STATE_MOVING )
		{
			
			/*�ړ��x�N�g�����傫���������Ă�����ړ��A���Ȃ������痧�����*/
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
//�J������]�@�\
//=============================================================================
void CSceneGameMain::CameraRotFunc()
{
	CCamera *pSetCam[] =
	{
		CCommonObject::GetCamera( SCREEN_MAIN ),
		CCommonObject::GetCamera( SCREEN_SUB ),
	};
	
	/*�J�����ړ�*/
	if( m_pPlayer->GetState() != CPlayer::STATE_MOVING )
	{
			m_pCamBtnSpr->Move( pSetCam, CCommonObject::GetResMgr(), m_pPlayer );
	}
	
}

//=============================================================================
//�J�������Z�b�g�@�\
//=============================================================================
void CSceneGameMain::CameraResetFunc()
{
	CCamera *pSetCam[] =
	{
		CCommonObject::GetCamera( SCREEN_MAIN ),
		CCommonObject::GetCamera( SCREEN_SUB ),
	};
	
	/*�J�������Z�b�g*/
	m_pCamBtnSpr->Reset( pSetCam, m_pPlayer );
}

//=============================================================================
//�ʐ^�B�e�@�\
//=============================================================================
void CSceneGameMain::ShootTargetFunc()
{
	#if defined ( CAM_TOOL )
	
	#else
		/*�ʐ^�B�e*/
		ShootPhoto();
	#endif
	
}


//=============================================================================
//�ߊl�@�\
//=============================================================================
void CSceneGameMain::CaptureFunc()
{
	/*�L���b�`�}�[�N�̕\��*/
	if( !m_pPlayer->GetCaptureFlag() )
	{	
		ShowCatchMark();
	}
	
	/*���ݕt���ړ��ʒu�̐ݒ�*/
	for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
	{	
		CEnemy *pEnemy = *i;
		/*�ߊl�Ώ۔͈͓��ŁA�G���ߊl����ĂȂ����*/
		if( pEnemy->GetCatchSpr3D()->GetVisibleFlag() 
		    && !m_pPlayer->GetCaptureFlag() )
		{
			m_pPlayer->SetTargetPos( CCommonObject::GetMouse()->GetMouse(), pEnemy, CCommonObject::GetSceneMgr( SCREEN_MAIN )->GetSceneMgr() );
		}
	}
	
	
}

//=============================================================================
//����@�\
//=============================================================================
void CSceneGameMain::ReleaseFunc()
{
	Math::Vector2D vPos = CCommonObject::GetMouse()->GetMousePos();
	
	/*����{�^����������Ă��āA�ߊl��Ԃ̎��������*/
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
	
	/*�ߊl���͕��ʂɕ\��*/
	if( m_pPlayer->GetCaptureFlag() )
	{
	}
	
	/*�ړ����̓O���[�X�P�[���\��*/
	else
	{
		m_pReleaseBtnSpr->SetAnimXID( 0 );
	}
	
	m_pReleaseBtnSpr->Rendering();
	
	
}

//=============================================================================
//���j���[�@�\
//=============================================================================
void CSceneGameMain::MenuFunc()
{
	/*���j���[�Ɉړ�*/
	MovePauseMenu();
}

//=================================================================================================
/*�����܂Œǉ��֐��̌ʏ���*/
//=================================================================================================

//=================================================================================================
/*��������@�\�̃����_�����O�̌ʏ���*/
//=================================================================================================
//[input]
//	flag:true���ʏ�ʂ�\��
//		 false���O���[�X�P�[���\��
//=================================================================================================

//=============================================================================
//�����_�����O�֐��̏���
//=============================================================================
void CSceneGameMain::RenderFuncExec()
{
	/*�֐��e�[�u��*/
	FuncRender FuncTbl[] = 
	{
		&CSceneGameMain::RenderMove,//�ړ��@�\
		&CSceneGameMain::RenderCameraRot,//�J������]�@�\
		&CSceneGameMain::RenderCameraReset,//�J�������Z�b�g�@�\
		&CSceneGameMain::RenderShootTarget,//�ʐ^�B�e�@�\
		&CSceneGameMain::RenderMenu,//���j���[�@�\
		&CSceneGameMain::RenderCapture,//�ߊl�@�\
		&CSceneGameMain::RenderRelease,//����@�\

	};
	
	for( int i = 0;i < FUNC_MAX;++i )
	{	
		(this->*FuncTbl[i])(m_IsAddFunc[i]);
	}


}

//=============================================================================
//�ړ����̕\��
//=============================================================================
void CSceneGameMain::RenderMove( bool flag )
{
}

//=============================================================================
//�J������]���̕\��
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
//�J�������Z�b�g���̕\��
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
//�ʐ^�B�e���̕\��
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
//�ߊl���̕\��
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
//������̕\��
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
//���j���[���̕\��
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
/*�����܂ŋ@�\�̃����_�����O�̌ʏ���*/
//=================================================================================================



//=============================================================================
//�A�N�^�[�̐���
//=============================================================================
void CSceneGameMain::CreateActor()
{
	//for( int i = 0;i < SCREEN_MAX;++i )
	//{
	//	CCommonObject::GetResMgr()->get->CreateActor( i, CCommonObject::GetSceneMgr(i)->GetSceneMgr() );
	//}
}

//=============================================================================
//�ʐ^�]��
//=============================================================================
void CSceneGameMain::GradePhoto()
{
	int Score = 0;
	
	for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
	{
		CEnemy *pEnemy = *i;
		
		CPhoto::PhotoCheckData datPhoto;
		
		Score = pEnemy->CalcScore( m_pPlayer );
		
		/*�B�e���I����ĂȂ��āA���b�N�I����Ԃ̂Ƃ��̂ݓ_�����Z*/
		if( pEnemy->GetLockOnFlag() && !pEnemy->GetShootEndFlag() )
		{
			datPhoto.m_Score = Score;
			datPhoto.m_strTargetName = pEnemy->GetTypeName();
			
			vecPhotoData.push_back( datPhoto );
			
			char Temp[16];
			
			sprintf_s( Temp, 16, "Photo%d", GetFilmCount() );
			
			CPhoto *pPhoto =  dynamic_cast<CPhoto *>( CCommonObject::GetResMgr()->FindObject(Temp) );
			
			pPhoto->SetPhotoData( vecPhotoData );
			
			//�ʐ^���̃Z�b�g
			pPhoto->SetPhotoInfo();
			
			/*���X�g�̃N���A*/
			vecPhotoData.clear();
			
			/*�B�e�I���t���O�̐ݒ�*/
			pEnemy->SetShootEndFlag( true );
			
			//�^�[�Q�b�g�����݂��Ă�����t���O�𗧂Ă�
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
//�f�o�b�O���̕\��
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
//�^�[�Q�b�g�ւ̖��̏���
//=============================================================================
void CSceneGameMain::TargetArrowExec()
{
	Math::Vector3D vArrowPos = CCommonObject::GetSceneMgr( SCREEN_MAIN )->GetSceneMgr()->TransformToScreen
								( Math::Vector3D( m_pPlayer->GetPosition().x, 
												  m_pPlayer->GetPosition().y + 10.0f, 
												  m_pPlayer->GetPosition().z ) ); 
	
	
	m_pArrow->SetPosition( m_pPlayer->GetPosition() + Math::Vector3D( 0, 5, 0 ) );
	
	Math::Vector3D vDirection = GetTarget()->GetPosition() - m_pArrow->GetPosition();
	
	/*�^�[�Q�b�g�Ƃ̋����ɂ���ĐF��ύX*/
	Sint32 MeshCount = m_pArrow->GetModelActor(SCREEN_MAIN)->GetMeshCount();
	
	for( int MeshIndex = 0; MeshIndex < MeshCount;++MeshIndex )
	{
		Sint32 MateCount = m_pArrow->GetModelActor(SCREEN_MAIN)->GetMeshMaterialCount( MeshIndex );
		
		for( int MateIndex = 0; MateIndex < MateCount;++MateIndex )
		{
			/*�߂�������ԐF��*/
			if( vDirection.Length() >= 0.0 && vDirection.Length() < 10.0 )
			{
				m_pArrow->GetModelActor(SCREEN_MAIN)->MeshMaterial_SetMaterialColor( MeshIndex, MateIndex, Math::Vector4D( 255, 0, 0, 255 ) );
			}
			
			/*�قǂقǋ߂������物�F��*/
			else if( vDirection.Length() >= 10.0 && vDirection.Length() < 30.0 )
			{
				m_pArrow->GetModelActor(SCREEN_MAIN)->MeshMaterial_SetMaterialColor( MeshIndex, MateIndex, Math::Vector4D( 255, 255, 0, 255 ) );
			}
			
			/*����������F*/
			else
			{
				m_pArrow->GetModelActor(SCREEN_MAIN)->MeshMaterial_SetMaterialColor( MeshIndex, MateIndex, Math::Vector4D( 0, 0, 255, 255 ) );
			}

		}
	}

	
	/*�^�[�Q�b�g�̈ʒu�ɂ���āA������ς���*/
	Sint32 RotX = Math::ATan2( -vDirection.z, vDirection.x );
	Sint32 RotY = Math::ATan2( -vDirection.z, vDirection.y );
	
	if( GetTarget()->GetStTypeName().compare( "�e�C�G��" ) == 0 )
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
//�ړ��}�[�J�[�̕\��
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
//�L���b�`�}�[�N�̕\��
//=============================================================================
void CSceneGameMain::ShowCatchMark()
{
	/*�L���b�`�}�[�N�\���͈�*/
	Collision::CBox HitBox = m_pPlayer->GetCapCheckBox();
	
	/*�J�����̃r���[�����[���h�ϊ����擾*/
	Math::Matrix matViewToWorld = CCommonObject::GetCamera( SCREEN_SUB )->GetCamera()->ViewToWorld();
	
	for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
	{	
		CEnemy *pEnemy = *i;
		
		/*���[���h�s��̐ݒ�*/
		pEnemy->GetCatchSpr3D()->SetMatWorld( matViewToWorld );
		
		/*�L���b�`�}�[�N�\���͈͂��`�F�b�N*/
		pEnemy->CheckCatch( HitBox );
	}
	
}

//=============================================================================
//�ړ��J�[�\���̕\��
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
	
	//���_�ɏd�ˍ��킹�镽�s�ړ�
	matTemp.Translation( -m_pMoveArrowSpr->GetSize().x / 2, 
						 -m_pMoveArrowSpr->GetSize().y / 3,
						 0.0f );
	matWorld *= matTemp;

	MoveAngle = Math::ATan2( -vTargetPos.y, vTargetPos.x );
	
	//�g��s��ƍ���
	matTemp.Scaling( 1.0f, fMoveDistance * 0.01f, 1.0f );
	matWorld *= matTemp;
	
	//��]�s��ƍ���
	matTemp.RotationZ( MoveAngle );
	//matTemp.RotationAxis( MoveAngle, vPos );
	matWorld *= matTemp;
	//
	////�w��̏ꏊ�ւƈړ�����s��Ƃ̍���
	matTemp.Translation( vOldMousePos.x, vOldMousePos.y, 0.0f );
	
	matWorld *= matTemp;
	
	Math::Rect2DF SrcRect( 0, 0, toF( m_pMoveArrowSpr->GetSize().x ), toF( m_pMoveArrowSpr->GetSize().y ) );
	
	m_pMoveArrowSpr->GetSprite()->Begin();
	
	m_pMoveArrowSpr->GetSprite()->DrawSquareMatrix( matWorld, SrcRect, CColor( 255, 255, 255 ) );
	
	
	m_pMoveArrowSpr->GetSprite()->End();
	
}

//=============================================================================
//�ʐ^�B�e
//=============================================================================
void CSceneGameMain::ShootPhoto()
{
	/*�J�����|�C���^�Ƃ̓����蔻��*/
	HitCheckCamPointa();
	
	if( GetPhotoSaveFlag() )
	{
		/*�ʐ^�]��*/
		GradePhoto();

	}
	
	/*�E�N���b�N�̎�*/
	if( CCommonObject::GetMouse()->GetMouse()->GetStateR() == MOUSE_PUSH )
	{
	
		string name = "file";
		char Temp[16];
		
		sprintf_s( Temp, 16,  "%d.tga", GetFilmCount() );
		
		name += Temp;
		
		/*�ʐ^���ꎞ�I�ɕۑ����āA���̃f�[�^��ǂݍ���ł����j��*/								
		CCommonObject::GetSceneMgr( SCREEN_SUB )->GetRenderTex()->SaveToTGA( name.c_str() );
		
		sprintf_s( Temp, 16,  "Photo%d", GetFilmCount() );
		
		
		if( GetTutorialFlag() )
		{
			if( GetTarget()->GetLockOnFlag() )
			{	
				
				CCommonObject::GetResMgr()->Push( new CFileData( name.c_str(), Temp, "PHOTO", Math::Vector3D( 0, 0, 0 ),
																 vecPhotoData ) );
				
				CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_SHUTTER );

				/*�ʐ^�`�F�b�N��ʂɑJ��*/
				SetNextScene( SCENE_PHOTOCHECK );
				
				//�^�[�Q�b�g��������i�߂�
				if( GetTarget() == m_pRabbit )
				{	
					GetWindowSpr()->AddStrCount( 1 );
				}
			
				
				/*�V�[�����I��*/
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
			
			/*���X�g�̃N���A*/
			vecPhotoData.clear();
			
			CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_SHUTTER );
			
			
			/*�ʐ^�`�F�b�N��ʂɑJ��*/
			SetNextScene( SCENE_PHOTOCHECK );
			
			/*�V�[�����I��*/
			SetSceneState( STATE_FINISH );
		
		
		}
		
	}

}

//=============================================================================
//��ʂ̐ݒ�
//=============================================================================
void CSceneGameMain::SetScreenParam()
{
	for( int ScreenNum = 0;ScreenNum < SCREEN_MAX;++ScreenNum )
	{	
		/*�p�����[�^�̐ݒ�*/
		CCommonObject::GetSceneMgr( ScreenNum )->SetParameter();
		
		// ���s����
		//   �V�[���ɑ΂��ĕ��s������ݒ肵�܂��B
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->SetLightParameter_Directional(
			Math::Vector3D( 0.5f, -0.5f, 0.7f ),		// ���C�g�̕���
			Math::Vector3D( 1.0f, 1.0f, 1.0f ) );		// ���C�g�̐F

		// �A���r�G���g
		// �������C�e�B���O���s���Ă���̂ŁA�V���ƒn�\�̏Ƃ�Ԃ��̐F��ݒ肵�܂��B
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->SetLightParameter_Ambient(
			Math::Vector3D( 0.2f, 0.2f, 0.2f ),			// �V���̐F
			Math::Vector3D( 0.5f, 0.5f, 0.5f ) );		// �n�\�̐F
			
		// �J�����̒����ڕW
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
		
			/*�ߊl���̓G�Ƀt�H�[�J�X�����킹��*/
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

		/*�J�����̉�]�␳*/
		CCommonObject::GetCamera( ScreenNum )->RotateAdjust();
		
		/*�J�����̕ό`*/
		#if defined(CAM_TOOL)
			
			CCommonObject::GetCamera( ScreenNum )->SetTransform3();
				
		#else
			
			if( m_IsDemo )
			{
				
				++CamCnt;
				
				const int TIME_MAX = 60 * 6;
				
				CEnemy *pTarget = GetTarget();
				
				if( GetTarget()->GetStTypeName().compare( "�e�C�G��" ) == 0 )
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
				
				else if( GetTarget()->GetStTypeName().compare( "�t���X�C" ) == 0 )
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
				
				else if( GetTarget()->GetStTypeName().compare( "�A���E�X" ) == 0 )
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
					m_pPlayer->GetCapedEnemy()->GetStTypeName().compare("�g��") == 0 )
				{	
					CCommonObject::GetCamera( ScreenNum )->SetTransformBird( MoveAngle, m_pMarkerSpr->GetVisibleFlag() );
				}
				
				else
				{
					CCommonObject::GetCamera( ScreenNum )->SetTransform( MoveAngle, m_pMarkerSpr->GetVisibleFlag() );
				}
			}
			
		#endif
		
		// �V�[���ɃV���h�E�}�b�v�p�J�����ݒ�t
		//   �V���h�E�}�b�v�̃����_�����O�Ɏg���J������ݒ�
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->SetParameter_Shadow(
			Math::Vector3D( -3.0f, 20.0f, -30.0f ),	// �J�����ʒu
			Math::Vector3D( 0, 10.0, 0 ),
			//objPlayer->GetPosition(),									// �J���������_
			100.0f,								// �����_�����O�T�C�Y
			10.0f,								// �߃N���b�v��
			30.0f,								// ���N���b�v��
			0.0f,								// Z�l�o�C�A�X�i���ۂɌ��Ă��������ɒ���
			0.7f );								// �e�̋����iSHADING_NORMAL�̎��̂ݗL���j
			
		// �n�b�`���O�p�̃p�����[�^�[
		//GetSceneMgr(ScreenNum)->GetSceneMgr()->SetParameter_Toon( Math::Vector3D(0.5, 0.5, 0.5 ), 0.1f );
		//GetSceneMgr(ScreenNum)->GetSceneMgr()->SetParameter_ToonEdge( 3.0f, 10.0f, false );
			
		// �_�̈ړ�
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->SceneSkydoom_SetCloudOffset( Math::Vector2D( 0.0002f, 0.0005f ) );
	}
	
}

//=============================================================================
//�ݒ�̃����_�����O
//=============================================================================
void CSceneGameMain::RenderingSetting( )
{
	for( int ScreenNum = 0;ScreenNum < SCREEN_MAX;++ScreenNum )
	{
		/*�A�N�^�[�C���f�b�N�X�̐؂�ւ�*/
		m_pField->SetActorIndex( ScreenNum );
		
		SetActorIndexAll( ScreenNum );
		
		//m_pPlayer->SetActorIndex( ScreenNum );
		//CCommonObject::GetResMgr()->Get3DObject()->SetActorIndex( ScreenNum );
		
		
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->Begin( false );
		
		// �X�J�C�h�[���̃����_�����O
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->SceneSkydoom_Rendering();
		
		// �e�̉e�����󂯂�悤�ɐݒ�
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->SetActorParameter_ProjectionShadow( PROJECTION_SHADOW_DROP_SHAPE, PROJECTION_SHADOW_PRIORITY_0 );
		
		m_pField->SetVisibleFlag( true );
		
		/*�t�B�[���h�̃����_�����O*/
		m_pField->Rendering();
		
		/*2�d�����_�����O��h��*/
		m_pField->SetVisibleFlag( false );

		// �e�𗎂Ƃ��悤�ɐݒ�
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->SetActorParameter_ProjectionShadow( PROJECTION_SHADOW_DROP_SHAPE, PROJECTION_SHADOW_PRIORITY_1 );
		
		

		/*�ʐ^�Ɏʂ��ė~�����Ȃ����̂̐ݒ�*/
		if( ScreenNum == SCREEN_SUB )
		{
			
			/*�T�u��ʂɂ̓v���C���[��\�������Ȃ�*/
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
			
			/*�ߊl���ɂ́A�ߊl���̓G���\�������Ȃ�*/
			if( m_pPlayer->GetCaptureFlag() )
			{
				m_pPlayer->GetCapedEnemy()->SetVisibleFlag( false );
			}
			
			
		}
		
		/*���C����ʎ�*/
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
		
		
		
		/*�ʐ^����p���C�̐ݒ�*/
		m_pPlayer->CreateShootRay( CCommonObject::GetSceneMgr( SCREEN_MAIN )->GetSceneMgr() );
		
		/*�ړ�����*/
		if( !GetTutorialFlag() )
		{
			if( m_pPlayer->GetState() != CPlayer::STATE_CAPSTART || 
				m_pPlayer->GetState() != CPlayer::STATE_RELSTART )
			{
				MoveExec3DObject();
			}
		}
		
		
		
		/*����*/
		Exec3DObject();
		
		//�����_�����O
		Rendering3DObject();
		
		for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
		{
			CEnemy *pEnemy = *i;
			
			if( pEnemy->GetVisibleFlag() )
			{
				/*�L���b�`�}�[�N�̃����_�����O*/
				pEnemy->RenderingCatchMark();
				
			}
		}
		
		// �V�[���Ǘ����I��
		//   �����܂łō\�z���ꂽ�V�[���������Ɏ��ۂɕ`��p�f�[�^�̍\�z���s���܂��B
		CCommonObject::GetSceneMgr( ScreenNum )->GetSceneMgr()->End();
	}

}

//=============================================================================
//�d�ԂƂ̓����蔻��
//=============================================================================
void CSceneGameMain::HitCheckTrain( )
{
	
	Collision::CLine3D vRay;
	Renderer::SCollisionResult Ret;
	
	vRay.vStart = m_pPlayer->GetPosition() + Math::Vector3D( 0, 3, 0 );
	
	vRay.vEnd = vRay.vStart + Math::Vector3D( 0, 0, 3 );
	
	static int count = 0;

	/*�����蔻��*/
	if( m_pPlayer->HitCheck( vRay, Ret ) )
	{
		if( Ret.Attribute == 1 )
		{
			#if defined (DEBUG) | (_DEBUG) 
				//pRender->DebugPrint( Math::Point2DI( 200, 100 ), CColor( 255, 255, 255 ), "�d�ԂɐڐG��" );
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
//�ʒu�̕ۑ�
//=============================================================================
void CSceneGameMain::SavePos()
{
	Math::Matrix mat = CCommonObject::GetCamera( SCREEN_MAIN )->GetCamera()->ViewToWorld();
	
	if( MarkerIdx > MARKER_MAX )
	{
		MarkerIdx = MARKER_MAX;
	}
	
	m_vecMarker.at(MarkerIdx).m_pMarker->SetMatWorld( mat );
	
	/*�ʒu�̐ݒ�*/
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
//�}�E�X�X�v���C�g�̏�ԏ���
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
		/*�������ĂȂ���Ԃ̂Ƃ�*/
		case MOUSE_PUSHNONE:
		{
			Anim[0] = 0;
			Anim[1] = 0;
			break;
		}
		
		/*���N���b�N��������Ԃ̎�*/
		case MOUSE_PUSHLEFT:
		{
			Anim[0] = 0;
			Anim[1] = 1;			
			
			break;
		}
		
		/*�E�N���b�N��������Ԃ̎�*/
		case MOUSE_PUSHRIGHT: 
		{
			Anim[0] = 0;
			Anim[1] = 2;
			
			break;
		}
		
		/*�h���b�O��Ԃ̎�*/
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
//�~�j�}�b�v�̕\��
//=============================================================================
void CSceneGameMain::ShowMiniMap()
{
	
	m_pMiniMap->Rendering();
	
	m_pMiniMap->SetMiniCharaPos( m_pPlayer, m_pPlayer->GetMinSpr(), true );
	
	//�v���C���[�̕\��
	m_pMiniMap->Move( m_pPlayer );
	
	//�~�j�L�����̕\��
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
//�J�����|�C���^�Ƃ̓����蔻��
//=============================================================================
void CSceneGameMain::HitCheckCamPointa()
{
	/*���[�v�p�J�E���g*/
	int EnemyCount = 0;
	
	/*�^�[�Q�b�g���J�����|�C���^�ɓ������Ă��邩�ǂ���*/
	for( vector<CEnemy *>::iterator i = m_pVecCatchEnemy.begin();i != m_pVecCatchEnemy.end();++i )
	{
		CEnemy *pEnemy = *i;
		
		float fDistance = ( pEnemy->GetPosition() - m_pPlayer->GetPosition() ).Length();
		
		
		/*�������Ă�����A�J�����|�C���^�̃A�j���[�V�����ԍ��ύX*/
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
		
		/*�G���ǂɓ������Ă��邩�`�F�b�N*/
		//pEnemy->HitCheckWall( m_pField );
		
		//pEnemy->SetSeed( GetAppli()->GetCore() );
	}
	
}

//=============================================================================
//�N���A�I�u�W�F�N�g�̒ǉ�
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
//�~�b�V�����̕`��
//=============================================================================
void CSceneGameMain::DrawMission()
{
	//�~�b�V������
	string strMissionName = vecStr[0];
	
	//�^�[�Q�b�g��
	string strTargetName = vecStr[1];
	
	//CCommonObject::GetAppli()->GetRenderer()->DrawTextLayer
	//( 2, Math::Point2DI( 0, 0 ), CColor( 255, 255, 255 ), strMissionName.c_str() );
	//
	CCommonObject::GetAppli()->GetRenderer()->DrawTextLayer
	( 2, Math::Point2DI( 40, 210 ), CColor( 0, 0, 0 ), "%s���B��", GetTarget()->GetStTypeName().c_str() );
	
	CCommonObject::GetAppli()->GetRenderer()->DrawTextLayer
	( 2, Math::Point2DI( 40, 260 ), CColor( 0, 0, 0 ), "�N���A�|�C���g:%d�|�C���g", GetClearPoint() );
	
	static int count = 0;
	
	++count;
	
	if( count > 0 && count <= 30 )
	{
		CCommonObject::GetAppli()->GetRenderer()->DrawTextLayer
		( 2, Math::Point2DI( 100, 330 ), CColor( 255, 255, 255 ), "���N���b�N�ŃX�^�[�g" );
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
//�~�b�V�����̃��[�h
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
	
	//�N���A�|�C���g
	int ClearPoint = Rand.GetInt( 100, 500 );
	
	CEnemy *pEnemy = m_pVecTarget.at( TargetNo );

	//�^�[�Q�b�g�̐ݒ�
	SetTarget( pEnemy );
	
	//�N���A�|�C���g�̐ݒ�
	SetClearPoint( ClearPoint );
	
	SAFE_RELEASE( pResFile );
	
}

//=============================================================================
//�^�[�Q�b�g�Ώۂ̓G�̐ݒ�
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
//3D�I�u�W�F�N�g�̏�����
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
//3D�I�u�W�F�N�g�̃����_�����O
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
//3D�I�u�W�F�N�g�̏���
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
//3D�I�u�W�F�N�g�̏���
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
//�A�N�^�[�C���f�b�N�X�̈ꊇ�ݒ�
//=============================================================================
//[input]
//	index:�ݒ肷��C���f�b�N�X
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
//�\���t���O�̈ꊇ�ݒ�
//=============================================================================
//[input]
//	flag:�ݒ肷��t���O
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
//��~�t���O�̈ꊇ�ݒ�
//=============================================================================
//[input]
//	flag:�ݒ肷��t���O
//=============================================================================
void CSceneGameMain::SetStopFlagAll( bool flag )
{
	for( int i = 0;i < m_vec3DList.size();++i )
	{
		CDraw3DObject *pObj = m_vec3DList.at( i );
		
		pObj->SetStopFlag( flag );
	}
}












