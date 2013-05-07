//*============================================================================
//FontSprite.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "FontSprite.h"

//============================================================================
//�R���X�g���N�^
//============================================================================
//[input]
//	pName:�f�[�^��
//	vPos:�ʒu
//===========================================================================
CFontSprite::CFontSprite( const char *pName, Math::Vector2D vPos ) 
:m_pFontSpr(NULL),
  CDraw2DObject( pName, vPos )

{
	m_Str = "";
	
	m_vecText.clear();
	
	m_FontColor = CColor( 255, 255, 255 );
	
	m_HitRect.Set( 0.0f, 0.0f, 0.0f, 0.0f );
	
	m_RefCount = 0;
	
	m_StrCount = 1;
	
	m_IsTextEnd = false;
}


//============================================================================
//�f�X�g���N�^
//============================================================================
CFontSprite::~CFontSprite(void)
{
	SAFE_RELEASE( m_pFontSpr );
}

//============================================================================
//�t�@�C���ǂݍ���
//============================================================================
//[input]
//	pRender:�����_���[�p�f�o�C�X
//	pFileMgr:�t�@�C���Ǘ��p�f�o�C�X
//===========================================================================
void CFontSprite::Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr )
{
	pFileMgr->SetCurrentPath("Font");
	
	printf("LOAD FONT[%s]", m_strFileName.c_str() );
	
	m_pFontSpr = pRender->CreateFontSprite2DFromFile( m_strFileName.c_str(), "tga", 1024 );
	
	printf( "                 : -> %s\n", m_pFontSpr->IsInvalid() ? "Failed" : "Succeeded" );
}


//============================================================================
//����
//============================================================================
void CFontSprite::Exec()
{
	if( m_pFontSpr != NULL )
	{
		/*�`��J�n*/
		m_pFontSpr->Begin();
		
		/*�`��L���[�ɒǉ�*/
		m_pFontSpr->DrawString( m_Str.c_str(), Math::Point2DF( m_vPos.x, m_vPos.y ), m_FontColor );
		
		/*�`��I��*/
		m_pFontSpr->End();
	}	
}

//============================================================================
//�����_�����O
//============================================================================
void CFontSprite::Rendering()
{
	if( m_pFontSpr != NULL )
	{
		if( GetVisibleFlag() )
		{	
			m_pFontSpr->Rendering();
		}
	}
}

