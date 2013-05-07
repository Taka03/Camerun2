//*============================================================================
//ResourceManager.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "ResourceManager.h"
#include "LuaScript.h"

//=============================================================================
//variable
//=============================================================================
list< CResourceManager::ListData > CResourceManager::m_DrawList;
list< CResourceManager::ListData > CResourceManager::m_SoundList;



//============================================================================
//�R���X�g���N�^
//============================================================================
CResourceManager::CResourceManager( ) 
: m_Page(0),
  m_eObjType( OBJ_DRAW )
{
	//m_pGameObj = new CGameObject();
	//m_pSoundObj = new CSoundObject();
	//m_p3DObj = new CDraw3DObject();
	//m_p2DObj = new CDraw2DObject();
	
	//memset( m_pQueTop, NULL, QUE_MAX );
	
	for( int i = 0;i < QUE_MAX;++i )
	{
		m_pQueTop[i] = NULL;
	}
	
	m_DrawList.clear();
	
	/*�X���b�h�̍쐬*/
	m_Thread.Create( LoadProc, (void*)this );
	
	
	printf("BOOT ResourceManager\n");
}	

//============================================================================
//�f�X�g���N�^
//============================================================================
CResourceManager::~CResourceManager()
{
	printf("ABORT ResourceManager\n");
	
	/*�I��*/
	m_Event.Set();
	
	/*�X���b�h�̏I���҂�*/
	while( !m_Thread.WaitForExit() )
	{
		Sleep( 100 );
	}
	
	vector< string > strRemoveObj;
	vector< string > strRemoveSound;
	
	//�����I�u�W�F�N�g���X�g�̎擾
	for( list< ListData >::iterator it = m_DrawList.begin();it != m_DrawList.end();++it )
	{
		string strTemp = it->m_strDataName;
		
		strRemoveObj.push_back( strTemp );
	}
	
	//�����T�E���h�I�u�W�F�N�g�̎擾
	for( list< ListData >::iterator it = m_SoundList.begin();it != m_SoundList.end();++it )
	{
		string strTemp = it->m_strDataName;
		
		strRemoveSound.push_back( strTemp );
	}
	
	//�`�惊�X�g�̏���
	for( Uint32 i = 0;i < strRemoveObj.size();++i )
	{
		RemoveObject( strRemoveObj.at( i ).c_str() );
	}
	
	//�T�E���h���X�g�̏���
	for( Uint32 i = 0;i < strRemoveSound.size();++i )
	{
		RemoveSound( strRemoveSound.at( i ).c_str() );
	}
	
	printf("EXIT ResourceManager\n");
	
}

//============================================================================
//�I�u�W�F�N�g�̎擾
//============================================================================
//[input]
//	pName:�f�[�^��
//[return]
//	�擾�����I�u�W�F�N�g
//===========================================================================
CGameObject *CResourceManager::FindObject( const char *pName )
{
	for( list< ListData >::iterator it = m_DrawList.begin();it != m_DrawList.end();++it )
	{
		string strName = it->m_strDataName;
		
		//��v�����炻�̃I�u�W�F�N�g��Ԃ�
		if( strName.compare( pName ) == 0 )
		{
			return it->m_pGameobj;
		}
	}
		 
	//_ASSERT(
	//
	return NULL;
}

//============================================================================
//���I�u�W�F�N�g�̎擾
//============================================================================
//[input]
//	pName:�f�[�^��
//[return]
//	�擾�������I�u�W�F�N�g
//===========================================================================
CGameObject *CResourceManager::FindSoundObj( const char *pName )
{
	for( list< ListData >::iterator it = m_SoundList.begin();it != m_SoundList.end();++it )
	{
		string strName = it->m_strDataName;
		
		//��v�����炻�̃I�u�W�F�N�g��Ԃ�
		if( strName.compare( pName ) == 0 )
		{
			return it->m_pGameobj;
		}
	}
		 
	//_ASSERT(
	//
	return NULL;
}



