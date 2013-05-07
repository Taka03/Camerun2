//*=============================================================================
//EnemyLizard.cpp
//*=============================================================================

//==============================================================================
//include
//==============================================================================
#include "EnemyLizard.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pName:�f�[�^��
//	vPos:�ݒ肷����W
//	pResFile:�G�̓����̃t�@�C��
//=============================================================================
CEnemyLizard::CEnemyLizard( const char *pName, Math::Vector3D vPos, File::IResourceFile *pResFile )  
:CEnemy( pName, vPos, pResFile )
{
	m_TypeName = "st*";//�g�J�Q
	m_StTypeName = "�g�J�Q";

	float Scale = 1.0f;
	
	m_vScale.Set( Scale, Scale, Scale );
	
	m_IsVisible = false;

	
}

//==============================================================================
//�ړ�����
//==============================================================================
//[input]
//	vTargetPos:�Ώۈʒu
//	pCam:�J�����f�o�C�X
//	pField:�`�F�b�N����}�b�v
//	IsShowMark:�}�[�N���\������Ă��邩
//[return]
//	�ړ������ǂ���
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
	
	
	/*�ړ��`�F�b�N*/
	if( m_vDirection.LengthSq() > 0.0f )
	{
		/*���K��*/
		m_vDirection /= fLength;
		
		/*�ړ�(-1, 0�̏ꍇ�͒ʂ��)*/
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
		
		/*�ǂ̏ꍇ���*/
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


