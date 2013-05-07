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
//�R���X�g���N�^
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
	
	/*�X�e�[�^�X�̓ǂݍ���*/
	LoadStatus();
	
	SetStateFunc( &CGameSceneManager::Title );
	SetRenderFunc( &CGameSceneManager::Title );
}

//=============================================================================
//�f�X�g���N�^
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
//�^�C�g���֐�
//=============================================================================
void CGameSceneManager::Title()
{
	if( m_pGameTitle->UpDate() == STATE_FINISH )
	{
		/*�Q�[���v���C�̏ꍇ*/
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
		
		/*�`���[�g���A���̏ꍇ*/
		else if( m_pGameTitle->GetSelectScene() == CSceneGameTitle::SELECT_TUTORIAL )
		{
			/*�`���[�g���A���t���O�𗧂Ē���*/
			SetTutorialFlag( true );
			
			//CCommonObject::GetResMgr()->Get3DObject()->Init();
			
			GetWindowSpr()->Init();
			
			//CCommonObject::GetResMgr()->Get2DObject()->Init();
			
	
			SetFadeIn( 60, CColor( 255, 255, 255 ), &CGameSceneManager::GameMain );		
			
			GetBGM()->GetBGMDevice()->Stop();

			
			
			//SetStateFunc( &CGameSceneManager::GameMain );
			//SetRenderFunc( &CGameSceneManager::GameMain );
		}
		
		/*�I���̏ꍇ*/
		else
		{
			SetFadeOut( 60, CColor( 255, 255, 255 ), &CGameSceneManager::Exit );		
		
		}
	}
}


//=============================================================================
//�~�b�V�����\���֐�
//=============================================================================
void CGameSceneManager::ShowMission()
{
	if( m_pShowMission->UpDate() == STATE_FINISH )
	{
		SetFadeIn( 60, CColor( 255, 255, 255 ), &CGameSceneManager::GameMain );

	}
}


//=============================================================================
//�Q�[�����C���֐�
//=============================================================================
void CGameSceneManager::GameMain()
{
	
	if( m_pGameMain->UpDate() == STATE_FINISH )
	{
		/*���ꂼ��̉�ʂɈڍs*/
		switch( m_pGameMain->GetNextScene() )
		{
			/*�ʐ^�m�F��ʂ̎�*/
			case CSceneGameMain::SCENE_PHOTOCHECK:
			{
				SetFadeIn( 60, CColor( 255, 255, 255 ), &CGameSceneManager::PhotoCheck );		
				break;
			}
			
			/*�|�[�Y���*/
			case CSceneGameMain::SCENE_PAUSE:
			{
				SetStateFunc( &CGameSceneManager::Pause );
				SetRenderFunc( &CGameSceneManager::Pause );
			
				break;
			}
			
			/*�^�C�g�����*/
			case CSceneGameMain::SCENE_TITLE:
			{
				SetFadeIn( 30, CColor( 255, 255, 255 ), &CGameSceneManager::Title );		
				break;
			}
			
			/*���U���g���*/
			case CSceneGameMain::SCENE_RESULT:
			{
				SetFadeIn( 10, CColor( 255, 255, 255 ), &CGameSceneManager::Result );		
				GetBGM()->GetBGMDevice()->Stop();
				break;
			}
			
			//�V�v�f�ǉ����
			case CSceneGameMain::SCENE_NEWELEM:
			{
				SetFadeIn( 10, CColor( 255, 255, 255 ), &CGameSceneManager::NewComp );	
				break;	
			}
		}
	}
	
}

//=============================================================================
//�ʐ^�m�F��ʊ֐�
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
//���U���g��ʊ֐�
//=============================================================================
void CGameSceneManager::Result()
{
	if( m_pResult->UpDate() == STATE_FINISH )
	{
		SetFadeIn( 10, CColor( 255, 255, 255 ), &CGameSceneManager::NewComp );		
		
	}
}

//=============================================================================
//�V�v�f�\��
//=============================================================================
void CGameSceneManager::NewComp()
{
	if( m_pNewComp->UpDate() == STATE_FINISH )
	{
		/*�X�e�[�^�X�̃Z�[�u*/
		SaveStatus();
		
		SetFadeIn( 60, CColor( 255, 255, 255 ), &CGameSceneManager::Title );
	}
}