//============================================================================
//�I�u�W�F�N�g�̃��X�g�ǉ�
//============================================================================
//[input]
//	pDataName:�f�[�^��
//	pGameObj:�Q�[���I�u�W�F�N�g
//===========================================================================
void CResourceManager::AppendList( string strDataName, CGameObject *pGameObj )
{
	static Uint32 priority = 0;
	
	ListData liData;
	
	liData.m_strDataName = strDataName;
	liData.m_pGameobj = pGameObj;
	liData.m_Priority = priority;
	
	//�`��I�u�W�F�N�g�̂Ƃ�
	if( m_eObjType == OBJ_DRAW )
	{	
		m_DrawList.push_back( liData );
	}
	
	//���I�u�W�F�N�g�̂Ƃ�
	else if( m_eObjType == OBJ_SND )
	{
		m_SoundList.push_back( liData );
	}
	
	pGameObj->Init();
	
	
	
	priority++;
	
}


//============================================================================
//�I�u�W�F�N�g�̏���
//============================================================================
//[input]
//	pDataName:�f�[�^��
//============================================================================
void CResourceManager::RemoveObject( const char *pDataName )
{
	list< ListData >::iterator it = m_DrawList.begin();
	
	for( it = m_DrawList.begin();it != m_DrawList.end(); )
	{
		//��v�����炻�̃I�u�W�F�N�g������
		if( it->m_strDataName.compare( pDataName ) == 0 )
		{
			SAFE_DELETE( it->m_pGameobj );
			
			//���X�g�������
			it = m_DrawList.erase( it );
			
			continue;
		}
		
		++it;
	}
}

//============================================================================
//�T�E���h�I�u�W�F�N�g�̏���
//============================================================================
//[input]
//	pDataName:�f�[�^��
//============================================================================
void CResourceManager::RemoveSound( const char *pDataName )
{
	list< ListData >::iterator it = m_SoundList.begin();
	
	for( it = m_SoundList.begin();it != m_SoundList.end(); )
	{
		//��v�����炻�̃I�u�W�F�N�g������
		if( it->m_strDataName.compare( pDataName ) == 0 )
		{
			SAFE_DELETE( it->m_pGameobj );
			
			//���X�g�������
			it = m_SoundList.erase( it );
			
			continue;
		}
		
		++it;
	}
}


//============================================================================
//�I�u�W�F�N�g�̏���
//============================================================================
//[input]
//	pRemObj:�����ΏۃI�u�W�F�N�g
//============================================================================
void CResourceManager::RemoveObject( CGameObject *pRemObj )
{
	list< ListData >::iterator it = m_DrawList.begin();
	
	for( it = m_DrawList.begin();it != m_DrawList.end(); )
	{
		//��v�����炻�̃I�u�W�F�N�g������
		if( it->m_pGameobj == pRemObj )
		{
			SAFE_DELETE( it->m_pGameobj );
			
			//���X�g�������
			it = m_DrawList.erase( it );
			
			continue;
		}
		
		++it;
	}
}




//============================================================================
//�I�u�W�F�N�g�̒ǉ�
//============================================================================
//[input]
//	pFile:�ǉ�����f�[�^
//===========================================================================
void CResourceManager::Push ( CFileData *pFile )
{
	/*�I��������������?*/
	if( m_Event.IsSignal() )
	{
		return;
	}
	
	//�I�[�g���b�N
	Thread::CAutoLock Lock( m_CS );
	
	/*�擪*/
	if( m_pQueTop[m_Page] == NULL )
	{
		m_pQueTop[m_Page] = pFile;
	}
	
	/*���X�g�̒ǉ�*/
	else
	{
		CFileData *pData = m_pQueTop[m_Page];
		
		while( pData->GetNext() != NULL )
		{
			pData = pData->GetNext();
		}
		
		pData->SetNext( pFile );
	}
	
	pFile->SetNext( NULL );
	
	printf("CResourceManager :PUSH [%s]\n", pFile->GetFileName().c_str() );
	
}



//============================================================================
//�ǂݍ��ݒ����ǂ�������
//============================================================================
Bool CResourceManager::IsLoading()
{
	//�I�[�g���b�N
	Thread::CAutoLock Lock( m_CS );
	
	if( m_pQueTop[0] != NULL )
	{
		return true;
	}
	
	if( m_pQueTop[1] != NULL )
	{
		return true;
	}
	
	return false;
}


