//*============================================================================
//Sprite3D.h
//*============================================================================
//[history]
//	08/03/19�@�쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Draw3DObject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�X�v���C�g�`��p�I�u�W�F�N�g
//=============================================================================
class CSprite3D :	public CDraw3DObject
{
	protected:
	
		Selene::Renderer::ITexture *m_pTex;//�e�N�X�`���p�n���h��
		Selene::Renderer::Object::ISprite3D *m_pSpr;//�X�v���C�g�p�n���h��
		Selene::Scene::ISpriteActor *m_pActorSprite[SCREEN_MAX];//�X�v���C�g�A�N�^�[
	
	protected:
	
		Math::Matrix m_matWorld;//���[�J���s��
		
		Math::Point2DI m_DivNum;//������
		Math::Point2DI m_Anim;//�A�j��ID
	
		Sint32 m_Width;//��
		Sint32 m_Height;//����
	
	public:
	
		CSprite3D( const char *pName, Math::Vector3D vPos );//�R���X�g���N�^
		~CSprite3D(void);//�f�X�g���N�^
		
		virtual void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//�t�@�C���ǂݍ���
		void CreateActor( int index, Scene::ISceneManager *pSceneMgr );//�A�N�^�[�̐���

		void Init(){};//������
		void Exec();//����
		void Rendering( );//�����_�����O
		
		void AddRef();//�Q�ƃJ�E���^�̑���
		
		void SetActorIndex( int index );//�A�N�^�[�C���f�b�N�X�̐ݒ�
		
	/*Set�n*/
	public:
	
		/*���[�J���s��̐ݒ�*/
		void SetMatWorld( Math::Matrix &mat )
		{
			m_matWorld = mat;
		}
		
		/*�������̐ݒ�*/
		void SetDivNum( Math::Point2DI Divnum )
		{
			m_DivNum = Divnum;
		}
		
		/*�A�j���[�V����ID�̐ݒ�*/
		void SetAnimID( Math::Point2DI animID )
		{
			m_Anim = animID;
		}
		
	/*Get�n*/
	public:

		//�e�N�X�`���p�n���h���̎擾
		Selene::Renderer::ITexture *GetTexture() const
		{
			return m_pTex;
		}
		
		//�X�v���C�g�p�n���h���̎擾
		Selene::Renderer::Object::ISprite3D *GetSprite() const
		{
			return m_pSpr;
		}
		
};
