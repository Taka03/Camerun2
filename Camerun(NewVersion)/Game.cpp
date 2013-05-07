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
//�R���X�g���N�^
//=============================================================================
CGame::CGame() : m_pGameSceneMgr(NULL)
{
	
	::ShowCursor( FALSE );
	
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CGame::~CGame()
{
	SAFE_DELETE( m_pGameSceneMgr );
	
}

//=============================================================================
//�Q�[���J�n
//=============================================================================
void CGame::Run()
{
	Renderer::IRender *pRender = CCommonObject::GetAppli()->GetRenderer();	
		
	//��ʃN���A
	pRender->Clear();
	
	//�`��J�n
	pRender->Begin();	
	
	if( CCommonObject::GetResMgr()->IsLoading() )
	{
		DrawNowLoading();
	}
	
	else
	{
		/*�����_�����O*/
		CCommonObject::GetGameSceneMgr()->Rendering();
		
		/*�Q�[���̍X�V*/
		CCommonObject::GetGameSceneMgr()->UpDate();	
	}
	
	//�`��I��
	pRender->End();	
	
}

//=============================================================================
//���[�h��ʂ̕`��
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



