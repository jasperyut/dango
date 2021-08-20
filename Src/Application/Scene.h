#pragma once

enum class ButtonName {
	Restart,		//リスタート	
	Home,			//メニュー
	Next,			//次のステージ
};

class Scene
{
public:
	virtual ~Scene();

	virtual void Update();
	virtual void Draw();
	virtual void SetCamera();
	virtual void Frame();
	

private:

};