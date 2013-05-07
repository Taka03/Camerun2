//*============================================================================
//Menu.h
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "Menu.h"
#include "SceneBase.h"


//=============================================================================
//�R���X�g���N�^
//=============================================================================
//[input]
//	pName:�f�[�^��
//	vPos:�\���ʒu
//	pMouse:�}�E�X�f�o�C�X
//===========================================================================
CMenu::CMenu( const char *pName, Math::Vector2D vPos, Peripheral::IMouse *pMouse ) 
 :m_pFontSpr(NULL),
  m_pMouse( pMouse ),
  CSprite( "window.png", vPos )
//  m_IsCheckMenu( false )
{
	m_pMouse->AddRef();	
	
	m_IsHitString = false;
	
	m_IsShowFrame = false;
	
	m_SelectIdx = 0;
	
	m_pFontSpr = new CFontSprite( pName, vPos );
	
	m_vecDrawStr.clear();
	
	m_strTitle.clear();

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CMenu::~CMenu()
{
	SAFE_RELEASE( m_pMouse );
	SAFE_DELETE( m_pFontSpr );
}

//============================================================================
//�t�@�C���ǂݍ���
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//	pFileMgr:�t�@�C���Ǘ��p�f�o�C�X
//===========================================================================
void CMenu::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	CSprite::Load( pRender, pFileMgr );
	
	m_pFontSpr->Load( pRender, pFileMgr );
}


//=============================================================================
//������
//=============================================================================
void CMenu::Init()
{
	CSprite::Init();
	
	m_pFontSpr->Init();
	
}

//=============================================================================
//�����_�����O
//=============================================================================
void CMenu::Rendering()
{
	/*�t�H���g�����j���[�ƘA��*/
	m_pFontSpr->SetVisibleFlag( GetVisibleFlag() );
	
	if( m_IsShowFrame )	
	{
		CSprite::Rendering();
	}
	
	if( m_pFontSpr->GetVisibleFlag() )
	{	
		m_pFontSpr->Rendering();	
	}
}

//=============================================================================
//����
//=============================================================================
void CMenu::Exec( )
{
	CSprite::Exec();
	
	/*���j���[�̕\��*/
	DrawMenu();
	
}

//=============================================================================
//���j���[�̕`��
//=============================================================================
void CMenu::DrawMenu()
{
		
	/*�`��J�n*/
	m_pFontSpr->GetFontSprite()->Begin();
	
	const float fMARGIN = 30.0f;
	
	Math::Vector2D vMousePos( toF( m_pMouse->GetPosX() ), toF( m_pMouse->GetPosY() ) );
	
	Uint32 MenuCount = 0;
	
	const Math::Point2DF fMARGIN_WIN( 190.0f, 10.0f );//�E�B���h�E����̗]��
	
	/*���j���[�^�C�g�����̕`��*/
	if( m_strTitle.length() > 0 )
	{
		Math::Point2DF Pos( m_vPos.x + fMARGIN_WIN.x, m_vPos.y + fMARGIN_WIN.y );
		
		m_pFontSpr->GetFontSprite()->DrawString( m_strTitle.c_str(), Pos, CColor( 255, 255, 255 ) );
	}
	
	/*���j���[���ڂ̕`��*/
	for( vector<StringList>::iterator i = m_vecDrawStr.begin();i != m_vecDrawStr.end();++i )
	{
		
		StringList strList = *i;
		
		string strTemp = strList.m_Str;
		
		Math::Point2DF Pos = strList.m_Pos;
								 
		Math::Rect2DF HitRect = strList.m_HitRect;
		
		bool IsEnable = strList.m_IsEnable;
		
		/*���j���[�Ƃ̓����蔻��*/
		if( IsEnable )
		{
			if( ::Collision::Point_Rect( vMousePos, HitRect ) && GetVisibleFlag() )
			{
				m_pFontSpr->GetFontSprite()->DrawString( strTemp.c_str(), Pos, CColor( 220, 0, 0 ) );
				m_SelectIdx = strList.priority;
				
				MenuCount = 0;
				
				m_IsHitString = true;
			
			}
		
			else
			{
				m_pFontSpr->GetFontSprite()->DrawString( strTemp.c_str(), Pos, CColor( 255, 255, 255 ) );
				
				MenuCount++;
				
				if( MenuCount == m_vecDrawStr.size() )
				{
					m_IsHitString = false;
				}
				
			}
		}
		
		else
		{
			if( ::Collision::Point_Rect( vMousePos, HitRect ) && GetVisibleFlag() )
			{
				
				MenuCount = 0;
				
				m_IsHitString = true;
			
			}
		
			else
			{
				MenuCount++;
				
				if( MenuCount == m_vecDrawStr.size() )
				{
					m_IsHitString = false;
				}
				
			}
			
			m_pFontSpr->GetFontSprite()->DrawString( strTemp.c_str(), Pos, CColor( 128, 128, 128, 128 ) );
			
		}
		
	}
	
	/*�`��I��*/
	m_pFontSpr->GetFontSprite()->End();
	
}

//=============================================================================
//�m�F���j���[�̐ݒ�
//=============================================================================
//[input]
//	strTitle:�^�C�g����
//===========================================================================
void CMenu::SetCheckMenu( string strTitle )
{
	const int CHECK_MENU_MAX = 2;
	
	CMenu::StringList strList;
	
	Math::Point2DF Pos[CHECK_MENU_MAX];//���j���[�̕\���ʒu
	
	/*���j���[���ږ�*/
	string strMenu[] =
	{
		"f e",//�n�C
		"e e 5",//�C�C�G
	};
	
	const float fMARGIN = 290.0f;
	const Math::Point2DF fMARGIN_WIN( 150.0f, 50.0f );//�E�B���h�E����̗]��
	
	//�^�C�g�����̐ݒ�
	m_strTitle = strTitle;
		
	for( int i = 0;	i < CHECK_MENU_MAX;++i )
	{
		Pos[i] = Math::Point2DF( m_vPos.x + toF( i * fMARGIN ) + fMARGIN_WIN.x, 
								 m_vPos.y + fMARGIN_WIN.y );
		
		
		strList.priority = i;
		strList.m_Pos = Pos[i];
		strList.m_Str = strMenu[i];
		strList.m_IsEnable = true;
		
		CFontSprite *pFontSpr = GetMenuFont();
		
		Math::Point2DF fSize = pFontSpr->GetFontSprite()->GetStringSize( strMenu[i].c_str() );
		
		strList.m_HitRect.Set( Pos[i].x, Pos[i].y, fSize.x, fSize.y );
		
		/*�`�敶���񃊃X�g�ɒǉ�*/
		SetStringList( strList );
		
	}
	
	/*�m�F��ʂ̎��́A��U�������Ă���*/
	SetVisibleFlag( false );
}







