//*============================================================================
//SoundManager.h
//*============================================================================
//[history]
//	08/12/27  作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Sound.h"
#include "SoundEffect.h"

class CResourceManager;

//=============================================================================
//class
//=============================================================================
//[desc]
//	サウンド管理用クラス
//=============================================================================
class CSoundManager :	public CSoundObject
{
	public:
	
		
	
	public:
	
		/*サウンドタイプ*/
		enum eSoundType
		{
			SND_SELECT,//セレクト音
			SND_DECIDE,//決定音
			SND_NEW,//新要素音
			SND_MESSAGE,//メッセージ音
			SND_PROHIBIT,//禁止音
			SND_SHOWENEMY,//敵出現音
			SND_PLAYERMOVE,//プレイヤー移動音
			SND_GETDOWN,//着地音
			SND_BITE,//噛み付き音
			SND_BOOST,//ブースト音
			SND_SHUTTER,//シャッター音
			SND_TRAIN,//電車音
			SND_BIRD,//トリの音
			SND_MOUSE,//ねずみの音
			SND_RIZARDMOVE,//トカゲ移動音
			SND_CLEAR,//ミッションクリア音
			SND_FAIL,//ミッション失敗音
			SND_CHANGE,//チェンジ音
			SND_CALCSCORE,//得点計算
			SND_EXIT,//終了
			SND_MAX,//サウンドの最大数
		};
		
	private:
	
		CSoundEffect *m_pSoundObj[SND_MAX];//サウンドオブジェクト
	
	public:
	
		CSoundManager(void);//コンストラクタ
		~CSoundManager(void);//デストラクタ
		
		void PushResource( CResourceManager *pResMgr );//リソースの追加
	
		void Play( eSoundType Type );//音の再生
		void Stop( eSoundType Type );//音の停止
		void SetVolume( eSoundType Type, float fVolume );//音量調整
		void SetPan( eSoundType Type, float fPan );//パン設定
};
