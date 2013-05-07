//*============================================================================
//ScenePhoto.h
//*============================================================================
//[history]
//	08/03/11�@�쐬
//	08/11/11  �C��
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
//	�Q�[���V�[��(�ʐ^)�N���X
//=============================================================================
class CScenePhoto :	public CSceneTemplate
{
	public:
	
		/*�ʐ^�m�F*/
		enum eSelectPhoto
		{
			SELECT_REGIST,//�ʐ^���c��
			SELECT_DESTROY,//�ʐ^���̂Ă�
			SELECT_MAX,
		};
	
	private:
	
		CPhoto *m_pPhoto;//�ʐ^�p�I�u�W�F�N�g
		CMenu  *m_pCheckMenu;//�ʐ^�ۑ��m�F���j���[
		CSprite *m_pBG;//�w�i
		CFontSprite *m_pScoreFont;//�X�R�A�t�H���g
		
		eSelectPhoto m_eSelPhoto;//�ʐ^�m�F
		
		bool m_IsShowMenu;//���j���[���\������Ă��邩
		
	private:
		
		/*�ʐ^�m�F���\�b�h*/
		typedef void (CScenePhoto::*SelectFunc)();
		
		void RegistPhoto();//�ʐ^�̓o�^
		void RemovePhoto();//�ʐ^�̔j��
	
	public:
	
		CScenePhoto( string strFileName );//�R���X�g���N�^
		virtual ~CScenePhoto(void);//�f�X�g���N�^
		
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
	
		void SelectFuncExec();//�Z���N�g�̏���
		void SetCheckMenu();//�ʐ^�m�F���j���[�̐ݒ�
		void MoveScene( eSelectPhoto eScene );//�V�[���̈ړ�
		
	public:
	
		void PhotoSaveScript();//�ʐ^�B�e�X�N���v�g
		void RenderMenu();//���j���[�̃����_�����O
		
	public:
	
		//�\������ʐ^�̃Z�b�g	
		void SetPhoto( CPhoto *pPhoto )
		{
			m_pPhoto = pPhoto;
		}
		
		//�ʐ^�m�F��ʂ̐ݒ�
		void SetSelectScene( eSelectPhoto eSelect )
		{
			m_eSelPhoto = eSelect;
		}
		
	public:
	
		/*���̃V�[���̎擾*/
		eSelectPhoto GetSelectScene() const
		{
			return m_eSelPhoto;
		}

		
		
		
};
