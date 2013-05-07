//*============================================================================
//character.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "character.h"
#include "SceneManager.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pName:�f�[�^��
//	vPos:�ݒ肷����W
//=============================================================================
CCharacter::CCharacter( const char *pName, Math::Vector3D vPos ) 
:m_pModel(NULL),
 m_pLine3D(NULL),
 m_IsMoving( false ),
 CDraw3DObject( pName, vPos )
{
	//std::fill( m_pActorModel, m_pActorModel, 0 ); 
	//std::fill( m_pActorLine,  m_pActorLine + SCREEN_MAX, NULL ); 
	
	
	//memset( m_pActorModel, NULL, SCREEN_MAX );
	//memset( m_pActorLine, NULL, sizeof( Scene::IPrimitiveActor ) * SCREEN_MAX );
	
	for( int numActor = 0;numActor < SCREEN_MAX;++numActor )
	{
		m_pActorModel[numActor] = NULL;
		m_pActorLine[numActor] = NULL;
	}
	
	m_vDirection.Set( 0.0f, 0.0f, 0.0f );
	
	m_fSpeed = 0.0f;
	
	m_fStSpeed = 0.0001f;
	
	m_fWeight = 0.0f;
	
	m_fGravity = 0.0f;
	
	m_IsExistAnim = false;
	
	m_IsFly = false;
	
	//memset( m_fAnimTime, 1.0f, sizeof( float ) * ANIM_MAX );
	memset( m_AnimID, 0, sizeof( int ) * ANIM_MAX );
	
	for( int Anim = 0;Anim < ANIM_MAX;++Anim )
	{
		m_fAnimTime[Anim] = 1.0f;
	//	m_AnimID[Anim] = 0;
	} 
	//
	m_eAnimState = ANIM_STANDBY;
	
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CCharacter::~CCharacter()
{
	printf( "%s:�f�X�g���N�^",  m_strFileName.c_str() );
	
	for( int numActor = 0;numActor < SCREEN_MAX;++numActor )
	{
		SAFE_RELEASE( m_pActorLine[numActor] );
		
		SAFE_RELEASE( m_pActorModel[numActor] ); 
	}
	
	SAFE_RELEASE( m_pLine3D );
	
	SAFE_RELEASE( m_pModel );
	
}

//=============================================================================
//������
//=============================================================================
void CCharacter::Init()
{
	CDrawObject::Init();
}

//=============================================================================
//����
//=============================================================================
void CCharacter::Exec()
{
	SetActorSetting();
}

//=============================================================================
//�A�N�^�[�ݒ�̃Z�b�g
//=============================================================================
void CCharacter::SetActorSetting()
{
	/*�p���̃��Z�b�g*/
	m_pActorModel[m_ActorIndex]->TransformReset();
	
	/*X������ɉ�]*/
	m_pActorModel[m_ActorIndex]->RotationX( m_Rot.y );
	
	/*Y������ɉ�]*/
	m_pActorModel[m_ActorIndex]->RotationY( m_Rot.x );
	
	/*�g��k��*/
	m_pActorModel[m_ActorIndex]->Scaling( m_vScale.x, m_vScale.y, m_vScale.z );
	
	/*�ړ�*/
	m_pActorModel[m_ActorIndex]->Translation( m_vPos );
	
	if( m_IsExistAnim )
	{
		// �L�����ɑ΂��ăA�j���[�V�������X�V
		m_pActorModel[m_ActorIndex]->UpdateAnimation( m_AnimID[ANIM_NOW], m_fAnimTime[ANIM_NOW] );
	}
	
	/*���ʃx�N�g���̎擾*/
	m_pActorModel[m_ActorIndex]->GetFront( m_vFront );
	
	/*�E�ʃx�N�g���̎擾*/
	m_pActorModel[m_ActorIndex]->GetRight( m_vRight );
	
	/*�p���̍X�V*/
	m_pActorModel[m_ActorIndex]->TransformUpdate();
	
}

//=============================================================================
//�����_�����O
//=============================================================================
void CCharacter::Rendering( )
{
	if( m_IsVisible )
	{
		m_pActorModel[m_ActorIndex]->RenderingRequest();
		
		#if defined ( DEBUG ) | ( _DEBUG )
		
			m_pActorLine[m_ActorIndex]->RenderingRequest();
		
		#endif 
	}
}

//============================================================================
//�t�@�C���ǂݍ���
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//	pFileMgr:�t�@�C���Ǘ��p�f�o�C�X
//===========================================================================
void CCharacter::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	printf("LOAD MODEL[%s]", m_strFileName.c_str() );
	
	pFileMgr->SetCurrentPath("Model");
	
	m_pModel = pRender->CreateModelFromFile( m_strFileName.c_str() );
	
	printf( "                 : -> %s\n", m_pModel->IsInvalid() ? "Failed" : "Succeeded" );
	
	#if defined ( DEBUG ) | ( _DEBUG )
	
		/*3D���C���̐���*/
		m_pLine3D = pRender->CreateLine3D( 10000, true );
	
	#endif
	
	//�A�N�^�[�̐���
	for( int i = 0;i < SCREEN_MAX;++i )
	{
		CreateActor( i, CCommonObject::GetSceneMgr( i )->GetSceneMgr() );
	}
	
}

