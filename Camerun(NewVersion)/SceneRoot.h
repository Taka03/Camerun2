//*============================================================================
//SceneRoot.h
//*============================================================================
//[history]
//	08/10/08�@�쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "SceneBase.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�Q�[���V�[���̃��[�g�N���X
//=============================================================================
class CSceneRoot :public CSceneBase
{
	private:
	
	
	public:
		//�R���X�g���N�^
		CSceneRoot();
		//�f�X�g���N�^
		~CSceneRoot();
		
	public:
	
		//������
		virtual void Init() = 0;
		//�ҋ@���
		virtual void Idle() = 0;
		//�I��
		virtual void End() = 0;
		//�X�V
		virtual eSceneState Update() = 0;
		
		
};
