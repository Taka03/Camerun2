//*============================================================================
//Photo.h
//*============================================================================
//[history]
//	08/03/11�@�쐬
//	08/04/01  �X�v���C�g�̌p���ɕύX
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Sprite.h"
#include <vector>

using namespace std;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�ʐ^�p�N���X
//=============================================================================
class CPhoto :public CSprite
{
	
	public:
	
		/*�ʐ^����̏��*/
		struct PhotoCheckData
		{
			Uint32 m_Score;//���_
			string m_strTargetName;//�^�[�Q�b�g��
			
			PhotoCheckData()
			{
				m_Score = 0;
				m_strTargetName.clear();
			}
		};
	
	private:
	
		Uint32 m_TotalScore;//�ʐ^�̍��v���_
		vector< PhotoCheckData > m_vecPhotoData;//�ʐ^�ɓ����Ă���^�[�Q�b�g��
		vector< string > m_vecTargetName;//�^�[�Q�b�g��
		vector< string > m_vecTargetScore;//�X�R�A
		int m_Score;//���v�X�R�A
		
	public:
	
		CPhoto( const char *pName, Math::Vector2D vPos, vector< PhotoCheckData > vecCheckData );//�R���X�g���N�^
		
		void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//�t�@�C���ǂݍ���
		
		void SetPhotoInfo();//�^�[�Q�b�g���̃Z�b�g
		
	public:
	
		//�ʐ^�f�[�^�̐ݒ�
		void SetPhotoData( vector< PhotoCheckData > vecPhotoData )
		{
			m_vecPhotoData = vecPhotoData;
		}
	
			
	/*Get�n*/
	public:
	
		/*�ʐ^�f�[�^�̎擾*/
		vector< PhotoCheckData > GetVecPhotoData() const
		{
			return m_vecPhotoData;
		}
		
		//�^�[�Q�b�g���̎擾
		vector< string > GetVecTargetName() const
		{
			return m_vecTargetName;
		}
		
		//�^�[�Q�b�g�X�R�A�̎擾
		vector< string > GetVecTargetScore() const
		{
			return m_vecTargetScore;
		}
		
		//���v�̎擾
		int GetScore() const
		{
			return m_Score;
		}
};
