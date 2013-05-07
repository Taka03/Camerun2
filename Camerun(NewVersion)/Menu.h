//*============================================================================
//Menu.h
//*============================================================================
//[history]
//	08/03/05�@�쐬
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "FontSprite.h"
#include "Sprite.h"

//=============================================================================
//using
//=============================================================================
using namespace std;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	���j���[�p
//=============================================================================
class CMenu : public CSprite
{
	public:
	
		/*�����񃊃X�g*/
		struct StringList
		{
			Uint32 priority;//����
			Math::Point2DF m_Pos;//�����ʒu
			string m_Str;//������
			Math::Rect2DF m_HitRect;//�����蔻��̈�
			bool m_IsEnable;//���j���[�����p�ł��邩
			bool m_IsHitString;//������ɓ������Ă��邩
			
			StringList()
			{	
				m_Pos.x = 0;
				m_Pos.y = 0;
				m_Str.clear();
				m_HitRect.Set( 0, 0, 0, 0 );
				m_IsEnable = true;
				m_IsHitString = false;
			}
			
		};
		
	private:
	
		CFontSprite *m_pFontSpr;//�t�H���g�X�v���C�g
		string m_strTitle;//�^�C�g����
		vector<StringList> m_vecDrawStr;//���j���[������
		int m_SelectIdx;//�Z���N�g����
		bool m_IsHitString;//������ɓ������Ă��邩
		bool m_IsShowFrame;//�t���[����\�������邩
		//bool m_IsCheckMenu;//�m�F���j���[���ǂ���
		Peripheral::IMouse *m_pMouse;//�}�E�X�f�o�C�X
		
	
	public:
	
		CMenu( const char *pName, Math::Vector2D vPos, Peripheral::IMouse *pMouse );//�R���X�g���N�^
		~CMenu();//�f�X�g���N�^
		
		void Init();//������
		void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//�t�@�C���ǂݍ���
		void Rendering();//�����_�����O
		void Exec();//����
		
		void SetCheckMenu( string strTitle );//�m�F���j���[�̐ݒ�
		
		void DrawMenu();//���j���[�̕`��
		void DrawCheckMenu();//�`�F�b�N���j���[�̕`��
		
	
	public:
	
		//�`�敶���񃊃X�g�̐ݒ�
		void SetStringList( StringList strList )
		{
			m_vecDrawStr.push_back( strList );
		}
		
		/*�^�C�g�����̐ݒ�*/
		void SetTitleString( string strTitle )
		{
			m_strTitle = strTitle;
		}
		
		//�t���[����\�����邩�ݒ�
		void SetShowFrameFlag( bool flag )
		{
			m_IsShowFrame = flag;
		}
			
		///*�m�F���j���[���ǂ����ݒ�*/
		//void SetIsCheckMenu( bool flag )
		//{
		//	m_IsCheckMenu = flag;
		//}
		//
	public:
	
		/*���j���[�t�H���g�̎擾*/
		CFontSprite *GetMenuFont() const
		{
			return m_pFontSpr;
		}
	
		/*�Z���N�g���ڂ̎擾*/
		int GetSelectIndex() const
		{
			return m_SelectIdx;
		}
		
		/*������ɓ������Ă��邩�ǂ����̎擾*/
		bool GetHitStringFlag() const
		{
			return m_IsHitString;
		}
		
		//�����񃊃X�g�̎擾
		StringList GetStringList( int No ) const
		{
			m_vecDrawStr.at( No );
		}
		
		void SetStringFlag( int No, bool flag )
		{
			m_vecDrawStr.at( No ).m_IsEnable = flag;
		}
		
		
		
		
		
};