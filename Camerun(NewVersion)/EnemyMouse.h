//*============================================================================
//EnemyMouse.h
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
//	ねずみ用クラス
//=============================================================================
class CEnemyMouse : public CEnemy
{
	public:
	
		CEnemyMouse( const char *pName, Math::Vector3D vPos, File::IResourceFile *pResFile );//コンストラクタ
		
		void Init();//初期化
		void Exec();//処理
		void MoveExec();//移動処理
		
		bool HitCheckWall( CField *pField );//壁との接触判定
		
		
		void MovePatternStand();//立ち状態の移動パターン
		void PlaySnd( Sound::ISound *pSound, float fDistance );//効果音の再生
};