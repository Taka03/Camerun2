//*============================================================================
//CamBtn.h
//*============================================================================
//[history]
//	08/12/04  作成
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
//	カメラボタン用クラス
//=============================================================================
class CCamButton :	public CSprite
{
	private:
	
		CCamBar *m_pMarkerSpr;//回転マーカー
		CSprite *m_pResetBtnSpr;//カメラリセットボタン
		CSprite *m_pRollSpr;//旋回スプライト
		bool m_IsCamMove;//カメラ移動中かどうか
		bool m_IsCamReset;//カメラリセットされたかどうか
	
	public:
	
		/*コンストラクタ*/
		CCamButton( const char *pName, Math::Vector2D vPos );
		
		/*デストラクタ*/
		~CCamButton();
		
		//初期化
		void Init();
		
		/*読み込み*/
		void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr );
		
		/*レンダリング*/
		void Rendering();
		
		/*処理*/
		void Exec();
	
		/*移動*/
		void Move( CCamera *pCam[], CResourceManager *pResMgr, CPlayer *pPlayer );
		
		/*カメラリセット*/
		void Reset( CCamera *pCam[], CPlayer *pPlayer );
		
	public:
	
		
	public:
	
		/*カメラ移動中かどうか*/
		bool GetCamMoveFlag() const
		{
			return m_IsCamMove;
		}
		
		/*カメラリセットされたかどうか*/
		bool GetCamResetFlag() const
		{
			return m_IsCamReset;
		}
		
		/*リセットボタンスプライトの取得*/
		CSprite *GetResetButton() const
		{
			return m_pResetBtnSpr;
		}
};
