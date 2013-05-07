//*============================================================================
//SceneChat.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneChat.h"
#include <fstream>

//=============================================================================
//namespace
//=============================================================================
namespace
{
	int time = 0;
}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CSceneChat::CSceneChat(  )
{
	SetState( &CSceneChat::Init );
	
	//GetResMgr()->Push( new CFileData( "chat.png", "Chat", SPRITE, Math::Vector3D( 0, 0, 0 ) ) );
	//GetResMgr()->Push( new CFileData( "ChatFont.sff", "ChatFont", FONT, Math::Vector3D( 110, 465, 0 ) ) );
	//GetResMgr()->Push( new CFileData( "ConvBGM.ogg", "ChatBGM", BGM ) );
	
}



//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pResMgr:���\�[�X�Ǘ�
//	pMissionMgr:�ݒ肷��~�b�V�����Ǘ�
//=============================================================================
CSceneChat::CSceneChat( CResourceManager *pResMgr, CMissionManager *pMissionMgr )
{
	SetResMgr( pResMgr );
	SetMissionMgr( pMissionMgr );

	SetState( &CSceneChat::Init );
	
	//GetResMgr()->Push( new CFileData( "chat.png", "Chat", SPRITE, Math::Vector3D( 0, 0, 0 ) ) );
	//GetResMgr()->Push( new CFileData( "ChatFont.sff", "ChatFont", FONT, Math::Vector3D( 110, 465, 0 ) ) );
	//GetResMgr()->Push( new CFileData( "ConvBGM.ogg", "ChatBGM", BGM ) );
	
	
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneChat::~CSceneChat(void)
{

}

//=============================================================================
//������
//=============================================================================
void CSceneChat::Init( Uint32 dt )
{
	printf("[GameChat]::Init\n");
	
	if( !GetResMgr()->IsLoading() )
	{
		m_pBG = dynamic_cast<CSprite *>( GetResMgr()->Get2DObject()->FindObjectFromName("Chat") );
		m_pChatFont = dynamic_cast<CFontSprite *>( GetResMgr()->Get2DObject()->FindObjectFromName("ChatFont") );
		m_pMusic = dynamic_cast<CBGM *>( GetResMgr()->GetSoundObject()->FindObjectFromName("ChatBGM") );
		
		SetState( &CSceneChat::Idle );
	}
}

//=============================================================================
//�ҋ@��
//=============================================================================
void CSceneChat::Idle( Uint32 dt )
{
	#if defined( DEBUG_CHAT )
	
		std::ifstream ifs("missionno.txt");
		
		Sint32 MissionNo = 0;
		
		ifs >> MissionNo;
		
		CMission *pMission = dynamic_cast<CMission *>( pScene->GetMissionMgr()->GetMission( MissionNo ) );
	
	
	#else
		Sint32 MissionNo = GetMissionMgr()->GetMissionNo();
		
		CMission *pMission = dynamic_cast<CMission *>( GetMissionMgr()->GetMission( MissionNo ) );
		
	#endif
	
	
	Peripheral::IMouse *pMouse = GetResMgr()->GetCore()->GetMouse();
	
	m_pChatFont->SetVecTextChat( pMission->GetMissionData().m_vecChat );
	
	printf("[GameChat]::Idle %d\n", time );
	
	time += dt;
	
	/*�����_�����O*/
	Rendering();
	
	/*�m�x�����ɕ`��*/
	if( m_pChatFont->DrawNovelStyle( GetResMgr()->GetCore() ) )
	{
		
	#if defined (DEBUG_CHAT)
	
		if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_R2 ) )
		{
			pChatFont->SetRefCount( 0 );
		}
	
	
	#else
	
		if( pMouse->GetClickL() )
		{
			SetState( &CSceneChat::End );
		
		}
	
		
	#endif
	
	}
	
	
	m_pBG->Exec();
	
	m_pMusic->Exec();
	
	
	
}

//=============================================================================
//�I��
//=============================================================================
void CSceneChat::End( Uint32 dt )
{
	printf("[GameChat]::End\n");
	
	m_eSceneState = STATE_FINISH;
	
	SetState( &CSceneChat::Init );
	
}

//=============================================================================
//�X�V
//=============================================================================
eSceneState CSceneChat::UpDate()
{
	( this->*m_pStateFunc )( 1 );
	return m_eSceneState;
}



//=============================================================================
//�����_�����O
//=============================================================================
void CSceneChat::Rendering()
{
	/*�w�i�̕`��*/
	m_pBG->Rendering();	
	
	/*�t�H���g�̕`��*/
	m_pChatFont->Rendering();
	
	
}


