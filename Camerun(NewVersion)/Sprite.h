//*============================================================================
//Sprite.h
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
#include "draw2dobject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�X�v���C�g�`��p�I�u�W�F�N�g
//=============================================================================
class CSprite :	public CDraw2DObject
{
	private:
	
	protected:
	
		Selene::Renderer::ITexture *m_pTex;//�e�N�X�`���p�n���h��
		Selene::Renderer::Object::ISprite2D *m_pSpr;//�X�v���C�g�p�n���h��
	
	protected:
	
		Math::Point2DI m_DivNum;//������
		Math::Point2DI m_Anim;//�A�j��ID
	
		Math::Point2DF m_fSize;//�摜�T�C�Y
		
		Math::Rect2DF m_DstRect;//�`����`
		Math::Rect2DF m_SrcRect;//�`�挳��`
				
		Sint32 m_AnimTime;//�A�j���[�V��������
		Sint32 m_AnimCount;//�A�j���[�V�����J�E���^
		
		Math::Rect2DF m_HitRect;//�����蔻��p��`
		
		bool m_IsAnim;//�A�j���[�V���������邩
		
	public:
	
		CSprite( const char *pName, Math::Vector2D vPos );//�R���X�g���N�^
		CSprite( const char *pName, Math::Vector2D vPos, Math::Point2DI DivNum );//�R���X�g���N�^
		~CSprite(void);//�f�X�g���N�^
		
		virtual void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//�t�@�C���ǂݍ���

		void Init(){};//������
		void Exec();//����
		void Rendering();//�����_�����O
		void Draw();//�`��
		
		void DrawGrayScale( Renderer::IRender *pRender );//�O���[�X�P�[���`��
		
		void CreateSprite( Renderer::IRender *pRender, Uint32 Num );//�X�v���C�g�̐��� 
		
		void AddRef();//�Q�ƃJ�E���^�̑���
		
		void SetAnimation();//�A�j���[�V�����̐ݒ�
		
	/*Set�n*/
	public:
		
		/*�e�N�X�`���n���h���̐ݒ�*/
		void SetTexture( Renderer::ITexture *pTex )
		{
			m_pTex = pTex;
		}
		
		//�������̐ݒ�	
		void SetDivNum( Math::Point2DI divnum )
		{
			m_DivNum = divnum;
			
			m_fSize.x = toF( m_pTex->GetOriginalSize().x / divnum.x );
			m_fSize.y = toF( m_pTex->GetOriginalSize().y / divnum.y );
			
		}
		
		/*X�����������̐ݒ�*/
		void SetDivNumX( int x )
		{
			SetDivNum( Math::Point2DI( x, m_DivNum.y ) );
		}
		
		/*Y�����������̐ݒ�*/
		void SetDivNumY( int y )
		{
			SetDivNum(  Math::Point2DI( m_DivNum.x, y ) );
		}
		
		//�A�j���[�V����ID�̐ݒ�
		void SetAnimID( Math::Point2DI anim )
		{
			m_Anim = anim;
		}
		
		//�A�j���[�V����ID(X���W)�̐ݒ�
		void SetAnimXID( int x )
		{
			SetAnimID( Math::Point2DI( x, m_Anim.y ) );
		}
		
		//�A�j���[�V����ID(Y���W)�̐ݒ�
		void SetAnimYID( int y )
		{
			SetAnimID( Math::Point2DI( m_Anim.x, y ) );
		}
		
		/*�摜�T�C�Y�̐ݒ�*/
		void SetGraphSize( Math::Point2DF Size )
		{
			m_fSize = Size;
		}
		
		/*�A�j���[�V�����t���O�̐ݒ�*/
		void SetAnimFlag( bool flag )
		{
			m_IsAnim = flag;
		}
		
		/*�`����`�̐ݒ�*/
		void SetDstRect( Math::Rect2DF Dst )
		{
			m_DstRect = Dst;
		}
		
		/*�`�挳��`�̐ݒ�*/
		void SetSrcRect( Math::Rect2DF Src )
		{
			m_SrcRect = Src;
		}
		
	/*Get�n*/
	public:

		//�e�N�X�`���p�n���h���̎擾
		Selene::Renderer::ITexture *GetTexture() const
		{
			return m_pTex;
		}
		
		//�X�v���C�g�p�n���h���̎擾
		Selene::Renderer::Object::ISprite2D *GetSprite() const
		{
			return m_pSpr;
		}
		
		/*�摜�T�C�Y�̎擾*/
		Math::Point2DF GetSize() const
		{
			return m_fSize;
		}
		
		/*�����蔻���`�̎擾*/
		Math::Rect2DF GetHitRect() const
		{
			return m_HitRect;
		}
		
		//�A�j��ID�̎擾
		Math::Point2DI GetAnimID() const
		{
			return m_Anim;
		}
		
};
