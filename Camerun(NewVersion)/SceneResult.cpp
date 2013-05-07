//*============================================================================
//SceneResult.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneResult.h"

//=============================================================================
//variable
//=============================================================================
namespace
{
	Math::Vector2D vMousePos;//�}�E�X�̈ʒu
	int PhotoCount = 0;//�ʐ^�J�E���^�[
	bool IsDemo = true;//�f�������ǂ���
	bool IsCountUp = false;//�J�E���g�A�b�v����
	bool IsShowTargetExp = false;//�^�[�Q�b�g���\������Ă��邩
	int CountScore = 0;//�X�R�A�̃J�E���g�A�b�v�p
	int UpCount = 0;//�ėp�J�E���^�[
};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	strFileName:�t�@�C����
//=============================================================================
CSceneResult::CSceneResult( string strFileName ) 
:CSceneTemplate( strFileName ),
 m_pBGSpr( 0 ),
 m_pScoreSpr( NULL ),
 m_SelectIdx( 0 )
{
	for( int i = 0;i < FILM_MAX;++i )
	{
		m_pPhoto[i] = NULL;
	}

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneResult::~CSceneResult(void)
{

}

//=============================================================================
//�I�u�W�F�N�g�f�[�^�̏�����
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CSceneResult::InitObjectData( Uint32 dt )
{
	
	if( !CCommonObject::GetResMgr()->IsLoading() )
	{
		Push2DObject();
			
		for( int i = 0;i < FILM_MAX;++i )
		{
			char Temp[16];
			
			sprintf_s( Temp, 16, "Photo%d", i );
			
			m_pPhoto[i] = dynamic_cast<CPhoto *>( CCommonObject::GetResMgr()->FindObject(Temp) );
		
		}
		
		m_pBGSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("Result") );
		m_pScoreSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("Score") );
		
		m_pExtBtnSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("ExitBtn") );
		
		m_pScoreFont = dynamic_cast<CFontSprite *>( CCommonObject::GetResMgr()->FindObject("MiniFont") );
		
		m_pTotalScFont = dynamic_cast<CFontSprite *>( CCommonObject::GetResMgr()->FindObject("TotalFont") );
		
		m_pListNumFont = dynamic_cast<CFontSprite *>( CCommonObject::GetResMgr()->FindObject("ListNumFont") );
		
		m_pListNameFont = dynamic_cast<CFontSprite *>( CCommonObject::GetResMgr()->FindObject("ListNameFont") );
		
		m_pTargetOKSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("TargetOK") );
		
		m_pTargetNGSpr = dynamic_cast<CSprite *>( CCommonObject::GetResMgr()->FindObject("NoTarget") );
		
		m_pResultBGM = dynamic_cast<CBGM *>( CCommonObject::GetResMgr()->FindSoundObj("ResultBGM") );
		
		m_pExtBtnSpr->SetDivNumX( 2 );

		SetState( &CSceneTemplate::Init );
	}

}


//=============================================================================
//������
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CSceneResult::Init( Uint32 dt )
{
	printf("[CSceneResult]::Init\n");
	
	m_eSceneState = STATE_CONTINUE;
	
	IsDemo = true;
	
	IsCountUp = false;
	
	IsShowTargetExp	= false;
	
	m_SelectIdx	= 0;
	
	PhotoCount = 0;
	
	CountScore = 0;
	
	UpCount = 0;
	
	SetBGM( m_pResultBGM );
	
	
	if( !CCommonObject::GetResMgr()->IsLoading() )
	{
		for( int i = 0;i < FILM_MAX;++i )
		{
			char Temp[16];
			
			sprintf_s( Temp, 16, "Photo%d", i );
			
			m_pPhoto[i] = dynamic_cast<CPhoto *>( CCommonObject::GetResMgr()->FindObject(Temp) );
			
		}
		
		SetState( &CSceneTemplate::Idle );
	}
	
}

