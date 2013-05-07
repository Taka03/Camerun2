//*============================================================================
//Application.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "FileData.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pFileName:�t�@�C����
//	pDataName:�f�[�^��
//	Type:���\�[�X�^�C�v
//=============================================================================
CFileData::CFileData( const char *pFileName, const char *pDataName, const char *pTypeName ) 
:m_strFileName(pFileName),
 m_strDataName(pDataName),
 m_pNext(NULL),
 m_strTypeName(pTypeName)

{

}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pFileName:�t�@�C����
//	pDataName:�f�[�^��
//	pTypeName:���\�[�X�^�C�v
//	vPos:�����ʒu
//=============================================================================
CFileData::CFileData( const char *pFileName, const char *pDataName, const char *pTypeName,
					  Math::Vector3D vPos, CGameObject *&pGameObj )
:m_strFileName(pFileName),
 m_strDataName(pDataName),
 m_pNext(NULL),
 m_strTypeName(pTypeName),
 m_vPos(vPos)
 
{

}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pFileName:�t�@�C����
//	pDataName:�f�[�^��
//	pTypeName:���\�[�X�^�C�v
//	vPos:�����ʒu
//	vecPhotoData:�ʐ^�f�[�^
//=============================================================================
CFileData::CFileData( const char *pFileName, const char *pDataName, const char *pTypeName,
					  Math::Vector3D vPos, vector< CPhoto::PhotoCheckData > vecPhotoData ) 
:m_strFileName(pFileName),
 m_strDataName(pDataName),
 m_pNext(NULL),
 m_strTypeName(pTypeName),
 m_vPos(vPos),
 m_vecPhotoData(vecPhotoData)

{

}




//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pFileName:�t�@�C����
//	pDataName:�f�[�^��
//	pTypeName:���\�[�X�^�C�v
//	vPos:�����ʒu
//	pResFile:���\�[�X�t�@�C��
//=============================================================================
CFileData::CFileData( const char *pFileName, const char *pDataName, const char *pTypeName, 
					  Math::Vector3D vPos, File::IResourceFile *pResFile ) 
:m_strFileName(pFileName),
 m_strDataName(pDataName),
 m_pNext(NULL),
 m_strTypeName(pTypeName),
 m_vPos(vPos),
 m_pResFile(pResFile)

{

}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pFileName:�t�@�C����
//	pDataName:�f�[�^��
//	pTypeName:���\�[�X�^�C�v
//	vPos:�����ʒu
//	DivNum:������
//=============================================================================
CFileData::CFileData( const char *pFileName, const char *pDataName, const char *pTypeName, 
					  Math::Vector3D vPos, Math::Point2DI DivNum ) 
:m_strFileName(pFileName),
 m_strDataName(pDataName),
 m_pNext(NULL),
 m_strTypeName(pTypeName),
 m_vPos(vPos),
 m_DivNum(DivNum)
 
{

}