//============================================================================
//�m�x�����ɕ`��
//============================================================================
//[input]
//	pCore:�ݒ肷��R�A�f�o�C�X
//===========================================================================
bool CFontSprite::DrawNovelStyle( ICore *pCore )
{
	Peripheral::IMouse *pMouse = pCore->GetMouse();
	
	/*�����̐i�ފԊu*/
	if( (pCore->GetSyncCount() % 5) == 0 )
	{
		m_StrCount ++;
	}
	
	if( m_pFontSpr != NULL )
	{
		Uint32 Cnt = m_StrCount;
		const char *pStr = m_vecText.at( m_RefCount ).c_str();//(char *)( m_Str.c_str() );
		
		Math::Rect2DF Dst( m_vPos.x, m_vPos.y, 0, 0 );
		
		/*�`��J�n*/
		m_pFontSpr->Begin();
		
		while( (*pStr != '\0') && (Cnt > 0) )
		{
			
			/*2Byte�������ǂ���*/
			Bool Is2Byte = Is2ByteChara( (unsigned char)(*pStr) );
			
			//Math::Point2DF Size = m_pFontSpr->GetStringSize( pStr );
			
			Sint32 FontSize = m_pFontSpr->GetSize();//21;//m_pFontSpr->gt;//�t�H���g�T�C�Y
			
			if( !Is2Byte )
			{
				/*���s���ǂ���*/
				if( *pStr == '\n' )
				{
					//Dst.y += toF( Size.y );	
					//Dst.y += FontSize;
					//Dst.x = m_vPos.x;
					pStr += 1;
					continue;
				}
				
				/*���s*/
				else if( *pStr == 'B' )
				{
					
					Dst.x = m_vInitPos.x;
					Dst.y += FontSize;
					pStr += 1;
					//m_pFontSpr->Begin();
					
					continue;
					
				}
				
				/*���N���b�N�̏ꍇ*/
				else if( *pStr == 'L' )
				{
					if( pMouse->GetStateL() == MOUSE_PUSH )
					{
						pStr += 1;
					}
					
					continue;

				}
				
				else if( *pStr == '@')
				{
					//IsStop = true;
					pStr += 1;
					
					continue;
				}
				
				/*�I���t���O*/
				else if( *pStr == 'E')
				{
					m_IsTextEnd = true;
					return true;
				}
				
				
			}
			
			Dst.x += FontSize;
			
			//Dst.x += Size;
			
			
		//	Math::Point2DF Size = m_pFontSpr->GetStringSize( Str2.c_str() );
	
			Dst.w = toF( FontSize );
			Dst.h = toF( FontSize );
			
			/*�ꕶ���`��*/
			m_pFontSpr->DrawChara( pStr, Dst, CColor(0, 0, 0 ));
			
			Dst.x -= FontSize;
			
			if( Is2Byte )
			{
				//Dst.x += Size.y;
				
				Dst.x += FontSize;
			}
			
			else
			{
				Dst.x += FontSize;
			}
			
			if( Dst.x >= 700 - FontSize * 2 )
			{
				Dst.x = m_vInitPos.x;
				Dst.y += FontSize;
			}
			
			pStr += Is2Byte ? 2 : 1;
			
			Cnt--;
			
		}
		
		/*�`��I��*/
		m_pFontSpr->End();
		
		if( Cnt > 0 && !m_IsTextEnd )
		{
			
			if( pCore->GetMouse()->GetClickL() )
			{	
				m_StrCount = 1;
				m_RefCount++;
				
			}
		}
		
		if( m_RefCount >= m_vecText.size() -1)
		{
			m_RefCount = m_vecText.size() -1;
		}
		
	}	
	
	return false;
	
}


//============================================================================
//�m�x�����ɕ`��
//============================================================================
bool CFontSprite::DrawNovelStyle( ICore *pCore, Peripheral::IInputController *pCtrl )
{
	
	if( (pCore->GetSyncCount() % 5) == 0 )
	{
		m_StrCount ++;
	}
	
	//if( pCtrl->GetState( BUTTON_STATE_HOLD, BUTTON_R1 ) )
	//{
	//	if( pCore->GetSyncCount() % 3 == 0 )
	//	{	
	//		m_StrCount += 1;
	//	}
	//}
	
	if( m_pFontSpr != NULL )
	{
		Uint32 Cnt = m_StrCount;
		const char *pStr = m_vecText.at( m_RefCount ).c_str();//(char *)( m_Str.c_str() );
		
		Math::Rect2DF Dst( m_vPos.x, m_vPos.y, 0, 0 );
		
		/*�`��J�n*/
		m_pFontSpr->Begin();
		
		while( (*pStr != '\0') && (Cnt > 0) )
		{
			
			/*2Byte�������ǂ���*/
			Bool Is2Byte = Is2ByteChara( (unsigned char)(*pStr) );
			
			//Math::Point2DF Size = m_pFontSpr->GetStringSize( pStr );
			
			Sint32 FontSize = m_pFontSpr->GetSize();//21;//m_pFontSpr->gt;//�t�H���g�T�C�Y
			
			if( !Is2Byte )
			{
				/*���s���ǂ���*/
				if( *pStr == '\n' )
				{
					//Dst.y += toF( Size.y );	
					//Dst.y += FontSize;
					//Dst.x = m_vPos.x;
					pStr += 1;
					continue;
				}
				
				/*���s*/
				else if( *pStr == 'B' )
				{
					
					Dst.x = m_vInitPos.x;
					Dst.y += FontSize;
					pStr += 1;
					//m_pFontSpr->Begin();
					
					continue;
					
				}
				
				else if( *pStr == '@')
				{
					//IsStop = true;
					pStr += 1;
					
					continue;
				}
				
				/*�I���t���O*/
				else if( *pStr == 'E')
				{
					m_IsTextEnd = true;
					return true;
				}
				
				
			}
			
			Dst.x += FontSize;
			
			//Dst.x += Size;
			
			
		//	Math::Point2DF Size = m_pFontSpr->GetStringSize( Str2.c_str() );
	
			Dst.w = toF( FontSize );
			Dst.h = toF( FontSize );
			
			/*�ꕶ���`��*/
			m_pFontSpr->DrawChara( pStr, Dst, CColor(0, 0, 0 ));
			
			Dst.x -= FontSize;
			
			if( Is2Byte )
			{
				//Dst.x += Size.y;
				
				Dst.x += FontSize;
			}
			
			else
			{
				Dst.x += FontSize;
			}
			
			if( Dst.x >= 700 - FontSize * 2 )
			{
				Dst.x = m_vInitPos.x;
				Dst.y += FontSize;
			}
			
			pStr += Is2Byte ? 2 : 1;
			
			Cnt--;
			
		}
		
		/*�`��I��*/
		m_pFontSpr->End();
		
		if( Cnt > 0 && !m_IsTextEnd )
		{
			
			//if( pCtrl->GetState( BUTTON_STATE_PUSH, BUTTON_R2 ) )
			//{	
			//	m_StrCount = 1;
			//	m_RefCount++;
			//	
			//}
		}
		
		if( m_RefCount >= m_vecText.size() -1)
		{
			m_RefCount = m_vecText.size() -1;
		}
		
		
		
	}	
	
	return false;
	
}

