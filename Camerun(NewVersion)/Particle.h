//*============================================================================
//Particle.h
//*============================================================================
//[history]
//	08/06/07 �쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Draw3DObject.h"

//=============================================================================
//define
//=============================================================================
const int PARTS_DIVIDE = 8;
const int BOMB_MAX = 8;
const int PERTICLE_MAX = (PARTS_DIVIDE * PARTS_DIVIDE) * BOMB_MAX;
const int BOMB_ALIVE_TIME = 60;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�p�[�e�B�N���`��p�I�u�W�F�N�g
//=============================================================================
class CParticle :	public CDraw3DObject
{
	protected:
	
		Selene::Renderer::ITexture *m_pTex;//�e�N�X�`���p�n���h��
		Selene::Renderer::Object::IParticle *m_pParticle;//�p�[�e�B�N���p�n���h��
		Selene::Scene::IParticleActor *m_pActorParticle[SCREEN_MAX];//�p�[�e�B�N���A�N�^�[
		Renderer::IRender *m_pRender;//�����_���[�p�f�o�C�X
		
	protected:
	
		Sint32 m_Width;//��
		Sint32 m_Height;//����
		
		Math::Point3D<Uint8> m_Alpha;//�A���t�@�l
	
	public:
	
		CParticle( const char *pName, Math::Vector3D vPos );//�R���X�g���N�^
		~CParticle(void);//�f�X�g���N�^
		
		virtual void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//�t�@�C���ǂݍ���
		void CreateActor( int index, Scene::ISceneManager *pSceneMgr );//�A�N�^�[�̐���

		void Init(){};//������
		void Exec();//����
		void Rendering( int index );//�����_�����O
		
	/*Set�n*/
	public:
	
		/*�����_�����O�f�o�C�X�̐ݒ�*/
		void SetRenderDevice( Renderer::IRender *pRender )
		{
			m_pRender = pRender;
			pRender->AddRef();
		}
		
		/*�A���t�@�l�̐ݒ�*/
		void SetAlpha( Math::Point3D<Uint8> Alpha)
		{
			m_Alpha = Alpha;
		}
		
	/*Get�n*/
	public:

		//�e�N�X�`���p�n���h���̎擾
		Selene::Renderer::ITexture *GetTexture() const
		{
			return m_pTex;
		}
		
		//�p�[�e�B�N���p�n���h���̎擾
		Selene::Renderer::Object::IParticle *GetParticle() const
		{
			return m_pParticle;
		}
		
};
