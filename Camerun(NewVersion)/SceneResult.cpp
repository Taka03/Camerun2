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
	Math::Vector2D vMousePos;//マウスの位置
	int PhotoCount = 0;//写真カウンター
	bool IsDemo = true;//デモ中かどうか
	bool IsCountUp = false;//カウントアップ中か
	bool IsShowTargetExp = false;//ターゲットが表示されているか
	int CountScore = 0;//スコアのカウントアップ用
	int UpCount = 0;//汎用カウンター
};

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	strFileName:ファイル名
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
//デストラクタ
//=============================================================================
CSceneResult::~CSceneResult(void)
{

}

//=============================================================================
//オブジェクトデータの初期化
//=============================================================================
//[input]
//	dt:時間の増加間隔
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
//初期化
//=============================================================================
//[input]
//	dt:時間の増加間隔
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
//待機中
//=============================================================================
//[input]
//	dt:時間の増加間隔
//=============================================================================
void CSceneResult::Idle( Uint32 dt )
{
	///*得点がクリアポイントを超えたらゲームクリア*/
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
	
	//スコアのカウントアップ
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

	/*レンダリング*/
	Rendering();
	
	//BGMの再生
	GetBGM()->Exec();
	
	//ハイスコアの更新
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
				/*次回写真撮影できるように削除*/
				CCommonObject::GetResMgr()->RemoveObject( m_pPhoto[i] );
			}
			
			CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_CHANGE );
			
			//BGMの再生
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
//レンダリング
//=============================================================================
void CSceneResult::Rendering( )
{
	/*背景の表示*/
	m_pBGSpr->Rendering();
	
	//デモ中のときは写真を増加
	if( IsDemo )
	{
		AddPhotoCount();
	}
	
	/*大きい写真の表示*/
	DrawBigPhoto();
	
	/*小さい写真の表示*/
	DrawMinPhoto();
	
	DrawPhotoInfo();
	
	/*スコアのレンダリング*/
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
//小さい写真の表示
//=============================================================================
void CSceneResult::DrawMinPhoto()
{
	/*サムネイル用の写真サイズ*/
	const Math::Point2DF fMIN_PHOTO_SIZE( 120, 90 );
	
	const float fMIN_PHOTO_Y = 495;//小さい写真のY位置
	const float fMARGIN_X = 142;//写真のXマージン
	
	const float fMARGIN_FRAME = 10.0f;
	
	/*写真枠の表示*/
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
//大きい写真の表示
//=============================================================================
void CSceneResult::DrawBigPhoto()
{
	/*拡大用の写真サイズ*/
	const Math::Point2DF fMAX_PHOTO_SIZE( 480, 360 );
	
	
	/*拡大用写真の位置*/
	const Math::Point2DF MAX_PHOTO_POS( 285, 60 );
	
	Math::Rect2DF Dst( MAX_PHOTO_POS.x, MAX_PHOTO_POS.y,
					   fMAX_PHOTO_SIZE.x, fMAX_PHOTO_SIZE.y );
					   
	Math::Rect2DF Src( 0, 0, toF( m_pPhoto[m_SelectIdx]->GetSize().x ), toF( m_pPhoto[m_SelectIdx]->GetSize().y ) );
		
	/*拡大写真の表示*/
	CCommonObject::GetAppli()->GetRenderer()->DrawTexture( Dst, CColor( 255, 255, 255 ), Src, m_pPhoto[m_SelectIdx]->GetTexture() );
}

//=============================================================================
//写真情報の表示
//=============================================================================
void CSceneResult::DrawPhotoInfo( )
{
	CPhoto *pPhoto = m_pPhoto[m_SelectIdx];
	
	int Score = 0;
	
	vector< string > vecTargetName;//ターゲット名
	vector< string > vecTargetScore;//ターゲットスコア
	
	vecTargetName = pPhoto->GetVecTargetName();
	vecTargetScore = pPhoto->GetVecTargetScore();
	
	/*リストの文字列を設定*/
	m_pListNameFont->SetVecTextChat( vecTargetName );
	m_pListNumFont->SetVecTextChat( vecTargetScore );
	
	/*複数文字列の描画*/
	m_pListNumFont->DrawMultiLine();
	m_pListNameFont->DrawMultiLine();
	
	/*レンダリング*/
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
//写真カウンターの増加
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
//スコアのカウントアップ
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
//ターゲットが含まれているかの表示
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
	
	//ターゲットが含まれていたらOKと表示
	if( GetTargetExistFlag() )
	{
		m_pTargetOKSpr->Exec();
		m_pTargetOKSpr->Rendering();
	}
	
	//含まれてなかったらNGと表示
	else
	{
		m_pTargetNGSpr->Exec();
		m_pTargetNGSpr->Rendering();
	}
	
}




