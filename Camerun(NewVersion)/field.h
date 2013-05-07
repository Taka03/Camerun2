//*============================================================================
//field.h
//*============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Draw3DObject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�t�B�[���h�p�N���X
//=============================================================================
class CField :public CDraw3DObject
{
	private:
	
		Renderer::Object::IMapModel *m_pMapModel;//�}�b�v�̃��f���f�[�^
		Scene::IMapActor			*m_pActorMap[SCREEN_MAX];//�}�b�v�A�N�^�[
		Renderer::Object::ILine3D   *m_pLine3D;//�f�o�b�O���C��
		
	public:
	
		CField( const char *pName, Math::Vector3D vPos );//�R���X�g���N�^
		~CField();//�f�X�g���N�^
		
		void Init();//������
		void Exec();//����
		void Rendering( );//�����_�����O
		void Rendering( int index );//�����_�����O
		
		void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//�t�@�C���ǂݍ���
		void SetActorIndex( int index );//�A�N�^�[�C���f�b�N�X�̃Z�b�g
		
	public:
		
		void	CreateActor( int index, Scene::ISceneManager *pSceneMgr );//�A�N�^�[�̐���
		
		/*�Փ˔���p���C��*/
		void SetCollisionLine( Renderer::Object::ILine3D *pLine )
		{
			m_pLine3D = pLine;
		}
	
	/*Get�n*/
	public:
	
		/*�}�b�v���f���f�[�^�̎擾*/
		Renderer::Object::IMapModel *GetMapModel() const
		{
			return m_pMapModel;
		}
		
		/*�}�b�v�A�N�^�[�̎擾*/
		Scene::IMapActor *GetMapActor( int index ) const
		{
			return m_pActorMap[index];
		}

		
	
		
		
};