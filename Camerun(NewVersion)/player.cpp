//*============================================================================
//player.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "player.h"
#include <math.h>
#include "camera.h"
#include <fstream>
#include "SceneGameMain.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pName:�f�[�^��
//	vPos:�ʒu
//=============================================================================
CPlayer::CPlayer( const char *pName, Math::Vector3D vPos ) 
 :CCharacter( pName, vPos )
{
	m_IsDead = false;
	m_IsExistAnim = true;
	
	m_vScale.Set( 0.5f, 0.5f, 0.5f );
	
	m_vInitScale = m_vScale;
	
	m_Rot.x = DEG_TO_ANGLE( 0 );
	
	m_InitRot = m_Rot;
	
	m_fGravity = 0.0f;
	
	m_fAccel = 0.01f;
	
	m_fStSpeed = 0.001f;
	
	m_fMaxSpeed = 1.0f;
	
	m_eAnimState = ANIM_STANDBY;
	
	m_pCapedEnemy = NULL;
	
	m_IsJumpFlag = false;
	m_IsDead = false;
	m_IsCapture = false;
	m_eAnimState = ANIM_STANDBY;
	m_eState = STATE_NONE;
	
	m_RelCount = 0;
	
	
	m_pMinSpr = new CSprite( "mini_player.dds", Math::Vector2D( m_vPos.x, m_vPos.y ) );
	
}


//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
	SAFE_DELETE( m_pMinSpr );
}

//=============================================================================
//������
//=============================================================================
void CPlayer::Init()
{
	if( CSceneBase::GetTutorialFlag() )
	{
		m_vInitPos = Math::Vector3D( 46, 7, -16 );
	}
	
	else
	{
		m_vInitPos = Math::Vector3D( 0, 7, -70 );
	
	}

	m_vPos = m_vInitPos;
	
	
	m_vScale = m_vInitScale;
	
	m_IsJumpFlag = false;
	m_IsDead = false;
	m_IsCapture = false;
	m_eAnimState = ANIM_STANDBY;
	m_eState = STATE_NONE;
	
	m_Rot = m_InitRot;
	
	m_fGravity = 0.0f;
	
	m_RelCount = 0;
	
}

//============================================================================
//�t�@�C���ǂݍ���
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//	pFileMgr:�t�@�C���Ǘ��p�f�o�C�X
//===========================================================================
void CPlayer::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	CCharacter::Load( pRender, pFileMgr );
	
	m_pMinSpr->Load( pRender, pFileMgr );
}

	
//=============================================================================
//����
//=============================================================================
void CPlayer::Exec()
{
	if( m_IsCapture )
	{
		SetPosition( m_pCapedEnemy->GetCatchPos() );
	}
	
	for( int Anim = 0;Anim < ANIM_MAX;++Anim )
	{
		m_fAnimTime[Anim] += 0.5f;
		
		float fLast = m_pActorModel[m_ActorIndex]->GetAnimationLastTime( m_AnimID[Anim] );
		
		/*���Ԃ��Ō�܂œ��B*/
		while( m_fAnimTime[Anim] > fLast ) 
		{
			/*�ŏ��ɖ߂�*/
			m_fAnimTime[Anim] -= fLast;
		}
		
	}

	/*��Ԃ̏���*/
	StateExec();
	
	/*�ߊl����{�b�N�X�̐���*/
	CreateCapBox();
	
	CCharacter::Exec();
}


//=============================================================================
//�~�j�L�����̕\��
//=============================================================================
void CPlayer::ShowMiniChara()
{
	m_pMinSpr->Exec();
	
	m_pMinSpr->Rendering();
}

//=============================================================================
//�����_�����O
//=============================================================================
void CPlayer::Rendering()
{
	#if defined ( DEBUG ) | ( _DEBUG )
	
		Collision::CBox Box[] =
		{
			m_CapChkBox,
			m_ShootChkBox,
		};
		
		CColor Color[] =
		{
			CColor( 255, 255, 255 ),
			CColor( 255, 0, 0 ),
		};
		
		const int BOX_NUM = 2;//�{�b�N�X�̐�
		
		/*�f�o�b�O�p�̔��̕`��*/
		m_pLine3D->Begin();
		
		for( int i = 0;i < BOX_NUM;++i )
		{
			m_pLine3D->PushBox( Box[i], Color[i] );
		}
		
		m_pLine3D->End();
		
	#endif
		
	CCharacter::Rendering();
	
	
}


