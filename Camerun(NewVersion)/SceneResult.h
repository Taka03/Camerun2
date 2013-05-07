//*============================================================================
//SceneResult.h
//*============================================================================
//[history]
//	08/03/11　作成
//	08/11/11  修正
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "SceneTemplate.h"

//=============================================================================
//const
//=============================================================================
const int MINSSION_MAX = 5;//ミッションの最大数

//=============================================================================
//class
//=============================================================================
//[Desc]
//	リザルト画面
//=============================================================================
class CSceneResult :	public CSceneTemplate
{
	public:
	
		//ミッション結果
		enum eMissionResult
		{
			RESULT_FAILURE,//ミッション失敗
			RESULT_SUCCESS,//ミッション成功
			RESULT_MAX
		};
	
	private:
	
		eMissionResult m_eMissionRes;//ミッション結果
	
	private:
	
		CPhoto *m_pPhoto[FILM_MAX];//写真の表示
		CFontSprite *m_pScoreFont;//小計フォント
		CFontSprite *m_pListNameFont;//リスト名フォント
		CFontSprite *m_pListNumFont;//リストスコアフォント
		CFontSprite *m_pTotalScFont;//合計点フォント
		
		CSprite *m_pBGSpr;//BG
		CSprite *m_pScoreSpr;//スコアスプライト
		CSprite *m_pExtBtnSpr;//終了ボタンスプライト
		
		CSprite *m_pTargetOKSpr;//ターゲットが存在するときに表示
		CSprite *m_pTargetNGSpr;//ターゲットが存在しないときに表示
		
		CBGM *m_pResultBGM;//リザルトBGM
		
		int m_SelectIdx;//写真セレクトインデックス
	
	public:
	
		CSceneResult( string strFileName );//コンストラクタ
		virtual ~CSceneResult(void);//デストラクタ
		
	public:
	
		/*オブジェクトデータの初期化*/
		void InitObjectData( Uint32 dt );
		
		/*初期化*/
		void Init( Uint32 dt );
		
		/*待機中*/
		void Idle( Uint32 dt );
		
		/*レンダリング*/
		void Rendering();
		
		
	public:
	
		void DrawBigPhoto();//大きい写真の描画
		void DrawMinPhoto();//小さい写真の描画
		
		void SetPhotoInfo();//写真情報のセット
		void DrawPhotoInfo( );//写真情報の描画
		
		void AddPhotoCount();//写真カウントの増加処理
		
		void CountUpScore();//スコアのカウントアップ
		
		void ShowTargetResult();//ターゲットが含まれているかの表示
		
	public:		
		/*ミッション結果の設定*/
		void SetResult( eMissionResult eResult )
		{
			m_eMissionRes = eResult;
		}
		
	public:
		
		/*ミッション結果の取得*/
		eMissionResult GetResult() const
		{
			return m_eMissionRes;
		}
	
};
