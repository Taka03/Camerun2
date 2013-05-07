//*============================================================================
//FontSprite3D.h
//*============================================================================
//[history]
//	08/03/16 �쐬
//	08/11/19 �C���J�n
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Draw3DObject.h"

#include <string>

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�t�H���g�X�v���C�g�`��p�I�u�W�F�N�g
//=============================================================================
class CFontSprite3D :	public CDraw3DObject
{
	private:
		
		Renderer::Object::IFontSprite3D *m_pFontSpr3D;//�t�H���g�X�v���C�g�p�n���h��
		Scene::IParticleActor *m_pActorFont[SCREEN_MAX];//�t�H���g�A�N�^�[
		Math::Point2DF m_fSize;//�T�C�Y
		std::string m_Str;//�\�����镶��
		
		Renderer::IRender *m_pRender;//�����_���[
	
	public:
	
		CFontSprite3D( const char *pName, Math::Vector3D vPos );//�R���X�g���N�^
		
		virtual ~CFontSprite3D(void);//�f�X�g���N�^
		
		void Init(){};//������
		void Exec();//����
		void Rendering();//�����_�����O
		
		void CreateActor( int index, Scene::ISceneManager *pSceneMgr );//�A�N�^�[�̐���
		void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//�ǂݍ���
		void SetActorIndex( int index );//�A�N�^�[�C���f�b�N�X�̃Z�b�g
		
	/*Set�n*/
	public:
	
		//�`�悷�镶���̐ݒ�
		void SetDrawString( std::string str )
		{
			m_Str = str;
		}
		
	/*Get�n*/	
	public:
	
		//�t�H���g�X�v���C�g�p�n���h���̎擾
		Renderer::Object::IFontSprite3D *GetFontSprite() const
		{
			return m_pFontSpr3D;
		}
		
		/*�t�H���g�A�N�^�[�̎擾*/
		Scene::IParticleActor *GetFontActor( int index ) const
		{
			return m_pActorFont[index];
		}	
		
	
};
