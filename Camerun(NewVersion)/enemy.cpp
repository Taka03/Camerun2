//*=============================================================================
//enemy.cpp
//*=============================================================================


//==============================================================================
//include
//==============================================================================
#include "enemy.h"
#include "player.h"
#include "FileLoader.h"

//==============================================================================
//namespace
//==============================================================================
using namespace std;

namespace
{
	Math::Vector3D vOldPos;//�ʒu�̕ۑ�
	
	int RootCount = 0;//���[�g���̃J�E���g
	
	int RootSpeed = 1;//���[�g�̃X�s�[�h
	
	Math::Vector3D vHitPos( 0, 0, 0 );//�ʐ^����ʒu
	
}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pName:�f�[�^��
//	vPos:�ݒ肷����W
//	pResFile:���\�[�X�t�@�C��
//=============================================================================
CEnemy::CEnemy( const char *pName, Math::Vector3D vPos, File::IResourceFile *pResFile ) 
:CCharacter( pName, vPos ),
 m_pCatchSpr3D(NULL),
 m_pAnimX(NULL),
 m_pAnimZ(NULL),
 m_eState(STATE_NONE)
 
{
	CFileLoader FileLoader;
	
	m_fKeyTime = 0.0f;
	m_IsExistAnim = true;
	m_IsHitWall = false;
	m_IsCatchable = true;
	m_IsEndPhoto = false;
	
	m_vNextPoint.Set( 0, 0, 0 );
	
	m_RootCount = 0;
	m_RootSpeed = 1;
	
	
	m_pCatchSpr3D = new CSprite3D( "catch.png", m_vPos );
	m_pPntFontSpr3D = new CFontSprite3D("NumFont.sff", m_vPos );
	m_pLockOnSpr3D = new CSprite3D( "pointa.bmp", m_vPos );
	m_pMinSpr = new CSprite( "mini_enemy.png", Math::Vector2D( m_vPos.x, m_vPos.y ) );

	m_IsCaptured = false;
	m_vCatchPos.Set( 0.0f, 0.0f, 0.0f );
	m_vCatchBefPos.Set( 0, 0, 0 );
	
	string FileName = pResFile->GetNamePointer();
	
	/*�ݒ�t�@�C���̓ǂݍ���*/
	FileLoader.Load( FileName );
	
	SAFE_RELEASE( pResFile );
	
	vector<string> list = FileLoader.GetStrList();
	vector<string>::iterator it = list.begin();
	
	m_fStSpeed = atof( list.at(0).c_str() );
	m_PhotoPoint = atoi( list.at(1).c_str() );
	
	/*���\�[�X�̓ǂݍ���*/
	for( it = list.begin() + 2;it != list.end();++it )
	{	
		vector<string> strSource = FileLoader.SplitString( *it, "," );
		
		Math::Vector3D vPos;
		
		vPos.x = atof( strSource[0].c_str() );
		vPos.y = m_vPos.y;
		vPos.z = atof( strSource[1].c_str() );
		
		m_vecKey.push_back( vPos );
	}
	
	
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
	SAFE_DELETE( m_pCatchSpr3D );
	SAFE_DELETE( m_pLockOnSpr3D );
	SAFE_DELETE( m_pPntFontSpr3D );
	SAFE_DELETE( m_pMinSpr );

}

//============================================================================
//�t�@�C���ǂݍ���
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//	pFileMgr:�t�@�C���Ǘ��p�f�o�C�X
//===========================================================================
void CEnemy::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr ) 
{
	CCharacter::Load( pRender, pFileMgr );
	
	m_pCatchSpr3D->Load( pRender, pFileMgr );
	
	m_pPntFontSpr3D->Load( pRender, pFileMgr );
	
	m_pLockOnSpr3D->Load( pRender, pFileMgr );
	
	m_pMinSpr->Load( pRender, pFileMgr );

}


//=============================================================================
//������
//=============================================================================
void CEnemy::Init()
{
	CCharacter::Init();
	
	m_IsCaptured = false;
	m_IsEndPhoto = false;
	m_IsLockOn = false;
	
	m_fKeyTime = 0.0f;
	
	m_RootCount = 0;
	
	m_ReleaseCnt = 0;
	
}


//=============================================================================
//�����_�����O
//=============================================================================
void CEnemy::Rendering()
{
	/*��Ԗ��̏���*/
	StateExec();
	
	/*�����_�����O*/
	CCharacter::Rendering();
	
	if( m_IsCaptured )
	{
		m_pCatchSpr3D->SetVisibleFlag( false );
	}
}

