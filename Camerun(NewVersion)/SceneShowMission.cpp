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
//�R���X�g���N�^
//=============================================================================
//[input]
//	strFileName:�t�@�C����
//=============================================================================
CSceneShowMission::CSceneShowMission( string strFileName ) 
:CSceneTemplate( strFileName )
{
	CCommonObject::GetAppli()->GetRenderer()->SetDrawTextFont( "MS�S�V�b�N", 50, 1 );
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneShowMission::~CSceneShowMission(void)
{
}

//=============================================================================
//�I�u�W�F�N�g�f�[�^�̏�����
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CSceneShowMission::InitObjectData( Uint32 dt )
{
	if( !CCommonObject::GetResMgr()->IsLoading() )
	{
		SetState( &CSceneTemplate::Init );
	}

}


//=============================================================================
//������
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
//=============================================================================
void CSceneShowMission::Init( Uint32 dt )
{
	printf("[CSceneShowMission]::Init\n");
	
	m_eSceneState = STATE_CONTINUE;
	
	SetState( &CSceneTemplate::Idle );
	
	time = 0;
	
}

//=============================================================================
//�ҋ@��
//=============================================================================
//[input]
//	dt:���Ԃ̑����Ԋu
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
//�����_�����O
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
	
	//�~�b�V������
	string strMissionName = vecStr[0];
	
	//�^�[�Q�b�g��
	string strTargetName = vecStr[1];
	
	//�N���A�|�C���g
	int ClearPoint = atoi( vecStr[2].c_str() );

	//�^�[�Q�b�g�̐ݒ�
	SetTarget( dynamic_cast<CEnemy *>( CCommonObject::GetResMgr()->FindObject( strTargetName.c_str() ) ) );
	
	//�N���A�|�C���g�̐ݒ�
	SetClearPoint( ClearPoint );
	
	SAFE_RELEASE( pResFile );
	
	CCommonObject::GetAppli()->GetRenderer()->DrawTextLayer
	( 1, Math::Point2DI( 0, 0 ), CColor( 255, 255, 255 ), strMissionName.c_str() );
	
	CCommonObject::GetAppli()->GetRenderer()->DrawTextLayer
	( 1, Math::Point2DI( 0, 50 ), CColor( 255, 255, 255 ), "%s���B��", GetTarget()->GetTypeName().c_str() );
	
	CCommonObject::GetAppli()->GetRenderer()->DrawTextLayer
	( 1, Math::Point2DI( 0, 100 ), CColor( 255, 255, 255 ), "�N���A�|�C���g:%d�|�C���g", ClearPoint );
	
}

