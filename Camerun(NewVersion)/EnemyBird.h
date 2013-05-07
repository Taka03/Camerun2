//*============================================================================
//EnemyBird.h
//*============================================================================
//[history]
//	08/04/15 �쐬
//[author]
//	Taka
//=============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "enemy.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	���p�N���X
//=============================================================================
class CEnemyBird : public CEnemy
{
	private:
	
		
	
	public:
	
		CEnemyBird( const char *pName, Math::Vector3D vPos, File::IResourceFile *pResFile );//�R���X�g���N�^
		
		void Init();//������
		void Exec();//����
		
		void MoveExec();//�ړ�����
		
		bool Move( Selene::Math::Vector3D vTargetPos, CCamera *pCam, CField *pField, bool IsShowMark );//�ړ�
		
		bool HitCheckWall( CField *pField );//�ǂƂ̐ڐG����
		
		void MovePatternFly();//��s�p
		void PlaySnd( Sound::ISound *pSound, float fDistance );//���ʉ��̍Đ�
		
};