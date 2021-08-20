#pragma once

enum class ButtonName {
	Restart,		//���X�^�[�g	
	Home,			//���j���[
	Next,			//���̃X�e�[�W
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