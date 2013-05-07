//*============================================================================
//ScenePause.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "ScenePause.h"

//=============================================================================
//const
//=============================================================================
namespace
{
	const int MENU_MAX = 3;
	int PhotoIdx = 0;
}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	strFileName:�t�@�C����
//=============================================================================
CScenePause::CScenePause( string strFileName ) 
:CSceneTemplate( strFileName ),
 m_pPauseMenu( NULL ),
 m_pCheckMenu( NULL )
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScenePause::~CScenePause(void)
{

}

//=============================================================================
//�I�u�W�F�N�g�f�[�^�̏�����
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CScenePause::InitObjectData( Uint32 dt )
{
	if( !CCommonObject::GetResMgr()->IsLoading() )
	{
		/*2D�I�u�W�F�N�g�̒ǉ�*/
		Push2DObject();
		
		m_pPauseMenu = dynamic_cast<CMenu *>( CCommonObject::GetResMgr()->FindObject("PauseMenu") );
		
		m_pCheckMenu = dynamic_cast<CMenu *>( CCommonObject::GetResMgr()->FindObject("CheckMenu") );
		
		m_pNextBtnSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("NextBtn") );
		
		m_pNextBtnSpr->SetDivNumX( 3 );
		
		m_pFontSpr = dynamic_cast<CFontSprite *>( CCommonObject::GetResMgr()->FindObject("PhotoMinFont") );
		
		m_pClearSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("ClearPoint") );
		
		m_pClrPntFontSpr = dynamic_cast<CFontSprite *>( CCommonObject::GetResMgr()->FindObject("ClearScoreFont") );
		
		m_pSkillExpSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("SkillExp") );
		
		m_pSkillExpSpr->SetDivNumX( 6 );
		
		m_pTargetSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("TargetExp") );
		
		m_pTargetSpr->SetDivNumX( 10 );
		
		//�X�L����
		string strSkill[] =
		{
			"Ameus",
			"Bird",
			"Car",
			"Manta",
			"Mouse",
		};
		
		for( int i = 0;i < SKILL_MAX;++i )
		{
			string strTemp = "Skill";
			
			strTemp += strSkill[i];
			
			m_pSkillSpr[i] = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject( strTemp.c_str() ) );
		}
		
		SetState( &CSceneTemplate::Init );
	}
	
	/*�m�F��ʂɐݒ�*/
	m_pCheckMenu->SetCheckMenu("q e s . i m S .");//�^�C�g���j���h��
		
	// �|�[�Y���j���[�̐ݒ�
	SetPauseMenu();
	
}


//=============================================================================
//������
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CScenePause::Init( Uint32 dt )
{
	printf("[CScenePause]::Init\n");
	
	m_eSceneState = STATE_CONTINUE;
	
	SetState( &CSceneTemplate::Idle );
	
	PhotoIdx = 0;
	
	if( GetTutorialFlag() )
	{
		for( int i = 1;i < 3;++i )
		{	
			m_pPauseMenu->SetStringFlag( i, false );
		}
	}
	
	else
	{
		for( int i = 1;i < 3;++i )
		{	
			m_pPauseMenu->SetStringFlag( i, true );
		}
	}
	
	
	
}

//=============================================================================
//�ҋ@��
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CScenePause::Idle( Uint32 dt )
{
	Rendering();
	
	
	
	NextBtnExec();
	
	
}

