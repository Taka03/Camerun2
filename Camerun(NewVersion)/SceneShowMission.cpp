//*============================================================================
//SceneShowMission.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneShowMission.h"

//=============================================================================
//variable
//=============================================================================
namespace 
{
	int time = 0;
}

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	strFileName:ファイル名
//=============================================================================
CSceneShowMission::CSceneShowMission( string strFileName ) 
:CSceneTemplate( strFileName )
{
	CCommonObject::GetAppli()->GetRenderer()->SetDrawTextFont( "MSゴシック", 50, 1 );
}

//=============================================================================
//デストラクタ
//=============================================================================
CSceneShowMission::~CSceneShowMission(void)
{
}

//=============================================================================
//オブジェクトデータの初期化
//=============================================================================
//[input]
//	dt:時間の増加間隔
//=============================================================================
void CSceneShowMission::InitObjectData( Uint32 dt )
{
	if( !CCommonObject::GetResMgr()->IsLoading() )
	{
		SetState( &CSceneTemplate::Init );
	}

}


//=============================================================================
//初期化
//=============================================================================
//[input]
//	dt:時間の増加間隔
//=============================================================================
void CSceneShowMission::Init( Uint32 dt )
{
	printf("[CSceneShowMission]::Init\n");
	
	m_eSceneState = STATE_CONTINUE;
	
	SetState( &CSceneTemplate::Idle );
	
	time = 0;
	
}

//=============================================================================
//待機中
//=============================================================================
//[input]
//	dt:時間の増加間隔
//=============================================================================
void CSceneShowMission::Idle( Uint32 dt )
{
	static int count = 0;
	
	const int TIME_MAX = 60 * 5;
	
	Rendering();
	
	if( ++count > TIME_MAX )
	{
		SetState( &CSceneTemplate::End );
		
		count = 0;
	}
		
	time += dt;
}

//=============================================================================
//レンダリング
//=============================================================================
void CSceneShowMission::Rendering( )
{
	CFileLoader FileLoader;

	CCommonObject::GetAppli()->GetFileMgr()->SetCurrentPath("CSV");
	
	File::IResourceFile *pResFile = CCommonObject::GetAppli()->GetFileMgr()->FileOpen( "MissionTarget.csv" );
	
	FileLoader.Load( pResFile->GetNamePointer() );
	
	vector< string > vecStr;
	
	if( GetTutorialFlag() )
	{
		vecStr = FileLoader.SplitString( FileLoader.GetStrList().at( 0 ), "," );
	}
	
	else
	{	
		vecStr = FileLoader.SplitString( FileLoader.GetStrList().at( GetClearCount() ), "," );
	}
	
	//ミッション名
	string strMissionName = vecStr[0];
	
	//ターゲット名
	string strTargetName = vecStr[1];
	
	//クリアポイント
	int ClearPoint = atoi( vecStr[2].c_str() );

	//ターゲットの設定
	SetTarget( dynamic_cast<CEnemy *>( CCommonObject::GetResMgr()->FindObject( strTargetName.c_str() ) ) );
	
	//クリアポイントの設定
	SetClearPoint( ClearPoint );
	
	SAFE_RELEASE( pResFile );
	
	CCommonObject::GetAppli()->GetRenderer()->DrawTextLayer
	( 1, Math::Point2DI( 0, 0 ), CColor( 255, 255, 255 ), strMissionName.c_str() );
	
	CCommonObject::GetAppli()->GetRenderer()->DrawTextLayer
	( 1, Math::Point2DI( 0, 50 ), CColor( 255, 255, 255 ), "%sを撮れ", GetTarget()->GetTypeName().c_str() );
	
	CCommonObject::GetAppli()->GetRenderer()->DrawTextLayer
	( 1, Math::Point2DI( 0, 100 ), CColor( 255, 255, 255 ), "クリアポイント:%dポイント", ClearPoint );
	
}

