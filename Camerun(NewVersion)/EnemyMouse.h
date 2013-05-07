//*============================================================================
//EnemyMouse.h
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
//	�˂��ݗp�N���X
//=============================================================================
class CEnemyMouse : public CEnemy
{
	public:
	
		CEnemyMouse( const char *pName, Math::Vector3D vPos, File::IResourceFile *pResFile );//�R���X�g���N�^
		
		void Init();//������
		void Exec();//����
		void MoveExec();//�ړ�����
		
		bool HitCheckWall( CField *pField );//�ǂƂ̐ڐG����
		
		
		void MovePatternStand();//������Ԃ̈ړ��p�^�[��
		void PlaySnd( Sound::ISound *pSound, float fDistance );//���ʉ��̍Đ�
};