//=============================================================================
//�ҋ@��
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CSceneResult::Idle( Uint32 dt )
{
	///*���_���N���A�|�C���g�𒴂�����Q�[���N���A*/
	//if( GetTotalScore() > GetClearPoint() && GetTargetExistFlag() )
	//{
	//	SetResult( RESULT_SUCCESS );
	//}
	//
	//else
	//{
	//	SetResult( RESULT_FAILURE );
	//}


	vMousePos.Set( toF( CCommonObject::GetMouse()->GetMouse()->GetPosX() ),
				   toF( CCommonObject::GetMouse()->GetMouse()->GetPosY() ) );

	m_eSceneState = STATE_CONTINUE;
	
	m_pBGSpr->Exec();
	
	m_pScoreSpr->Exec();
	
	m_pExtBtnSpr->Exec();
	
	//�X�R�A�̃J�E���g�A�b�v
	if( IsCountUp )
	{	
		CountUpScore();
	}
	
	if( IsCountUp && IsDemo )
	{
//		CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_CALCSCORE );
	}
	
	if( GetTotalScore() <= 0 )
	{
	//	CCommonObject::GetSoundMgr()->Stop( CSoundManager::SND_CALCSCORE );
	}

	/*�����_�����O*/
	Rendering();
	
	//BGM�̍Đ�
	GetBGM()->Exec();
	
	//�n�C�X�R�A�̍X�V
	if( GetTotalScore() > GetHiScore() )
	{
		SetHiScore( GetTotalScore() );
	}
	
	if( Collision::Point_Rect( vMousePos, m_pExtBtnSpr->GetHitRect() ) && !IsDemo )
	{
		m_pExtBtnSpr->SetAnimXID( 1 );
		
		if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH )
		{
			for( int i = 0;i < FILM_MAX;++i )
			{	
				/*����ʐ^�B�e�ł���悤�ɍ폜*/
				CCommonObject::GetResMgr()->RemoveObject( m_pPhoto[i] );
			}
			
			CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_CHANGE );
			
			//BGM�̍Đ�
			GetBGM()->GetBGMDevice()->Stop();
			
			SetState( &CSceneTemplate::End );
		}
		
	}
	
	else
	{
		m_pExtBtnSpr->SetAnimXID( 0 );
	}
}


//=============================================================================
//�����_�����O
//=============================================================================
void CSceneResult::Rendering( )
{
	/*�w�i�̕\��*/
	m_pBGSpr->Rendering();
	
	//�f�����̂Ƃ��͎ʐ^�𑝉�
	if( IsDemo )
	{
		AddPhotoCount();
	}
	
	/*�傫���ʐ^�̕\��*/
	DrawBigPhoto();
	
	/*�������ʐ^�̕\��*/
	DrawMinPhoto();
	
	DrawPhotoInfo();
	
	/*�X�R�A�̃����_�����O*/
	m_pScoreSpr->Rendering();
	
	if( IsCountUp )
	{
		m_pTotalScFont->Exec();
		
		m_pTotalScFont->Rendering();
	}
	
	m_pExtBtnSpr->Rendering();
	
	if( IsShowTargetExp )	
	{
		ShowTargetResult();
	}
	
	RenderMouseIco();
	
}

//=============================================================================
//�������ʐ^�̕\��
//=============================================================================
void CSceneResult::DrawMinPhoto()
{
	/*�T���l�C���p�̎ʐ^�T�C�Y*/
	const Math::Point2DF fMIN_PHOTO_SIZE( 120, 90 );
	
	const float fMIN_PHOTO_Y = 495;//�������ʐ^��Y�ʒu
	const float fMARGIN_X = 142;//�ʐ^��X�}�[�W��
	
	const float fMARGIN_FRAME = 10.0f;
	
	/*�ʐ^�g�̕\��*/
	Math::Point2DF vPos( m_pPhoto[m_SelectIdx]->GetPosition().x, 
						 m_pPhoto[m_SelectIdx]->GetPosition().y );
	
	Math::Rect2DF DstRect( vPos.x - fMARGIN_FRAME, 
						   vPos.y - fMARGIN_FRAME,
						   fMIN_PHOTO_SIZE.x + fMARGIN_FRAME * 2,
						   fMIN_PHOTO_SIZE.y + fMARGIN_FRAME * 2 );
						   
	CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_ADD );					   
	
	if( !IsDemo )
	{	
		CCommonObject::GetAppli()->GetRenderer()->FillRect( DstRect, CColor( 255, 255, 255, 128 ) );
	}
	
	CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_NORMAL );					   
	
	for( int i = 0;i < PhotoCount;++i )
	{
		Math::Rect2DF Dst( 20.0f + toF( i * fMARGIN_X ), fMIN_PHOTO_Y,
						   fMIN_PHOTO_SIZE.x, fMIN_PHOTO_SIZE.y );
						   
		m_pPhoto[i]->SetPosition( Math::Vector2D( Dst.x, Dst.y ) );						   
						   
		Math::Rect2DF Src( 0, 0, toF( m_pPhoto[i]->GetSize().x ), toF( m_pPhoto[i]->GetSize().y ) );
		
		CCommonObject::GetAppli()->GetRenderer()->DrawTexture( Dst, CColor( 255, 255, 255 ), Src, m_pPhoto[i]->GetTexture() ); 
		
		if( CCommonObject::GetMouse()->GetMouse()->GetStateL() == MOUSE_PUSH && 
		    Collision::Point_Rect( vMousePos, Dst ) && !IsDemo )
		{
			m_SelectIdx = i;
			CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_CHANGE );
		}
		
		
		
	}
	
}	

