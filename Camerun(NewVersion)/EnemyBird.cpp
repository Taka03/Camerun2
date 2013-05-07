//*=============================================================================
//EnemyBird.cpp
//*=============================================================================

//==============================================================================
//include
//==============================================================================
#include "EnemyBird.h"
#include <fstream>

//==============================================================================
//enum
//==============================================================================
//���A�j���[�V�����^�C�v
enum eBirdAnimType
{
	ANIM_STAND,
	ANIM_WALK,
	ANIM_FLY_START,
	ANIM_FLY,
	ANIM_FLY_END,
	ANIM_STUN,
};


//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pName:�f�[�^��
//	vPos:�ݒ肷����W
//	pResFile:�G�̓����̃t�@�C��
//=============================================================================
CEnemyBird::CEnemyBird( const char *pName, Math::Vector3D vPos, File::IResourceFile *pResFile ) 
: CEnemy( pName, vPos, pResFile ) 
{
	m_TypeName = "sl";//�g��
	
	m_StTypeName = "�g��";
	
	m_IsFly = true;
	
}


//=============================================================================
//������
//=============================================================================
void CEnemyBird::Init()
{
	CEnemy::Init();
	
	m_AnimID[ANIM_NOW] = ANIM_FLY;
	
	SetRootKey();
	
}

//=============================================================================
//����
//=============================================================================
void CEnemyBird::Exec()
{
	m_vCatchPos = m_vPos + Math::Vector3D( 0, 0.1f, 0 ) + m_vFront * 0.8f;

	CEnemy::Exec();	
	
}

//==============================================================================
//�ړ�����
//==============================================================================
//[input]
//	vTargetPos:�Ώۈʒu
//	pCam:�J�����f�o�C�X
//	pField:�`�F�b�N����}�b�v
//	IsShowMark:�ړ��}�[�J�[���\������Ă��邩
//==============================================================================
bool CEnemyBird::Move( Selene::Math::Vector3D vTargetPos, CCamera *pCam, CField *pField, bool IsShowMark )
{
	m_GravityCnt++;
	
	const int TIME_MAX = 60 * 5;
	
	const float fGRAVITY_MIN = 0.1f;
	const float fGRAVITY_MAX = 0.3f;
	
	if( m_GravityCnt > TIME_MAX )
	{
		m_GravityCnt = TIME_MAX;
	}
	
	
	if( IsShowMark )
	{
		m_vDirection.x = vTargetPos.x * pCam->GetRight().x + vTargetPos.y * (-pCam->GetFront().x);
		m_vDirection.z = vTargetPos.x * pCam->GetRight().z + vTargetPos.y * (-pCam->GetFront().z);
		
		m_vPos.y += ::Interpolation::Add( fGRAVITY_MIN, fGRAVITY_MAX, TIME_MAX, m_GravityCnt );
	}
	
	else
	{
		m_vPos.y -= ::Interpolation::Add( fGRAVITY_MIN, fGRAVITY_MAX, TIME_MAX, m_GravityCnt );
	}
	
	if( m_vPos.y < 0.0f )
	{
		m_vPos.y = 0.0f;		
	}
	
	if( m_vPos.y > 210.0f )
	{
		m_vPos.y = 210.0f;
	}
	
	
	
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
		
		/*�ړ�(-1�̏ꍇ�͒ʂ��)*/
		if( !HitCheckWall( pField ) )
		{
			if( IsShowMark )
			{
				m_vPos += m_vDirection * m_fSpeed;
			}
			
			m_IsMoving = true;
			return true;
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


//=============================================================================
//�ړ�����
//=============================================================================
void CEnemyBird::MoveExec()
{
	MoveRoot();
}


//=============================================================================
//�ǂƂ̔���
//=============================================================================
//[input]
//	pField:�t�B�[���h
//[return]
//	�ǂɓ������Ă��邩�ǂ���
//=============================================================================
bool CEnemyBird::HitCheckWall( CField *pField )
{
	m_HitRay.vStart = m_vPos + Math::Vector3D( 0.0f, 3.0f, 0.0f );
	m_HitRay.vEnd = m_HitRay.vStart + m_vFront * 0.2f;
	
	Renderer::SCollisionResultExtend RetEx;
	
	Bool HitCheck = MoveCheck( pField );
	
	//�ʂ��ӏ��̐ݒ�
	if( HitCheck == MASK_LAKE || HitCheck == -1 )
	{
		return false;
	}
	
	else
	{
		return true;
	}
	
}


//=============================================================================
//���̖����̍Đ�
//=============================================================================
//[input]
//	pSound:�T�E���h�f�o�C�X
//	fDistance:����
//=============================================================================
void CEnemyBird::PlaySnd(Selene::Sound::ISound *pSound, float fDistance )
{
	static float Pan = -100.0f;
	
	Pan += 1.0f;
	
	if( Pan >= 100 )
	{
		Pan = 100;
	}
	
	pSound->SetVolume( 0, 100 - (fDistance * 0.5f) );
	
	pSound->Play( 0, true );
	
	
}
