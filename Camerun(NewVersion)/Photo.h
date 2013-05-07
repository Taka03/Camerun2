//*============================================================================
//Photo.h
//*============================================================================
//[history]
//	08/03/11　作成
//	08/04/01  スプライトの継承に変更
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
//	写真用クラス
//=============================================================================
class CPhoto :public CSprite
{
	
	public:
	
		/*写真判定の情報*/
		struct PhotoCheckData
		{
			Uint32 m_Score;//得点
			string m_strTargetName;//ターゲット名
			
			PhotoCheckData()
			{
				m_Score = 0;
				m_strTargetName.clear();
			}
		};
	
	private:
	
		Uint32 m_TotalScore;//写真の合計得点
		vector< PhotoCheckData > m_vecPhotoData;//写真に入っているターゲット名
		vector< string > m_vecTargetName;//ターゲット名
		vector< string > m_vecTargetScore;//スコア
		int m_Score;//小計スコア
		
	public:
	
		CPhoto( const char *pName, Math::Vector2D vPos, vector< PhotoCheckData > vecCheckData );//コンストラクタ
		
		void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );//ファイル読み込み
		
		void SetPhotoInfo();//ターゲット情報のセット
		
	public:
	
		//写真データの設定
		void SetPhotoData( vector< PhotoCheckData > vecPhotoData )
		{
			m_vecPhotoData = vecPhotoData;
		}
	
			
	/*Get系*/
	public:
	
		/*写真データの取得*/
		vector< PhotoCheckData > GetVecPhotoData() const
		{
			return m_vecPhotoData;
		}
		
		//ターゲット名の取得
		vector< string > GetVecTargetName() const
		{
			return m_vecTargetName;
		}
		
		//ターゲットスコアの取得
		vector< string > GetVecTargetScore() const
		{
			return m_vecTargetScore;
		}
		
		//小計の取得
		int GetScore() const
		{
			return m_Score;
		}
};
