#pragma once
#include"Scene.h"

class GameOver:public Scene
{
public:
	GameOver();
	~GameOver();
	void Init();
	void Update()override;
	void Draw()override;
	void SetCamera()override;
	void ButtonSet(ButtonName _name, Math::Matrix& _mat, bool _touch);
	void Release();

private:
	KdTexture m_bg;
	KdTexture m_Over;
	KdTexture m_Restart;
	KdTexture m_Home;

	Math::Matrix m_Restartmat;
	Math::Matrix m_Homemat;

	bool soundCheck;
	float overalpha;

	POINT m_basept;
	POINT pt;

	std::shared_ptr<KdSoundEffect> m_Soundbgm;
	std::shared_ptr<KdSoundInstance> m_BgmInst;

};
