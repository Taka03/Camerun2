//*============================================================================
//SoundEffect.h
//*============================================================================
//[history]
//	08/03/16　作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "Sound.h"

//=============================================================================
//class
//=============================================================================
//[desc]
//	効果音再生用クラス
//=============================================================================
class CSoundEffect :	public CSoundObject
{
	private:
	
		Sound::ISound *m_pSE;//効果音再生用デバイス
	
	public:
	
		CSoundEffect( const char *pName );//コンストラクタ
		virtual ~CSoundEffect(void);//デストラクタ
		
		virtual void LoadSound( ICore *pCore, File::IFileManager *pFileMgr );//サウンドの読み込み
		
		void Init(){};//初期化
		void Exec();//処理
		
	/*Get系*/
	public:

		//効果音再生用デバイスの取得	
		Sound::ISound *GetSEDevice() const
		{
			return m_pSE;
		}
		
};