//==============================================================================
//�A�N�^�[�̐���
//==============================================================================
//[input]
//	index:��������A�N�^�[�C���f�b�N�X
//	pSceneMgr:�V�[���Ǘ��f�o�C�X
//==============================================================================
void CCharacter::CreateActor( int index, Scene::ISceneManager *pSceneMgr )
{
	if( m_pModel != NULL )
	{
		m_pActorModel[index] = pSceneMgr->CreateActor( m_pModel );
		
		//�R���W�����̐���
		CreateCollision( index );
	}
	
	#if defined ( DEBUG ) | ( _DEBUG )
	
		m_pActorLine[index] = pSceneMgr->CreateActor( m_pLine3D );
	
	#endif
}

//==============================================================================
//���̕`��
//==============================================================================
//[input]
//	index:��������A�N�^�[�C���f�b�N�X
//	pSceneMgr:�V�[���Ǘ��f�o�C�X
//==============================================================================
void CCharacter::DrawBox( Collision::CBox Box[], int num )
{
	#if defined ( _DEBUG ) | ( _DEBUG )
		
		/*���C���`��J�n*/
		m_pLine3D->Begin();
		
		/*�f�o�b�O�{�b�N�X�̒ǉ�*/
		for( int i = 0;i < num;++i )
		{
			m_pLine3D->PushBox( Box[i], CColor( 255, 255, 255 ) );
		}
		
		/*�����蔻��̕`��*/
		m_pActorModel[SCREEN_MAIN]->Collision_Rendering( m_pLine3D );
	
		/*���C���`��I��*/
		m_pLine3D->End();
		
	#endif
		
}

//=============================================================================
//�R���W�����f�[�^�̍쐬
//=============================================================================
//[input]
//	index:�ݒ肷��C���f�b�N�X
//=============================================================================
void CCharacter::CreateCollision( int index )
{
	GetModelActor( index )->Collision_Create();
}

//=============================================================================
//�Q�ƃJ�E���^�̑���
//=============================================================================
void CCharacter::AddRef()
{
	m_pModel->AddRef();
	
	for( int actornum = 0;actornum < SCREEN_MAX;++actornum )
	{
		m_pActorModel[actornum]->AddRef();
	}	
}

//=============================================================================
//�A�N�^�[�C���f�b�N�X�̃Z�b�g
//=============================================================================
//[input]
//	index:�ݒ肷��C���f�b�N�X
//=============================================================================
void CCharacter::SetActorIndex( int index )
{
	m_ActorIndex = index;
}

//==============================================================================
//�����`�F�b�N
//==============================================================================
//[input]
//	pChara:�`�F�b�N����L�����N�^�[
//[return]
//	����
//==============================================================================
float CCharacter::CheckDistance( CCharacter *pChara )
{
	Math::Vector3D vDirection = pChara->GetPosition() - m_vPos;
	
	return vDirection.Length();
	
}

