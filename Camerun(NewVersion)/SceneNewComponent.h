//*============================================================================
//SceneNewComponent.h
//*============================================================================
//[history]
//	08/12/26  �쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "SceneTemplate.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�V�v�f�\�����
//=============================================================================
class CSceneNewComponent :	public CSceneTemplate
{
	public:
	
	private:
	
		CFontSprite *m_pClearFont;//�N���A�����t�H���g
		
		CSprite *m_pBGSpr;//�w�i
		CSprite *m_pClearSpr;//�Q�[���N���A
		CSprite *m_pFailSpr;//�Q�[�����s
	
	public:
	
		CSceneNewComponent( string strFileName );//�R���X�g���N�^
		virtual ~CSceneNewComponent(void);//�f�X�g���N�^
		
	public:
	
		/*�I�u�W�F�N�g�f�[�^�̏�����*/
		void InitObjectData( Uint32 dt );
		
		/*������*/
		void Init( Uint32 dt );
		
		/*�ҋ@��*/
		void Idle( Uint32 dt );
		
		/*�����_�����O*/
		void Rendering();
		
	public:
	
		void DrawMessage();//���b�Z�[�W�̕`��
	
};
