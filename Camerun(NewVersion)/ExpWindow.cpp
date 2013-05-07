//*============================================================================
//ExpWindow.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "ExpWindow.h"
#include "FileLoader.h"
#include <fstream>

//=============================================================================
//namespace
//=============================================================================
namespace
{
	Math::Vector2D vMousePos( 0.0f, 0.0f );
	Math::Vector2D vDir( 0.0f, 0.0f );
	Math::Vector3D vPos( 0.0f, 0.0f, 0.0f );
	::Peripheral::IMouse *pMouse = NULL;
	
}

//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	pName:�f�[�^��
//	vPos:�\���ʒu
//===========================================================================
CExpWindow::CExpWindow( const char *pName, Math::Vector2D vPos ) 
 :CSprite( pName, vPos ),
  m_StrCount( 0 ),
  m_OldStrCount( 0 )

{
	const float fMARGIN = 20.0f;
	
	m_pTrlFontSpr = new CFontSprite( "TutorialFont.sff", vPos + Math::Vector2D( fMARGIN, fMARGIN ) );
}

//============================================================================
//�f�X�g���N�^
//============================================================================
CExpWindow::~CExpWindow()
{
	SAFE_DELETE( m_pTrlFontSpr );
}

//============================================================================
//�t�@�C���ǂݍ���
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//	pFileMgr:�t�@�C���Ǘ��p�f�o�C�X
//============================================================================
void CExpWindow::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	CSprite::Load( pRender, pFileMgr );
	
	m_pTrlFontSpr->Load( pRender, pFileMgr );
	
}

//============================================================================
//����
//============================================================================
void CExpWindow::Init()
{
	m_StrCount = 0;
	m_OldStrCount = 0;
}


//============================================================================
//����
//============================================================================
void CExpWindow::Exec()
{
	CSprite::Exec();
	
	m_pTrlFontSpr->SetVisibleFlag( GetVisibleFlag() );
	
	/*�����J�E���g�␳*/
	if( m_StrCount > m_pTrlFontSpr->GetVecString().size() - 1 )
	{
		m_StrCount = m_pTrlFontSpr->GetVecString().size() - 1;
	}
	
	/*�`�敶����*/
	string strDraw = m_pTrlFontSpr->GetDrawString();
	
	string::size_type index = strDraw.find("Br");
	
	/*Br�����񂪌���������A������𕪉�����*/
	if( index != string::npos )
	{
		vector<string> strRet =  CFileLoader::SplitString( strDraw, "Br" );
		
		m_pTrlFontSpr->DrawMultiLine( strRet );
		
	}
	
	/*�ʏ�ʂ�`��*/
	else
	{
		m_pTrlFontSpr->Exec();
	}
}

//============================================================================
//�����_�����O
//============================================================================
void CExpWindow::Rendering()
{
	CSprite::Rendering();
	
	if( m_pTrlFontSpr->GetVisibleFlag() )
	{	
		m_pTrlFontSpr->Rendering();
	}
}

//=============================================================================
//�`���[�g���A���������̃Z�b�g
//=============================================================================
//[input]
//	pFileMgr:�t�@�C���Ǘ��p�f�o�C�X
//=============================================================================
void CExpWindow::SetTutorialExp( File::IFileManager *pFileMgr )
{
	char Temp[1024];
	std::vector<string> vecText;
	
	File::IResourceFile *pResFile = NULL;
	
	pFileMgr->SetCurrentPath("Text");
	
	pResFile = 	pFileMgr->FileOpen("TutorialFont.txt");
	
	ifstream ifs( pResFile->GetNamePointer() );
	
	SAFE_RELEASE( pResFile );
	
	while( !ifs.eof() )
	{
		ifs >> Temp;
		vecText.push_back( Temp );
	}
	
	m_pTrlFontSpr->SetVecTextChat( vecText );
}
