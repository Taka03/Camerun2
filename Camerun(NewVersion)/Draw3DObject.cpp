//*===========================================================================
//Draw3DObject.cpp
//*===========================================================================

//============================================================================
//include
//============================================================================
#include "Draw3DObject.h"
#include <list>

//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	pName:�f�[�^��
//	vPos:�ʒu
//===========================================================================
CDraw3DObject::CDraw3DObject( const char *pName, Math::Vector3D vPos ) 
: CDrawObject( pName ),
  m_vPos( vPos ),
  m_vInitPos( vPos ),
  m_Rot( 0, 0, 0 ),
  m_InitRot( m_Rot ),
  m_vScale( 1.0f, 1.0f, 1.0f ),
  m_vInitScale( m_vScale ),
  m_ActorIndex( SCREEN_MAIN )
{
	
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CDraw3DObject::~CDraw3DObject(void)
{
}

//=============================================================================
//������
//=============================================================================
void CDraw3DObject::Init()
{
	m_vPos = m_vInitPos;
	m_Rot = m_InitRot;
	m_vScale = m_vInitScale;
}


//=============================================================================
//����
//=============================================================================
void CDraw3DObject::Exec()
{
}

//=============================================================================
//�ړ�����
//=============================================================================
void CDraw3DObject::MoveExec()
{
}



//=============================================================================
//�����_�����O
//=============================================================================
void CDraw3DObject::Rendering( )
{
	
}

//=============================================================================
//�t�@�C���ǂݍ���
//=============================================================================
//[input]
//	pRender:�����_�����O�p�f�o�C�X
//	pFileMgr:�t�@�C���Ǘ��f�o�C�X
//=============================================================================
void CDraw3DObject::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	
}

//=============================================================================
//�A�N�^�[�̐���
//=============================================================================
//[input]
//	pSceneMgr:�V�[���Ǘ��p�f�o�C�X
//=============================================================================
void CDraw3DObject::CreateActor( int index, Scene::ISceneManager *pSceneMgr )
{
}


//=============================================================================
//�����蔻��̃`�F�b�N
//=============================================================================
//[input/output]
//	ppChara:���肷��L����
//[return]
//	�����������ǂ���
//=============================================================================
bool CDraw3DObject::HitCheck( CDraw3DObject **ppChara )
{
	//list<ListData>::iterator i;
	//
	//for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	//{
	//	CDraw3DObject *obj = dynamic_cast<CDraw3DObject *>( i->gameobj );
	//	
	//	if( obj->GetObjectType() == OBJ_ENEMY && this->HitCheck( &obj ) )
	//	{
	//		*ppChara = obj;
	//		return true;
	//	}
	//		
	//}
	
	return false;
}

//=============================================================================
//�����蔻��̃`�F�b�N
//=============================================================================
//[input]
//	vRay:����p�̃��C
//[return]
//	�����������ǂ���
//=============================================================================
bool CDraw3DObject::HitCheck( Collision::CLine3D &vRay )
{
	//list<ListData>::iterator i;
	//
	//for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	//{
	//	CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
	//	
	//	if( pChara->HitCheck( vRay ) )
	//	{
	//		return true;
	//	}
	//}
	
	return false;
}

//=============================================================================
//�����蔻��̃`�F�b�N
//=============================================================================
//[input]
//	vRay:����p�̃��C
//	ppHitObj:���������I�u�W�F�N�g�̎擾
//[output]
//	obj:�Փ˂����I�u�W�F�N�g	
//[return]
//	�����������ǂ���
//=============================================================================
bool CDraw3DObject::HitCheck( Selene::Collision::CLine3D &vRay, CDraw3DObject **ppHitObj )
{
	//list<ListData>::iterator i;
	//
	//for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	//{
	//	CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
	//	
	//	if( pChara->HitCheck( vRay ) )
	//	{
	//		*ppHitObj = pChara;
	//		return true;
	//	}
	//}
	
	return false;
}


//=============================================================================
//�����蔻��̃`�F�b�N
//=============================================================================
//[input]
//	vRay:����p�̃��C
//	Out:�Փ˔���̌���
//[return]
//	�����������ǂ���
//=============================================================================
bool CDraw3DObject::HitCheck( Collision::CLine3D &vRay, Renderer::SCollisionResult &Out )
{
	//list<ListData>::iterator i;
	//
	//for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	//{
	//	CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
	//	
	//	if( pChara->HitCheck( vRay, Out ) )
	//	{
	//		return true;
	//	}
	//}
	
	return false;
}

//=============================================================================
//�����蔻��̃`�F�b�N
//=============================================================================
//[input]
//	vRay:����p�̃��C
//	Out:�Փ˔���̌���
//[output]
//	ppHitObj:���������I�u�W�F�N�g
//[return]
//	�����������ǂ���
//=============================================================================
bool CDraw3DObject::HitCheck( Collision::CLine3D &vRay, Renderer::SCollisionResult &Out, CDraw3DObject **ppHitObj )
{
	//list<ListData>::iterator i;
	//
	//for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	//{
	//	CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
	//	
	//	if( pChara->HitCheck( vRay, Out ) )
	//	{
	//		*ppHitObj = pChara;
	//		
	//		return true;
	//	}
	//}
	
	return false;
}

//=============================================================================
//�A�N�^�[�C���f�b�N�X�̃Z�b�g
//=============================================================================
//[input]
//	index:�ݒ肷��C���f�b�N�X
//=============================================================================
void CDraw3DObject::SetActorIndex( int index )
{
	m_ActorIndex = index;
	//list<ListData>::iterator i;
	//
	//for( i = m_ObjectList.begin();i != m_ObjectList.end();++i )
	//{
	//	CDraw3DObject *pChara = dynamic_cast<CDraw3DObject *>( i->gameobj );
	//	
	//	pChara->SetActorIndex( index );		
	//}
}