//=============================================================================
//�~�j�L�����̕\��
//=============================================================================
void CEnemy::ShowMiniChara()
{
	if( GetVisibleFlag() )
	{
		m_pMinSpr->Exec();
		
		m_pMinSpr->Rendering();
	}
}


//=============================================================================
//�L���b�`�}�[�N�̃����_�����O
//=============================================================================
void CEnemy::RenderingCatchMark()
{
	/*����*/
	m_pCatchSpr3D->Exec();
	
	//m_pLockOnSpr3D->Exec();
	
	/*�L���b�`�}�[�N�̃����_�����O*/
	m_pCatchSpr3D->Rendering();

}

//=============================================================================
//���_�̃����_�����O
//=============================================================================
void CEnemy::RenderingPoint()
{
	if( !m_IsCaptured )
	{	
		m_pPntFontSpr3D->SetVisibleFlag( true );
	}
	
	char Temp[5];
	
	sprintf_s( Temp, 5, "%d", m_PhotoPoint );
	
	/*���_���Z�b�g*/
	m_pPntFontSpr3D->SetDrawString( Temp );
	
	/*����*/
	m_pPntFontSpr3D->Exec();
	
	/*�|�C���g�̃����_�����O*/
	m_pPntFontSpr3D->Rendering();
	

}

//==============================================================================
//���b�N�I���}�[�N�̃����_�����O
//==============================================================================
void CEnemy::RenderingLockOn()
{
	//if( m_IsLockOn )
	//{
	//	m_pLockOnSpr3D->SetVisibleFlag( true );
	//	
	//}
	//
	//else
	//{
	//	m_pLockOnSpr3D->SetVisibleFlag( false );
	//}
	//
	
	//m_pLockOnSpr3D->Rendering();
	

}

