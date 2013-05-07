//*============================================================================
//Draw2DObject.h
//*============================================================================
//[history]
//	08/03/16 �쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "drawobject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	2D�`��p�I�u�W�F�N�g
//=============================================================================
class CDraw2DObject :	public CDrawObject
{
	protected:
	
		Math::Vector2D m_vPos;//�ʒu
		Math::Vector2D m_vInitPos;//�����ʒu
		Math::Point2DI m_Rot;//��]�p�x
		Math::Point2DI m_InitRot;//�����p�x
		Math::Vector2D m_vScale;//�X�P�[��
		Math::Vector2D m_vInitScale;//�����X�P�[��
	
	public:
	
		CDraw2DObject( const char *pName, Math::Vector2D vPos );//�R���X�g���N�^
		~CDraw2DObject(void);//�f�X�g���N�^
		
		virtual void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr ){};//�t�@�C���ǂݍ���
		
		void Init();//������
		void Exec(){};//����
		virtual void Rendering(){};//�����_�����O
		
	public:
	
		//�ʒu�̐ݒ�
		void SetPosition( Math::Vector2D vPos )
		{
			m_vPos = vPos;
		}
		
		/*�����ʒu�̐ݒ�*/
		void SetInitPosition( Math::Vector2D vPos )
		{
			m_vInitPos = vPos;
		}
		
		//��]�p�x�̐ݒ�
		void SetRotate( Math::Point2DI Rot )
		{
			m_Rot = Rot;
		}
		
		//X�����̉�]�p�x�̐ݒ�
		void SetXRotate( Sint32 RotX )
		{
			m_Rot.x = RotX;
		}
		
	public:
	
		//�ʒu�̎擾
		Math::Vector2D GetPosition() const
		{
			return m_vPos;
		}
		
		/*�������W�̎擾*/
		Math::Vector2D GetInitPos() const
		{
			return m_vInitPos;
		}
		
		
		//��]�p�x�̎擾
		Math::Point2DI GetRotate() const
		{
			return m_Rot;
		}
		
		//�g�k�̎擾
		Math::Vector2D GetScale() const
		{
			return m_vScale;
		}
		
};
