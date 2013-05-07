//*============================================================================
//SceneResult.h
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
//const
//=============================================================================
const int MINSSION_MAX = 5;//�~�b�V�����̍ő吔

//=============================================================================
//class
//=============================================================================
//[Desc]
//	���U���g���
//=============================================================================
class CSceneResult :	public CSceneTemplate
{
	public:
	
		//�~�b�V��������
		enum eMissionResult
		{
			RESULT_FAILURE,//�~�b�V�������s
			RESULT_SUCCESS,//�~�b�V��������
			RESULT_MAX
		};
	
	private:
	
		eMissionResult m_eMissionRes;//�~�b�V��������
	
	private:
	
		CPhoto *m_pPhoto[FILM_MAX];//�ʐ^�̕\��
		CFontSprite *m_pScoreFont;//���v�t�H���g
		CFontSprite *m_pListNameFont;//���X�g���t�H���g
		CFontSprite *m_pListNumFont;//���X�g�X�R�A�t�H���g
		CFontSprite *m_pTotalScFont;//���v�_�t�H���g
		
		CSprite *m_pBGSpr;//BG
		CSprite *m_pScoreSpr;//�X�R�A�X�v���C�g
		CSprite *m_pExtBtnSpr;//�I���{�^���X�v���C�g
		
		CSprite *m_pTargetOKSpr;//�^�[�Q�b�g�����݂���Ƃ��ɕ\��
		CSprite *m_pTargetNGSpr;//�^�[�Q�b�g�����݂��Ȃ��Ƃ��ɕ\��
		
		CBGM *m_pResultBGM;//���U���gBGM
		
		int m_SelectIdx;//�ʐ^�Z���N�g�C���f�b�N�X
	
	public:
	
		CSceneResult( string strFileName );//�R���X�g���N�^
		virtual ~CSceneResult(void);//�f�X�g���N�^
		
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
	
		void DrawBigPhoto();//�傫���ʐ^�̕`��
		void DrawMinPhoto();//�������ʐ^�̕`��
		
		void SetPhotoInfo();//�ʐ^���̃Z�b�g
		void DrawPhotoInfo( );//�ʐ^���̕`��
		
		void AddPhotoCount();//�ʐ^�J�E���g�̑�������
		
		void CountUpScore();//�X�R�A�̃J�E���g�A�b�v
		
		void ShowTargetResult();//�^�[�Q�b�g���܂܂�Ă��邩�̕\��
		
	public:		
		/*�~�b�V�������ʂ̐ݒ�*/
		void SetResult( eMissionResult eResult )
		{
			m_eMissionRes = eResult;
		}
		
	public:
		
		/*�~�b�V�������ʂ̎擾*/
		eMissionResult GetResult() const
		{
			return m_eMissionRes;
		}
	
};