//=============================================================================
//�����_�����O
//=============================================================================
void CScenePause::Rendering( )
{
	CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_NORMAL );
	
	/*2D���X�g�̏���*/
	Exec2DList();

	/*2D���X�g�̃����_�����O*/
	Rendering2DList();
	
	if( !m_pCheckMenu->GetVisibleFlag() )
	{	
		m_pPauseMenu->Exec();
	
		m_pPauseMenu->Rendering();
	}
	
	//�X�L���̕`��
	DrawSkill();
	
	//�^�[�Q�b�g�̕`��
	DrawTarget();
	
	//�X�L���̐����`��
	DrawSkillExp(0);
	
	
	/*�ʐ^�̕\��*/
	DrawPhoto();
	
	m_pCheckMenu->Exec();
	
	m_pCheckMenu->Rendering();
	
	/*�w�A�C�R���̏���*/
	FingIcoExec();
	
	
	if( GetTutorialFlag() )
	{
		GetWindowSpr()->Exec();
		GetWindowSpr()->Rendering();
	}
	
	/*������ɓ������Ă���Ƃ�*/
	if( m_pPauseMenu->GetHitStringFlag() && m_pPauseMenu->GetVisibleFlag() )
	{
		switch( m_pPauseMenu->GetSelectIndex()  )
		{
			/*�Q�[���ɖ߂�ꍇ�͊m�F�Ȃ�*/
			case SCENE_RETURNGAME:
			{
				/*�V�[���̈ړ�*/
				MoveScene( ( eSelectScene )( m_pPauseMenu->GetSelectIndex() ) );
				break;
			}
			
			//���g���C
			case SCENE_RETRY:
			{
				if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
				{
					if( GetTutorialFlag() )
					{
						CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_PROHIBIT );
					}
					
					else
					{	
						/*�^�C�g����ݒ�(���g���C�X��)*/
						m_pCheckMenu->SetTitleString( "l s o e r ." );
						
						m_pCheckMenu->SetShowFrameFlag( true );
						m_pCheckMenu->SetVisibleFlag( true );
					}
				}
				
				break;
			}
			
			//�^�C�g���ɂ��ǂ�
			case SCENE_RETURNTITLE:
			{
				if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
				{
					if( GetTutorialFlag() )
					{
						CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_PROHIBIT );
					}
					
					else
					{	
						/*�^�C�g����ݒ�(�^�C�g���j���h��)*/
						m_pCheckMenu->SetTitleString( "q e s . i m S ."	 );
						
						m_pCheckMenu->SetShowFrameFlag( true );
						m_pCheckMenu->SetVisibleFlag( true );
					}
				}


				break;
			}
		}
		
		
	}
	
	CheckMenuExec();
	
	if( GetFilmCount() > 0 )
	{
		m_pFontSpr->Exec();
		
		m_pFontSpr->Rendering();
	}
	
	m_pClearSpr->Exec();
	m_pClearSpr->Rendering();
	
	char Temp[10];
	
	sprintf_s( Temp, 10, "%d", GetClearPoint() ); 
	
	m_pClrPntFontSpr->SetDrawString( Temp );
	
	m_pClrPntFontSpr->Exec();
	m_pClrPntFontSpr->Rendering();
	


	GetMouseCursor()->SetVisibleFlag( true );
	GetMouseCursor()->SetAnimXID( 1 );
	
	RenderMouseIco();
	
	//CCommonObject::GetAppli()->GetRenderer()->DebugPrint( Math::Point2DI( 0, 120 ), CColor( 255, 255, 255 ), "%d", PhotoIdx );
	
}

//=============================================================================
// �|�[�Y���j���[�̐ݒ�
//=============================================================================
void CScenePause::SetPauseMenu()
{
	CMenu::StringList strList;
	
	Math::Point2DF Pos[MENU_MAX];//���j���[�̕\���ʒu
	
	/*���j���[���ږ�*/
	string strMenu[] =
	{
		"m S .",//���h��
		"l s o e",//���g���C
		"q e s .",//�^�C�g��
	};
	
	const float fMARGIN = 50.0f;
	
	for( int i = 0;	i < MENU_MAX;++i )
	{
		Pos[i] = Math::Point2DF( m_pPauseMenu->GetPosition().x, 
								 m_pPauseMenu->GetPosition().y + toF( i * fMARGIN ) );
		
		strList.priority = i;
		strList.m_Pos = Pos[i];
		strList.m_Str = strMenu[i];
		strList.m_IsEnable = true;
		
		CFontSprite *pFontSpr = m_pPauseMenu->GetMenuFont();
		
		Math::Point2DF fSize = pFontSpr->GetFontSprite()->GetStringSize( strMenu[i].c_str() );
		
		strList.m_HitRect.Set( Pos[i].x, Pos[i].y, fSize.x, fSize.y );
		
		/*�`�敶���񃊃X�g�ɒǉ�*/
		m_pPauseMenu->SetStringList( strList );
		
	}
	
}

