//*=============================================================================
//EnemyCar.cpp
//*=============================================================================

//==============================================================================
//include
//==============================================================================
#include "EnemyCar.h"
#include <vector>
#include <fstream>

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pName:�f�[�^��
//	vPos:�ݒ肷����W
//	pResFile:�G�̓����̃t�@�C��
//=============================================================================
CEnemyCar::CEnemyCar( const char *pName, Math::Vector3D vPos, File::IResourceFile *pResFile )  
:CEnemy( pName, vPos, pResFile )
{
	m_TypeName = "h.j";//�N���}
	m_StTypeName = "�N���}";

	//float Scale = 15.0f;
	float Scale = 2.0f;
	
	m_IsExistAnim = true;
	
	m_vScale.Set( Scale, Scale, Scale );
	
	m_vInitScale = m_vScale;
	
}


//=============================================================================
//������
//=============================================================================
void CEnemyCar::Init()
{
	CEnemy::Init();
	
	//���[�g�̈ړ��L�[�̐ݒ�
	SetRootKey();
	
}

//=============================================================================
//����
//=============================================================================
void CEnemyCar::Exec()
{
	m_vCatchPos = m_vPos + Math::Vector3D( 0, -0.5f, 0 ) + m_vFront * 0.8f;

	CEnemy::Exec();	
}

//=============================================================================
//�ړ�����
//=============================================================================
void CEnemyCar::MoveExec()
{
	MoveRoot();
}