//=============================================================================
//�A�j���[�V�����p����
//=============================================================================
void CPlayer::AnimExec()
{
	
	//if( m_eAnimState == ANIM_STANDBY )
	//{
	//
	//}	
	//
	//else if( m_eAnimState == ANIM_CHANGESTART )
	//{
	//	m_fAnimTime[ANIM_NEXT] = 0.0f;
	//	m_fWeight = 0.0f;
	//	
	//	m_eAnimState = ANIM_CHANGE;
	//}
	//
	//else if( m_eAnimState == ANIM_CHANGE )
	//{
	//	UpdateAnimation();
	//}
	//
	
}

//=============================================================================
//��Ԗ��̏���
//=============================================================================
void CPlayer::StateExec()
{
	switch( m_eState )
	{
		/*�������ĂȂ����*/
		case STATE_NONE:
		{
			m_AnimID[ANIM_NOW] = ANIM_STAND;
			
			break;
		}
		
		/*�ߊl�J�n*/
		case STATE_CAPSTART:
		{
			static int count = 0;
			
			const int MAX_COUNT = 60 * 2;
			
			m_AnimID[ANIM_NOW] = ANIM_CAPMOVE;
			
			count++;
			
			//if( count < 60 )
			//{	
			//	m_vPos.y += 1.0f;
			//}
			//
			//else if( count > 60 )
			//{	
			//	m_vPos.x += ( m_pCapedEnemy->GetCatchPos().x - m_vPos.x ) * 0.01f;
			//}
			
			/*�u�[�X�g���̍Đ�*/
			
			
			m_vPos.x = Interpolation::Add( m_vCapedPos.x, m_pCapedEnemy->GetCatchPos().x, MAX_COUNT, count  );
			m_vPos.y = Interpolation::Sin( m_vCapedPos.y , m_pCapedEnemy->GetCatchPos().y + 5.0f, MAX_COUNT, count);
			//m_vPos.y = Interpolation::Neville( m_vCapedPos.y, m_vCapedPos.y + m_pCapedEnemy->GetCatchPos().y + 2.0, 
			//									 m_pCapedEnemy->GetCatchPos().y, count );

			m_vPos.z = Interpolation::Add( m_vCapedPos.z, m_pCapedEnemy->GetCatchPos().z, MAX_COUNT, count );
			m_Rot.y = Math::ATan2( m_vCapedPos.y, m_vCapedPos.z );
			//Interpolation::Flat( DEG_TO_ANGLE( 90 ), DEG_TO_ANGLE( -80 ), MAX_COUNT, count );
			
			//if( count < 30 )
			//{
			//	CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_BOOST );
			//}
			
			
			if( m_vPos.y < m_pCapedEnemy->GetCatchPos().y  && count > MAX_COUNT / 2 )
			{
				/*����������*/
				const float fSCALE = 0.3f;
				
				SetScale( Math::Vector3D( fSCALE, fSCALE, fSCALE ) );
				
				/*���ݕt�����̍Đ�*/
				CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_BITE );
				
				SetState( STATE_CAPTURE );
				
				m_IsCapture = true;
				
				count = 0;	
				
			}
			
			break;
		}
		
		/*�ߊl���̎�*/
		case STATE_CAPTURE:
		{
			
			m_AnimID[ANIM_NOW] = ANIM_CAPING;
				
			break;
		}
		
		/*����J�n*/
		case STATE_RELSTART:
		{
			m_AnimID[ANIM_NOW] = ANIM_CAPSTART;
			
			const Uint32 MAX_COUNT = 60 * 3;
			
			m_RelCount++;
			
			m_vPos.y = Interpolation::Sin( m_pCapedEnemy->GetPosition().y,
										   m_pCapedEnemy->GetPosition().y + 5.0f,
										   MAX_COUNT, m_RelCount );
			
			m_vPos.x = Interpolation::Flat( m_pCapedEnemy->GetPosition().x,
											 m_pCapedEnemy->GetPosition().x - m_vFront.x, MAX_COUNT, m_RelCount );
			
			m_vPos.z = Interpolation::Flat( m_pCapedEnemy->GetPosition().z, 
											m_pCapedEnemy->GetPosition().z - m_vFront.z, MAX_COUNT, m_RelCount );
			
			m_Rot.y = Interpolation::Flat( DEG_TO_ANGLE( -80 ), DEG_TO_ANGLE( 0 ), MAX_COUNT, m_RelCount );
			
			if( m_RelCount > MAX_COUNT )
			{
				m_eState = STATE_RELEASE;
				
				/*�X�P�[�������ɖ߂�*/
				SetScale( m_vInitScale );
				
				m_RelCount = 0;
			}
			
			
			break;
		}
		
		/*�����*/
		case STATE_RELEASE:
		{
			m_IsCapture = false;
			
			m_pCapedEnemy->SetCapdFlag( false );
	
			m_pCapedEnemy->SetState( CEnemy::STATE_RELEASE );
			
			m_eState = STATE_NONE;
		
			
			break;
		}
		
		/*�ړ����̎�*/
		case STATE_MOVING:
		{
			m_AnimID[ANIM_NOW] = ANIM_WALK;
			
			break;
		}
		
		
		
		/*��~��*/
		case STATE_STOP:
		{
			break;
		}
		
		/*�d�Ԃɓ��������Ƃ�*/
		case STATE_HIT_TRAIN:
		{
			static int count = 0;
			
			m_vPos.y += 1;
			
			if( ++count > 60 * 1 )
			{
				count = 0;
				m_eState = STATE_NONE;
			}
				
			break;
		}
		
		/*�G�ɓ��������Ƃ�*/
		case STATE_HIT_ENEMY:
		{
			static int count = 0;
			
			//m_fSpeed = 0.0f;

			m_vPos += GetFront() * 0.01f;
			
			if( ++count > 30 )
			{
				count = 0;
				m_eState = STATE_NONE;
			}
			
			break;
		}
		
		
	}
	
	
}

