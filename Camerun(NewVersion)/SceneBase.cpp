//*============================================================================
//SceneBase.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "SceneBase.h"

#include <fstream>

//=============================================================================
//variable
//=============================================================================
Uint32 CSceneBase::m_FilmCount = 0;
int CSceneBase::m_TotalScore = 0;
int CSceneBase::m_ClearCount = 0;
int CSceneBase::m_ClearPoint = 0;
int CSceneBase::m_HiScore = 0;

float CSceneBase::m_fTargetDis = 0.0f;
Math::Vector3D CSceneBase::m_vTargetPos = Math::Vector3D( 0, 0, 0 );

bool CSceneBase::m_IsTutorial = false;
bool CSceneBase::m_IsFirstGame = false;
bool CSceneBase::m_IsTargetExist = false;
bool CSceneBase::m_IsSavePhoto = false;
CExpWindow *CSceneBase::m_pWindowSpr = NULL;
CSprite *CSceneBase::m_pFingIcoSpr = NULL;
CSprite *CSceneBase::m_pCursorSpr = NULL;
CSceneBase::eFingState CSceneBase::m_eFingState = FING_NONE;

CBGM *CSceneBase::m_pBGM = NULL;
CEnemy *CSceneBase::m_pTarget = NULL;

CCamButton *CSceneBase::m_pCamBtnSpr = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CSceneBase::CSceneBase()
{
	
	
}	

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	strFileName:ファイル名
//===========================================================================
CSceneBase::CSceneBase( string strFileName ) 
{
	///*リスト初期化*/
	//m_Draw2DList.clear();
	//
	//m_DataNameList.clear();
	//
	///*リソースの読み込み*/
	LoadResource( strFileName );
	
	
}



//=============================================================================
//デストラクタ
//=============================================================================
CSceneBase::~CSceneBase()
{
	
	
}

//=============================================================================
//初期化
//=============================================================================
void CSceneBase::Init()
{
	m_FilmCount = 0;
	m_TotalScore = 0;
	
	m_IsTargetExist = false;
	
}

//=============================================================================
//リソース読み込み
//=============================================================================
//[input]
//	strFileName:ファイル名
//===========================================================================
void CSceneBase::LoadResource( string strFileName )
{
	CFileLoader FileLoader;
	
	File::IResourceFile *pResFile = NULL;
	
	CCommonObject::GetAppli()->GetFileMgr()->SetCurrentPath("CSV");
	
	pResFile = CCommonObject::GetAppli()->GetFileMgr()->FileOpen( strFileName.c_str() );
	
	string FileName = pResFile->GetNamePointer();

	/*設定ファイルの読み込み*/
	FileLoader.Load( FileName );
	
	SAFE_RELEASE( pResFile );
	
	vector<string> list = FileLoader.GetStrList();
	vector<string>::iterator it = list.begin();
	
	/*リソースの読み込み*/
	for( it = list.begin();it != list.end();++it )
	{	
		
		/*形式に合わせて、読み込むデータを変更する*/
		vector<string> strSource = FileLoader.SplitString( *it, "," );
		
		string strFileName = strSource[0];//ファイル名
		string strDataName = strSource[1];//データ名
		string strTypeName = strSource[2];//タイプ名
		
		/*音の場合*/
		if(  strTypeName =="BGM" || strTypeName == "SOUND" )
		{
			CCommonObject::GetResMgr()->Push( new CFileData( strFileName.c_str(), strDataName.c_str(),
															 strTypeName.c_str() ) );
		}
		
		/*敵オブジェクトの場合*/
		else if( strTypeName == "AMEUS" || strTypeName == "MANTA" ||
				 strTypeName == "BIRD"  || strTypeName == "MOUSE" ||
				 strTypeName == "RABBIT" || strTypeName == "LIZARD" ||
				 strTypeName == "DOG" || strTypeName == "CAR" ||
				 strTypeName == "TRAIN" || strTypeName == "FOUNT" ||
				 strTypeName == "SKY")
		{
			Math::Vector3D vPos( toF( atof( strSource[3].c_str() ) ), 
								 toF( atof( strSource[4].c_str() ) ),
								 toF( atof( strSource[5].c_str() ) ) );
			
			string strResFileName = strSource[6];
			
			CCommonObject::GetAppli()->GetFileMgr()->SetCurrentPath( "CSV" );
			
			pResFile = CCommonObject::GetAppli()->GetFileMgr()->FileOpen( strResFileName.c_str() );
			
			CCommonObject::GetResMgr()->Push( new CFileData( strFileName.c_str(), 
															 strDataName.c_str(), 
															 strTypeName.c_str(), vPos, pResFile ) );
			
			
		}
		
		/*2Dオブジェクト(スプライト)の場合*/
		else if( strTypeName == "SPRITE" || strTypeName == "PHOTO" 
				|| strTypeName == "Font" || strTypeName == "CAMBUTTON" 
				|| strTypeName == "Menu" )
		{
			Math::Vector3D vPos( toF( atof( strSource[3].c_str() ) ), 
								 toF( atof( strSource[4].c_str() ) ),
								 toF( atof( strSource[5].c_str() ) ) );
								 
			CGameObject *pGameObj = NULL;								 
			
			CCommonObject::GetResMgr()->Push( new CFileData( strFileName.c_str(), strDataName.c_str(), 
															 strTypeName.c_str(), vPos, pGameObj ) );
			
			StringList strList;
			
			strList.m_DataName = strDataName;
			
			/*すぐ消すオブジェクトに関しては、追加しない*/
			if( strList.m_DataName.compare( "Cloud" ) != 0 )
			{	
				m_DataNameList.push_back( strList );
			}
			
		} 
		
		/*その他のオブジェクト(3D)の場合*/
		else
		{
			CGameObject *pGameObj = NULL;								 
			
			Math::Vector3D vPos( toF( atof( strSource[3].c_str() ) ), 
								 toF( atof( strSource[4].c_str() ) ),
								 toF( atof( strSource[5].c_str() ) ) );
			
			CCommonObject::GetResMgr()->Push( new CFileData( strFileName.c_str(), strDataName.c_str(),
															 strTypeName.c_str(), vPos, pGameObj ) );
			
		}
			
	}
	
}