//=============================================================================
// �m�F��ʂ̏���
//=============================================================================
void CScenePause::CheckMenuExec()
{
	
	if( m_pCheckMenu->GetVisibleFlag() && CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
	{
		if( m_pCheckMenu->GetHitStringFlag() )
		{
			/*�͂���I�񂾏ꍇ*/
			if( m_pCheckMenu->GetSelectIndex() == 0 )
			{
				for( Uint32 i = 0;i < GetFilmCount();++i )
				{
					char Temp[10];
					
					sprintf_s( Temp, 10, "Photo%d", i );
					
					CPhoto *pPhoto = dynamic_cast<CPhoto *>( CCommonObject::GetResMgr()->FindObject(Temp) );
					
					/*����ʐ^�B�e�ł���悤�ɍ폜*/
					CCommonObject::GetResMgr()->RemoveObject( pPhoto );
				}
				
				GetBGM()->GetBGMDevice()->Stop();
				
				CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_DECIDE );
				
				
				MoveScene( ( eSelectScene )( m_pPauseMenu->GetSelectIndex() ) );
				m_pCheckMenu->SetVisibleFlag( false );
				m_pCheckMenu->SetShowFrameFlag( false );

			}
			
			/*��������I�񂾏ꍇ*/
			else
			{
				m_pCheckMenu->SetVisibleFlag( false );
				m_pCheckMenu->SetShowFrameFlag( false );
				
				CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_DECIDE );

			}
		}
	}	
	
}

//=============================================================================
// �V�[���̈ړ�
//=============================================================================
//[input]
//	eScene:�ړ�����V�[��
//=============================================================================
void CScenePause::MoveScene( eSelectScene eScene )
{
	if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
	{
		SetSelectScene( eScene );
		
		CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_DECIDE );
		
		SetState( &CSceneTemplate::End );
		
	}
}


//=============================================================================
// �|�[�Y���j���[�X�N���v�g
//=============================================================================
void CScenePause::PauseMenuScript()
{
	/*�E�����̖��\��*/
	SetFingState( CSceneBase::FING_RIGHT );
	
	GetFingerSpr()->SetInitPosition( m_pPauseMenu->GetPosition() + Math::Vector2D( -120.0f, 20.0f ) );
	
	if( m_pPauseMenu->GetHitStringFlag() && m_pPauseMenu->GetVisibleFlag() )
	{
		if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH && m_pPauseMenu->GetSelectIndex() == SCENE_RETURNGAME )
		{
			/*�����\���ɂ���*/
			SetFingState( CSceneBase::FING_NONE );
			
			GetWindowSpr()->AddStrCount( 1 );	
		}	
	}
}

//=============================================================================
//�ʐ^�̕`��
//=============================================================================
void CScenePause::DrawPhoto()
{
	char Temp[10];
	
	sprintf_s( Temp, 10, "Photo%d", PhotoIdx );
	
	CPhoto *pPhoto = dynamic_cast<CPhoto *>( CCommonObject::GetResMgr()->FindObject( Temp ) );
	
	if( pPhoto != NULL )
	{
		CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_NORMAL );
		
		Math::Rect2DF Dst( 95.0f, 40.0f, 360, 270 );
		
		Math::Rect2DF Src( 0, 0, pPhoto->GetSize().x, pPhoto->GetSize().y );
		
		CCommonObject::GetAppli()->GetRenderer()->DrawTexture( Dst, CColor( 255, 255, 255 ), Src, pPhoto->GetTexture() );
		
		char Temp[20];
		
		sprintf_s( Temp, 20, "%dpoint", pPhoto->GetScore() );
		
		m_pFontSpr->SetDrawString( Temp );
		
	}
	
	
	
	CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
	
	
}