//==============================================================================
//�J�������[�h�̐؂�ւ�
//==============================================================================
//[input]
//	pSnd:�Đ�����T�E���h
//==============================================================================
void CPlayer::ChangeCameraMode( Sound::ISound *pSnd )
{
}

//=============================================================================
//�A�j���[�V�����̍X�V
//=============================================================================
void CPlayer::UpdateAnimation()
{
	if( m_AnimID[ANIM_NOW] != m_AnimID[ANIM_NEXT] )
	{
		/*��b�Ő؂�ւ���*/
		m_fWeight += 1.0f / 120.0f;
		
		if( m_fWeight >= 1.0f )
		{
			m_fWeight = 0.0f;
			m_fAnimTime[ANIM_NOW] = m_fAnimTime[ANIM_NEXT];
			m_AnimID[ANIM_NOW] = m_AnimID[ANIM_NEXT];
			m_eAnimState = ANIM_STANDBY;
		}
	}
}

//=============================================================================
//�A�j���[�V�����̐ݒ�
//=============================================================================
//[input]
//	animID:�ݒ肷��A�j���[�V����ID
//=============================================================================
void CPlayer::ChangeAnimation( int animID )
{
	m_AnimID[ANIM_NEXT] = animID;
}

//==============================================================================
//�n�ʕ␳(�v���C���[��Y���W�����ȉ��ɂȂ����Ƃ��������W�ɖ߂��Ă��)
//==============================================================================
void CPlayer::GroundAdjust()
{
	if( GetCaptureFlag() )
	{
		if( m_vPos.y <= -30.0f )
		{
			SetState( STATE_RELSTART );
			
			m_fGravity = 0.0f;
			m_vPos = m_vInitPos;
			
		}
	}
	
	else
	{
		if( m_vPos.y <= -30.0f )
		{
			m_fGravity = 0.0f;
			m_vPos = m_vInitPos;
		}
	}
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
bool CPlayer::Move( Selene::Math::Vector3D vTargetPos, CCamera *pCam, 
					CField *pField, bool IsShowMark )
{
	if( IsShowMark )
	{
		/*�J������������Ɉړ�*/
		
		m_vDirection.x = vTargetPos.x * pCam->GetRight().x + vTargetPos.y * (-pCam->GetFront().x);
		m_vDirection.y = 0.0f;
		m_vDirection.z = vTargetPos.x * pCam->GetRight().z + vTargetPos.y * (-pCam->GetFront().z);
		
		//
		
		
		float fLength = m_vDirection.Length();
		
		m_fSpeed = fLength * m_fStSpeed ;
		
		if( m_fSpeed > 2.0f )
		{
			m_fSpeed = 2.0f;
		}
		
		
		/*�ړ��`�F�b�N*/
		if( m_vDirection.Length() > 0.0f )
		{
			if( vTargetPos.Length() > 0.5f )
			{	
				m_Rot.x = toF( Math::ATan2( -m_vDirection.z, -m_vDirection.x ) );
			}
			
			/*���K��*/
			m_vDirection /= fLength;
			
			/*�ړ�(-1�̏ꍇ�͒ʂ��)*/
			if( MoveCheck( pField ) == -1 )
			{
				m_vPos += m_vDirection * m_fSpeed;
				//CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_PLAYERMOVE );
				return true;
			}
			
			else
			{
				m_fSpeed = 0.0f;
				
			}
			
		
		}
	}
		
	return false;
	
}

//==============================================================================
//�ړ�����(�c�[���p)
//==============================================================================
//[input]
//	pCam:�J�����f�o�C�X
//	pMouse:�}�E�X�f�o�C�X
//	pField:�t�B�[���h
//	pSceneMgr:�V�[���Ǘ��f�o�C�X
//==============================================================================
void CPlayer::Move( CCamera *pCam, Peripheral::IMouse *pMouse, CField *pField, Scene::ISceneManager *pSceneMgr )
{
	
	Collision::CLine3D vRay( 
			pSceneMgr->TransformFromScreen( Math::Vector3D(toF(pMouse->GetPosX()), toF(pMouse->GetPosY()), 0.0f) ),
			pSceneMgr->TransformFromScreen( Math::Vector3D(toF(pMouse->GetPosX()), toF(pMouse->GetPosY()), 1.0f) ) );
			
		
	Renderer::SCollisionResult Ret;
	
	if( pField->GetMapActor( SCREEN_MAIN )->HitCheckByRay( vRay, Ret ) )
	{
		m_vTarget = Ret.vHitPosition;
	}
				
	
	m_vDirection.x = m_vTarget.x - m_vPos.x;
	m_vDirection.y = 0.0f;
	m_vDirection.z = m_vTarget.z - m_vPos.z;
	
	m_fSpeed = 0.3f ;
	
	/*�ړ��`�F�b�N*/
	if( m_vDirection.LengthSq() > 0.0f )
	{
		m_Rot.x = toF( Math::ATan2( m_vDirection.z, m_vDirection.x ) );
		
		float fLength = m_vDirection.Length();
		
		/*���K��*/
		m_vDirection /= fLength;
		
		if( pMouse->GetClickL() )
		{	
			m_vPos += m_vDirection * m_fSpeed;
		}
	}
		
	
	
}

//==============================================================================
//�ړ��ʒu�̐ݒ�
//==============================================================================
//[input]
//	pMouse:�}�E�X�p�f�o�C�X
//	pEnemy:�G�N���X
//	pSceneMgr:�V�[���Ǘ��f�o�C�X
//==============================================================================
void CPlayer::SetTargetPos( Selene::Peripheral::IMouse *pMouse, CEnemy *pEnemy, Scene::ISceneManager *pSceneMgr )
{
	Collision::CLine3D vRay( 
			pSceneMgr->TransformFromScreen( Math::Vector3D(toF(pMouse->GetPosX()), toF(pMouse->GetPosY()), 0.0f) ),
			pSceneMgr->TransformFromScreen( Math::Vector3D(toF(pMouse->GetPosX()), toF(pMouse->GetPosY()), 1.0f) ) );
	
	
	/*���N���b�N�ŏ��ڂ�*/
	if( pMouse->GetStateL() == MOUSE_PUSH && pEnemy->GetModelActor( SCREEN_MAIN )->Collision_Check( vRay ))
	{
				
		/*�ߊl�t���O��ݒ�*/
		pEnemy->SetCapdFlag( true );
		
		/*�ߊl�ʒu���o�b�N�A�b�v*/
		pEnemy->SetCatchBeforePos( pEnemy->GetPosition() );
		
		m_vCapedPos = m_vPos;
		
		/*��Ԃ�ߊl��Ԃɂ���*/
		SetState( STATE_CAPSTART );
				
		/*�ߊl�����G����*/
		m_pCapedEnemy = pEnemy;
		
	}	
}

//==============================================================================
//�ߊl���Ă����G�̉��
//==============================================================================
void CPlayer::ReleaseEnemy()
{
	SetState( CPlayer::STATE_RELSTART );
		
}

//==============================================================================
//�ߊl����{�b�N�X�̐���
//==============================================================================
void CPlayer::CreateCapBox()
{
	Math::Matrix matTemp;
	Math::Matrix matWorld;
	
	/*������*/
	matTemp.Identity();
	matWorld.Identity();
	
	/*��]*/
	matTemp.RotationY( toI( m_Rot.x - DEG_TO_ANGLE( 180 ) ) );
	
	matWorld *= matTemp;
	
	/*�ړ�*/
	matTemp.Translation( m_vPos.x, m_vPos.y, m_vPos.z );
	
	matWorld *= matTemp;
	
	/*�{�b�N�X�̐���*/
	m_CapChkBox.CreateBox( Math::Vector3D( -2, 0, 0 ), Math::Vector3D( 2, 5, 30 ), matWorld );
	

}

//==============================================================================
//�ߊl����{�b�N�X�̐���
//==============================================================================
//[input]
//	pCam:�J�����N���X
//==============================================================================
void CPlayer::CreateShootBox( CCamera *pCam, CSceneManager *pSceneMgr )
{
	Math::Matrix matTemp;
	Math::Matrix matWorld;
	
	/*������*/
	matTemp.Identity();
	matWorld.Identity();
	
	//matWorld = pCam->GetCamera()->WorldToView();
	
	//GetModelActor( 0 )->Collision_Check(
	
	//matWorld = pCam->GetCamera()->WorldToView();
	
	///*X����]*/
	matTemp.RotationX( toI( pCam->GetRotate().x ) );
	//
	matWorld *= matTemp;
	//
	///*Y����]*/
	matTemp.RotationY( toI( m_Rot.x - DEG_TO_ANGLE( 180 ) ) );
	
	matWorld *= matTemp;
	
	/*�ړ�*/
	matTemp.Translation( m_vPos.x, m_vPos.y, m_vPos.z );
	
	matWorld *= matTemp;
	
	//Math::Vector3D vPt1 = pSceneMgr->GetSceneMgr()->TransformFromScreen( Math::Vector3D( 0, 0, 0 ) );
	//Math::Vector3D vPt2 = pSceneMgr->GetSceneMgr()->TransformFromScreen( Math::Vector3D( SCREEN_WIDTH, SCREEN_HEIGHT, 2.0f ) );
	
	/*�{�b�N�X�̐���*/
	//m_ShootChkBox.
//	m_ShootChkBox.CreateBox( vPt1, vPt2, matWorld );
}


//==============================================================================
//�ʐ^�B�e����p���C�̐���
//==============================================================================
//[input]
//	pMouse:�}�E�X�f�o�C�X
//	pSceneMgr:�V�[���Ǘ��f�o�C�X
//==============================================================================
void CPlayer::CreateShootRay( Scene::ISceneManager *pSceneMgr )
{
	Math::Vector3D vPt0( toF( SCREEN_WIDTH / 2 ), toF( SCREEN_HEIGHT / 2 ), 0.0f );
	Math::Vector3D vPt1( vPt0.x, vPt0.y, 1.0f );
	
	m_ShootChkRay.vStart = pSceneMgr->TransformFromScreen( vPt0 );
	m_ShootChkRay.vEnd = pSceneMgr->TransformFromScreen( vPt1 );
}


//==============================================================================
//�n�ʃ`�F�b�N
//==============================================================================
//[input]
//	pField:�`�F�b�N����}�b�v
//[return]
//	�n�ʂɏՓ˕�����������
//==============================================================================
bool CPlayer::GroundCheck( CField *pField )
{
	Renderer::SCollisionResultExtend RetEx;
	Collision::CLine3D vRay;
	
	const float GRAVITY = 0.01f;
	
	//------------------------------------------------
	// �d�͉����x
	//------------------------------------------------
	m_fGravity += GRAVITY;
	
	if ( m_fGravity > 1.0f )
	{
		// ���l�ȏ�ɂ��Ȃ��i�Q�[���I���o�j
		m_fGravity = 1.0f;
		
	}
	

	//------------------------------------------------
	// �L�����̎��R����
	//------------------------------------------------
	#if defined(DEBUG_MAP_EDIT)
	
	#else
		m_vPos.y -= m_fGravity;
	#endif
	
	//------------------------------------------------
	// �����Ɋւ��Ẵ}�b�v�ƃR���W���������
	//  �L�����̍��t�߂��瑫���փ��C���΂��Ĕ��肷��B
	//------------------------------------------------
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,1.2f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pField->GetMapActor(m_ActorIndex)->HitCheckByRay( vRay, RetEx ) )
	{
		if( m_IsJumpFlag )
		{
			m_IsJumpFlag = false;

			CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_GETDOWN );
		}
		
		if( RetEx.Attribute == 0 || RetEx.Attribute == 2 )
		{
			// �Փˈʒu�Ɉړ�
			m_vPos = RetEx.vHitPosition;
			// �d�͉���������
			m_fGravity = 0.0f;
		}
		
		else if( RetEx.Attribute == 6 )
		{
			if( m_vPos.y < -10.0f )
			{
				m_vPos = Math::Vector3D( -104.8f, 0.0f, -415.0f );
				
				// �d�͉���������
				m_fGravity = 0.0f;

			}
		}

		return true;
	}
	
	else
	{
		if( m_vPos.y >= RetEx.vHitPosition.y + 0.5 )
		{
			m_IsJumpFlag = true;
		}
		
	}
	
	return false;

}

