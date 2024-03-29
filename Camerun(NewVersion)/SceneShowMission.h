//*============================================================================
//SceneShowMission.h
//*============================================================================
//[history]
//	08/12/26  作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "SceneTemplate.h"

//=============================================================================
//class
//=============================================================================
//[Desc]
//	ミッション表示画面
//=============================================================================
class CSceneShowMission :	public CSceneTemplate
{

	private:
	
	public:
	
		CSceneShowMission( string strFileName );//コンストラクタ
		virtual ~CSceneShowMission(void);//デストラクタ
		
	public:
	
		/*オブジェクトデータの初期化*/
		void InitObjectData( Uint32 dt );
		
		/*初期化*/
		void Init( Uint32 dt );
		
		/*待機中*/
		void Idle( Uint32 dt );
		
		/*レンダリング*/
		void Rendering();
	
};
