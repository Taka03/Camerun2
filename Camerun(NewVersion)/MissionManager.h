//*============================================================================
//MissionManager.h
//*============================================================================
//[history]
//	08/03/11�@�쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Mission.h"
#include <iostream>

using namespace std;

//=============================================================================
//struct
//=============================================================================
//�~�b�V�������X�g
struct MissionList
{
	int m_MissionNo;//�~�b�V����No
	CMission *m_pMission;//�~�b�V����
};

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�~�b�V�����Ǘ��p�N���X
//=============================================================================
class CMissionManager
{
	private:
		
		list<MissionList> m_MissionList;//�~�b�V�������X�g
		
		Sint32 m_MissionNo;//�I������Ă���~�b�V�����ԍ�
	
	public:
	
		CMissionManager(void);//�R���X�g���N�^
		~CMissionManager(void);//�f�X�g���N�^
		
		void AppendMission( int no, CMission *pMission );//�~�b�V�����̒ǉ�
		
	/*Set�n*/
	public:
	
		//�~�b�V�����ԍ��̃Z�b�g	
		void SetMissionNo( int no )
		{
			m_MissionNo = no;
		}
		
	/*Get�n*/
	public:
	
		CMission *GetMission( int no );//�~�b�V�����̎擾
		
		/*�I�𒆂̃~�b�V�����ԍ��̎擾*/
		Sint32 GetMissionNo() const
		{
			return m_MissionNo;
		}
		
		/*�~�b�V�������̎擾*/
		Sint32 GetMissionNum() const
		{
			return m_MissionList.size();
		}
};
