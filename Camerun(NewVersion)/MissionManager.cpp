//*============================================================================
//MissionManager.cpp
//*============================================================================
#include "MissionManager.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CMissionManager::CMissionManager(void)
{
	m_MissionNo = 1;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CMissionManager::~CMissionManager(void)
{
	list<MissionList>::iterator it;
	
	for( it = m_MissionList.begin();it != m_MissionList.end();it++ )
	{
		SAFE_DELETE( it->m_pMission );
	}
}

//=============================================================================
//�~�b�V�����̒ǉ�
//=============================================================================
//[input]
//	no:�~�b�V�����ԍ�
//	pMission:�ǉ�����~�b�V����
//=============================================================================
void CMissionManager::AppendMission( int no, CMission *pMission )
{
	if( pMission == NULL )
	{
		return;
	}	
	
	MissionList liMission;//�~�b�V�������X�g
	
	liMission.m_MissionNo = no;
	liMission.m_pMission = pMission;
	
	m_MissionList.push_back(liMission);
}

//=============================================================================
//�~�b�V�����̎擾
//=============================================================================
//[input]
//	no:�~�b�V�����ԍ�
//=============================================================================
CMission *CMissionManager::GetMission( int no )
{
	list<MissionList>::iterator it;
	
	for( it = m_MissionList.begin();it != m_MissionList.end();it++ )
	{
		if( it->m_MissionNo == no )
		{
			return it->m_pMission;
		}
	}
	
	return NULL;
}



