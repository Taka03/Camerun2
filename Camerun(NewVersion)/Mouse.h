//*============================================================================
//Mouse.h
//*============================================================================
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Application.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�}�E�X�p�N���X
//=============================================================================
class CMouse
{
	private:
	
		static Peripheral::IMouse *m_pMouse;//�}�E�X�f�o�C�X
		static Math::Vector2D m_vPos;//�}�E�X�̈ʒu
		
		
	public:
	
		//�R���X�g���N�^
		CMouse( ICore *pCore );
		
		//�f�X�g���N�^
		~CMouse();
		
	/*Get�n*/
	public:
		
		/*�}�E�X�f�o�C�X�̎擾*/
		static Peripheral::IMouse *GetMouse( )
		{
			return m_pMouse;
		}
		
		//�}�E�X�ʒu�̎擾
		static Math::Vector2D GetMousePos()
		{
			m_vPos.x = toF( GetMouse()->GetPosX() );
			m_vPos.y = toF( GetMouse()->GetPosY() );
			
			return m_vPos;
		}
		
};