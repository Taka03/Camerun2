//*============================================================================
//SoundManager.h
//*============================================================================
//[history]
//	08/12/27  �쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Sound.h"
#include "SoundEffect.h"

class CResourceManager;

//=============================================================================
//class
//=============================================================================
//[desc]
//	�T�E���h�Ǘ��p�N���X
//=============================================================================
class CSoundManager :	public CSoundObject
{
	public:
	
		
	
	public:
	
		/*�T�E���h�^�C�v*/
		enum eSoundType
		{
			SND_SELECT,//�Z���N�g��
			SND_DECIDE,//���艹
			SND_NEW,//�V�v�f��
			SND_MESSAGE,//���b�Z�[�W��
			SND_PROHIBIT,//�֎~��
			SND_SHOWENEMY,//�G�o����
			SND_PLAYERMOVE,//�v���C���[�ړ���
			SND_GETDOWN,//���n��
			SND_BITE,//���ݕt����
			SND_BOOST,//�u�[�X�g��
			SND_SHUTTER,//�V���b�^�[��
			SND_TRAIN,//�d�ԉ�
			SND_BIRD,//�g���̉�
			SND_MOUSE,//�˂��݂̉�
			SND_RIZARDMOVE,//�g�J�Q�ړ���
			SND_CLEAR,//�~�b�V�����N���A��
			SND_FAIL,//�~�b�V�������s��
			SND_CHANGE,//�`�F���W��
			SND_CALCSCORE,//���_�v�Z
			SND_EXIT,//�I��
			SND_MAX,//�T�E���h�̍ő吔
		};
		
	private:
	
		CSoundEffect *m_pSoundObj[SND_MAX];//�T�E���h�I�u�W�F�N�g
	
	public:
	
		CSoundManager(void);//�R���X�g���N�^
		~CSoundManager(void);//�f�X�g���N�^
		
		void PushResource( CResourceManager *pResMgr );//���\�[�X�̒ǉ�
	
		void Play( eSoundType Type );//���̍Đ�
		void Stop( eSoundType Type );//���̒�~
		void SetVolume( eSoundType Type, float fVolume );//���ʒ���
		void SetPan( eSoundType Type, float fPan );//�p���ݒ�
};
