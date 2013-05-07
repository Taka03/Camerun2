//*============================================================================
//FileData.h
//*============================================================================
//[history]
//	08/03/19�@�쐬
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
//	�t�@�C���f�[�^�p�N���X
//=============================================================================
class CFileData
{
	friend class CResourceManager;
	
	public:
	
		//���\�[�X�^�C�v
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
		string  m_strTypeName;//�^�C�v��
		
		string  m_strFileName;//�t�@�C����
		string  m_strDataName;//�f�[�^��
		
		Math::Vector3D m_vPos;//�L�����̈ʒu
		File::IResourceFile *m_pResFile;//���\�[�X�t�@�C��
		
		Math::Point2DI m_DivNum;//������
		
		vector< CPhoto::PhotoCheckData > m_vecPhotoData;//�ʐ^����f�[�^	
	
	private:
	
	
		
	public:

		/*�R���X�g���N�^*/
		CFileData(){}
		
		/*�R���X�g���N�^*/
		CFileData( const char *pFileName, const char *pDataName, const char *pTypeName );
		
		/*�R���X�g���N�^*/
		CFileData( const char *pFileName, const char *pDataName, const char *pTypeName, Math::Vector3D vPos,
				   CGameObject *&pGameObj );
		
		/*�R���X�g���N�^*/
		CFileData( const char *pFileName, const char *pDataName, const char *pTypeName, 
				   Math::Vector3D vPos, vector< CPhoto::PhotoCheckData > vecPhotoData );
		
		/*�R���X�g���N�^*/
		CFileData( const char *pFileName, const char *pDataName, const char *pTypeName, 
				   Math::Vector3D vPos, File::IResourceFile *pResFile );
				   
		CFileData( const char *pFileName, const char *pDataName, const char *pTypeName, 
				   Math::Vector3D vPos, Math::Point2DI DivNum );
		
		/*�f�X�g���N�^*/
		~CFileData(){}
		
	/*Set�n*/
	public:
	
		/*������X�g�̐ݒ�*/
		void SetNext( CFileData *pData )
		{
			m_pNext = pData;
		}
		
	/*Get�n*/
	public:

		/*�t�@�C�����̎擾*/
		string GetFileName() const
		{
			return m_strFileName;
		}
		
		/*�f�[�^���̎擾*/
		string GetDataName() const
		{
			return m_strDataName;
		}
		
		/*���\�[�X�^�C�v�̎擾*/
		//eResourceType GetType( void ) const
		//{
		//	return m_Type;
		//}
		
		/*�^�C�v���̎擾*/
		string GetTypeName() const
		{
			return m_strTypeName;
		}
		
		/*�L�����ʒu�̎擾*/
		Math::Vector3D GetPosition( void ) const
		{
			return m_vPos;
		}
		
		/*���\�[�X�t�@�C���̎擾*/
		File::IResourceFile *GetResFile( ) const
		{
			return m_pResFile;
		}
		
		/*�ʐ^�f�[�^�̎擾*/
		vector< CPhoto::PhotoCheckData > GetVecPhotoData() const
		{
			return m_vecPhotoData;
		}		

		/*������X�g���擾*/
		CFileData *GetNext( void ) const
		{
			return m_pNext;
		}
		
		//�������̎擾
		Math::Point2DI GetDivNum() const
		{
			return m_DivNum;
		}

};