//============================================================================
//�N��
//============================================================================
void CResourceManager::Run()
{
	for(;;)
	{
		CFileData *pFile = NULL;
		Sint32 ActivePage = -1;
		
		/*�I���`�F�b�N*/
		if( m_Event.IsSignal() )
		{
			break;
		}
		
		/*����擾���郊�X�g���擾*/
		m_CS.Enter();
		
		/*���ꂩ�珈������y�[�W*/
		ActivePage = m_Page;
		
		/*�y�[�W�؂�ւ�*/
		m_Page = 1 - m_Page;
		
		/*�擪���擾*/
		pFile = m_pQueTop[ActivePage];
		
		m_CS.Leave();
		
		if( pFile == NULL )
		{
			::Sleep( 250 );
			
			continue;
		}
		
		while( pFile != NULL )
		{
			/*���\�[�X�^�C�v�𔻕�*/
			CheckType( pFile );
			
			/*�����擾*/
			CFileData *pNext = pFile->GetNext();
			
			/*���݂̂��̂��폜*/
			delete pFile;
			
			pFile = pNext;
			
		}
		
		/*�Q�[���f�[�^�̓ǂݍ���*/
		//m_pGameObj->Load( m_pRender, m_pFileMgr );
		
		/*2D�f�[�^�̓ǂݍ���*/
		//m_p2DObj->Load( m_pRender, m_pFileMgr );
		
		/*3D�f�[�^�̓ǂݍ���*/
		//m_p3DObj->Load( m_pRender, m_pFileMgr );
		
		/*�����̓ǂݍ���*/
		//m_pSoundObj->LoadSound( m_pCore, m_pFileMgr );
		
		/*���X�g������*/
		m_pQueTop[ActivePage] = NULL;
		
	}
	
	//----------------------------------------------------------------------------
	//�L���[�̒��g���N���A
	//----------------------------------------------------------------------------
	for( Sint32 i = 0;i < QUE_MAX;++i )
	{
		CFileData *pFile = m_pQueTop[i];
		
		while( pFile != NULL )
		{
			CFileData *pNext = pFile->GetNext();
			delete pFile ;
			pFile = pNext;
		}
		
		m_pQueTop[i] = NULL;
	}

	
}

//============================================================================
//�^�C�v�̔���
//============================================================================
//[input]
//	pFile:���肷��f�[�^
//===========================================================================
void CResourceManager::CheckType( CFileData *pFile )
{
	string strDataName[] =
	{
		"SPRITE",
		"PHOTO",
		"MINIMAP",
		"CAMBUTTON",
		"MENU",
		"WINDOW",
		"FONT",
		"SOUND",
		"BGM",
		"FIELD",
		"FONT3D",
		"SPRITE3D",
		"CHARACTER",
		"PLAYER",
		"TRAIN",
		"AMEUS",
		"MANTA",
		"BIRD",
		"MOUSE",
		"RABBIT",
		"LIZARD",
		"CAR",
		"FOUNT",
		"SKY",
	};
	
	CreateFunc CreateTbl[] =
	{
		&CResourceManager::CreateSprite,
		&CResourceManager::CreatePhoto,
		&CResourceManager::CreateMiniMap,
		&CResourceManager::CreateCamButton,
		&CResourceManager::CreateMenu,
		&CResourceManager::CreateExpWindow,
		&CResourceManager::CreateFontSprite,
		&CResourceManager::CreateSound,
		&CResourceManager::CreateBGM,
		&CResourceManager::CreateField,
		&CResourceManager::CreateFontSprite3D,
		&CResourceManager::CreateSprite3D,
		&CResourceManager::CreateCharacter,
		&CResourceManager::CreatePlayer,
		&CResourceManager::CreateTrain,
		&CResourceManager::CreateAmeus,
		&CResourceManager::CreateManta,
		&CResourceManager::CreateBird,
		&CResourceManager::CreateMouse,
		&CResourceManager::CreateRabbit,
		&CResourceManager::CreateLizard,
		&CResourceManager::CreateCar,
		&CResourceManager::CreateFount,
		&CResourceManager::CreateSkyObj,
	};		
	
	
	int Count = 0;

	for( int i = 0;i < CFileData::RESOURCE_MAX;++i )
	{
		
		string strTemp = pFile->GetTypeName();
		
		string strData = strDataName[i];
		
		if( strTemp.compare( strDataName[i] ) == 0 )
		{
			(this->*CreateTbl[i])( pFile );
			
			break;
		}
		
	}
	
}

