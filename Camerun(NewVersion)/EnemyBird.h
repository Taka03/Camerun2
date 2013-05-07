//*============================================================================
//EnemyBird.h
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
//	鳥用クラス
//=============================================================================
class CEnemyBird : public CEnemy
{
	private:
	
		
	
	public:
	
		CEnemyBird( const char *pName, Math::Vector3D vPos, File::IResourceFile *pResFile );//コンストラクタ
		
		void Init();//初期化
		void Exec();//処理
		
		void MoveExec();//移動処理
		
		bool Move( Selene::Math::Vector3D vTargetPos, CCamera *pCam, CField *pField, bool IsShowMark );//移動
		
		bool HitCheckWall( CField *pField );//壁との接触判定
		
		void MovePatternFly();//飛行用
		void PlaySnd( Sound::ISound *pSound, float fDistance );//効果音の再生
		
};