//=============================================================================
//����
//=============================================================================
//[input]
//	pScene:�ݒ肷��V�[��
//=============================================================================
//void CSceneChat::Exec( CScene *pScene )
//{
//	Selene::Renderer::IRender *pRender = pScene->GetAppDevice()->GetRenderer();
//	
//	CSprite *pBG = dynamic_cast<CSprite *>( pScene->Get2DObject()->FindObjectFromName("Chat") );
//	
//	#if defined( DEBUG_CHAT )
//	
//		std::ifstream ifs("missionno.txt");
//		
//		Sint32 MissionNo = 0;
//		
//		ifs >> MissionNo;
//		
//		CMission *pMission = dynamic_cast<CMission *>( pScene->GetMissionMgr()->GetMission( MissionNo ) );
//	
//	
//	#else
//		Sint32 MissionNo = pScene->GetMissionMgr()->GetMissionNo();
//		
//		CMission *pMission = dynamic_cast<CMission *>( pScene->GetMissionMgr()->GetMission( MissionNo ) );
//		
//	#endif
//	
//	CFontSprite *pChatFont = dynamic_cast<CFontSprite *>( pScene->Get2DObject()->FindObjectFromName("ChatFont") );
//	
//	pChatFont->SetVecTextChat( pMission->GetMissionData().m_vecChat );
//	
//	CBGM *pGameMusic = dynamic_cast<CBGM *>( pScene->GetSoundObj()->FindObjectFromName("ChatBGM") );
//	
//	pGameMusic->Exec();
//	
//	/*��ʂ̃N���A*/
//	pRender->Clear();
//	
//	/*�`��J�n*/
//	pRender->Begin();
//	
//	pBG->Rendering();
//	
//	pChatFont->Rendering();
//	
//	//pChatFont->Draw();
//	
//	pRender->End();
//	
//	if( pChatFont->DrawNovelStyle( pScene->GetAppDevice()->GetCore(), pScene->GetJoyPad()->GetController() ) )
//	{
//		
//	#if defined (DEBUG_CHAT)
//	
//		if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_R2 ) )
//		{
//			pChatFont->SetRefCount( 0 );
//		}
//	
//	
//	#else
//		
//		if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_R2 ) )
//		{
//			pBG->SetVisibleFlag( false );
//			
//			pScene->SetFontSize( 15 );
//			
//			pScene->SetNextScene( SCENE_DRAWMISSION );
//			
//			pScene->SetSceneState( STATE_FADEOUT );
//		
//		}
//		
//	#endif
//	
//	}
//	
//	pBG->Exec();
//	
//	//pChatFont->Exec();
//	
//	//pChatFont->GetFontSprite()->Begin();
//	
//	//const int STR_LENGTH = 29;
//	
//	
//	//pChatFont->GetFontSprite()->DrawString( pChatFont->GetFontSprite
//	
//	//string Str = pChatFont->GetDrawString().substr(0, (STR_LENGTH+1)*2);
//	//
//	//pChatFont->GetFontSprite()->DrawString( Str.c_str(), Math::Point2DF( 110, 465 ), CColor(100, 100, 100 ), STR_LENGTH );
//	//
//	//Str = pChatFont->GetDrawString().substr( (STR_LENGTH+1)*2, (STR_LENGTH+1)*3 );
//	//
//	//pChatFont->GetFontSprite()->DrawString( Str.c_str(), Math::Point2DF( 110, 465 + pChatFont->GetFontSprite()->GetSize() ), CColor(100, 100, 100 ), STR_LENGTH );
//
//	//Str = pChatFont->GetDrawString().substr( (STR_LENGTH+1)*3, (STR_LENGTH+1)*4 );
//	//
//	//pChatFont->GetFontSprite()->DrawString( Str.c_str(), Math::Point2DF( 110, 465 + pChatFont->GetFontSprite()->GetSize() * 2 ), CColor(100, 100, 100 ), STR_LENGTH );
//	//
//	//pChatFont->GetFontSprite()->End();
//	//
//	#if defined( RELEASE )	
//		if( pMission->GetGameClearFlag() )
//	#endif
//	{
//	
//		/*���̃V�[���Ɉړ�*/
//		if( pScene->GetJoyPad()->GetController()->GetState( BUTTON_STATE_PUSH, BUTTON_START ) )
//		{	
//			pBG->SetVisibleFlag( false );
//			
//			pScene->SetFontSize( 40 );
//			
//			pScene->SetNextScene( SCENE_DRAWMISSION );
//			
//			pScene->SetSceneState( STATE_FADEOUT );
//			
//			
//		}
//	}
//
//	//eInputButtonType eButtonUpDown = pScene->GetJoyPad()->GetController()->CursorRepeatUpDown( 0, Cursor, MissionClrCount + 1 );
//	//eInputButtonType eButtonUpDown = pScene->GetJoyPad()->GetController()->CursorRepeatUpDown( 0, Cursor, 4 );
//
//}