//==============================================================================
//�ړ�����
//==============================================================================
//[input]
//	vTargetPos:�Ώۈʒu
//	pCam:�J�����f�o�C�X
//	pField:�`�F�b�N����}�b�v
//==============================================================================
bool CCharacter::Move( Selene::Math::Vector3D vTargetPos, CCamera *pCam, CField *pField )
{
	m_vDirection.x = vTargetPos.x * pCam->GetRight().x + vTargetPos.y * (-pCam->GetFront().x);
	m_vDirection.y = 0.0f;
	m_vDirection.z = vTargetPos.x * pCam->GetRight().z + vTargetPos.y * (-pCam->GetFront().z);
	
	m_Rot.x = Math::ATan2( -m_vDirection.z, -m_vDirection.x );
	
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
		if( MoveCheck( pField ) == -1 )
		{
			m_vPos += m_vDirection * m_fSpeed;
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


//==============================================================================
//�ړ��`�F�b�N
//==============================================================================
//[input]
//	pChara:�`�F�b�N����L����
//[return]
//	�ړ���ɏ�Q�������邩
//==============================================================================
bool CCharacter::MoveCheck( CCharacter *pChara )
{
	Renderer::SCollisionResultExtend RetEx;
	Renderer::SCollisionResult Ret;
	Collision::CLine3D vRay[6];
	
	Collision::CBox Box;
	
	Math::Vector3D vCharaFront(0, 0, 0);
	Math::Vector3D vCharaRight;
	
	this->GetModelActor(SCREEN_MAIN)->GetFront( vCharaFront );
	m_pActorModel[SCREEN_MAIN]->GetRight( vCharaRight );
	
	
	//if ( m_vDirection.LengthSq() > 0.0f )
	//{
		// �ړ���
		m_vDirection *= m_fSpeed;
		
		//------------------------------------------------
		// �ړ��Ɋւ��Ẵ}�b�v�ƃR���W���������
		//  �L�����̍��t�߂��瑫���փ��C���΂��Ĕ��肷��B
		//------------------------------------------------
		// �R���W���������΍�Ń��[�v
		Math::Vector3D vMove = m_vDirection;
		Math::Vector3D vPos = m_vPos;
		Sint32 Limit = 10;
		
		vRay[0].vStart = Math::Vector3D( 0.0f,0.8f, 0.0f ) + m_vPos + vCharaFront * 0.2f;
		vRay[0].vEnd   = vRay[0].vStart + vMove;
		
		vRay[1].vStart = vRay[0].vStart ;
		vRay[1].vEnd   = vRay[0].vStart + vMove + vCharaRight * 0.2f;
		
		vRay[2].vStart = vRay[0].vStart ;
		vRay[2].vEnd   = vRay[2].vStart + vMove - vCharaRight * 0.2f;
		
		vRay[3].vStart = Math::Vector3D( 0.0f,0.8f, 0.0f ) + m_vPos + vCharaFront * 0.1f;
		vRay[3].vEnd   = vRay[3].vStart + vMove;
		
		vRay[4].vStart = vRay[3].vStart;
		vRay[4].vEnd   = vRay[4].vStart + vMove + vCharaRight * 0.1f;
		
		vRay[5].vStart = vRay[3].vStart;
		vRay[5].vEnd   = vRay[5].vStart + vMove - vCharaRight * 0.1f;
		
		
		
		//for ( ; ; )
		//{
				
			if( pChara->GetVisibleFlag() )
			{
			
				if ( pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[0], RetEx ) || 
					 pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[1], RetEx ) || 
					 pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[2], RetEx ) ||
					 pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[3], RetEx ) ||
					 pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[4], RetEx ) ||
					 pChara->GetModelActor(m_ActorIndex)->HitCheckByRay( vRay[5], RetEx )  )
				{
					// �Փˈʒu�Ɉړ�
					Math::Vector3D RetPos = RetEx.vSlidePosition + (RetEx.vNormal * 0.03f);
					vMove = RetPos - vPos;
					vMove.y = 0.0f;
					//vMove.Set( 0.0, 0.0, 0.0 );
					m_fSpeed = 0.1f;
					
					return true;				
				}
				
				else
				{
					// �ړ�
					m_vPos += vMove;
						//IsHit = false;
					
				}
			
				
				//if ( this->GetModelActor(SCREEN_MAIN)->Collision_Check( pChara->GetModelActor(SCREEN_MAIN) )  )
				//{
				//	//m_fSpeed = 0.0f;
				//	//
				//	//m_vDirection.Set( 0, 0, 0 );
				//	//
				//	m_vPos = (pChara->GetPosition() - m_vPos);
				//	
				//	
				//	vMove.Set( 0.0, 0.0, 0.0 );
				//	
				//	return true;				
				//}
				//
				//else
				//{
				//	m_vPos += vMove;
				//		
				//	break;
				//	
				//}
			}
			
			//// ���E���˔j
			//if ( --Limit ==  0 )
			//{
			//	// �ǂ�����Ă����܂�̂ňړ������ɒE�o
			//	break;
			//}
		
	//}
	
	
	return false;
}


