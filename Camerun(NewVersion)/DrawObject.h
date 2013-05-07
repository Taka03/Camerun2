//*============================================================================
//DrawObject.h
//*============================================================================
//[history]
//	08/03/03 �C���J�n
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "gameobject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�`��p�I�u�W�F�N�g
//=============================================================================
class CDrawObject :public CGameObject
{
	protected:
		
		bool m_IsStop;//�Î~����t���O
		bool m_IsVisible;//�\������t���O
		
	public:
	
		//�R���X�g���N�^
		CDrawObject( const char *pName );
		
		//�f�X�g���N�^
		virtual ~CDrawObject(void){};
		
		//������
		virtual void Init();
		
		//����
		virtual void Exec(){};
		
		//�t�@�C���ǂݍ���
		virtual void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr ) = 0;
		
		//�����_�����O
		virtual void Rendering() = 0;
		
	/*Set�n*/
	public:
	
		/*�\���t���O�̐ݒ�*/
		void SetVisibleFlag( bool IsVisible )
		{
			m_IsVisible = IsVisible;
		}
		
		/*�Î~�t���O�̐ݒ�*/
		void SetStopFlag( bool IsStop )
		{
			m_IsStop = IsStop;
		}
		
	public:
		
		//�\���t���O�̎擾
		bool GetVisibleFlag() const
		{
			return m_IsVisible;
		}
		
		//�Î~�t���O�̎擾		
		bool GetStopFlag() const
		{
			return m_IsStop;
		}
		
		
};
