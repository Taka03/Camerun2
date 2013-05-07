//*============================================================================
//ScenePhoto.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "ScenePhoto.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	strFileName:�t�@�C����
//=============================================================================
CScenePhoto::CScenePhoto( string strFileName ) 
:m_pPhoto(NULL),
 m_pCheckMenu(NULL),
 CSceneTemplate( strFileName )
{
	m_IsShowMenu = false;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScenePhoto::~CScenePhoto(void)
{

}

//=============================================================================
//�I�u�W�F�N�g�f�[�^�̏�����
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CScenePhoto::InitObjectData( Uint32 dt )
{
	if( !CCommonObject::GetResMgr()->IsLoading() )
	{
		char Temp[16];
		
		sprintf_s( Temp, 16, "Photo%d", GetFilmCount() );
		
		m_pPhoto = dynamic_cast<CPhoto *>( CCommonObject::GetResMgr()->FindObject(Temp) );
		
		m_pCheckMenu = dynamic_cast<CMenu *>( CCommonObject::GetResMgr()->FindObject("PhotoCheckMenu") );
		
		m_pBG = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("ShootBG") );
		
		m_pCheckMenu->SetCheckMenu( "- C y d j r t" );
	
		SetState( &CSceneTemplate::Init );
	}

}

//=============================================================================
//������
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CScenePhoto::Init( Uint32 dt )
{
	printf("[CScenePhoto]::Init\n");
	
	m_eSceneState = STATE_CONTINUE;
	
	if( !GetTutorialFlag() )
	{
		m_IsShowMenu = true;
	}
	
	else
	{
		m_IsShowMenu = false;
	}
	
	m_pCheckMenu->SetVisibleFlag( true );
	
	if( GetTutorialFlag() )
	{
		m_pCheckMenu->SetStringFlag( 1, false );
		
		//m_pCheckMenu->GetStringList( 1 ).m_IsHitString
		
		//m_pCheckMenu->GetStringList( 1 ).m_IsEnable = false;
	}
	
	else
	{
		m_pCheckMenu->SetStringFlag( 1, true );
	}
	
	
	
	if( !CCommonObject::GetResMgr()->IsLoading() )
	{
		char Temp[16];
		
		sprintf_s( Temp, 16, "Photo%d", GetFilmCount() );
		
		m_pPhoto = dynamic_cast<CPhoto *>( CCommonObject::GetResMgr()->FindObject(Temp) );
		
		m_pPhoto->SetPosition( Math::Vector2D( 160, 50 ) );
		
		SetState( &CSceneTemplate::Idle );
		
	}	
	
}

//=============================================================================
//�ҋ@��
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CScenePhoto::Idle( Uint32 dt )
{
	/*�g��p�̎ʐ^�T�C�Y*/
	const Math::Point2DF fMAX_PHOTO_SIZE( 480, 360 );
	
	CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_NORMAL );
	
	if( m_pPhoto != NULL )
	{
		Math::Rect2DF Dst( m_pPhoto->GetPosition().x, m_pPhoto->GetPosition().y,
						   fMAX_PHOTO_SIZE.x, fMAX_PHOTO_SIZE.y );
		
		m_pPhoto->SetDstRect( Dst );
		
		/*�`��*/
		m_pPhoto->Draw();	
		
		/*�����_�����O*/
		Rendering();
	}
	
	CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
	
	/*�w�A�C�R���̏���*/
	FingIcoExec();
	
	if( GetTutorialFlag() )
	{
		GetWindowSpr()->Exec();
		
		GetWindowSpr()->Rendering();
	}
	
	/*���j���[�̕\��*/
	RenderMenu();
	
	if( !GetTutorialFlag() )
	{
		if( m_pCheckMenu->GetHitStringFlag() )
		{
			MoveScene( (CScenePhoto::eSelectPhoto)( m_pCheckMenu->GetSelectIndex() ) );
		}
	}
	
	
	
	
}


//=============================================================================
//�����_�����O
//=============================================================================
void CScenePhoto::Rendering( )
{
	m_pBG->Exec();
	
	m_pBG->Rendering();
	
	m_pPhoto->Rendering();
	
	GetMouseCursor()->SetVisibleFlag( true );
	GetMouseCursor()->SetAnimXID( 1 );
	
	
	RenderMouseIco();
	
}

//=============================================================================
// �V�[���̈ړ�
//=============================================================================
//[input]
//	eScene:�ړ�����V�[��
//=============================================================================
void CScenePhoto::MoveScene( eSelectPhoto eSelect )
{
	if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
	{
		SetSelectScene( eSelect );
		
		CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_DECIDE );

		
		if( GetTutorialFlag() )
		{
			GetWindowSpr()->AddStrCount( 1 );
		}
		
		SetState( &CSceneTemplate::End );
	}
}

//=================================================================================================
//�ʐ^�m�F����
//=================================================================================================
void CScenePhoto::SelectFuncExec()
{
	SelectFunc FuncTbl[] =
	{
		&CScenePhoto::RegistPhoto,
		&CScenePhoto::RemovePhoto,
	};	
	
	(this->*FuncTbl[ m_pCheckMenu->GetSelectIndex() ])();

}

//=================================================================================================
/*��������ʐ^�m�F�̌ʏ���*/
//=================================================================================================

//=============================================================================
// �ʐ^���c��
//=============================================================================
void CScenePhoto::RegistPhoto()
{
	SetPhotoSaveFlag( true );
}

//=============================================================================
// �ʐ^��j������
//=============================================================================
void CScenePhoto::RemovePhoto()
{
	CCommonObject::GetResMgr()->RemoveObject( m_pPhoto );
}

//=================================================================================================
/*�����܂Ŏʐ^�m�F�̌ʏ���*/
//=================================================================================================

//=================================================================================================
/*��������X�N���v�g�̌ʏ���*/
//=================================================================================================

//=============================================================================
// �ʐ^�ۑ��X�N���v�g
//=============================================================================
void CScenePhoto::PhotoSaveScript()
{
	const int REGIST_PHOTO = 0;//�ʐ^�ۑ�
	
	m_IsShowMenu = true;
	
	/*�E�����̖��\��*/
	SetFingState( CSceneBase::FING_RIGHT );
	
	GetFingerSpr()->SetInitPosition( m_pCheckMenu->GetPosition() + Math::Vector2D( -10.0f, 60.0f ) );
	
	if( m_pCheckMenu->GetHitStringFlag() )
	{
		if( m_pCheckMenu->GetSelectIndex() == REGIST_PHOTO )
		{	
			//��Α��݂��Ȃ��G���^�[�Q�b�g�ɂ���
			SetTarget( dynamic_cast<CEnemy *>( CCommonObject::GetResMgr()->FindObject( "Manta1" ) ) );
			
			MoveScene( SELECT_REGIST );
			
		}
		
		else
		{
			CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_PROHIBIT );
		}
	}
	
	
}

//=================================================================================================
/*�����܂ŃX�N���v�g�̌ʏ���*/
//=================================================================================================

//=============================================================================
// ���j���[�̃����_�����O
//=============================================================================
void CScenePhoto::RenderMenu( )
{
	m_pCheckMenu->Exec();
	
	m_pCheckMenu->Rendering();
	
}