//==============================================================================
//�ړ��`�F�b�N
//==============================================================================
//[input]
//	pField:�`�F�b�N����}�b�v
//[return]
//	�ړ���̕Ǒ���
//==============================================================================
Bool CCharacter::MoveCheck( CField *pField )
{
	Renderer::SCollisionResult RetEx;
	Collision::CLine3D vRay[6];
	
	//------------------------------------------------
	// �ړ��Ɋւ��Ẵ}�b�v�ƃR���W���������
	//  �L�����̍��t�߂��瑫���փ��C���΂��Ĕ��肷��B
	//------------------------------------------------

	Math::Vector3D vMove = m_vDirection;
	Math::Vector3D vPos = m_vPos;
	
	vRay[0].vStart = Math::Vector3D( 0.0f,0.8f, 0.0f ) + m_vPos + m_vFront * 0.2f;
	vRay[0].vEnd   = vRay[0].vStart + vMove;
	
	vRay[1].vStart = vRay[0].vStart ;
	vRay[1].vEnd   = vRay[0].vStart + vMove + m_vRight * 0.2f;
	
	vRay[2].vStart = vRay[0].vStart ;
	vRay[2].vEnd   = vRay[2].vStart + vMove - m_vRight * 0.2f;
	
	vRay[3].vStart = Math::Vector3D( 0.0f,0.8f, 0.0f ) + m_vPos + m_vFront * 0.1f;
	vRay[3].vEnd   = vRay[3].vStart + vMove;
	
	vRay[4].vStart = vRay[3].vStart;
	vRay[4].vEnd   = vRay[4].vStart + vMove + m_vRight * 0.1f;
	
	vRay[5].vStart = vRay[3].vStart;
	vRay[5].vEnd   = vRay[5].vStart + vMove - m_vRight * 0.1f;
	
	/*���C���΂��āA�������Ă��邩����*/
	if ( pField->GetMapActor(SCREEN_MAIN)->HitCheckByRay( vRay[0], RetEx ) || 
		 pField->GetMapActor(SCREEN_MAIN)->HitCheckByRay( vRay[1], RetEx ) || 
		 pField->GetMapActor(SCREEN_MAIN)->HitCheckByRay( vRay[2], RetEx ) ||
		 pField->GetMapActor(SCREEN_MAIN)->HitCheckByRay( vRay[3], RetEx ) ||
		 pField->GetMapActor(SCREEN_MAIN)->HitCheckByRay( vRay[4], RetEx ) ||
		 pField->GetMapActor(SCREEN_MAIN)->HitCheckByRay( vRay[5], RetEx )  )
	{
		return RetEx.Attribute;				
	}
	
	return -1;
}



//==============================================================================
//�n�ʃ`�F�b�N
//==============================================================================
//[input]
//	pChara:���肷��L�����N�^�[
//[return]
//	�n�ʂɏՓ˕�����������
//==============================================================================
bool CCharacter::GroundCheck( CCharacter *pChara )
{
	Renderer::SCollisionResult Ret;
	Collision::CLine3D vRay;
	
	//------------------------------------------------
	// �d�͉����x
	//------------------------------------------------
	//m_fGravity += GRAVITY;
	//
	//if ( m_fGravity > 1.0f )
	//{
	//	// ���l�ȏ�ɂ��Ȃ��i�Q�[���I���o�j
	//	m_fGravity = 1.0f;
	//}

	//------------------------------------------------
	// �L�����̎��R����
	//------------------------------------------------
	//m_vPos.y -= m_fGravity;

	//------------------------------------------------
	// �����Ɋւ��Ẵ}�b�v�ƃR���W���������
	//  �L�����̍��t�߂��瑫���փ��C���΂��Ĕ��肷��B
	//------------------------------------------------
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,5.0f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pChara->GetModelActor(SCREEN_MAIN)->HitCheckByRay( vRay, Ret ) )
	{
		if( Ret.Attribute == 2 )
		{
			// �Փˈʒu�Ɉړ�
			m_vPos = Ret.vHitPosition;
			
			m_vPos.z -= pChara->GetSpeed() * 2;
		
		
		//m_vDirection += pChara->GetSpeed();
		// �d�͉���������
		
			return true;
		}
	}
	
	return false;

}

