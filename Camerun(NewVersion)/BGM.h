//*============================================================================
//BGM.h
//*============================================================================
//[history]
//	08/03/16�@�쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Sound.h"

//=============================================================================
//class
//=============================================================================
//[desc]
//	BGM�Đ��p�N���X
//=============================================================================
class CBGM :	public CSoundObject
{
	private:
	
		Sound::IStreamSound *m_pBGM;//BGM�Đ��p�f�o�C�X
	
	public:
	
		CBGM( const char *pName );//�R���X�g���N�^
		virtual ~CBGM(void);//�f�X�g���N�^
		
		virtual void LoadSound( ICore *pCore, File::IFileManager *pFileMgr );//�T�E���h�̓ǂݍ���
		
		void Init(){};//������
		
		//�Đ�
		void Play( Sound::SPlayBlock *pTbl, int count );
		
		void Exec();//����
		
		void FadeOut();//�t�F�[�h�A�E�g
		
		void AddRef();//�Q�ƃJ�E���^�̑���
		
	/*Get�n*/
	public:

		//���ʉ��Đ��p�f�o�C�X�̎擾	
		Sound::IStreamSound *GetBGMDevice() const
		{
			return m_pBGM;
		}
		
};
