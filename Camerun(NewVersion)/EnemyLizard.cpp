//*=============================================================================
//EnemyLizard.cpp
//*=============================================================================

//==============================================================================
//include
//==============================================================================
#include "EnemyLizard.h"

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	pName:データ名
//	vPos:設定する座標
//	pResFile:敵の動きのファイル
//=============================================================================
CEnemyLizard::CEnemyLizard( const char *pName, Math::Vector3D vPos, File::IResourceFile *pResFile )  
:CEnemy( pName, vPos, pResFile )
{
	m_TypeName = "st*";//トカゲ
	m_StTypeName = "トカゲ";

	float Scale = 1.0f;
	
	m_vScale.Set( Scale, Scale, Scale );
	
	m_IsVisible = false;

	
}

//==============================================================================
//移動処理
//==============================================================================
//[input]
//	vTargetPos:対象位置
//	pCam:カメラデバイス
//	pField:チェックするマップ
//	IsShowMark:マークが表示されているか
//[return]
//	移動中かどうか
//==============================================================================
bool CEnemyLizard::Move( Selene::Math::Vector3D vTargetPos, CCamera *pCam, CField *pField, bool IsShowMark )
{
	m_vDirection.x = vTargetPos.x * pCam->GetRight().x + vTargetPos.y * (-pCam->GetFront().x);
	m_vDirection.y = 0.0f;
	m_vDirection.z = vTargetPos.x * pCam->GetRight().z + vTargetPos.y * (-pCam->GetFront().z);
	
	m_Rot.x = toF( Math::ATan2( -m_vDirection.z, -m_vDirection.x ) );
	
	float fLength = m_vDirection.Length();
	
	m_fSpeed = fLength * 0.001f ;
	
	if( m_fSpeed > 2.0f )
	{
		m_fSpeed = 2.0f;
	}
	
	
	/*移動チェック*/
	if( m_vDirection.LengthSq() > 0.0f )
	{
		/*正規化*/
		m_vDirection /= fLength;
		
		/*移動(-1, 0の場合は通れる)*/
		if( MoveCheck( pField ) == -1  )
		{
			if( IsShowMark )
			{
				m_Rot.y = DEG_TO_ANGLE( 0 );
				m_vPos += m_vDirection * m_fSpeed;
				m_IsMoving = true;
			}
				
			return true;
		}
		
		/*壁の場合上る*/
		else if( MoveCheck( pField ) == 0 )
		{
			if( IsShowMark )
			{
				m_Rot.y = DEG_TO_ANGLE( 90 );
				m_vPos.y += m_vDirection.Length() * m_fSpeed;
				m_vPos.x += m_vDirection.x * m_fSpeed;
			}
		}
		
		else
		{
			m_fSpeed = 0.0f;
			m_IsMoving = false;
			
		}
		
	}
	
	else
	{
		m_IsMoving = false;
	}
	
	return false;
	
}


