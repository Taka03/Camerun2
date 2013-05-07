//*============================================================================
//field.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "field.h"
#include "SceneManager.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pName:�f�[�^��
//	vPos:�ʒu
//=============================================================================
CField::CField( const char *pName, Math::Vector3D vPos ) 
: m_pMapModel(NULL),
  m_pLine3D(NULL),
  CDraw3DObject( pName, vPos )
{
	//memset( m_pActorMap, NULL, SCREEN_MAX );
	
	for( int numActor = 0;numActor < SCREEN_MAX;++numActor )
	{
		m_pActorMap[numActor] = NULL;
	}
}


//=============================================================================
//�f�X�g���N�^
//=============================================================================
CField::~CField()
{
	for( int numActor = 0;numActor < SCREEN_MAX;++numActor )
	{
		SAFE_RELEASE( m_pActorMap[numActor] );
	}
	
	SAFE_RELEASE( m_pMapModel );
	
}

//=============================================================================
//������
//=============================================================================
void CField::Init()
{
	
}

//=============================================================================
//����
//=============================================================================
void CField::Exec()
{

}

//=============================================================================
//�����_�����O
//=============================================================================
void CField::Rendering(  )
{
	m_pActorMap[m_ActorIndex]->RenderingRequest();
}

//============================================================================
//�t�@�C���ǂݍ���
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//	pFileMgr:�t�@�C���Ǘ��p�f�o�C�X
//===========================================================================
void CField::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	printf("LOAD FIELD[%s]", m_strFileName.c_str() );
	
	pFileMgr->SetCurrentPath("Map");
	
	m_pMapModel = pRender->CreateMapModelFromFile( m_strFileName.c_str() );
	
	printf( "                 : -> %s\n", m_pMapModel->IsInvalid() ? "Failed" : "Succeeded" );
	
	//�A�N�^�[�̐���
	for( int i = 0;i < SCREEN_MAX;++i )
	{
		CreateActor( i, CCommonObject::GetSceneMgr( i )->GetSceneMgr() );
	}
	
}

//==============================================================================
//�A�N�^�[�̐���
//==============================================================================
//[input]
//	pSceneMgr:�V�[���Ǘ��f�o�C�X
//==============================================================================
void CField::CreateActor( int index, Scene::ISceneManager *pSceneMgr )
{
	if( m_pMapModel != NULL )
	{
		m_pActorMap[index] = pSceneMgr->CreateActor( m_pMapModel );
		
		#if defined( DEBUG ) | (_DEBUG )
			
//			m_pActorMap[index]->CreateCollisionDrawPrimitive( m_pLine );
			
		#endif
	}
	
}

//=============================================================================
//�A�N�^�[�C���f�b�N�X�̃Z�b�g
//=============================================================================
//[input]
//	index:�ݒ肷��C���f�b�N�X
//=============================================================================
void CField::SetActorIndex( int index )
{
	m_ActorIndex = index;
}