//============================================================================
//����������̕`��
//============================================================================
void CFontSprite::DrawMultiLine(  )
{
	m_pFontSpr->Begin();
	
	for( Uint32 i = 0; i < m_vecText.size();++i )
	{	
		m_pFontSpr->DrawString( m_vecText.at(i).c_str(), Math::Point2DF( m_vPos.x, m_vPos.y + i * 30 ), CColor( 255, 255, 255 ) );
	}
	
	m_pFontSpr->End();
}

//============================================================================
//����������̕`��
//============================================================================
//[input]
//	vPos:�ݒ肷��ʒu
//===========================================================================
void CFontSprite::DrawMultiLine( Math::Point2DF vPos[] )
{
	m_pFontSpr->Begin();
	
	for( Uint32 i = 0; i < m_vecText.size();++i )
	{	
		m_pFontSpr->DrawString( m_vecText.at(i).c_str(), vPos[i], CColor( 255, 255, 255 ) );
	}
	
	m_pFontSpr->End();
}

//============================================================================
//����������̕`��
//============================================================================
//[input]
//	vPos:�ݒ肷��ʒu
//	Str:�ݒ肷�镶����
//	num:�`�悷�鐔
//===========================================================================
void CFontSprite::DrawMultiLine( Math::Point2DF vPos[], string Str[], int num )
{
	m_pFontSpr->Begin();
	
	for( int i = 0; i < num;++i )
	{	
		m_pFontSpr->DrawString( Str[i].c_str(), vPos[i], CColor( 255, 255, 255 ) );
	}
	
	m_pFontSpr->End();
}

//============================================================================
//����������̕`��
//============================================================================
//[input]
//	vecStr:�`�悷�镶��
//===========================================================================
void CFontSprite::DrawMultiLine( vector<string> vecStr )
{
	m_pFontSpr->Begin();
	
	const float fMARGIN = 20.0f;//�����̗]��
	
	for( Uint32 i = 0; i < vecStr.size();++i )
	{	
		m_pFontSpr->DrawString( vecStr.at(i).c_str(), Math::Point2DF( m_vPos.x, m_vPos.y + i * fMARGIN ),
								CColor( 255, 255, 255 ) );
	}
	
	m_pFontSpr->End();
}



//============================================================================
//�\�����镶���̐ݒ�
//============================================================================
//[input]
//	str:�ݒ肷�镶����
//===========================================================================
void CFontSprite::SetDrawString(std::string str)
{
	m_Str = str;
}

