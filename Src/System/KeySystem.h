#pragma once

#include"./Application/SceneManager.h"
#include"Application/SoundManager.h"
#include<string>

//�V���O���g��
class System
{
public:
	static System& GetInstance()
	{
		static System system;

		return system;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�G���^�[�L�[��ݒ肷��i�A���A���h�~�j
	void SetEnterKeyFlg(bool _flg)
	{
		enterKeyFlg = _flg;
	}
	//���🹂�邩�ǂ�����ݒ肷��
	void SetwaterFlg(bool _waterflg)
	{
		waterFlg = _waterflg;
	}
	//�ϊ���Ԃ�ݒ肷��i�A���A���h�~�j
	void SetChangeFlg(bool _changeflg)
	{
		changeFlg = _changeflg;
	}
	//�p�^�[���ϊ��̒i�K��ݒ肷��i0:�ŏ���ԁ@1�F�ϊ��r���@2�F�ŏI��ԁj
	void SettransStep(int _step)
	{
		transStep = _step;
	}
	//���̃X�e�[�W��ݒ肷��
	void SetnowStage(int _stage)
	{
		nowStage = _stage;
	}
	//���̃X�e�[�W��ݒ肷��
	void SetnextStage(int _nextstage)
	{
		nextStage = _nextstage;
	}
	//���̎��Ԃ��L�^����
	void SetCurrenTime(int _time)
	{
		currentTime = _time;
	}
	//�p�^�[���ϊ�����̐ݒ�ON/OFF
	void Setplayframe(bool _playing)
	{
		playingframe = _playing;
	}
	//�p�^�[���̏�Ԃ��Z�b�g
	void Setstate(int _state)
	{
		state = _state;
	}
	//���p�^�[���c�q�̐F��؂�ւ���i1�F��2�F�s���N3�F�΁j
	void Setcolormode(int _color)
	{
		colormode = _color;
	}
	//�M�~�b�N�J�������N������
	void Setstagecam(bool _stagecam)
	{
		stagecam = _stagecam;
	}
	//�R�����̉΂�����
	void Sethotstate(bool _hot)
	{
		hot = _hot;
	}
	//�Q�[���I�[�o�[�t���O�ݒ�
	void SetOverFlg(bool _overflg)
	{
		overFlg = _overflg;
	}
	//�V�[�\�[��ԋN���ݒ�
	void SetSpoonFlg(bool _spoonflg)
	{
		spoonFlg = _spoonflg;
	}
	//��O�p�^�[���̗����ݒ�
	void Setfalling(bool _s3falling)
	{
		s3falling = _s3falling;
	}
	//���p�^�[���̃W�����v��Ԑݒ�
	void Setjumping(bool _s2jumping)
	{
		s2jumping = _s2jumping;
	}
	//��O�X�e�[�W�L�����N�^�[�؂�ւ��J���� true:�J�������Œ肵�� false:�J�������ړ���
	void SetbuttonCam(bool _buttoncam)
	{
		buttoncamflg = _buttoncam;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//�G���^�[�L�[���Q�b�g����i�A���A���h�~�j
	bool GetEnterKeyFlg()
	{
		return enterKeyFlg;
	}
	//���̐���Ԃ��Q�b�g����
	bool GetwaterFlg()
	{
		return waterFlg;
	}
	//���̕ϊ���Ԃ��Q�b�g����
	bool GetChangeFlg()
	{
		return changeFlg;
	}
	//�p�^�[����Ԃ��Q�b�g����i1:�ŏ���ԁ@2�F�ϊ��r���@3�F�ŏI��ԁj
	int GettransStep()
	{
		return transStep;
	}
	//���̃X�e�[�W���Q�b�g����
	int GetnowStage()
	{
		return nowStage;
	}
	//���̃X�e�[�W���Q�b�g����
	int GetnextStage()
	{
		return nextStage;
	}
	//�L�^�������Ԃ��Q�b�g����
	int GetnowTime()
	{
		return currentTime;
	}
	//�p�^�[���ϊ�����̏�Ԃ��Q�b�g����
	bool Getplayframe()
	{
		return playingframe;
	}
	//���̃p�^�[����Ԃ��Q�b�g����
	int Getstate()
	{
		return state;
	}
	//���̒c�q�̐F���Q�b�g����i1�F��2�F�s���N3�F�΁j
	int Getcolormode()
	{
		return colormode;
	}
	//���̃M�~�b�N�J������Ԃ��Q�b�g����
	bool Getstagecam()
	{
		return stagecam;
	}
	//�R�����̏�Ԃ��Q�b�g����
	bool GetHotState()
	{
		return hot;
	}
	//�Q�[���I�[�o�[�̃t���O���m�F
	bool GetoverFlg()
	{
		return overFlg;
	}
	//�V�[�\�[��Ԃ̊m�F
	bool GetSpoonFlg()
	{
		return spoonFlg;
	}
	//��O�p�^�[���̗������m�F
	bool Getfalling()
	{
		return s3falling;
	}
	//���p�^�[���̃W�����v��Ԋm�F
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

