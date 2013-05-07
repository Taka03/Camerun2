//*============================================================================
//Draw2DObject.h
//*============================================================================
//[history]
//	08/03/16 作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "drawobject.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	2D描画用オブジェクト
//=============================================================================
class CDraw2DObject :	public CDrawObject
{
	protected:
	
		Math::Vector2D m_vPos;//位置
		Math::Vector2D m_vInitPos;//初期位置
		Math::Point2DI m_Rot;//回転角度
		Math::Point2DI m_InitRot;//初期角度
		Math::Vector2D m_vScale;//スケール
		Math::Vector2D m_vInitScale;//初期スケール
	
	public:
	
		CDraw2DObject( const char *pName, Math::Vector2D vPos );//コンストラクタ
		~CDraw2DObject(void);//デストラクタ
		
		virtual void Load( Renderer::IRender *pRender, File::IFileManager *pFileMgr ){};//ファイル読み込み
		
		void Init();//初期化
		void Exec(){};//処理
		virtual void Rendering(){};//レンダリング
		
	public:
	
		//位置の設定
		void SetPosition( Math::Vector2D vPos )
		{
			m_vPos = vPos;
		}
		
		/*初期位置の設定*/
		void SetInitPosition( Math::Vector2D vPos )
		{
			m_vInitPos = vPos;
		}
		
		//回転角度の設定
		void SetRotate( Math::Point2DI Rot )
		{
			m_Rot = Rot;
		}
		
		//X方向の回転角度の設定
		void SetXRotate( Sint32 RotX )
		{
			m_Rot.x = RotX;
		}
		
	public:
	
		//位置の取得
		Math::Vector2D GetPosition() const
		{
			return m_vPos;
		}
		
		/*初期座標の取得*/
		Math::Vector2D GetInitPos() const
		{
			return m_vInitPos;
		}
		
		
		//回転角度の取得
		Math::Point2DI GetRotate() const
		{
			return m_Rot;
		}
		
		//拡縮の取得
		Math::Vector2D GetScale() const
		{
			return m_vScale;
		}
		
};