//=============================================================================
//�l�N�X�g�{�^���̏���
//=============================================================================
void CScenePause::NextBtnExec()
{
	static int count = 0;
	
	Math::Vector2D vPos( toF( CCommonObject::GetMouse()->GetMouse()->GetPosX() ), toF( CCommonObject::GetMouse()->GetMouse()->GetPosY() ) );
	
	if( GetFilmCount() > 1 )
	{
		if( ::Collision::Point_Rect( vPos, m_pNextBtnSpr->GetHitRect() ) )
		{
			m_pNextBtnSpr->SetAnimXID( 2 );
			
			if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
			{
				CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_SHUTTER );
				count++;
			}
			
		}
		
		else
		{
			m_pNextBtnSpr->SetAnimXID( 1 );
		}
	}
	
	else
	{
		if( ::Collision::Point_Rect( vPos, m_pNextBtnSpr->GetHitRect() ) )
		{
			if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
			{
				CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_PROHIBIT );
			}
		}
		
		m_pNextBtnSpr->SetAnimXID( 0 );
		
	}
	
	if( GetFilmCount() > 0 )
	{	
		PhotoIdx = ( count / 2 ) % GetFilmCount();
	}
	
}

//=============================================================================
//�X�L���̕`��
//=============================================================================
void CScenePause::DrawSkill()
{
	CPlayer *pPlayer = dynamic_cast<CPlayer *>( CCommonObject::GetResMgr()->FindObject("Player") );
	
	string strTypeName[] =
	{
		"�A���E�X",
		"�g��",
		"�N���}",
		"�}���^",
		"�l�Y�~",
	};
	
	for( int i = 0;i < SKILL_MAX;++i )
	{
		if( pPlayer->GetCaptureFlag() )
		{
			if( pPlayer->GetCapedEnemy()->GetStTypeName().compare( strTypeName[i] ) == 0 )
			{
				m_pSkillSpr[i]->SetPosition( Math::Vector2D( 300, 437 ) );
				
				m_pSkillSpr[i]->Exec();
				
				m_pSkillSpr[i]->Rendering();
				
				
			}
			
		}
	}
}

//=============================================================================
//�X�L�������̕`��
//=============================================================================
//[input]
//	no:�����ԍ�
//=============================================================================
void CScenePause::DrawSkillExp( int no )
{
	CPlayer *pPlayer = dynamic_cast<CPlayer *>( CCommonObject::GetResMgr()->FindObject("Player") );
	
	string strTypeName[] =
	{
		"�A���E�X",
		"�g��",
		"�N���}",
		"�}���^",
		"�l�Y�~",
	};
	
	int MenuCount = 0;
		
	for( int i = 0;i < SKILL_MAX;++i )
	{
		if( pPlayer->GetCaptureFlag() )
		{
			if( pPlayer->GetCapedEnemy()->GetStTypeName().compare( strTypeName[i] ) == 0 )
			{
				m_pSkillExpSpr->SetAnimXID( i + 1 );
			}
			
		}
		
		else
		{
			MenuCount++;
			
			if( MenuCount == SKILL_MAX )
			{
				m_pSkillExpSpr->SetAnimXID( 0 );
			}
		}
	}

	
	m_pSkillExpSpr->Exec();
	
	m_pSkillExpSpr->Rendering();

}

//=============================================================================
//�^�[�Q�b�g�̕`��
//=============================================================================
void CScenePause::DrawTarget()
{
	string strTypeName[] =
	{
		"�A���E�X",
		"�g��",
		"�e�C�G��",
		"�}���^",
		"�l�Y�~",
		"�E�T�M",
		"�A�I�E�T�M",
		"�A�J�E�T�M",
		"�t���X�C",
		"�f���V��",
	};
	
	const int TARGET_MAX = 10;
	
	for( int i = 0;i < TARGET_MAX;++i )
	{
		if( GetTarget()->GetStTypeName().compare( strTypeName[i] ) == 0 )
		{
			m_pTargetSpr->SetAnimXID( i );
		}
	}
	
	m_pTargetSpr->Exec();
	
	m_pTargetSpr->Rendering();
}






