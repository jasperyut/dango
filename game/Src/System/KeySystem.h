#pragma once

#include"./Application/SceneManager.h"
#include"Application/SoundManager.h"
#include<string>

//シングルトン
class System
{
public:
	static System& GetInstance()
	{
		static System system;

		return system;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//エンターキーを設定する（連続輸入防止）
	void SetEnterKeyFlg(bool _flg)
	{
		enterKeyFlg = _flg;
	}
	//水を淹れるかどうかを設定する
	void SetwaterFlg(bool _waterflg)
	{
		waterFlg = _waterflg;
	}
	//変換状態を設定する（連続輸入防止）
	void SetChangeFlg(bool _changeflg)
	{
		changeFlg = _changeflg;
	}
	//パターン変換の段階を設定する（0:最初状態　1：変換途中　2：最終状態）
	void SettransStep(int _step)
	{
		transStep = _step;
	}
	//今のステージを設定する
	void SetnowStage(int _stage)
	{
		nowStage = _stage;
	}
	//次のステージを設定する
	void SetnextStage(int _nextstage)
	{
		nextStage = _nextstage;
	}
	//今の時間を記録する
	void SetCurrenTime(int _time)
	{
		currentTime = _time;
	}
	//パターン変換動画の設定ON/OFF
	void Setplayframe(bool _playing)
	{
		playingframe = _playing;
	}
	//パターンの状態をセット
	void Setstate(int _state)
	{
		state = _state;
	}
	//第一パターン団子の色を切り替える（1：白2：ピンク3：緑）
	void Setcolormode(int _color)
	{
		colormode = _color;
	}
	//ギミックカメラを起動する
	void Setstagecam(bool _stagecam)
	{
		stagecam = _stagecam;
	}
	//コンロの火をつける
	void Sethotstate(bool _hot)
	{
		hot = _hot;
	}
	//ゲームオーバーフラグ設定
	void SetOverFlg(bool _overflg)
	{
		overFlg = _overflg;
	}
	//シーソー状態起動設定
	void SetSpoonFlg(bool _spoonflg)
	{
		spoonFlg = _spoonflg;
	}
	//第三パターンの落下設定
	void Setfalling(bool _s3falling)
	{
		s3falling = _s3falling;
	}
	//第二パターンのジャンプ状態設定
	void Setjumping(bool _s2jumping)
	{
		s2jumping = _s2jumping;
	}
	//第三ステージキャラクター切り替えカメラ true:カメラが固定した false:カメラが移動中
	void SetbuttonCam(bool _buttoncam)
	{
		buttoncamflg = _buttoncam;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//エンターキーをゲットする（連続輸入防止）
	bool GetEnterKeyFlg()
	{
		return enterKeyFlg;
	}
	//今の水状態をゲットする
	bool GetwaterFlg()
	{
		return waterFlg;
	}
	//今の変換状態をゲットする
	bool GetChangeFlg()
	{
		return changeFlg;
	}
	//パターン状態をゲットする（1:最初状態　2：変換途中　3：最終状態）
	int GettransStep()
	{
		return transStep;
	}
	//今のステージをゲットする
	int GetnowStage()
	{
		return nowStage;
	}
	//次のステージをゲットする
	int GetnextStage()
	{
		return nextStage;
	}
	//記録した時間をゲットする
	int GetnowTime()
	{
		return currentTime;
	}
	//パターン変換動画の状態をゲットする
	bool Getplayframe()
	{
		return playingframe;
	}
	//今のパターン状態をゲットする
	int Getstate()
	{
		return state;
	}
	//今の団子の色をゲットする（1：白2：ピンク3：緑）
	int Getcolormode()
	{
		return colormode;
	}
	//今のギミックカメラ状態をゲットする
	bool Getstagecam()
	{
		return stagecam;
	}
	//コンロの状態をゲットする
	bool GetHotState()
	{
		return hot;
	}
	//ゲームオーバーのフラグを確認
	bool GetoverFlg()
	{
		return overFlg;
	}
	//シーソー状態の確認
	bool GetSpoonFlg()
	{
		return spoonFlg;
	}
	//第三パターンの落下を確認
	bool Getfalling()
	{
		return s3falling;
	}
	//第二パターンのジャンプ状態確認
	bool Getjumping()
	{
		return s2jumping;
	}

	bool GetbuttonCam()
	{
		return buttoncamflg;
	}


	SceneManager& GetSceneManager()
	{
		return sceneManager;
	}

	Soundmanager& GetSoundManager()
	{
		return soundManager;
	}

private:

	Math::Matrix AimDangoMat = {};
	Math::Vector3 FrontVec = {};

	bool enterKeyFlg = false;
	bool waterFlg = false;
	bool FKeyFlg = false;
	bool changeFlg = false;
	bool stagecam = false;
	bool playingframe = false;
	bool hot = false;
	bool overFlg = false;
	bool spoonFlg = false;
	bool s3falling = false;
	bool s2jumping = false;
	bool buttoncamflg = false;

	int transStep = 0;
	int nowStage = {};
	int state = 1;
	int nextStage = {};
	int currentTime = 60;
	int colormode = 1;

	SceneManager sceneManager;
	Soundmanager soundManager;

};

#define SYSTEM System::GetInstance()

