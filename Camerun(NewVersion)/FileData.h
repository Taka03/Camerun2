//*============================================================================
//FileData.h
//*============================================================================
//[history]
//	08/03/19　作成
//[author]
//	Taka
//=============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Sprite.h"
#include "SoundEffect.h"
#include "BGM.h"
#include "field.h"
#include "FontSprite.h"
#include "FontSprite3D.h"
#include "camera.h"
#include "character.h"
#include "player.h"
#include "Train.h"
#include "Photo.h"
#include "CamBtn.h"
#include "Menu.h"
#include "ExpWindow.h"
#include "MiniMap.h"
#include "Sprite3D.h"
#include "EnemyAmeus.h"
#include "EnemyMouse.h"
#include "EnemyBird.h"
#include "EnemyManta.h"
#include "EnemyRabbit.h"
#include "EnemyLizard.h"
#include "EnemyCar.h"
#include "EnemySkyObj.h"
#include "EnemyFountObj.h"

//=============================================================================
//enum
//=============================================================================


//=============================================================================
//class
//=============================================================================
//[desc]
//	ファイルデータ用クラス
//=============================================================================
class CFileData
{
	friend class CResourceManager;
	
	public:
	
		//リソースタイプ
		enum eResourceType
		{
			SPRITE,
			PHOTO,
			MINIMAP,
			CAMBUTTON,
			MENU,
			WINDOW,
			FONT,
			SOUND,
			BGM,
			FIELD,
			FONT3D,
			SPRITE3D,
			CHARACTER,
			PLAYER,
			TRAIN,
			AMEUS,
			MANTA,
			BIRD,
			MOUSE,
			RABBIT,
			RIZARD,
			CAR,
			FOUNT,
			SKY,
			RESOURCE_MAX,
		};
	
	private:

		CFileData					*m_pNext;
		//eResourceType				m_Type;
		string  m_strTypeName;//タイプ名
		
		string  m_strFileName;//ファイル名
		string  m_strDataName;//データ名
		
		Math::Vector3D m_vPos;//キャラの位置
		File::IResourceFile *m_pResFile;//リソースファイル
		
		Math::Point2DI m_DivNum;//分割数
		
		vector< CPhoto::PhotoCheckData > m_vecPhotoData;//写真判定データ	
	
	private:
	
	
		
	public:

		/*コンストラクタ*/
		CFileData(){}
		
		/*コンストラクタ*/
		CFileData( const char *pFileName, const char *pDataName, const char *pTypeName );
		
		/*コンストラクタ*/
		CFileData( const char *pFileName, const char *pDataName, const char *pTypeName, Math::Vector3D vPos,
				   CGameObject *&pGameObj );
		
		/*コンストラクタ*/
		CFileData( const char *pFileName, const char *pDataName, const char *pTypeName, 
				   Math::Vector3D vPos, vector< CPhoto::PhotoCheckData > vecPhotoData );
		
		/*コンストラクタ*/
		CFileData( const char *pFileName, const char *pDataName, const char *pTypeName, 
				   Math::Vector3D vPos, File::IResourceFile *pResFile );
				   
		CFileData( const char *pFileName, const char *pDataName, const char *pTypeName, 
				   Math::Vector3D vPos, Math::Point2DI DivNum );
		
		/*デストラクタ*/
		~CFileData(){}
		
	/*Set系*/
	public:
	
		/*後方リストの設定*/
		void SetNext( CFileData *pData )
		{
			m_pNext = pData;
		}
		
	/*Get系*/
	public:

		/*ファイル名の取得*/
		string GetFileName() const
		{
			return m_strFileName;
		}
		
		/*データ名の取得*/
		string GetDataName() const
		{
			return m_strDataName;
		}
		
		/*リソースタイプの取得*/
		//eResourceType GetType( void ) const
		//{
		//	return m_Type;
		//}
		
		/*タイプ名の取得*/
		string GetTypeName() const
		{
			return m_strTypeName;
		}
		
		/*キャラ位置の取得*/
		Math::Vector3D GetPosition( void ) const
		{
			return m_vPos;
		}
		
		/*リソースファイルの取得*/
		File::IResourceFile *GetResFile( ) const
		{
			return m_pResFile;
		}
		
		/*写真データの取得*/
		vector< CPhoto::PhotoCheckData > GetVecPhotoData() const
		{
			return m_vecPhotoData;
		}		

		/*後方リストを取得*/
		CFileData *GetNext( void ) const
		{
			return m_pNext;
		}
		
		//分割数の取得
		Math::Point2DI GetDivNum() const
		{
			return m_DivNum;
		}

};
