//*============================================================================
//SceneNewComponent.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneNewComponent.h"

//=============================================================================
//variable
//=============================================================================
namespace 
{
	int time = 0;
	vector< string > strList;
	bool IsPlaySE = false;
	
	Sint32 MessageNo = 0;
	
	
}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	strFileName:�t�@�C����
//=============================================================================
CSceneNewComponent::CSceneNewComponent( string strFileName ) 
:CSceneTemplate( strFileName )
{
	CFileLoader FileLoader;
	
	CCommonObject::GetAppli()->GetFileMgr()->SetCurrentPath("Text");
	
	::File::IResourceFile *pResFile = CCommonObject::GetAppli()->GetFileMgr()->FileOpen( "ClearText.txt" );
	
	FileLoader.Load( pResFile->GetNamePointer() );
	
	strList = FileLoader.GetStrList();
	
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneNewComponent::~CSceneNewComponent(void)
{

}

//=============================================================================
//�I�u�W�F�N�g�f�[�^�̏�����
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CSceneNewComponent::InitObjectData( Uint32 dt )
{
	if( !CCommonObject::GetResMgr()->IsLoading() )
	{
		m_pClearFont = dynamic_cast<CFontSprite *>( CCommonObject::GetResMgr()->FindObject("ClearFont") );
		
		m_pBGSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("CompBack") );
		
		m_pClearSpr	= dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("GameClear") );	
		
		m_pFailSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("GameFail") );		
		
		SetState( &CSceneTemplate::Init );
	}

}


//=============================================================================
//������
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CSceneNewComponent::Init( Uint32 dt )
{
	m_eSceneState = STATE_CONTINUE;
	
	
	printf("[CSceneNewComponent]::Init\n");
	
	if( !CCommonObject::GetResMgr()->IsLoading() )
	{
		IsPlaySE = false;
	
		SetState( &CSceneTemplate::Idle );
	}
	
	time = 0;
	
	Math::CRandom Rand( CCommonObject::GetAppli()->GetCore()->GetSyncCount() );
	
	MessageNo = Rand.GetInt( 1, 4 )	;
	
}

//=============================================================================
//�ҋ@��
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CSceneNewComponent::Idle( Uint32 dt )
{
	
	const int TIME_MAX = 60 * 5;
	
	Rendering();
	
	static int count = 0;
	
	++count;
	
	if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH && count > 30 )
	{
		if( GetClearCount() == 0 )
		{
			AddClearCount();
		}
		
		SetState( &CSceneTemplate::End );
		
		count = 0;
		
		//const int MISSION_MAX = 4;
		//
		////�N���A�J�E���g�̐���
		//if( GetClearCount() > MISSION_MAX )
		//{
		//	SetClearCount( MISSION_MAX );
		//}
	}
		
		

		
	time += dt;
}

//=============================================================================
//�����_�����O
//=============================================================================
void CSceneNewComponent::Rendering( )
{
	m_pBGSpr->Exec();
	m_pBGSpr->Rendering();
	
	if( GetClearCount() == 0 )
	{
		//�`�敶����̐ݒ�
		m_pClearFont->SetDrawString( strList.at( 0 ) );
		
		m_pClearSpr->Exec();
		
		m_pClearSpr->Rendering();
		
		if( !IsPlaySE )
		{	
			CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_CLEAR );
			
			IsPlaySE = true;
		}
		
	}

	else
	{
		/*���_���N���A�|�C���g�𒴂�����Q�[���N���A*/
		if( GetTotalScore() > GetClearPoint() && GetTargetExistFlag() )
		{
			//�`�敶����̐ݒ�
			m_pClearFont->SetDrawString( strList.at( MessageNo ) );
			
			m_pClearSpr->Exec();
			
			m_pClearSpr->Rendering();
			
			if( !IsPlaySE )
			{	
				CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_CLEAR );
				
				IsPlaySE = true;
			}
			
			//�N���A�J�E���g�̑���
			//AddClearCount();
			
		}
		
		
		else
		{
			m_pFailSpr->Exec();
			
			m_pFailSpr->Rendering();
			
			if( !IsPlaySE )
			{	
				CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_FAIL );
				
				IsPlaySE = true;
			}
			
		}
	}
	
	//���b�Z�[�W�̕`��
	DrawMessage();
	
	static int count = 0;
	
	++count;
	
	if( count > 0 && count <= 30 )
	{
		CCommonObject::GetAppli()->GetRenderer()->DrawTextLayer( 2, Math::Point2DI( 20, 540 ), CColor( 255, 255, 255 ),
												  "���N���b�N�ŏI��" );
	}
	
	else if( count > 30 && count < 60 )
	{
	
	}
	
	else if( count > 60 )
	{
		count = 0;
	}
	
	
	GetMouseCursor()->SetVisibleFlag( true );
	GetMouseCursor()->SetAnimXID( 1 );
	
	RenderMouseIco();
	
}

//=============================================================================
//���b�Z�[�W�̕`��
//=============================================================================
void CSceneNewComponent::DrawMessage()
{
	/*�`�敶����*/
	string strDraw = m_pClearFont->GetDrawString();
	
	string::size_type index = strDraw.find("Br");
	
	/*Br�����񂪌���������A������𕪉�����*/
	if( index != string::npos )
	{
		vector<string> strRet =  CFileLoader::SplitString( strDraw, "Br" );
		
		m_pClearFont->DrawMultiLine( strRet );
		
	}
		
	/*�ʏ�ʂ�`��*/
	else
	{
		m_pClearFont->Exec();
	}
	
	vector< string > strTemp;
	
	strTemp.clear();
	
	//�N���A�|�C���g�𒴂��Ă��Ȃ�
	if( GetClearCount() != 0 )
	{
		if( GetTotalScore() < GetClearPoint() )
		{
			strTemp.push_back( strList.at( 6 ) );
		}
		
		//�^�[�Q�b�g���ʂ��Ă��Ȃ�
		if( !GetTargetExistFlag() )
		{
			strTemp.push_back( strList.at( 5 ) );
		}
		
		if( strTemp.size() > 0 )
		{
			m_pClearFont->DrawMultiLine( strTemp );
		}
	}
	
	m_pClearFont->Rendering();

}




