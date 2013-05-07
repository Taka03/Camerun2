//*============================================================================
//SceneManager.h
//*============================================================================
//[history]
//	08/03/05�@�쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Selene.h"

//=============================================================================
//using
//=============================================================================
using namespace Selene;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�V�[��(3D)�Ǘ��p�N���X
//=============================================================================
class CSceneManager
{
	private:
	
		Renderer::IRender *m_pRender;//�����_���[�f�o�C�X
		Scene::ISceneManager *m_pSceneMgr;//�V�[���Ǘ��p�f�o�C�X
		//Scene::ICustomizedSceneManager *m_pSceneMgr;//�V�[���Ǘ��p�f�o�C�X
		
	private:
	
		Sint32 m_RenderTargetWidth;//�`��̈敝
		Sint32 m_RenderTargetHeight;//�`��̈捂��
		
		bool m_IsRenderTex;//�e�N�X�`���Ƀ����_�����O���邩
	
		Renderer::ITexture *m_pRenderTex;//�����_�����O�^�[�Q�b�g�p�e�N�X�`��
	
	public:
	
		CSceneManager( Renderer::IRender *pRender );//�R���X�g���N�^
		~CSceneManager(void);//�f�X�g���N�^
		
	public:
	
		void CreateDevice( bool IsRenderTex );//�f�o�C�X�̐���
		void SetParameter( );//�p�����[�^�[�̐ݒ�
		void SetInitParameter( );//�����p�����[�^�̐ݒ�
		void CreateSkyDoom( Renderer::ITexture *pTex );//�X�J�C�h�[���̐���
	
	/*Set�n*/
	public:
	
		void SetRenderSize( Sint32 width, Sint32 height );//�`��̈�T�C�Y�̐ݒ�
		void SetRenderPos( Math::Vector2D vPos );//�`��ʒu�̐ݒ�
		
	/*Get�n*/
	public:
		
		/*�V�[���Ǘ��p�f�o�C�X�̎擾*/
		Scene::ISceneManager *GetSceneMgr() const
		{
			return m_pSceneMgr;
		}
		
		/*�V�[���Ǘ��p�f�o�C�X�̎擾*/
		//Scene::ICustomizedSceneManager *GetSceneMgr() const
		//{
		//	return m_pSceneMgr;
		//}
		
		
		//�`��̈敝�̎擾	
		Sint32 GetRenderWidth() const
		{
			return m_RenderTargetWidth;
		}
		
		//�`��̈敝�̎擾		
		Sint32 GetRenderHeight() const
		{
			return m_RenderTargetHeight;
		}
		
		//�����_�����O�^�[�Q�b�g�p�e�N�X�`���̎擾
		Renderer::ITexture *GetRenderTex() const
		{
			return m_pRenderTex;
		}
		
		
};
