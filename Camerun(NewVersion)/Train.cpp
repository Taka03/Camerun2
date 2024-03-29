//*=============================================================================
//enemy.cpp
//*=============================================================================

//==============================================================================
//include
//==============================================================================
#include "Train.h"
#include "SoundManager.h"

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	pName:データ名
//	vPos:設定する座標
//=============================================================================
CTrain::CTrain( const char *pName, Math::Vector3D vPos, File::IResourceFile *pResFile ) 
:CEnemy( pName, vPos, pResFile )
{
	m_TypeName = "Wyd'";//電車
	m_StTypeName = "デンシャ";
	
	m_Rot.x = DEG_TO_ANGLE(-90);
	m_InitRot = m_Rot;
	
	m_fSpeed = 0.31f;
	
	
	m_fWeight = 0.0f;
	
	m_IsExistAnim = false;
	m_IsCatchable = false;
	
}

//=============================================================================
//初期化
//=============================================================================
void CTrain::Init()
{
	CEnemy::Init();
}

//=============================================================================
//処理
//=============================================================================
void CTrain::Exec()
{
	CEnemy::Exec();
}

//=============================================================================
//移動処理
//=============================================================================
void CTrain::MoveExec()
{
	if( m_vPos.z < -540.0f )
	{
		m_vPos.z = m_vInitPos.z;
	}
	
	else
	{
		m_vPos.z -= m_fSpeed;
	}

}



//=============================================================================
//電車音の再生
//=============================================================================
//[input]
//	pSound:サウンドデバイス
//	fDistance:距離
//=============================================================================
void CTrain::PlaySnd( float fDistance )
{
	static float Pan = -100.0f;
	
	Pan += 1.0f;
	
	if( Pan >= 100 )
	{
		Pan = 100;
	}
	
	CCommonObject::GetSoundMgr()->SetVolume( CSoundManager::SND_TRAIN, 100 - (fDistance * 0.5f) );
	
	CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_TRAIN );
	
	
	
	
}