//****************************************************************************
//�������烊�\�[�X�̍쐬
//****************************************************************************

//============================================================================
//�X�v���C�g�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//===========================================================================
void CResourceManager::CreateSprite( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	Math::Vector2D vPos( pFile->GetPosition().x, pFile->GetPosition().y );
	
	CSprite *pSpr = new CSprite( pFile->GetFileName().c_str(), vPos, pFile->GetDivNum() );
	
	pSpr->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pSpr );
}

//============================================================================
//�ʐ^�X�v���C�g�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//===========================================================================
void CResourceManager::CreatePhoto( CFileData *pFile )
{
	
	m_eObjType = OBJ_DRAW;
	
	Math::Vector2D vPos( pFile->GetPosition().x, pFile->GetPosition().y );
	
	CPhoto *pPhoto = new CPhoto( pFile->GetFileName().c_str(), vPos, pFile->GetVecPhotoData() );
	
	pPhoto->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pPhoto );
}

//============================================================================
//�~�j�}�b�v�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//===========================================================================
void CResourceManager::CreateMiniMap( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	
	Math::Vector2D vPos( pFile->GetPosition().x, pFile->GetPosition().y );
	
	CMiniMap *pMiniMap =  new CMiniMap( pFile->GetFileName().c_str(), vPos );
	
	pMiniMap->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pMiniMap );
}

//============================================================================
//�J�����{�^���̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//===========================================================================
void CResourceManager::CreateCamButton( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	
	Math::Vector2D vPos( pFile->GetPosition().x, pFile->GetPosition().y );
	
	CCamButton *pCamBtn = new CCamButton( pFile->GetFileName().c_str(), vPos );
	
	pCamBtn->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pCamBtn );	
}

//============================================================================
//���j���[�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//===========================================================================
void CResourceManager::CreateMenu( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	Math::Vector2D vPos( pFile->GetPosition().x, pFile->GetPosition().y );
	
	CMenu *pMenu = new CMenu( pFile->GetFileName().c_str(), vPos, CCommonObject::GetAppli()->GetCore()->GetMouse() );
	
	pMenu->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pMenu );	
}

//============================================================================
//�E�B���h�E�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//===========================================================================
void CResourceManager::CreateExpWindow( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	
	Math::Vector2D vPos( pFile->GetPosition().x, pFile->GetPosition().y );
	
	CExpWindow *pExpWindow = new CExpWindow( pFile->GetFileName().c_str(), vPos );
	
	pExpWindow->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pExpWindow );	
}

//============================================================================
//�t�H���g�X�v���C�g�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//===========================================================================
void CResourceManager::CreateFontSprite( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	Math::Vector2D vPos( pFile->GetPosition().x, pFile->GetPosition().y );
	
	CFontSprite *pFontSpr = new CFontSprite( pFile->GetFileName().c_str(), vPos );
	
	pFontSpr->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pFontSpr );	
}

//============================================================================
//���ʉ��̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//===========================================================================
void CResourceManager::CreateSound( CFileData *pFile )
{
	m_eObjType = OBJ_SND;
	
	CSoundEffect *pSnd = new CSoundEffect( pFile->GetFileName().c_str() );
	
	pSnd->LoadSound( CCommonObject::GetAppli()->GetCore(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pSnd );	
}

//============================================================================
//BGM�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//===========================================================================
void CResourceManager::CreateBGM( CFileData *pFile )
{
	m_eObjType = OBJ_SND;
	
	CBGM *pSnd = new CBGM( pFile->GetFileName().c_str() );
	
	pSnd->LoadSound( CCommonObject::GetAppli()->GetCore(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pSnd );	
}

//============================================================================
//�t�B�[���h�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//===========================================================================
void CResourceManager::CreateField( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CField *pField = new CField( pFile->GetFileName().c_str(), pFile->GetPosition() );
	
	pField->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pField );	

}

//============================================================================
//3D�t�H���g�X�v���C�g�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//===========================================================================
void CResourceManager::CreateFontSprite3D( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CFontSprite3D *pFontSpr3D = new CFontSprite3D( pFile->GetFileName().c_str(), pFile->GetPosition() );
	
	pFontSpr3D->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pFontSpr3D );	

}