//=============================================================================
//�傫���ʐ^�̕\��
//=============================================================================
void CSceneResult::DrawBigPhoto()
{
	/*�g��p�̎ʐ^�T�C�Y*/
	const Math::Point2DF fMAX_PHOTO_SIZE( 480, 360 );
	
	
	/*�g��p�ʐ^�̈ʒu*/
	const Math::Point2DF MAX_PHOTO_POS( 285, 60 );
	
	Math::Rect2DF Dst( MAX_PHOTO_POS.x, MAX_PHOTO_POS.y,
					   fMAX_PHOTO_SIZE.x, fMAX_PHOTO_SIZE.y );
					   
	Math::Rect2DF Src( 0, 0, toF( m_pPhoto[m_SelectIdx]->GetSize().x ), toF( m_pPhoto[m_SelectIdx]->GetSize().y ) );
		
	/*�g��ʐ^�̕\��*/
	CCommonObject::GetAppli()->GetRenderer()->DrawTexture( Dst, CColor( 255, 255, 255 ), Src, m_pPhoto[m_SelectIdx]->GetTexture() );
}

//=============================================================================
//�ʐ^���̕\��
//=============================================================================
void CSceneResult::DrawPhotoInfo( )
{
	CPhoto *pPhoto = m_pPhoto[m_SelectIdx];
	
	int Score = 0;
	
	vector< string > vecTargetName;//�^�[�Q�b�g��
	vector< string > vecTargetScore;//�^�[�Q�b�g�X�R�A
	
	vecTargetName = pPhoto->GetVecTargetName();
	vecTargetScore = pPhoto->GetVecTargetScore();
	
	/*���X�g�̕������ݒ�*/
	m_pListNameFont->SetVecTextChat( vecTargetName );
	m_pListNumFont->SetVecTextChat( vecTargetScore );
	
	/*����������̕`��*/
	m_pListNumFont->DrawMultiLine();
	m_pListNameFont->DrawMultiLine();
	
	/*�����_�����O*/
	m_pListNumFont->Rendering();
	m_pListNameFont->Rendering();
	
	char Temp[20];
	
	sprintf_s( Temp, 20, "%d", pPhoto->GetScore() );
	
	string strTemp = Temp;
	
	m_pScoreFont->SetDrawString( strTemp );
	
	m_pScoreFont->Exec();
	m_pScoreFont->Rendering();
	
	GetMouseCursor()->SetVisibleFlag( true );
	GetMouseCursor()->SetAnimXID( 1 );
	
}

//=============================================================================
//�ʐ^�J�E���^�[�̑���
//=============================================================================
void CSceneResult::AddPhotoCount()
{
	static int count = 0;
	
	const int TIME_MAX = 60 * FILM_MAX;
	
	++count;
	
	if( count % 60 == 0 )
	{
		PhotoCount++;
	}
	
	if( PhotoCount > FILM_MAX )
	{
		PhotoCount = FILM_MAX;
	}
	
	m_SelectIdx = PhotoCount % FILM_MAX;

	if( count > TIME_MAX )
	{
		IsShowTargetExp = true;
		count = 0;
	}
	
	if( PhotoCount < FILM_MAX && count % 60 == 59 )
	{
		CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_SHUTTER );
	}
	
	
}

//=============================================================================
//�X�R�A�̃J�E���g�A�b�v
//=============================================================================
void CSceneResult::CountUpScore()
{
	
	const int TIME_MAX = 60 * 5;
	
	UpCount++;
	
	if( UpCount >= TIME_MAX )
	{
		UpCount = TIME_MAX;
		IsDemo = false;
	}
	
	CountScore = ::Interpolation::Add( 0, GetTotalScore(), TIME_MAX, UpCount );
	
	char Temp[20];
	
	if( CountScore > GetClearPoint() )
	{
		m_pTotalScFont->SetFontColor( CColor( 255, 0, 0, 255 ) );
	}
	
	else
	{
		m_pTotalScFont->SetFontColor( CColor( 255, 255, 255, 255 ) );
	}
	
	sprintf_s( Temp, 20, "%d", CountScore );
	
	m_pTotalScFont->SetDrawString( Temp );
	
}

//=============================================================================
//�^�[�Q�b�g���܂܂�Ă��邩�̕\��
//=============================================================================
void CSceneResult::ShowTargetResult()
{
	static int count = 0;
	
	++count;
	
	const int TIME_MAX = 60 * 2;
	
	if( count > TIME_MAX )
	{
		IsShowTargetExp = false;
		IsCountUp = true;
		count = 0;

	}
	
	//�^�[�Q�b�g���܂܂�Ă�����OK�ƕ\��
	if( GetTargetExistFlag() )
	{
		m_pTargetOKSpr->Exec();
		m_pTargetOKSpr->Rendering();
	}
	
	//�܂܂�ĂȂ�������NG�ƕ\��
	else
	{
		m_pTargetNGSpr->Exec();
		m_pTargetNGSpr->Rendering();
	}
	
}




