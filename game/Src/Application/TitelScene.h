#pragma once
#include"Scene.h"
#include"ground/ground.h"
#include"background.h"
//タイトル画面

class TitleScene :public Scene
{
public:
	TitleScene();
	~TitleScene();
	void Init();
	void Update()override;
	void Draw()override;
	void SetCamera()override;
	void Release();

	//タイトル画面として
	//スプライトで1枚の画像を表示

	//Sceneクラスの代わりにTitleSceneクラスを宣言することで
	//実行するとタイトル画像が表示されるはず

private:
	KdModel m_Model;	//タイトル画像
	KdTexture m_Title;
	KdTexture m_StartButton;

	std::unique_ptr<C_ground> m_Ground;
	std::unique_ptr<C_Background> m_Background;
	
	Math::Matrix m_Mat;
	Math::Matrix m_TitleMat;
	Math::Matrix m_StartbtMat;
	

	Math::Vector3 m_Pos;
	Math::Vector3 camPos, camLook, camHead;

	int time = 0;
	float fade;
	float m_camAngX;
	bool soundCheck;
	bool alphaswitch;

	DirectX::SpriteFont* SpriteFont;
	POINT m_basept;
	//bgm
	std::shared_ptr<KdSoundEffect> m_Soundbgm;
	std::shared_ptr<KdSoundInstance> m_BgmInst;
};