//==============================================================================
//�n�ʃ`�F�b�N
//==============================================================================
//[input]
//	
//[return]
//	�n�ʂɏՓ˕�����������
//==============================================================================
bool CPlayer::GroundCheck( CCharacter *pChara )
{
	Renderer::SCollisionResultExtend RetEx;
	Collision::CLine3D vRay;
	
	const float GRAVITY = 0.01f;
	
	//------------------------------------------------
	// �d�͉����x
	//------------------------------------------------
	m_fGravity += GRAVITY;
	
	if ( m_fGravity > 1.0f )
	{
		// ���l�ȏ�ɂ��Ȃ��i�Q�[���I���o�j
		m_fGravity = 1.0f;
		
	}
	
	//------------------------------------------------
	// �L�����̎��R����
	//------------------------------------------------
	#if defined(DEBUG_MAP_EDIT)
	
	#else
		m_vPos.y -= m_fGravity;
	#endif
	
	//------------------------------------------------
	// �����Ɋւ��Ẵ}�b�v�ƃR���W���������
	//  �L�����̍��t�߂��瑫���փ��C���΂��Ĕ��肷��B
	//------------------------------------------------
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,1.2f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay, RetEx ) )
	{
		if( m_IsJumpFlag )
		{
			m_IsJumpFlag = false;

			if( !GetCaptureFlag() )
			{	
				CCommonObject::GetSoundMgr()->Play( CSoundManager::SND_GETDOWN );
			}
		}
		
		// �Փˈʒu�Ɉړ�
		m_vPos = RetEx.vHitPosition;
		// �d�͉���������
		m_fGravity = 0.0f;

		return true;
	}
	
	else
	{
		if( m_vPos.y >= RetEx.vHitPosition.y + 0.5 )
		{
			m_IsJumpFlag = true;
		}
		
	}
	
	return false;

}


//==============================================================================
//�ړ��␳
//==============================================================================
void CPlayer::MoveAdjust()
{
	if( m_vPos.x <= -359 )
	{
		m_vPos.x = -359;
	}
	
	if( m_vPos.x >= 359 )
	{
		m_vPos.x = 359;
	}
	
	if( m_vPos.z >= 0 )
	{
		m_vPos.z = 0;
	}
	
	if( m_vPos.z <= -528 )
	{
		if( m_IsDead )
		{
			
		}
		
		else
		{	
			m_vPos.z = -528;
		}	
			
	}
}



	
