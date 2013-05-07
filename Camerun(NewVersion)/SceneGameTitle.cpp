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
//コンストラクタ
//=============================================================================
//[input]
//	strFileName:ファイル名
//=============================================================================
CSceneGameTitle::CSceneGameTitle( string strFileName ) 
: m_pTitleBGM(NULL),
 m_eSelectScene(SELECT_TUTORIAL),
 CSceneTemplate( strFileName )
{
}


//=============================================================================
//デストラクタ
//=============================================================================
CSceneGameTitle::~CSceneGameTitle()
{

}

//=============================================================================
//オブジェクトデータの初期化
//=============================================================================
//[input]
//	dt:時間の増加間隔
//=============================================================================
void CSceneGameTitle::InitObjectData( Uint32 dt )
{
	if( !CCommonObject::GetResMgr()->IsLoading() )
	{
		/*2Dオブジェクトの追加*/
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
		
		//チュートリアル説明文の設定
		GetWindowSpr()->SetTutorialExp( CCommonObject::GetAppli()->GetFileMgr() );
		
		//サウンドオブジェクトの追加
		CCommonObject::GetSoundMgr()->PushResource( CCommonObject::GetResMgr() );
		
		SetState( &CSceneTemplate::Init );
	}

}


//=============================================================================
//初期化
//=============================================================================
//[input]
//	dt:時間の増加間隔
//=============================================================================
void CSceneGameTitle::Init( Uint32 dt )
{
	m_eSceneState = STATE_CONTINUE;
	
	printf("[GameTitle]::Init\n");
	
	GetMouseCursor()->SetDivNumX( 3 );
	
	GetMouseCursor()->SetAnimXID( 1 );
	
	GetFingerSpr()->SetVisibleFlag( false );
	
	//初期プレイ時は、強制的にチュートリアルモードに移行
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
	
	//タイトルメニューの設定
	SetTitleMenu();
	
	IsFade = false;
	
	SetBGM( m_pTitleBGM );
	
	SetState( &CSceneTemplate::Idle );
	
	
}

//=============================================================================
//待機中
//=============================================================================
//[input]
//	dt:時間の増加間隔
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
	
	//BGMの再生
	GetBGM()->Play( Tbl, 2 );
	
	//レンダリング
	Rendering();
	
	time += dt;
	
	
}

//=============================================================================
//レンダリング
//=============================================================================
void CSceneGameTitle::Rendering()
{
	
	/*2Dリストの処理*/
	//Exec2DList();

	/*2Dリストのレンダリング*/
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
	
	
	//マウスアイコンのレンダリング
	RenderMouseIco();
	
	if( m_pTitleMenu->GetHitStringFlag() && !IsFade )
	{
		/*シーンの移動*/
		MoveScene( ( eSelectScene )( m_pTitleMenu->GetSelectIndex() ) );
	}
	
	
	
	

}

//=============================================================================
//タイトルメニューの設定
//=============================================================================
void CSceneGameTitle::SetTitleMenu()
{
	CMenu::StringList strList;
	
	const int TUTORIAL_POS = 1;
	
	//メニューの表示位置
	Math::Point2DF Pos[] =
	{
		Math::Point2DF( 599, 262 ),
		Math::Point2DF( 594, 317 ),
		Math::Point2DF( 593, 375 ),
	};
	
	/*メニュー項目名*/
	string strMenu[] =
	{
		"r q _ s",//スタート
		"a ( _ s l 3 .",//チュートリアル
		"d ( 4 l ) 4",//シュウリョウ
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
		
		/*描画文字列リストに追加*/
		/*初期プレイ時は、チュートリアルを表示させない*/
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
// シーンの移動
//=============================================================================
//[input]
//	eScene:移動するシーン
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



