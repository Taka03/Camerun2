//*============================================================================
//ExpWindow.h
//*============================================================================
//[history]
//	08/12/13�@�쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Sprite.h"
#include "FontSprite.h"

//=============================================================================
//variable
//=============================================================================
class CResourceManager;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�E�B���h�E�`��p�I�u�W�F�N�g
//=============================================================================
class CExpWindow :	public CSprite
{
	private:
	
		CFontSprite *m_pTrlFontSpr;//�`���[�g���A���p�t�H���g
		Uint32 m_StrCount;//������J�E���g
		Uint32 m_OldStrCount;//������J�E���g�o�b�N�A�b�v
	
	public:
	
		CExpWindow( const char *pName, Math::Vector2D vPos );//�R���X�g���N�^
		~CExpWindow(void);//�f�X�g���N�^
		
		void Init();//������
		
		/*�ǂݍ���*/
		void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );
		
		/*�����_�����O*/
		void Rendering();
		
		/*����*/
		void Exec();
		
		/*�`���[�g���A�����̐ݒ�*/
		void SetTutorialExp( File::IFileManager *pFileMgr );
		
		/*������J�E���g�̑���*/
		//[input]
		//	dt:���������镝
		void AddStrCount( int dt )
		{
			m_StrCount += dt;
		}
		
		//������J�E���g�̐ݒ�
		void SetStrCount( Uint32 count )
		{
			m_StrCount = count;
		}
		
		//������J�E���g(�o�b�N�A�b�v)�̐ݒ�
		void SetOldStrCount( Uint32 count )
		{
			m_OldStrCount = count;
		}
		
	public:
	
		/*������J�E���g�̎擾*/
		Uint32 GetStrCount() const
		{
			return m_StrCount;
		}
		
		//�o�b�N�A�b�v�p������J�E���g�̎擾
		Uint32 GetInitStrCount() const
		{
			return m_OldStrCount;
		}

		
		/*�`���[�g���A���t�H���g�̎擾*/
		CFontSprite *GetTrlFont() const
		{
			return m_pTrlFontSpr;
		}
		
		/*���݂̕�����̎擾*/
		string GetNowString() const
		{
			return m_pTrlFontSpr->GetVecString().at( m_StrCount );
		}
		
	
	
		
};
