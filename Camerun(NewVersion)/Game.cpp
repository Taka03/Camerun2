//*============================================================================
//Game.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Game.h"
#include "LuaManager.h"
#include "LuaScript.h"
#include <fstream>

static char*        strTestScript = "print(\"Hello\")";
    
static LUAMANAGER*  luaManager;      // object to manage all scripts
static LUASCRIPT *luaScript;

//=============================================================================
//コンストラクタ
//=============================================================================
CGame::CGame() : m_pGameSceneMgr(NULL)
{
	
	::ShowCursor( FALSE );
	
}

//=============================================================================
//デストラクタ
//=============================================================================
CGame::~CGame()
{
	SAFE_DELETE( m_pGameSceneMgr );
	
}

//=============================================================================
//ゲーム開始
//=============================================================================
void CGame::Run()
{
	Renderer::IRender *pRender = CCommonObject::GetAppli()->GetRenderer();	
		
	//画面クリア
	pRender->Clear();
	
	//描画開始
	pRender->Begin();	
	
	if( CCommonObject::GetResMgr()->IsLoading() )
	{
		DrawNowLoading();
	}
	
	else
	{
		/*レンダリング*/
		CCommonObject::GetGameSceneMgr()->Rendering();
		
		/*ゲームの更新*/
		CCommonObject::GetGameSceneMgr()->UpDate();	
	}
	
	//描画終了
	pRender->End();	
	
}

//=============================================================================
//ロード画面の描画
//=============================================================================
void CGame::DrawNowLoading()
{
	string strNowLoading = "NowLoading";
	
	string strConma = "";
	
	static int count = 0;
	
	if( CCommonObject::GetAppli()->GetCore()->GetSyncCount() % 60 == 0 )
	{
		count++;
		
		if( count > 3 )
		{
			count = 0;
		}
	}
	
	for( int i = 0;i < count;++i )
	{
		strConma += ".";
	}
	
	strNowLoading += strConma;
	
	CCommonObject::GetAppli()->GetRenderer()->DrawTextLayer( 1, Math::Point2DI( 500, SCREEN_HEIGHT - 50 ), 
													  CColor( 255, 255, 255 ), strNowLoading.c_str() );
	
	
	
}