//==============================================================================
//���[�g�̈ړ��ӏ��L�[�̐ݒ�
//==============================================================================
void CEnemy::SetRootKey()
{

	/*���ɐi�ޏꏊ��ݒ�*/
	m_vNextPoint = m_vecKey.at( 1 );
	
	m_vInitPoint = m_vPos;

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
bool CEnemy::Move( Selene::Math::Vector3D vTargetPos, CCamera *pCam, CField *pField, bool IsShowMark )
{
	if( IsShowMark )
	{
		m_vDirection.x = vTargetPos.x * pCam->GetRight().x + vTargetPos.y * (-pCam->GetFront().x);
		m_vDirection.y = 0.0f;
		m_vDirection.z = vTargetPos.x * pCam->GetRight().z + vTargetPos.y * (-pCam->GetFront().z);
	}
	
	m_Rot.x = toF( Math::ATan2( -m_vDirection.z, -m_vDirection.x ) );
	
	float fLength = m_vDirection.Length();
	
	m_fSpeed = fLength * m_fStSpeed ;
	
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
//��Ԗ��̏���
//=============================================================================
void CEnemy::Exec()
{
	m_vCatchMrkPos.x = m_vPos.x;
	m_vCatchMrkPos.z = m_vPos.z;
	
	static int count = 0;
	
	const int COUNT_MAX = 60 * 5;
	
	++count;
	
	m_vCatchMrkPos.y = ::Interpolation::Sub( m_vPos.y + 2.0f, m_vPos.y + 2.5f, COUNT_MAX, count );
	
	if( count >= COUNT_MAX )
	{
		count = 0;
	}
	
	m_vLockMrkPos = m_vPos - m_vFront;
	
	/*�|�C���g�\���ʒu��ݒ�*/
	m_pPntFontSpr3D->SetPosition( m_vCatchMrkPos + Math::Vector3D( 0, 3.0, 0 ) );

	/*�L���b�`�}�[�N�̕\���ʒu��ݒ�*/
	m_pCatchSpr3D->SetPosition( m_vCatchMrkPos );
	
	/*���b�N�I���}�[�N�̐ݒ�*/
	m_pLockOnSpr3D->SetPosition( m_vLockMrkPos );
	
	if( m_IsExistAnim )
	{
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
	}
	
	/*�A�N�^�[�̐ݒ�̃Z�b�g*/
	SetActorSetting();
	
	if( m_IsCaptured )
	{
		m_IsStop = true;
	}
	
	else
	{
		m_IsStop = false;
	}
	
}

//=============================================================================
//��Ԗ��̏���
//=============================================================================
void CEnemy::StateExec()
{
	switch( m_eState )
	{
		/*�����Ȃ���Ԃ̂Ƃ�*/
		case STATE_NONE:
		{
			break;
		}
		
		/*�����*/
		case STATE_RELEASE:
		{
			Math::Vector3D vMovePos = GetPosition();
			
			const int MAX_COUNT = 60*5;//�ő�J�E���g��
			
			m_ReleaseCnt ++;
			
			/*�����ňړ�*/
			m_vPos.x = Interpolation::Flat( vMovePos.x, m_vCatchBefPos.x, MAX_COUNT, m_ReleaseCnt );
			m_vPos.y = Interpolation::Flat( vMovePos.y, m_vCatchBefPos.y, MAX_COUNT, m_ReleaseCnt );
			m_vPos.z = Interpolation::Flat( vMovePos.z, m_vCatchBefPos.z, MAX_COUNT, m_ReleaseCnt );
			
			if( m_ReleaseCnt >= MAX_COUNT )
			{
				m_eState = STATE_NONE;
				m_ReleaseCnt = 0;
			}
			
			break;
		}
		
		//�G�Ƃ̔��菈��
		case STATE_HITENEMY:
		{
			static int count = 0;
			
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

//=============================================================================
//���[�g�ł̈ړ�
//=============================================================================
void CEnemy::MoveRoot()
{
	m_fKeyTime += 1.0f;
	
	const float fTIME_MAX = 240;
	
	m_vDirection = m_vNextPoint - m_vInitPoint;
	
	m_Rot.x = toF( Math::ATan2( -m_vDirection.z, -m_vDirection.x ) );
	m_vPos.x = ::Interpolation::Flat( m_vInitPoint.x, m_vNextPoint.x, fTIME_MAX, m_fKeyTime );
	m_vPos.z = ::Interpolation::Flat( m_vInitPoint.z, m_vNextPoint.z, fTIME_MAX, m_fKeyTime );
	
	//if( m_RootCount >= m_vecKey.size() - 2 )
	//{
	//	m_RootSpeed *= -1;
	//}
	//
	//else if( m_RootCount < 0 )
	//{
	//	m_RootSpeed *= -1;
	//}
	//
	//
	if( m_fKeyTime > fTIME_MAX )
	{
		m_vInitPoint = m_vNextPoint;
		
		m_RootCount += m_RootSpeed;
		
		if( m_RootCount < m_vecKey.size() )
		{	
			m_vNextPoint = m_vecKey.at( m_RootCount );
		}
		
		else
		{
			m_RootCount = 0;
		}
		
		m_fKeyTime = 0;
	}
	
	
	
	
	
	////
	//m_vDirection = m_vNextPoint - m_vInitPoint;
	////
	////float fDis = m_vDirection.Length();
	////
	////float Time = fDis / m_fSpeed;
	////
	//const float fTIME = 60;
	//
	////m_Rot.x = toF( Math::ATan2( -m_vDirection.z, -m_vDirection.x ) );
	////
	//m_vPos.x = m_pAnimX->GetParameter( m_fKeyTime, ANIMATION_TYPE_LINEAR, 0.0f );
	//m_vPos.z = m_pAnimZ->GetParameter( m_fKeyTime, ANIMATION_TYPE_LINEAR, 0.0f );
	
	//m_vPos.x = Interpolation::Flat( m_vPos.x, m_vNextPoint.x, fTIME, m_fKeyTime );
	//
	//m_vPos.z = Interpolation::Flat( m_vPos.z, m_vNextPoint.z, fTIME, m_fKeyTime );
	
	//m_vPos += m_vDirection * 0.4f/* * m_fStSpeed*/;
	
	//if( RootCount > 2 )
	//{
	//	RootCount = 0;
	//}
	
	
	//if( m_fKeyTime >= fTIME )
	//{
	//	
	//	m_vInitPoint = m_vNextPoint;

	//	Math::Vector3D vPoint = m_vecKey.at( RootCount );
	//	
	//	RootCount++;
	//	
	//	m_vNextPoint = vPoint;
	//}
	//
}

//=============================================================================
//�����_���E�H�[�N
//=============================================================================
void CEnemy::MoveRandom()
{
	static float count = 0.0f;
	m_vDirection = m_vNextPoint - m_vPos;
	
	/*���̈ړ��|�C���g�̐ݒ�*/

	m_Rot.x = toF( Math::ATan2( -m_vDirection.z, -m_vDirection.x ) );
	
	float fDis = m_vDirection.Length();
	
	//float Time = fDis / 0.0001f;
	
	float Time = 60 * 8;
	
	count += 1.0f;
	
	m_vPos.x = ::Interpolation::Flat( m_vInitPoint.x, m_vNextPoint.x, Time, count );
	
	if( m_IsFly )
	{
		m_vPos.y = ::Interpolation::Flat( m_vInitPoint.y, m_vNextPoint.y, Time, count );
	}
	
	m_vPos.z = ::Interpolation::Flat( m_vInitPoint.z, m_vNextPoint.z, Time, count );
	
	if( count > Time )
	{
		m_vInitPoint = m_vNextPoint;
		
		SetNextPoint();
	
		count = 0;
	}
	
	//m_vPos += m_vDirection * 0.7f/* * m_fStSpeed*/;
	
}



//=============================================================================
//�ړ�����
//=============================================================================
void CEnemy::MoveExec()
{
	if( !m_IsCaptured )
	{
		//m_vDirection = m_vNextPoint - m_vPos;
		
		m_vDirection = -m_vFront;
		
		static int count = 0;
		
		count ++;
		
		const int TIME = 60 * 5;
		
		static Sint32 Hit = 1;
		
		
		//m_vPos.x = Interpolation::Flat( vOldPos.x, m_vNextPoint.x, TIME, count ) * 0.1;
		//m_vPos.z = Interpolation::Flat( vOldPos.z, m_vNextPoint.z, TIME, count ) * 0.1;
		
		if( m_IsHitWall )
		{
			m_Rot.x += DEG_TO_ANGLE( Hit );
		}
		
		else
		{
			m_vPos += m_vDirection * m_fSpeed;
			
			//Hit = Rand.GetInt( -1, 1 );
			
			
		}
		
		if( count > TIME )
		{
			
			Sint32 Rot = m_Rand.GetInt( -20, 20 );
			
			m_Rot.x += DEG_TO_ANGLE( Rot );
			
			count = 0;
		}
		
		
		
	}

}

//=============================================================================
//�ߊl�Ώۂ��`�F�b�N
//=============================================================================
//[input]
//	Box:���肷��{�b�N�X
//=============================================================================
void CEnemy::CheckCatch( Collision::CBox Box )
{
	if( GetVisibleFlag() && GetCatchableFlag() )
	{
		if( GetModelActor( SCREEN_MAIN )->Collision_Check( Box ) )
		{
			m_pCatchSpr3D->SetVisibleFlag( true );
		}
		
		else
		{
			m_pCatchSpr3D->SetVisibleFlag( false );
		}
	}	
		
}

//=============================================================================
//�G�̓��_�v�Z
//=============================================================================
//[input]
//	pPlayer:�v���C���[
//[return]
//	�v�Z���ꂽ�X�R�A
//=============================================================================
int CEnemy::CalcScore( CPlayer *pPlayer )
{
	int Score = 0;
	
	float fLength = ( pPlayer->GetPosition() - this->GetPosition() ).Length();
	
	float fCheckDis = fCHECK_DISTANCE - fLength;
	
	Score = m_PhotoPoint + fCheckDis + CheckPosScore();
	
	return Score;
}

//=============================================================================
//�ʐ^�̈ʒu�ł̓��_�v�Z
//=============================================================================
//[return]
//	�X�R�A
//=============================================================================
int CEnemy::CheckPosScore()
{
	int Score = 0;
	
	Math::Vector2D vHitPos2D( vHitPos.x, vHitPos.y );
	
	const float fMARGIN = 20.0f;
	
	//�f���͈͂𐧌�����
	if( ( vHitPos2D.x > fMARGIN && vHitPos2D.x < SCREEN_WIDTH - fMARGIN ) && 
		( vHitPos2D.y > fMARGIN && vHitPos2D.y < SCREEN_HEIGHT - fMARGIN ) )
	{
		
		/*�^�񒆃G���A�͈̔�*/
		const Math::Point2DF fMIDDLE_AREA( 200, 150 );		
		
		//�^�񒆃G���A�͈̔͂̐ݒ�
		Math::Rect2DF HitRect( SCREEN_WIDTH / 2 - fMIDDLE_AREA.x, SCREEN_HEIGHT / 2 - fMIDDLE_AREA.y, 
							   fMIDDLE_AREA.x * 2, fMIDDLE_AREA.y * 2 );
							   
		//�^�񒆂̏ꍇ
		if( Collision::Point_Rect( vHitPos2D, HitRect ) )
		{
			Score = 100;
		}

		//���̑��̏ꍇ
		else
		{
			Score = 20;
		}
		
	}
	
	return Score;
	
}


//=============================================================================
//�G�̓��_�v�Z
//=============================================================================
//[input]
//	pSceneMgr:���肷��V�[���Ǘ��N���X
//[return]
//	�ʐ^�B�e�\���ǂ���
//=============================================================================
bool CEnemy::CheckShoot( CSceneManager *pSceneMgr )
{
	Math::Rect2DF HitRect( 0, 0, toF( SCREEN_WIDTH ), toF( SCREEN_HEIGHT ) );
	
	vHitPos = pSceneMgr->GetSceneMgr()->TransformToScreen( m_vPos );
	
	Math::Vector2D vHitPos2D( vHitPos.x, vHitPos.y );
	
	if( GetVisibleFlag() && 
		Collision::Point_Rect( vHitPos2D, HitRect ) )
	{
		return true;
	}

	return false;
	
}

////=============================================================================
////�G�̓��_�v�Z
////=============================================================================
////[input]
////	pPlayer:���肷��v���C���[
////[return]
////	�ʐ^�B�e�\���ǂ���
////=============================================================================
//bool CEnemy::CheckShoot( CPlayer *pPlayer )
//{
//	const int CHECK_POINT_MAX = 9;
//	
//	/*�ʐ^����|�C���g*/
//	Math::Vector2D CheckPointTbl[] =
//	{
//		Math::Vector2D(400, 300),
//		Math::Vector2D(350, 300),
//		Math::Vector2D(450, 300),
//		Math::Vector2D(400, 250),
//		Math::Vector2D(400, 350),
//		Math::Vector2D(350, 250),
//		Math::Vector2D(350, 350),
//		Math::Vector2D(450, 250),
//		Math::Vector2D(450, 350),
//		
//	};
//	
//	for( int i = 0;i < CHECK_POINT_MAX;++i )
//	{
//		if( GetVisibleFlag() && 
//			GetModelActor( SCREEN_MAIN )->Collision_Check( pPlayer->GetShootChkBox() ) )
//		{
//			return true;
//		}
//		
//	}
//	
//	return false;
//	
//}



//=============================================================================
//�A�N�^�[�C���f�b�N�X�̃Z�b�g
//=============================================================================
//[input]
//	index:�ݒ肷��C���f�b�N�X
//=============================================================================
void CEnemy::SetActorIndex( int index )
{
	m_ActorIndex = index;
	m_pCatchSpr3D->SetActorIndex( index );
	m_pPntFontSpr3D->SetActorIndex( index );
}


//=============================================================================
//�A�j���[�V�����̐؂�ւ�
//=============================================================================
void CEnemy::ChangeAnimation()
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
		}
	}
}

//=============================================================================
//���̈ړ��|�C���g�̐ݒ�
//=============================================================================
void CEnemy::SetNextPoint( )
{
	const float fMOVEAREA = 20.0f;//�ړ��͈�
	
	m_vNextPoint.x = m_Rand.GetFloat( m_vInitPos.x - fMOVEAREA, m_vInitPos.x + fMOVEAREA );
	m_vNextPoint.z = m_Rand.GetFloat( m_vInitPos.z - fMOVEAREA, m_vInitPos.z + fMOVEAREA );
	
	if( m_IsFly )
	{
		m_vNextPoint.y = m_Rand.GetFloat( m_vInitPos.y - fMOVEAREA / 2, m_vInitPos.y + fMOVEAREA / 2 );
	}
		
}

//=============================================================================
//�ǂƂ̔���
//=============================================================================
//[input]
//	pField:�t�B�[���h
//[return]
//	�ǂɓ������Ă��邩�ǂ���
//=============================================================================
bool CEnemy::HitCheckWall( CField *pField )
{
	m_HitRay.vStart = m_vPos + Math::Vector3D( 0.0f, 3.0f, 0.0f );
	m_HitRay.vEnd = m_HitRay.vStart + m_vFront * 0.2f;
	
	Renderer::SCollisionResultExtend RetEx;
	
	//�ʂ��ӏ��̐ݒ�
	if( MoveCheck( pField ) == -1 )
	{
		return false;
	}
	
	else
	{
		return true;
	}
	
}



//=============================================================================
//�����̎�̐ݒ�
//=============================================================================
//[input]
//	pCore:�R�A�f�o�C�X
//=============================================================================
void CEnemy::SetSeed( ICore *pCore )
{
	m_Rand.Seed( pCore->GetSyncCount() );
}

