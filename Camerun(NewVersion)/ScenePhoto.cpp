//*============================================================================
//ScenePhoto.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "ScenePhoto.h"

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	strFileName:ファイル名
//=============================================================================
CScenePhoto::CScenePhoto( string strFileName ) 
:m_pPhoto(NULL),
 m_pCheckMenu(NULL),
 CSceneTemplate( strFileName )
{
	m_IsShowMenu = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
CScenePhoto::~CScenePhoto(void)
{

}

//=============================================================================
//オブジェクトデータの初期化
//=============================================================================
//[input]
//	dt:時間の増加間隔
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
//初期化
//=============================================================================
//[input]
//	dt:時間の増加間隔
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
//待機中
//=============================================================================
//[input]
//	dt:時間の増加間隔
//=============================================================================
void CScenePhoto::Idle( Uint32 dt )
{
	/*拡大用の写真サイズ*/
	const Math::Point2DF fMAX_PHOTO_SIZE( 480, 360 );
	
	CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_NORMAL );
	
	if( m_pPhoto != NULL )
	{
		Math::Rect2DF Dst( m_pPhoto->GetPosition().x, m_pPhoto->GetPosition().y,
						   fMAX_PHOTO_SIZE.x, fMAX_PHOTO_SIZE.y );
		
		m_pPhoto->SetDstRect( Dst );
		
		/*描画*/
		m_pPhoto->Draw();	
		
		/*レンダリング*/
		Rendering();
	}
	
	CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
	
	/*指アイコンの処理*/
	FingIcoExec();
	
	if( GetTutorialFlag() )
	{
		GetWindowSpr()->Exec();
		
		GetWindowSpr()->Rendering();
	}
	
	/*メニューの表示*/
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
//レンダリング
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
// シーンの移動
//=============================================================================
//[input]
//	eScene:移動するシーン
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
//写真確認処理
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
/*ここから写真確認の個別処理*/
//=================================================================================================

//=============================================================================
// 写真を残す
//=============================================================================
void CScenePhoto::RegistPhoto()
{
	SetPhotoSaveFlag( true );
}

//=============================================================================
// 写真を破棄する
//=============================================================================
void CScenePhoto::RemovePhoto()
{
	CCommonObject::GetResMgr()->RemoveObject( m_pPhoto );
}

//=================================================================================================
/*ここまで写真確認の個別処理*/
//=================================================================================================

//=================================================================================================
/*ここからスクリプトの個別処理*/
//=================================================================================================

//=============================================================================
// 写真保存スクリプト
//=============================================================================
void CScenePhoto::PhotoSaveScript()
{
	const int REGIST_PHOTO = 0;//写真保存
	
	m_IsShowMenu = true;
	
	/*右方向の矢印表示*/
	SetFingState( CSceneBase::FING_RIGHT );
	
	GetFingerSpr()->SetInitPosition( m_pCheckMenu->GetPosition() + Math::Vector2D( -10.0f, 60.0f ) );
	
	if( m_pCheckMenu->GetHitStringFlag() )
	{
		if( m_pCheckMenu->GetSelectIndex() == REGIST_PHOTO )
		{	
			//絶対存在しない敵をターゲットにする
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
/*ここまでスクリプトの個別処理*/
//=================================================================================================

//=============================================================================
// メニューのレンダリング
//=============================================================================
void CScenePhoto::RenderMenu( )
{
	m_pCheckMenu->Exec();
	
	m_pCheckMenu->Rendering();
	
}






