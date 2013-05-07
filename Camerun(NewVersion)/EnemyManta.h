//*============================================================================
//EnemyManta.h
//*============================================================================
//[history]
//	08/05/31 �쐬
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
//	�}���^�p�N���X
//=============================================================================
class CEnemyManta : public CEnemy
{
	private:
	
		bool m_IsLimitTime;//���~�b�g�^�C���ɒB�������ǂ���
	
	public:
	
		CEnemyManta( const char *pName, Math::Vector3D vPos, File::IResourceFile *pResFile );//�R���X�g���N�^
		
		void Init();//������
		void Exec();//����
		void MoveExec();//�ړ�����
		
		bool HitCheckWall( CField *pField );//�ǂƂ̐ڐG����
		
		
	/*Set�n*/
	public:
	
		/*���~�b�g�^�C������t���O�̐ݒ�*/
		void SetLimitFlag( bool flag )
		{
			m_IsLimitTime = flag;
		}
		
	public:
	
		/*���~�b�g�^�C������t���O�̎擾*/
		bool GetLimitFlag( ) const
		{
			return m_IsLimitTime;
		}
		
};