//==============================================================================
//�n�ʃ`�F�b�N
//==============================================================================
//[input]
//	pActor:�`�F�b�N����}�b�v�A�N�^�[
//[return]
//	�n�ʂɏՓ˕�����������
//==============================================================================
bool CCharacter::GroundCheck( CField *pField )
{
	Renderer::SCollisionResultExtend RetEx;
	Collision::CLine3D vRay;
	
	const float GRAVITY = 0.01f;
	
	//------------------------------------------------
	// �d�͉����x
	//------------------------------------------------
	if( !m_IsFly )
	{
		m_fGravity += GRAVITY;
		
		if ( m_fGravity > 0.7f )
		{
			// ���l�ȏ�ɂ��Ȃ��i�Q�[���I���o�j
			m_fGravity = 0.7f;
			
		}
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
	vRay.vStart = m_vPos + Math::Vector3D(0.0f,1.5f,0.0f);
	vRay.vEnd   = m_vPos;
	
	if ( pField->GetMapActor(m_ActorIndex)->HitCheckByRay( vRay, RetEx ) )
	{
		if( RetEx.Attribute == 0 || RetEx.Attribute == 2 )
		{
			 //�Փˈʒu�Ɉړ�
			m_vPos = RetEx.vHitPosition;
			 //�d�͉���������
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
	
	return false;

}

//==============================================================================
//�����蔻��
//==============================================================================
//[input]
//	pChara:���肷��L�����N�^�[
//[return]
//	�L�����ɏՓ˂�����
//==============================================================================
bool CCharacter::HitCheck( CCharacter *pChara )
{
	if( this->GetModelActor(SCREEN_MAIN)->Collision_Check( pChara->GetModelActor( SCREEN_MAIN ) )
		&& GetVisibleFlag() )
	{
		return true;
	}
	
	return false;

}

//==============================================================================
//�����蔻��
//==============================================================================
//[input/output]
//	ppChara:���肷��L�����N�^�[
//[return]
//	�L�����ɏՓ˂�����
//==============================================================================
bool CCharacter::HitCheck( CDraw3DObject **ppChara )
{
	CCharacter *obj = dynamic_cast<CCharacter *>( *ppChara );
	
	if( this->GetModelActor(SCREEN_MAIN)->Collision_Check( obj->GetModelActor( SCREEN_MAIN ) ) )
	{
		return true;
	}
	
	return false;

}

//==============================================================================
//�����蔻��
//==============================================================================
//[input]
//	vRay:����p�̃��C
//[return]
//	�L�����ɏՓ˂�����
//==============================================================================
bool CCharacter::HitCheck( Selene::Collision::CLine3D &vRay )
{
	if( this->GetModelActor(SCREEN_MAIN)->HitCheckByRay( vRay ) )
	{
		return true;
	}	
	
	return false;
}

//==============================================================================
//�����蔻��
//==============================================================================
//[input]
//	vRay:����p�̃��C
//	Out:�Փˌ��ʊi�[�p
//[return]
//	�L�����ɏՓ˂�����
//==============================================================================
bool CCharacter::HitCheck( Selene::Collision::CLine3D &vRay, Renderer::SCollisionResult &Out )
{
	if( this->GetModelActor(SCREEN_MAIN)->HitCheckByRay( vRay, Out ) )
	{
		return true;
	}	
	
	return false;
}

//==============================================================================
//�A���t�@�l�̐ݒ�
//==============================================================================
//[input]
//	alpha:�ݒ肷��A���t�@�l
//==============================================================================
void CCharacter::SetAlphaColor( Sint32 alpha )
{
	Sint32 meshcount = m_pActorModel[m_ActorIndex]->GetMeshCount();
	
	for( int i = 0;i < meshcount;++i )
	{
		Sint32 mtrlcount = m_pActorModel[m_ActorIndex]->GetMeshMaterialCount( i );
		
		for( int j = 0;j < mtrlcount;++j )
		{
			m_pActorModel[m_ActorIndex]->MeshMaterial_SetDrawType( i, j, DRAW_TYPE_ADD );
			
			m_pActorModel[m_ActorIndex]->MeshMaterial_SetEmissiveColor( i, j, Math::Vector4D( 255, 255, 255, alpha ) );
		}
	}
}



