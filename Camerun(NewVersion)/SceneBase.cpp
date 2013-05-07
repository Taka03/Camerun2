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
//�R���X�g���N�^
//=============================================================================
CSceneBase::CSceneBase()
{
	
	
}	

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	strFileName:�t�@�C����
//===========================================================================
CSceneBase::CSceneBase( string strFileName ) 
{
	///*���X�g������*/
	//m_Draw2DList.clear();
	//
	//m_DataNameList.clear();
	//
	///*���\�[�X�̓ǂݍ���*/
	LoadResource( strFileName );
	
	
}



//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneBase::~CSceneBase()
{
	
	
}

//=============================================================================
//������
//=============================================================================
void CSceneBase::Init()
{
	m_FilmCount = 0;
	m_TotalScore = 0;
	
	m_IsTargetExist = false;
	
}

//=============================================================================
//���\�[�X�ǂݍ���
//=============================================================================
//[input]
//	strFileName:�t�@�C����
//===========================================================================
void CSceneBase::LoadResource( string strFileName )
{
	CFileLoader FileLoader;
	
	File::IResourceFile *pResFile = NULL;
	
	CCommonObject::GetAppli()->GetFileMgr()->SetCurrentPath("CSV");
	
	pResFile = CCommonObject::GetAppli()->GetFileMgr()->FileOpen( strFileName.c_str() );
	
	string FileName = pResFile->GetNamePointer();

	/*�ݒ�t�@�C���̓ǂݍ���*/
	FileLoader.Load( FileName );
	
	SAFE_RELEASE( pResFile );
	
	vector<string> list = FileLoader.GetStrList();
	vector<string>::iterator it = list.begin();
	
	/*���\�[�X�̓ǂݍ���*/
	for( it = list.begin();it != list.end();++it )
	{	
		
		/*�`���ɍ��킹�āA�ǂݍ��ރf�[�^��ύX����*/
		vector<string> strSource = FileLoader.SplitString( *it, "," );
		
		string strFileName = strSource[0];//�t�@�C����
		string strDataName = strSource[1];//�f�[�^��
		string strTypeName = strSource[2];//�^�C�v��
		
		/*���̏ꍇ*/
		if(  strTypeName =="BGM" || strTypeName == "SOUND" )
		{
			CCommonObject::GetResMgr()->Push( new CFileData( strFileName.c_str(), strDataName.c_str(),
															 strTypeName.c_str() ) );
		}
		
		/*�G�I�u�W�F�N�g�̏ꍇ*/
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
		
		/*2D�I�u�W�F�N�g(�X�v���C�g)�̏ꍇ*/
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
			
			/*���������I�u�W�F�N�g�Ɋւ��ẮA�ǉ����Ȃ�*/
			if( strList.m_DataName.compare( "Cloud" ) != 0 )
			{	
				m_DataNameList.push_back( strList );
			}
			
		} 
		
		/*���̑��̃I�u�W�F�N�g(3D)�̏ꍇ*/
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
//2D�I�u�W�F�N�g�̃��X�g�ǉ�
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
//2D�I�u�W�F�N�g�̏���
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
//2D�I�u�W�F�N�g�̃����_�����O
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
//�w�A�C�R���̏�ԏ���
//=============================================================================
void CSceneBase::FingIcoExec()
{
	static Math::Vector2D vMovePos( 0, 0 );//�ړ��ʒu
	
	const int TIME_MAX = 30;
	
	static int count = 0;
	
	const float fMOVE = 5.0f;
	
	count++;
	
	switch( GetFingState() )
	{
		
		/*�����\���ɂ���*/
		case FING_NONE:
		{
			GetFingerSpr()->SetVisibleFlag( false );
			break;
		}
		
		/*�����*/
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
		
		/*������*/
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
		
		/*������*/
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
		
		/*�E����*/
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
//�}�E�X�A�C�R���̃����_�����O
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

















