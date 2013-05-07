//*============================================================================
//Application.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "FileData.h"

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	pFileName:ファイル名
//	pDataName:データ名
//	Type:リソースタイプ
//=============================================================================
CFileData::CFileData( const char *pFileName, const char *pDataName, const char *pTypeName ) 
:m_strFileName(pFileName),
 m_strDataName(pDataName),
 m_pNext(NULL),
 m_strTypeName(pTypeName)

{

}

//=============================================================================
//コンストラクタ
//=============================================================================
//[input]
//	pFileName:ファイル名
//	pDataName:データ名
//	pTypeName:リソースタイプ
//	vPos:初期位置
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
//コンストラクタ
//=============================================================================
//[input]
//	pFileName:ファイル名
//	pDataName:データ名
//	pTypeName:リソースタイプ
//	vPos:初期位置
//	vecPhotoData:写真データ
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
//コンストラクタ
//=============================================================================
//[input]
//	pFileName:ファイル名
//	pDataName:データ名
//	pTypeName:リソースタイプ
//	vPos:初期位置
//	pResFile:リソースファイル
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
//コンストラクタ
//=============================================================================
//[input]
//	pFileName:ファイル名
//	pDataName:データ名
//	pTypeName:リソースタイプ
//	vPos:初期位置
//	DivNum:分割数
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