//=============================================================================
// �X�^�[�g���j���[
//=============================================================================
void CGameSceneManager::Pause(void)
{
	if( m_pPause->UpDate() == STATE_FINISH )
	{
		/*�Q�[���ɖ߂�̏ꍇ*/
		if( m_pPause->GetSelectScene() == CScenePause::SCENE_RETURNGAME )
		{
			SetStateFunc( &CGameSceneManager::GameMain );
			SetRenderFunc( &CGameSceneManager::GameMain );
		}
		
		/*���g���C�̏ꍇ*/
		else if( m_pPause->GetSelectScene() == CScenePause::SCENE_RETRY )
		{
			m_pGameMain->SetState( &CSceneTemplate::Init );
			
			SetFadeIn( 10, CColor( 255, 255, 255 ), &CGameSceneManager::GameMain );		
		
		}
		
		/*�^�C�g���ɖ߂�ꍇ*/
		else if( m_pPause->GetSelectScene() == CScenePause::SCENE_RETURNTITLE )
		{
			m_pGameMain->SetState( &CSceneTemplate::Init );
			
			SetFadeIn( 10, CColor( 0, 0, 0 ), &CGameSceneManager::Title );		
		}
	}
}

//=============================================================================
//�I��
//=============================================================================
void CGameSceneManager::Exit()
{
	if( !IsFade())
	{
		/*�I��*/
		CCommonObject::GetAppli()->GetCore()->Exit();
	}
}



//=============================================================================
//�����_�����O
//=============================================================================
void CGameSceneManager::Rendering()
{
	/*�`�揈��*/
	( this->*m_pRenderFunc )();
	
}

//=============================================================================
//�V�[���̍X�V
//=============================================================================
//[return]
//	�V�[���̏��
//=============================================================================
eSceneState CGameSceneManager::UpDate()
{
	
	/*�`���[�g���A������*/
	if( GetTutorialFlag() && !IsFade() )
	{
		TutorialExec();
	}
	
	/*�Q�[���̍X�V*/
	( this->*m_pStateFunc )();
	
	FadeExec();
	
	return m_eSceneState;
	
	
}

