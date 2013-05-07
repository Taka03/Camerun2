//*============================================================================
//FileLoader.cpp
//*============================================================================

//=============================================================================
//include
//=============================================================================
#include "FileLoader.h"
#include <fstream>
#include <iostream>

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CFileLoader::CFileLoader()
{
	m_StrList.clear();
}

//=============================================================================
//�t�@�C���ǂݍ���
//=============================================================================
//[input]
//	strFilePath:�t�@�C���ǂݍ��ݐ�
//=============================================================================
void CFileLoader::Load( string strFilePath )
{
	ifstream ifs( strFilePath.c_str() );
	
	if( ifs.fail() )
	{
		
	}
	
	char Temp[256];
	
	ifs.getline( Temp, 256 );
	
	while( !ifs.eof() )
	{
		string line(Temp);
		
		if( line.substr( 0, 1 ).compare("#") != 0 )
		{
			//�s�������łȂ��ꍇ
			if( line.length() > 0 )
			{
				m_StrList.push_back( line );
			}
		}
		
		ifs.getline( Temp, 256 );
	}
	
	ifs.close();
}

//=============================================================================
//������̕���
//=============================================================================
//[input]
//	strSource:���ɂȂ镶����
//	strDelim:�������镶��
//=============================================================================
vector<string> CFileLoader::SplitString( std::string strSource, std::string strDelim )
{
	vector<string> strRet;
	
	/*�����������������Ƃ�����L��*/
	size_t Delim = strSource.find( strDelim );
	
	//����������������Ȃ��Ȃ�܂Ń��[�v
	while( Delim != -1 )
	{
		/*����*/
		string strVal = strSource.substr( 0, Delim );
		
		//�����s�łȂ������烊�X�g�ɒǉ�
		if( strVal.length() > 0 )
		{
			strRet.push_back( strVal );
		}
		
		/*���̕���������Ɉړ�*/
		strSource = strSource.substr( Delim + strDelim.size() );
		
		Delim = strSource.find( strDelim );
	}
	
	/*�Ō�̕����������*/
	if( strSource.length() > 0 )
	{
		strRet.push_back( strSource );
	}
	
	return strRet;
}




