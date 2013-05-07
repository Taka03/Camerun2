//*============================================================================
//SceneGameTitle.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneGameTitle.h"
#include "LuaScript.h"

//=============================================================================
//namespace
//=============================================================================
namespace
{
	int time = 0;
	int Cursor = 0;
	bool IsFade;
}


//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	strFileName:�t�@�C����
//=============================================================================
CSceneGameTitle::CSceneGameTitle( string strFileName ) 
: m_pTitleBGM(NULL),
 m_eSelectScene(SELECT_TUTORIAL),
 CSceneTemplate( strFileName )
{
}


//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneGameTitle::~CSceneGameTitle()
{

}

//=============================================================================
//�I�u�W�F�N�g�f�[�^�̏�����
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CSceneGameTitle::InitObjectData( Uint32 dt )
{
	if( !CCommonObject::GetResMgr()->IsLoading() )
	{
		/*2D�I�u�W�F�N�g�̒ǉ�*/
		//Push2DObject();
		
		m_pBG = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("Title") );
		
		m_pTitleBGM = dynamic_cast<CBGM *>( CCommonObject::GetResMgr()->FindSoundObj("TitleBGM") );
		
		m_pTitleMenu = dynamic_cast<CMenu *>( CCommonObject::GetResMgr()->FindObject("TitleMenu") );
		
		m_pCamBtnSpr = dynamic_cast<CCamButton *>( CCommonObject::GetResMgr()->FindObject("CamBtn") );
		
		m_pHiScoreSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("HiScore") );
		
		m_pHiScoreFont = dynamic_cast<CFontSprite *>( CCommonObject::GetResMgr()->FindObject("HiScoreFont") );
		
		SetMouseCursor( dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("Cursor") ) );
		
		SetWindowSpr( dynamic_cast<CExpWindow *>( CCommonObject::GetResMgr()->FindObject("Window") ) );
		
		SetFingIcoSpr( dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("FingIco") ) );
		
		//�`���[�g���A���������̐ݒ�
		GetWindowSpr()->SetTutorialExp( CCommonObject::GetAppli()->GetFileMgr() );
		
		//�T�E���h�I�u�W�F�N�g�̒ǉ�
		CCommonObject::GetSoundMgr()->PushResource( CCommonObject::GetResMgr() );
		
		SetState( &CSceneTemplate::Init );
	}

}


//=============================================================================
//������
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CSceneGameTitle::Init( Uint32 dt )
{
	m_eSceneState = STATE_CONTINUE;
	
	printf("[GameTitle]::Init\n");
	
	GetMouseCursor()->SetDivNumX( 3 );
	
	GetMouseCursor()->SetAnimXID( 1 );
	
	GetFingerSpr()->SetVisibleFlag( false );
	
	//�����v���C���́A�����I�Ƀ`���[�g���A�����[�h�Ɉڍs
	if( GetFirstGameFlag() )
	{
		SetTutorialFlag( true );
	}
	
	else
	{
		SetTutorialFlag( false );
	}
	
	char Temp[10];
	
	sprintf_s( Temp, 10, "%d", GetHiScore() );
	
	m_pHiScoreFont->SetDrawString( Temp );
	
	//�^�C�g�����j���[�̐ݒ�
	SetTitleMenu();
	
	IsFade = false;
	
	SetBGM( m_pTitleBGM );
	
	SetState( &CSceneTemplate::Idle );
	
	
}

//=============================================================================
//�ҋ@��
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CSceneGameTitle::Idle( Uint32 dt )
{
	
	printf("[GameTitle]::Idle %d\n", time );
	
	
	Sound::SPlayBlock Tbl[] =
	{
		{
			1,
			Sound::PLAY_TIME_AUTO,
			Sound::PLAY_TIME_AUTO,
		},
		
		{
			-1,
			4.0f,
			Sound::PLAY_TIME_AUTO,
		},
	};
	
	//BGM�̍Đ�
	GetBGM()->Play( Tbl, 2 );
	
	//�����_�����O
	Rendering();
	
	time += dt;
	
	
}

//=============================================================================
//�����_�����O
//=============================================================================
void CSceneGameTitle::Rendering()
{
	
	/*2D���X�g�̏���*/
	//Exec2DList();

	/*2D���X�g�̃����_�����O*/
	//Rendering2DList();
	
	m_pBG->Exec();
	
	m_pBG->Rendering();
	
	m_pTitleMenu->Exec();
		
	m_pTitleMenu->Rendering();
	
	if( GetClearCount() > 0 )
	{
		m_pHiScoreSpr->Exec();
		
		m_pHiScoreSpr->Rendering();
		
		m_pHiScoreFont->Exec();
		
		m_pHiScoreFont->Rendering();
	}
	
	GetMouseCursor()->SetVisibleFlag( true );
	GetMouseCursor()->SetAnimXID( 1 );
	
	
	//�}�E�X�A�C�R���̃����_�����O
	RenderMouseIco();
	
	if( m_pTitleMenu->GetHitStringFlag() && !IsFade )
	{
		/*�V�[���̈ړ�*/
		MoveScene( ( eSelectScene )( m_pTitleMenu->GetSelectIndex() ) );
	}
	
	
	
	

}

//=============================================================================
//�^�C�g�����j���[�̐ݒ�
//=============================================================================
void CSceneGameTitle::SetTitleMenu()
{
	CMenu::StringList strList;
	
	const int TUTORIAL_POS = 1;
	
	//���j���[�̕\���ʒu
	Math::Point2DF Pos[] =
	{
		Math::Point2DF( 599, 262 ),
		Math::Point2DF( 594, 317 ),
		Math::Point2DF( 593, 375 ),
	};
	
	/*���j���[���ږ�*/
	string strMenu[] =
	{
		"r q _ s",//�X�^�[�g
		"a ( _ s l 3 .",//�`���[�g���A��
		"d ( 4 l ) 4",//�V���E�����E
	};
	
	for( int i = 0;	i < MENU_MAX;++i )
	{
		
		
		strList.priority = i;
		strList.m_Pos = Pos[i];
		strList.m_Str = strMenu[i];
		strList.m_IsEnable = true;
		
		CFontSprite *pFontSpr = m_pTitleMenu->GetMenuFont();
		
		
		Math::Point2DF fSize = pFontSpr->GetFontSprite()->GetStringSize( strMenu[i].c_str() );
		
		strList.m_HitRect.Set( Pos[i].x, Pos[i].y, fSize.x, fSize.y );
		
		/*�`�敶���񃊃X�g�ɒǉ�*/
		/*�����v���C���́A�`���[�g���A����\�������Ȃ�*/
		if( GetFirstGameFlag() && i == TUTORIAL_POS )
		{
		}
		
		else
		{
			m_pTitleMenu->SetStringList( strList );
		}
		
	}

}

//=============================================================================
// �V�[���̈ړ�
//=============================================================================
//[input]
//	eScene:�ړ�����V�[��
//=============================================================================
void CSceneGameTitle::MoveScene( eSelectScene eScene )
{
	if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
	{
		SetSelectScene( eScene );
		
		SetState( &CSceneTemplate::End );
		
		CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_DECIDE );
		
		IsFade = true;
		
	}
}



