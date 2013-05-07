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
//コンストラクタ
//=============================================================================
//[input]
//	strFileName:ファイル名
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
//デストラクタ
//=============================================================================
CSceneNewComponent::~CSceneNewComponent(void)
{

}

//=============================================================================
//オブジェクトデータの初期化
//=============================================================================
//[input]
//	dt:時間の増加間隔
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
//初期化
//=============================================================================
//[input]
//	dt:時間の増加間隔
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
//待機中
//=============================================================================
//[input]
//	dt:時間の増加間隔
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
		////クリアカウントの制限
		//if( GetClearCount() > MISSION_MAX )
		//{
		//	SetClearCount( MISSION_MAX );
		//}
	}
		
		

		
	time += dt;
}

//=============================================================================
//レンダリング
//=============================================================================
void CSceneNewComponent::Rendering( )
{
	m_pBGSpr->Exec();
	m_pBGSpr->Rendering();
	
	if( GetClearCount() == 0 )
	{
		//描画文字列の設定
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
		/*得点がクリアポイントを超えたらゲームクリア*/
		if( GetTotalScore() > GetClearPoint() && GetTargetExistFlag() )
		{
			//描画文字列の設定
			m_pClearFont->SetDrawString( strList.at( MessageNo ) );
			
			m_pClearSpr->Exec();
			
			m_pClearSpr->Rendering();
			
			if( !IsPlaySE )
			{	
				CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_CLEAR );
				
				IsPlaySE = true;
			}
			
			//クリアカウントの増加
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
	
	//メッセージの描画
	DrawMessage();
	
	static int count = 0;
	
	++count;
	
	if( count > 0 && count <= 30 )
	{
		CCommonObject::GetAppli()->GetRenderer()->DrawTextLayer( 2, Math::Point2DI( 20, 540 ), CColor( 255, 255, 255 ),
												  "左クリックで終了" );
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
//メッセージの描画
//=============================================================================
void CSceneNewComponent::DrawMessage()
{
	/*描画文字列*/
	string strDraw = m_pClearFont->GetDrawString();
	
	string::size_type index = strDraw.find("Br");
	
	/*Br文字列が見つかったら、文字列を分解する*/
	if( index != string::npos )
	{
		vector<string> strRet =  CFileLoader::SplitString( strDraw, "Br" );
		
		m_pClearFont->DrawMultiLine( strRet );
		
	}
		
	/*通常通り描画*/
	else
	{
		m_pClearFont->Exec();
	}
	
	vector< string > strTemp;
	
	strTemp.clear();
	
	//クリアポイントを超えていない
	if( GetClearCount() != 0 )
	{
		if( GetTotalScore() < GetClearPoint() )
		{
			strTemp.push_back( strList.at( 6 ) );
		}
		
		//ターゲットが写っていない
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




