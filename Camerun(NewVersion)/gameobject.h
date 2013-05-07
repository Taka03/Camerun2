//*============================================================================
//gameobject.h
//*============================================================================
//[history]
//	08/03/03　修正開始
//[author]
//	Taka
//============================================================================
//二重インクルード防止
#pragma once

//=============================================================================
//include
//=============================================================================
#include "CommonObject.h"
#include <string>

//=============================================================================
//variable
//=============================================================================
class CGameObject;

using namespace std;

//=============================================================================
//class
//=============================================================================
//[desc]
//	ゲームオブジェクト用クラス
//=============================================================================
class CGameObject 
{
	public:
	
	protected:
	
		//ファイル名
		string m_strFileName;
	
	public:
	
		//コンストラクタ
		CGameObject(){};
		
		//コンストラクタ
		CGameObject( const char *pName );
		
		//デストラクタ
		virtual ~CGameObject();
		
		//初期化
		virtual void Init() = 0;
		
		//処理
		virtual void Exec() = 0;
		
		//参照カウンタの増加
		virtual void AddRef(){};
		
	/*Get系*/
	public:
	
		//ファイル名の取得
		string GetFileName() const
		{
			return m_strFileName;
		}
		
};