//=============================================================================
//�X�e�[�^�X�̃��[�h
//=============================================================================
void CGameSceneManager::LoadStatus( )
{
	#if defined( DEBUG ) | ( _DEBUG )	
	
		ifstream ifs( "save.dat", ios::in );
		
		/*�t�@�C�����Ȃ������琶��*/
		if( ifs.fail() )
		{
			ofstream out( "save.dat" );
			
			/*�n�C�X�R�A�̐ݒ�*/
			out << "0" << std::endl;
			
			/*�Q�[�������N���t���O�̐ݒ�*/
			out << "1" << std::endl;
			
			/*�N���A�J�E���g�̐ݒ�*/
			out << "0" << std::endl;
			
		}
	#else
	
		ifstream ifs( "save.dat", ios::in | ios::binary );
	
		/*�t�@�C�����Ȃ������琶��*/
		if( ifs.fail() )
		{
			ofstream out( "save.dat" , ios::out |ios::binary );
			
			/*�n�C�X�R�A�̐ݒ�*/
			out << "0" << std::endl;
			
			/*�Q�[�������N���t���O�̐ݒ�*/
			out << "1" << std::endl;
			
			/*�N���A�J�E���g�̐ݒ�*/
			out << "0" << std::endl;
			
			
		}
	
		
	#endif
	
		//-------------------------------------------------------
		//�f�[�^�̓ǂݍ���
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
//�X�e�[�^�X�̃Z�[�u
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
//�t�F�[�h�C��
//=============================================================================
void CGameSceneManager::FadeIn()
{
	m_Color.a = (Uint8)( ::Interpolation::Flat( 255L, 0L, m_TimeLast, m_Time ) );
	
	CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
	
	/*��ʑS�̂𕢂�*/
	CCommonObject::GetAppli()->GetRenderer()->FillRect( ScreenRect, m_Color );
	
	//�V�[�����Z�b�g
	SetStateFunc( m_pStateFunc );
	SetRenderFunc( m_pStateFunc );
	
	// �^�C�}�[
	if ( ++m_Time > m_TimeLast )
	{
		
		m_eSceneState = STATE_FADEOUT;
		
	}
	
}

//=============================================================================
//�t�F�[�h�A�E�g
//=============================================================================
void CGameSceneManager::FadeOut()
{
	
	
	m_Color.a = (Uint8)( ::Interpolation::Flat( 0L, 255L, m_TimeLast, m_Time ) );
	
	CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
	
	/*��ʑS�̂𕢂�*/
	CCommonObject::GetAppli()->GetRenderer()->FillRect( ScreenRect, m_Color );
	

	
	// �^�C�}�[�{
	if ( ++m_Time > m_TimeLast )
	{
		
		/*�t�F�[�h�C��*/
		//SetFadeIn( m_TimeLast, m_Color, m_pStateFunc );
		

		m_eSceneState = STATE_CONTINUE;
	}
}

//=============================================================================
//�t�F�[�h�C���̐ݒ�
//=============================================================================
//[input]
//	Time:�t�F�[�h�C������
//	Color:�`�悷��F
//	pStateFunc:�X�e�[�g���\�b�h
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
//�t�F�[�h�A�E�g�̐ݒ�
//=============================================================================
//[input]
//	Time:�t�F�[�h�A�E�g����
//	Color:�`�悷��F
//	pStateFunc:�X�e�[�g���\�b�h
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
//�t�F�[�h�����ǂ���
//=============================================================================
Bool CGameSceneManager::IsFade()
{
	return m_eSceneState != STATE_CONTINUE;
}

//=============================================================================
//�t�F�[�h����
//=============================================================================
void CGameSceneManager::FadeExec()
{
	switch( m_eSceneState )
	{
		case STATE_CONTINUE:
		{
			break;
		}
		
		/*�t�F�[�h�C��*/
		case STATE_FADEIN:
		{
			FadeIn();
			break;
		}
		
		/*�t�F�[�h�A�E�g*/
		case STATE_FADEOUT:
		{
			FadeOut();
			break;
		}
	}
}

//=============================================================================
//�X�N���v�g�̏���
//=============================================================================
//[input]
//	strSource:�����Ώۂ̕�����
//[return]
//	strRet:�\�������镶����
//===========================================================================
string CGameSceneManager::ScriptExec( string strSource )
{
	
	string strRet;
	
	/*�����镶����*/
	string strFind[] =
	{
		"Left",//���N���b�N�̏ꍇ
		"Right",//�E�N���b�N�̏ꍇ
		"Drag",//�h���b�O�̏ꍇ
		"Camera",//�J������]�̏ꍇ
		"Reset",//�J�������Z�b�g�̏ꍇ
		"Arrow",//���\���̏ꍇ
		"Score",//�X�R�A�����̏ꍇ
		"Film",//�t�B���������̏ꍇ
		"TargetShow",//�^�[�Q�b�g�\���̏ꍇ
		"DisTarget",//�^�[�Q�b�g�̏���
		"Shoot",//�^�[�Q�b�g�̎B�e
		"Go",//�^�[�Q�b�g�|�C���g�ɍs���ꍇ
		"Release",//�����[�X�{�^�����������ꍇ
		"Menu",//���j���[�{�^�����������Ƃ�
		"Catch",//�L���b�`�}�[�N��
		"End",//�X�N���v�g�I��
		"AddFunc",//�J������]�@�\�ǉ�
		"ReturnGame",//�Q�[���ɖ߂�
		"Save",//�ʐ^�ۑ���
		
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
	
	const int SCRIPT_MAX = 19;//�X�N���v�g��
	
	int ScriptCount = 0;//�X�N���v�g�̃J�E���g�p
	
	for( int i = 0;i < SCRIPT_MAX;++i )
	{
		/*����������*/
		string strSearch = strFind[i];
		
		/*���������񂪌����ꏊ*/
		string::size_type index = strSource.rfind(strSearch);
		
		/*�������v*/
		if( index != string::npos )
		{
			/*�]���ȕ���������*/
			strSource.erase( index, strSearch.length() );
			
			ScriptCount = 0;			
			
			/*�ʐ^�ۑ����̂Ƃ�*/
			if( i == SCRIPT_MAX - 1 )
			{ 
				m_pPhotoCheck->PhotoSaveScript();
			}
			
			/*�Q�[���ɖ߂�̂Ƃ�*/
			else if( i == SCRIPT_MAX - 2 )
			{
				m_pPause->PauseMenuScript();
			}
			
			/*���̑��̏ꍇ*/
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
//�`���[�g���A������
//=============================================================================
void CGameSceneManager::TutorialExec()
{
	string strDraw;//�`�敶����
	
	strDraw = ScriptExec( GetWindowSpr()->GetNowString() );
	
	GetWindowSpr()->GetTrlFont()->SetDrawString( strDraw );
	
}
