//*============================================================================
//EnemyAmeus.h
//*============================================================================
//[history]
//	08/04/15 作成
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
//	アメウス用クラス
//=============================================================================
class CEnemyAmeus : public CEnemy
{
	private:
	
	public:
	
		CEnemyAmeus( const char *pName, Math::Vector3D vPos, File::IResourceFile *pResFile );//コンストラクタ
		
		void Init();//初期化
		void Exec();//処理
		
		bool HitCheckWall( CField *pField );//壁との接触判定
		
		void StateExec();
		
		void MoveExec( );//移動
};