//=============================================================================
//2Dオブジェクトのリスト追加
//=============================================================================
void CSceneBase::Push2DObject()
{
	for( list<StringList>::iterator it = m_DataNameList.begin();it != m_DataNameList.end();++it )
	{
		m_Draw2DList.push_back( dynamic_cast<CDraw2DObject *>
								( CCommonObject::GetResMgr()->FindObject( it->m_DataName.c_str() ) ) );
	}
	
}

//=============================================================================
//2Dオブジェクトの処理
//=============================================================================
void CSceneBase::Exec2DList()
{
	for( list<CDraw2DObject *>::iterator it = m_Draw2DList.begin();it != m_Draw2DList.end();++it )
	{
		CDraw2DObject *obj = *it;	
		
		obj->Exec();
	}
}

//=============================================================================
//2Dオブジェクトのレンダリング
//=============================================================================
void CSceneBase::Rendering2DList()
{
	for( list<CDraw2DObject *>::iterator it = m_Draw2DList.begin();it != m_Draw2DList.end();++it )
	{
		CDraw2DObject *obj = *it;	
		
		CCommonObject::GetAppli()->GetRenderer()->SetDrawType( DRAW_TYPE_BLEND );
		
		obj->Rendering();
	}
}

//=============================================================================
//指アイコンの状態処理
//=============================================================================
void CSceneBase::FingIcoExec()
{
	static Math::Vector2D vMovePos( 0, 0 );//移動位置
	
	const int TIME_MAX = 30;
	
	static int count = 0;
	
	const float fMOVE = 5.0f;
	
	count++;
	
	switch( GetFingState() )
	{
		
		/*矢印を非表示にする*/
		case FING_NONE:
		{
			GetFingerSpr()->SetVisibleFlag( false );
			break;
		}
		
		/*上方向*/
		case FING_UP:
		{
			GetFingerSpr()->SetXRotate( DEG_TO_ANGLE( -90 ) );
			GetFingerSpr()->SetVisibleFlag( true );
			
			vMovePos.x = GetFingerSpr()->GetInitPos().x;
			
			vMovePos.y = ::Interpolation::Add( GetFingerSpr()->GetInitPos().y,
											   GetFingerSpr()->GetInitPos().y - fMOVE,
											   TIME_MAX,
											   count % TIME_MAX );
											   
				
											   
			
			break;
		}
		
		/*下方向*/
		case FING_DOWN:
		{
			GetFingerSpr()->SetXRotate( DEG_TO_ANGLE( 90 ) );
			
			GetFingerSpr()->SetVisibleFlag( true );
			
		
			vMovePos.x = GetFingerSpr()->GetInitPos().x;
			
			vMovePos.y = ::Interpolation::Add( GetFingerSpr()->GetInitPos().y,
											   GetFingerSpr()->GetInitPos().y + fMOVE,
											   TIME_MAX,
											   count % TIME_MAX );
			
			break;
		}
		
		/*左方向*/
		case FING_LEFT:
		{
			GetFingerSpr()->SetXRotate( DEG_TO_ANGLE( 180 ) );
			GetFingerSpr()->SetVisibleFlag( true );
			
			
			vMovePos.x = ::Interpolation::Sub( GetFingerSpr()->GetInitPos().x,
											   GetFingerSpr()->GetInitPos().x - fMOVE,
											   TIME_MAX,
											   count % TIME_MAX );
											   
			vMovePos.y = GetFingerSpr()->GetInitPos().y;
			
			
			break;
		}
		
		/*右方向*/
		case FING_RIGHT:
		{
			GetFingerSpr()->SetVisibleFlag( true );
			
			
			GetFingerSpr()->SetXRotate( DEG_TO_ANGLE( 0 ) );
			
			vMovePos.x = ::Interpolation::Add( GetFingerSpr()->GetInitPos().x + fMOVE,
											   GetFingerSpr()->GetInitPos().x ,
											   TIME_MAX,
											   count );
											   
			vMovePos.y = GetFingerSpr()->GetInitPos().y;
											   
											   
			if( count > TIME_MAX )
			{
				count = 0;
			}
			
			
			break;
		}
		
	}
	
	GetFingerSpr()->SetPosition( vMovePos );
	
	
	GetFingerSpr()->Exec();
	
	GetFingerSpr()->Rendering();
}

//=============================================================================
//マウスアイコンのレンダリング
//=============================================================================
void CSceneBase::RenderMouseIco()
{
	if( GetMouseCursor() != NULL )
	{
		Math::Vector2D vMousePos( CCommonObject::GetMouse()->GetMousePos() );
								  
		
		Math::Vector2D vCenterPos( GetMouseCursor()->GetSize().x / 2, GetMouseCursor()->GetSize().y / 2 );
		
		GetMouseCursor()->SetPosition( vMousePos - vCenterPos );
		
		GetMouseCursor()->Exec();
		
		GetMouseCursor()->Rendering();
	}
	
}

















