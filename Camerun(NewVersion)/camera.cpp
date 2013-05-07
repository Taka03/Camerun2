//*============================================================================
//camera.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "camera.h"
#include "player.h"
#include "enemy.h"

#if defined(DEBUG) | (_DEBUG)
	namespace
	{
		Math::Vector3D vDebugPos( 0.0f, 5.0f, 8.0f );
	}
#endif

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CCamera::CCamera() :m_pCamera(NULL)
{
	m_vPos.Set( 0, 50.0f, 50.0f );
	m_vInitPos = m_vPos;
	m_InitRot = m_Rot;
	
	m_vDirection.Set( 0.0f, 0.0f, 8.0f );
	
	m_IsChangeTopView = false;
	
	
}


//=============================================================================
//�f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
	SAFE_RELEASE( m_pCamera ); 
}

//=============================================================================
//������
//=============================================================================
void CCamera::Init()
{
	m_vPos = m_vInitPos;
	m_Rot = m_InitRot;
	
	m_CamCnt = 0;
	
}

//=============================================================================
//����
//=============================================================================
void CCamera::Exec()
{

}


//=============================================================================
//�J�����̃Z�b�g
//=============================================================================
//[input]
//	pScene:�V�[���Ǘ��f�o�C�X
//=============================================================================
void CCamera::SetCamera( Scene::ISceneManager *pScene )
{
	/*�V�[������J�������擾*/
	m_pCamera = pScene->GetCamera();
	
}

//=============================================================================
//�J�����̃Z�b�g
//=============================================================================
//[input]
//	pScene:�V�[���Ǘ��f�o�C�X
//=============================================================================
//void CCamera::SetCamera( Scene::ICustomizedSceneManager *pScene )
//{
//	/*�V�[������J�������擾*/
//	m_pCamera = pScene->GetCamera();
//	
//}

//=============================================================================
//�v���W�F�N�V�����̐ݒ�
//=============================================================================
//[input]
//	fNear:��Z���ʃN���b�v
//	fFar:��Z�ʃN���b�v
//	fov:����p
//	Width:��ʕ�
//	Height:��ʍ���
//=============================================================================
void CCamera::SetProjection( float fNear, float fFar, Sint32 fov, Sint32 Width, Sint32 Height )
{
	if( m_pCamera != NULL )
	{
		m_pCamera->UpdateProjection( fNear, fFar, DEG_TO_ANGLE(fov), Width, Height );
	}
}

//=============================================================================
//�ό`�̐ݒ�
//=============================================================================
//[input]
//	style:�p���f�[�^
//=============================================================================
void CCamera::SetTransform( Math::Style style )
{
	if( m_pCamera != NULL )
	{
		/*�J�����̏�Ԃ̃��Z�b�g*/
		m_pCamera->Reset();
		
		/*�ό`��K�p*/
		m_pCamera->SetTransform( style );
		
		/*�J�����̍X�V*/
		m_pCamera->Update();
	}
}

