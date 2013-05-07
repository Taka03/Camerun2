//*============================================================================
//Mission.h
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
#include "Selene.h"
#include "Draw3DObject.h"
#include "Sprite.h"
#include <vector>

//=============================================================================
//struct
//=============================================================================
struct tagTime
{
	Sint32 MinSec;//�~���b
	Sint32 Sec;//�b
	Sint32 Min; //��
	Sint32 Hour;//����
	
	tagTime()
	{
		MinSec = 0;
		Sec = 0;
		Min = 0;
		Hour = 0;
	}
	
	void Initialize()
	{
		MinSec = 0;
		Sec = 0;
		Min = 0;
		Hour = 0;
	}
};

//=============================================================================
//using
//=============================================================================
using namespace Selene;

//=============================================================================
//struct
//=============================================================================
struct MissionData
{
	string m_MissionName;//�~�b�V������
	string m_MissionChat;//�~�b�V������b
	vector< string > m_vecChat;//��b���e
	vector< string > m_vecMissionContent;//�~�b�V�������e
	string m_TargetName;//�^�[�Q�b�g��
	CSprite *m_pFontSpr;//�~�b�V�����t�H���g�X�v���C�g
	CSprite *m_pPhotoSpr;//�~�b�V�����̎ʐ^�X�v���C�g
	Sint32 m_ClearPoint;//�N���A�\�ƂȂ�|�C���g
	Sint32 m_FilmNum;//�~�b�V�����̃t�B��������
	tagTime m_LimitTime;//��������
	tagTime m_TimeBorder;//�^�C���{�[�_�[
	float m_DistanceMax;//�^�[�Q�b�g������Max
	float m_DistanceMin;//�^�[�Q�b�g������Min
	float m_TargetPosMax;//�^�[�Q�b�g�ʒu��Min
	float m_TargetPosMin;//�^�[�Q�b�g�ʒu��Min
	
};


//=============================================================================
//class
//=============================================================================
//[Desc]
//	�~�b�V�����p�N���X
//=============================================================================
class CMission 
{
	protected:
	
		MissionData m_datMission;//�~�b�V�����f�[�^
		CDraw3DObject *m_pTarget;//�^�[�Q�b�g�ƂȂ�I�u�W�F�N�g
		bool m_IsGameClear;//�~�b�V�����N���A�������ǂ���
		bool m_IsFirstPlay;//�����v���C��
		Sint32 m_HiScore;//�~�b�V�����̃n�C�X�R�A
		//Sint32 m_ExistScore;//���݃X�R�A
		//Sint32 m_PosScore;//�ʒu�X�R�A
		//Sint32 m_DistScore;//�����X�R�A
		Sint32 m_ClearTime;//�N���A����
		Sint32 m_PhotoIndex;//�I�����ꂽ�ʐ^�̃C���f�b�N�X
		
	public:
		
		CMission(void);//�R���X�g���N�^
		CMission( CDraw3DObject *pTarget, MissionData datMission );//�R���X�g���N�^
		~CMission(void);//�f�X�g���N�^
		
		void Exec();//����
		void Rendering();//�����_�����O
		
	/*Set�n*/
	public:
	
		/*�^�[�Q�b�g�̐ݒ�*/
		void SetTarget( CDraw3DObject *pTarget )
		{
			m_pTarget = pTarget;
		}
		
		/*�~�b�V�����N���A�t���O�̐ݒ�*/
		void SetGameClearFlag( bool flag )
		{
			m_IsGameClear = flag;
		}
		
		/*�n�C�X�R�A�̐ݒ�*/
		void SetHiScore( Sint32 HiScore )
		{
			m_HiScore = HiScore;
		}
		
		/*�����v���C�t���O�̐ݒ�*/
		void SetFirstPlayFlag( bool flag )
		{
			m_IsFirstPlay = flag;
		}
		
		///*���݃X�R�A�̐ݒ�*/
		//void SetExistScore( Sint32 Score )
		//{
		//	m_ExistScore = Score;
		//}
		//
		///*�ʒu�X�R�A�̐ݒ�*/
		//void SetPosScore( Sint32 Score )
		//{
		//	m_PosScore = Score;
		//}

		///*�傫���X�R�A�̐ݒ�*/
		//void SetDistScore( Sint32 Score )
		//{
		//	m_DistScore = Score;
		//}
		
		
		/*�ʐ^�p�X�v���C�g�̐ݒ�*/
		void SetPhotoSprite( CSprite *pSpr )
		{
			m_datMission.m_pPhotoSpr = pSpr;
		}
		
		/*�I���ʐ^�̃C���f�b�N�X�̃Z�b�g*/
		void SetPhotoIndex( Sint32 index )
		{
			m_PhotoIndex = index;
		}
		
		
	/*Get�n*/
	public:

		/*�~�b�V�����f�[�^�̎擾*/
		MissionData GetMissionData() const
		{
			return m_datMission;
		}
		
		/*�~�b�V�������̎擾*/
		string GetMissionName() const
		{
			return m_datMission.m_MissionName;
		}

		//�^�[�Q�b�g�ƂȂ�I�u�W�F�N�g�̎擾
		CDraw3DObject *GetTarget() const
		{
			return m_pTarget;
		}
		
		//�N���A�\�ƂȂ�|�C���g�̎擾		
		Sint32 GetClearPoint() const
		{
			return m_datMission.m_ClearPoint;
		}
		
		/*�t�B���������̎擾*/
		Sint32 GetFilmNum() const
		{
			return m_datMission.m_FilmNum;
		}
		
		/*�������Ԃ̎擾*/
		tagTime GetLimitTime() const
		{
			return m_datMission.m_LimitTime;
		}
		
		/*�~�b�V�����N���A����t���O�̎擾*/
		bool GetGameClearFlag()
		{
			return m_IsGameClear;
		}
		
		/*�����v���C�t���O�̎擾*/
		bool GetFirstPlayFlag()
		{
			return m_IsFirstPlay;
		}
		
		/*�n�C�X�R�A�̎擾*/
		Sint32 GetHiScore()
		{
			return m_HiScore;
		}
		//
		///*���݃X�R�A�̎擾*/
		//Sint32 GetExistScore()
		//{
		//	return m_ExistScore;
		//}

		///*�ʒu�X�R�A�̎擾*/
		//Sint32 GetPosScore()
		//{
		//	return m_PosScore;
		//}

		///*�傫���X�R�A�̎擾*/
		//Sint32 GetDistScore()
		//{
		//	return m_DistScore;
		//}
		
		
		/*�^�C���{�[�_�[�̎擾*/
		tagTime GetTimeBorder()
		{
			return m_datMission.m_TimeBorder;
		}
		
		/*�I���ʐ^�̃C���f�b�N�X*/
		Sint32 GetPhotoIndex()
		{
			return m_PhotoIndex;
		}
	
};
