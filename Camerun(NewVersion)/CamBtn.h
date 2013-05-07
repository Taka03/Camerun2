//*============================================================================
//CamBtn.h
//*============================================================================
//[history]
//	08/12/04  �쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Sprite.h"
#include "camera.h"
#include "CamBar.h"
#include "player.h"

class CResourceManager;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	�J�����{�^���p�N���X
//=============================================================================
class CCamButton :	public CSprite
{
	private:
	
		CCamBar *m_pMarkerSpr;//��]�}�[�J�[
		CSprite *m_pResetBtnSpr;//�J�������Z�b�g�{�^��
		CSprite *m_pRollSpr;//����X�v���C�g
		bool m_IsCamMove;//�J�����ړ������ǂ���
		bool m_IsCamReset;//�J�������Z�b�g���ꂽ���ǂ���
	
	public:
	
		/*�R���X�g���N�^*/
		CCamButton( const char *pName, Math::Vector2D vPos );
		
		/*�f�X�g���N�^*/
		~CCamButton();
		
		//������
		void Init();
		
		/*�ǂݍ���*/
		void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );
		
		/*�����_�����O*/
		void Rendering();
		
		/*����*/
		void Exec();
	
		/*�ړ�*/
		void Move( CCamera *pCam[], CResourceManager *pResMgr, CPlayer *pPlayer );
		
		/*�J�������Z�b�g*/
		void Reset( CCamera *pCam[], CPlayer *pPlayer );
		
	public:
	
		
	public:
	
		/*�J�����ړ������ǂ���*/
		bool GetCamMoveFlag() const
		{
			return m_IsCamMove;
		}
		
		/*�J�������Z�b�g���ꂽ���ǂ���*/
		bool GetCamResetFlag() const
		{
			return m_IsCamReset;
		}
		
		/*���Z�b�g�{�^���X�v���C�g�̎擾*/
		CSprite *GetResetButton() const
		{
			return m_pResetBtnSpr;
		}
};