//============================================================================
//3D�X�v���C�g�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//===========================================================================
void CResourceManager::CreateSprite3D( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CSprite3D *pSpr3D = new CSprite3D( pFile->GetFileName().c_str(), pFile->GetPosition() );
	
	pSpr3D->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pSpr3D );	

}

//============================================================================
//�L�����N�^�[�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//============================================================================
void CResourceManager::CreateCharacter( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CCharacter *pChara = new CCharacter( pFile->GetFileName().c_str(), pFile->GetPosition() );
	
	pChara->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pChara );	
}


//============================================================================
//�v���C���[�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//===========================================================================
void CResourceManager::CreatePlayer( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CPlayer *pPlayer = new CPlayer( pFile->GetFileName().c_str(), pFile->GetPosition() );
	
	pPlayer->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pPlayer );	
}

//============================================================================
//�d�Ԃ̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//===========================================================================
void CResourceManager::CreateTrain( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CTrain *pTrain = new CTrain( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pTrain->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pTrain );	
}

//============================================================================
//�A���E�X�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//============================================================================
void CResourceManager::CreateAmeus( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemyAmeus *pAmeus = new CEnemyAmeus( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pAmeus->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pAmeus );	
}

//============================================================================
//�}���^�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//============================================================================
void CResourceManager::CreateManta( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemyManta *pManta = new CEnemyManta( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pManta->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pManta );	
}

//============================================================================
//�g���̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//============================================================================
void CResourceManager::CreateBird( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemyBird *pBird = new CEnemyBird( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pBird->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pBird );	
}

//============================================================================
//�l�Y�~�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//============================================================================
void CResourceManager::CreateMouse( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemyMouse *pMouse = new CEnemyMouse( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pMouse->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pMouse );	
}

//============================================================================
//�E�T�M�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//============================================================================
void CResourceManager::CreateRabbit( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemyRabbit *pRabbit = new CEnemyRabbit( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pRabbit->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pRabbit );	
}

//============================================================================
//�g�J�Q�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//============================================================================
void CResourceManager::CreateLizard( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemyLizard *pLizard = new CEnemyLizard( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pLizard->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pLizard );	
}

//============================================================================
//�Ԃ̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//============================================================================
void CResourceManager::CreateCar( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemyCar *pCar = new CEnemyCar( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pCar->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pCar );	
}

//============================================================================
//�����̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//============================================================================
void CResourceManager::CreateFount( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemyFountObj *pFountObj = new CEnemyFountObj( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pFountObj->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pFountObj );	
}

//============================================================================
//�󒆒뉀�̐���
//============================================================================
//[input]
//	pFile:�t�@�C���f�[�^
//============================================================================
void CResourceManager::CreateSkyObj( CFileData *pFile )
{
	m_eObjType = OBJ_DRAW;
	
	CEnemySkyObj *pSkyObj = new CEnemySkyObj( pFile->GetFileName().c_str(), pFile->GetPosition(), pFile->GetResFile() );
	
	pSkyObj->Load( CCommonObject::GetAppli()->GetRenderer(), CCommonObject::GetAppli()->GetFileMgr() );
	
	//���X�g�ւ̒ǉ�
	AppendList( pFile->GetDataName(), pSkyObj );	
}

//****************************************************************************
//�����܂Ń��\�[�X�̍쐬
//****************************************************************************


//============================================================================
//���[�h�p�X���b�h
//============================================================================
//[input]
//	pData:
//===========================================================================
void CResourceManager::LoadProc( void *pData )
{
	//�g�p����CPU�ԍ�
	System::SetThreadCPUNo( 1 );
	
	//�N��
	( (CResourceManager*)pData)->Run();
	
	//if( !m_IsLoading )
	//{
	//	::ExitThread( 0 );
	//}
}



					
									