//=============================================================================
//�ό`�̐ݒ�
//=============================================================================
void CCamera::SetTransform( )
{
	if( m_pCamera != NULL )
	{
		// �J�����̖ڕW�ʒu
		Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
		Math::Matrix mTemp;
		mTemp.RotationX( toI( m_Rot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( m_Rot.y )  );
		vDirection.TransformNormal( mTemp );
		
		//mTemp.RotationX( m_Rot.z );
		//vDirection.TransformNormal( mTemp );

		Math::Vector3D vCameraTarget = m_vTarget + vDirection;

		//// ������Ƃ��߂Â�������
		//if( vCameraTarget.y > 3.0 )
		//{	
		//	m_vPos.y =  m_vTarget.y + 3;
		//	mTemp.RotationX( DEG_TO_ANGLE( 60 ) );
		//	vDirection.TransformNormal( mTemp );
		//}
		
		//if( vCameraTarget
		
			m_vPos += ( vCameraTarget - m_vPos ) * 0.1f;
		
		

		// �J�����̃g�����X�t�H�[��
		m_Style.TransformReset();

		m_Style.LookAt(
			m_vPos,				// �J�����ʒu
			m_vTarget,							// �J�����^�[�Q�b�g�i�L�����̓��j
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// �����
			
		m_Style.GetFront( m_vFront );
		m_Style.GetRight( m_vRight );
		m_Style.GetUp( m_vUp );
			
		/*�J�����̏�Ԃ̃��Z�b�g*/
		m_pCamera->Reset();
		
		/*�ό`��K�p*/
		m_pCamera->SetTransform( m_Style );
		
		/*�J�����̍X�V*/
		m_pCamera->Update();
	}
}

//=============================================================================
//�ό`�̐ݒ�
//=============================================================================
//[input]
//	pPlayer:�v���C���[�I�u�W�F�N�g
//=============================================================================
void CCamera::SetTransform( CPlayer *pPlayer )
{
	if( m_pCamera != NULL )
	{
		// �J�����̖ڕW�ʒu
		Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
		Math::Matrix mTemp;
		mTemp.RotationX( toI( m_Rot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( m_Rot.y )  );
		vDirection.TransformNormal( mTemp );
		
		static float fZoom = 0.1f;
		
		//mTemp.RotationX( m_Rot.z );
		//vDirection.TransformNormal( mTemp );
		
		//m_vDirection = vDirection;
		
		
		if( pPlayer->GetRotate().x > DEG_TO_ANGLE( 90 ) && pPlayer->GetRotate().x < DEG_TO_ANGLE( 270 ) ) 
		{
			fZoom += 0.1f;
		}
		
		else
		{
			fZoom -= 0.1f;
		}
		
		const float fMAX_ZOOM = 0.0f;
		const float fMIN_ZOOM = 0.0f;
		
		if( fZoom > fMAX_ZOOM )
		{
			fZoom = fMAX_ZOOM;
		}
		
		else if( fZoom < fMIN_ZOOM )
		{
			fZoom = fMIN_ZOOM;
		}
		
		Math::Vector3D vZoom( 0.0f, 0.0f, fZoom );
		
		Math::Vector3D vCameraTarget = m_vTarget + vDirection + vZoom;
		
		Math::Vector3D vCamDir = ( vCameraTarget - m_vPos );
		
		m_vPos += vCamDir * 0.1f;
		
		

		// �J�����̃g�����X�t�H�[��
		m_Style.TransformReset();

		m_Style.LookAt(
			m_vPos,				// �J�����ʒu
			m_vTarget,							// �J�����^�[�Q�b�g�i�L�����̓��j
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// �����
			
		m_Style.GetFront( m_vFront );
		m_Style.GetRight( m_vRight );
			
		/*�J�����̏�Ԃ̃��Z�b�g*/
		m_pCamera->Reset();
		
		/*�ό`��K�p*/
		m_pCamera->SetTransform( m_Style );
		
		/*�J�����̍X�V*/
		m_pCamera->Update();
	}

}

//=============================================================================
//�ό`�̐ݒ�
//=============================================================================
//[input]
//	Angle:��]�p�x
//	IsCamMove:�J�������ړ������ǂ���
//=============================================================================
void CCamera::SetTransform( Sint32 Angle, bool IsCamMove )
{
	if( m_pCamera != NULL )
	{
	
		// �J�����̖ڕW�ʒu
		Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
		Math::Matrix mTemp;

		static float fZoom = 0.1f;
		
		//mTemp.RotationX( m_Rot.z );
		//vDirection.TransformNormal( mTemp );
		
		//m_vDirection = vDirection;
		
		
		
		if( IsCamMove )
		{
			if( Angle > DEG_TO_ANGLE( 90 ) && 
				Angle < DEG_TO_ANGLE( 270 ) ) 
			{
				fZoom += 0.1f;
			}
			
			else
			{
				fZoom -= 0.1f;
			}
		}
		
		else
		{
			fZoom = 0.0f;
		}
		
		const float fMAX_ZOOM = 5.0f;
		const float fMIN_ZOOM = 0.0f;
		
		if( fZoom > fMAX_ZOOM )
		{
			fZoom = fMAX_ZOOM;
		}
		
		else if( fZoom < fMIN_ZOOM )
		{
			fZoom = fMIN_ZOOM;
		}
		
		
		mTemp.RotationX( toI( m_Rot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( m_Rot.y ) );
		
		vDirection.TransformNormal( mTemp );
		
	
		Math::Vector3D vCameraTarget = m_vTarget + vDirection - m_vFront * fZoom;
		
		
		Math::Vector3D vCamDir = ( vCameraTarget - m_vPos );
		
		m_vPos += vCamDir * 0.1f;
		
		// �J�����̃g�����X�t�H�[��
		m_Style.TransformReset();

		m_Style.LookAt(
			m_vPos,				// �J�����ʒu
			m_vTarget,							// �J�����^�[�Q�b�g�i�L�����̓��j
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// �����
			
		m_Style.GetFront( m_vFront );
		m_Style.GetRight( m_vRight );
			
		/*�J�����̏�Ԃ̃��Z�b�g*/
		m_pCamera->Reset();
		
		/*�ό`��K�p*/
		m_pCamera->SetTransform( m_Style );
		
		/*�J�����̍X�V*/
		m_pCamera->Update();
	}

}

//=============================================================================
//�ό`�̐ݒ�(�g���̏ꍇ)
//=============================================================================
//[input]
//	Angle:��]�p�x
//	IsCamMove:�J�������ړ������ǂ���
//=============================================================================
void CCamera::SetTransformBird( Sint32 Angle, bool IsCamMove )
{
	if( m_pCamera != NULL )
	{
	
		// �J�����̖ڕW�ʒu
		Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
		Math::Matrix mTemp;

		static float fZoom = 0.1f;
		
		//mTemp.RotationX( m_Rot.z );
		//vDirection.TransformNormal( mTemp );
		
		//m_vDirection = vDirection;
		
		
		
		if( IsCamMove )
		{
			if( Angle > DEG_TO_ANGLE( 90 ) && 
				Angle < DEG_TO_ANGLE( 270 ) ) 
			{
				fZoom += 0.1f;
			}
			
			else
			{
				fZoom -= 0.1f;
			}
		}
		
		else
		{
			fZoom = 0.0f;
		}
		
		const float fMAX_ZOOM = 5.0f;
		const float fMIN_ZOOM = 0.0f;
		
		if( fZoom > fMAX_ZOOM )
		{
			fZoom = fMAX_ZOOM;
		}
		
		else if( fZoom < fMIN_ZOOM )
		{
			fZoom = fMIN_ZOOM;
		}
		
		
		mTemp.RotationX( toI( m_Rot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( m_Rot.y ) );
		
		vDirection.TransformNormal( mTemp );
		
	
		Math::Vector3D vCameraTarget = m_vTarget + vDirection - m_vFront * fZoom;
		
		
		Math::Vector3D vCamDir = ( vCameraTarget - m_vPos );
		
		m_vPos += vCamDir * 0.1f;
		
		// �J�����̃g�����X�t�H�[��
		m_Style.TransformReset();

		m_Style.LookAt(
			m_vPos + Math::Vector3D( 0, 2, 0 ),				// �J�����ʒu
			m_vTarget,							// �J�����^�[�Q�b�g�i�L�����̓��j
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// �����
			
		m_Style.GetFront( m_vFront );
		m_Style.GetRight( m_vRight );
			
		/*�J�����̏�Ԃ̃��Z�b�g*/
		m_pCamera->Reset();
		
		/*�ό`��K�p*/
		m_pCamera->SetTransform( m_Style );
		
		/*�J�����̍X�V*/
		m_pCamera->Update();
	}

}


//=============================================================================
//�L���v�`���[���̃J�����ό`
//=============================================================================
//[input]
//	pPlayer:�v���C���[�I�u�W�F�N�g
//	pTarget:�^�[�Q�b�g�I�u�W�F�N�g
//=============================================================================
void CCamera::SetTransformCap( CPlayer *pPlayer, CEnemy *pTarget )
{
	// �J�����̖ڕW�ʒu
	Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
	Math::Matrix mTemp;

	static float fZoom = 0.1f;
	
	//mTemp.RotationX( m_Rot.z );
	//vDirection.TransformNormal( mTemp );
	
	//m_vDirection = vDirection;
	
	
	const float fMAX_ZOOM = 5.0f;
	const float fMIN_ZOOM = 0.0f;
	
	if( fZoom > fMAX_ZOOM )
	{
		fZoom = fMAX_ZOOM;
	}
	
	else if( fZoom < fMIN_ZOOM )
	{
		fZoom = fMIN_ZOOM;
	}
	
	
	mTemp.RotationX( toI( m_Rot.x ) );
	
	vDirection.TransformNormal( mTemp );
	mTemp.RotationY( toI( m_Rot.y ) );
	
	vDirection.TransformNormal( mTemp );
	

	Math::Vector3D vCameraTarget = m_vTarget + vDirection - m_vFront * fZoom;
	
	
	Math::Vector3D vCamDir = ( vCameraTarget - m_vPos );
	
	m_vPos += vCamDir * 0.1f;
	
	// �J�����̃g�����X�t�H�[��
	m_Style.TransformReset();

	m_Style.LookAt(
		m_vPos,				// �J�����ʒu
		m_vTarget,							// �J�����^�[�Q�b�g�i�L�����̓��j
		Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// �����
		
	m_Style.GetFront( m_vFront );
	m_Style.GetRight( m_vRight );
		
	/*�J�����̏�Ԃ̃��Z�b�g*/
	m_pCamera->Reset();
	
	/*�ό`��K�p*/
	m_pCamera->SetTransform( m_Style );
	
	/*�J�����̍X�V*/
	m_pCamera->Update();

}



//=============================================================================
//�J�����̉�]
//=============================================================================
//[input]
//	Type:�J�����̉�]�^�C�v
//=============================================================================
void CCamera::RotateCamera( eRollType Type )
{
	if( m_pCamera != NULL )
	{
		/*����]�̏ꍇ*/
		if( Type == ROLL_LEFT )
		{
			m_Rot.y -= DEG_TO_ANGLE(1);
		}
		
		/*�E��]�̏ꍇ*/
		else if( Type == ROLL_RIGHT )
		{
			m_Rot.y += DEG_TO_ANGLE(1);
		}
		
		
		/*���]�̏ꍇ*/
		else if( Type == ROLL_UP )
		{
			m_Rot.x -= DEG_TO_ANGLE(1);
		}
		
		/*����]�̏ꍇ*/
		else if( Type == ROLL_DOWN )
		{
			m_Rot.x += DEG_TO_ANGLE(1);
		}
	}
}

//=============================================================================
//�J�����̉�]�␳
//=============================================================================
void CCamera::RotateAdjust()
{
	const int MAX_ANGLE = 30;//�J�����̍ő�p�x
	
	if( m_Rot.x > DEG_TO_ANGLE( MAX_ANGLE - 1 ) )
	{
		m_Rot.x = DEG_TO_ANGLE( MAX_ANGLE - 1 );
	}
	
	else if( m_Rot.x < DEG_TO_ANGLE( -MAX_ANGLE + 1 ) )
	{
		m_Rot.x = DEG_TO_ANGLE( -MAX_ANGLE + 1 );
	}
	
	if( m_Rot.y >= DEG_TO_ANGLE( 360 ) )
	{
		m_Rot.y = DEG_TO_ANGLE( 0 );
	}
	
	if( m_Rot.y <= DEG_TO_ANGLE( -360 ) )
	{
		m_Rot.y = DEG_TO_ANGLE( 0 );
	}
	
	
}



//=============================================================================
//�ό`�̐ݒ�
//=============================================================================
void CCamera::SetTransform2( )
{
	if( m_pCamera != NULL )
	{
		// �J�����̖ڕW�ʒu
		Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
		Math::Matrix mTemp;
		mTemp.RotationX( toI( m_Rot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( -m_Rot.y ) );
		vDirection.TransformNormal( mTemp );

		Math::Vector3D vCameraTarget = m_vTarget + vDirection;

		/*������Ƃ��߂Â�������*/
		m_vPos = m_vTarget + Math::Vector3D( 0.0f, 0.8f, 0.0f );
		
		// �J�����̃g�����X�t�H�[��
		m_Style.TransformReset();
		
		m_Style.LookAt(
			m_vPos,				// �J�����ʒu
			vCameraTarget,							// �J�����^�[�Q�b�g�i�L�����̓��j
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// �����
			

		/*�J�����̏�Ԃ̃��Z�b�g*/
		m_pCamera->Reset();
		
		/*�ό`��K�p*/
		m_pCamera->SetTransform( m_Style );
		
		/*�J�����̍X�V*/
		m_pCamera->Update();
	}
}

//=============================================================================
//�ό`�̐ݒ�
//=============================================================================
void CCamera::SetTransform3( )
{
	if( m_pCamera != NULL )
	{
		// �J�����̖ڕW�ʒu
		Math::Vector3D vDirection( 0.0f, 100.0f, 0.0f );
		Math::Matrix mTemp;
		mTemp.RotationX( toI( m_Rot.x ) );
		
		vDirection.TransformNormal( mTemp );
		mTemp.RotationY( toI( m_Rot.y ) );
		vDirection.TransformNormal( mTemp );
		
		//mTemp.RotationX( m_Rot.z );
		//vDirection.TransformNormal( mTemp );

		Math::Vector3D vCameraTarget = m_vTarget + vDirection;

		// ������Ƃ��߂Â�������
		m_vPos = vCameraTarget;

		// �J�����̃g�����X�t�H�[��
		m_Style.TransformReset();

		m_Style.LookAt(
			m_vPos,				// �J�����ʒu
			m_vTarget,							// �J�����^�[�Q�b�g�i�L�����̓��j
			Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// �����

		/*�J�����̏�Ԃ̃��Z�b�g*/
		m_pCamera->Reset();
		
		/*�ό`��K�p*/
		m_pCamera->SetTransform( m_Style );
		
		/*�J�����̍X�V*/
		m_pCamera->Update();
	}
}

//=============================================================================
//�ό`�̐ݒ�(�f���p)
//=============================================================================
void CCamera::SetTransformDemo( CEnemy *pEnemy )
{
	if( m_pCamera != NULL )
	{
		m_CamCnt++;
		
		const Sint32 TIME_MAX = 60 * 3;
		
		// �J�����̖ڕW�ʒu
		Math::Vector3D vDirection( 0.0f, 0.0f, 8.0f );
		Math::Matrix mTemp;
		mTemp.RotationX( toI( m_Rot.x ) );
		
		vDirection.TransformNormal( mTemp );
		
		mTemp.RotationY( ::Interpolation::Flat( DEG_TO_ANGLE(0), DEG_TO_ANGLE( 180 ), TIME_MAX, m_CamCnt ) );
		vDirection.TransformNormal( mTemp );
		
		if( m_CamCnt > TIME_MAX )
		{
			m_CamCnt = 0;
		}
		
		//mTemp.RotationX( m_Rot.z );
		//vDirection.TransformNormal( mTemp );

		Math::Vector3D vCameraTarget = m_vTarget + vDirection;

		//// ������Ƃ��߂Â�������
		//if( vCameraTarget.y > 3.0 )
		//{	
		//	m_vPos.y =  m_vTarget.y + 3;
		//	mTemp.RotationX( DEG_TO_ANGLE( 60 ) );
		//	vDirection.TransformNormal( mTemp );
		//}
		//
		//m_vPos += Math::Vector3D( 0, 0, -2 );
		//
		//m_vPos += ( vCameraTarget - m_vPos ) * 0.1f;

		// �J�����̃g�����X�t�H�[��
		m_Style.TransformReset();

		if( pEnemy->GetStTypeName().compare( "�A���E�X" ) == 0 )
		{
			m_Style.LookAt(
				pEnemy->GetPosition() + Math::Vector3D( 5.0f, 10.0, -5.0f ),				// �J�����ʒu
				pEnemy->GetPosition(),							// �J�����^�[�Q�b�g�i�L�����̓��j
				Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// �����
		}
		
		else
		{
			m_Style.LookAt(
				pEnemy->GetPosition() + Math::Vector3D( 10.0f, 10.0, -10.0f ),				// �J�����ʒu
				pEnemy->GetPosition(),							// �J�����^�[�Q�b�g�i�L�����̓��j
				Math::Vector3D( 0.0f, 1.0f, 0.0f ) );	// �����
		}
				
		/*�J�����̏�Ԃ̃��Z�b�g*/
		m_pCamera->Reset();
		
		/*�ό`��K�p*/
		m_pCamera->SetTransform( m_Style );
		
		/*�J�����̍X�V*/
		m_pCamera->Update();
	}
}





//=============================================================================
//�ʒu�̐ݒ�
//=============================================================================
//[input]
//	vPos:�ʒu
//=============================================================================
void CCamera::SetPosition( Math::Vector3D vPos )
{
	m_vPos = vPos;
}

//=============================================================================
//��]�p�x�̐ݒ�
//=============================================================================
//[input]
//	Rot:��]�p�x
//=============================================================================
void CCamera::SetRotate( Math::Point3DI Rot )
{
	m_Rot = Rot;
}

//=============================================================================
//�^�[�Q�b�g�̐ݒ�
//=============================================================================
//[input]
//	vTarget:�^�[�Q�b�g�̈ʒu
//=============================================================================
void CCamera::SetTargetPos( Math::Vector3D vTarget )
{
	m_vTarget = vTarget;
}

//=============================================================================
//�p���f�[�^�ݒ�	
//=============================================================================
//[input]
//	style:�p���f�[�^
//=============================================================================
void CCamera::SetStyle( Math::Style style )	
{
	m_Style = style;
}



