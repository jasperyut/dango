#include"SoundManager.h"

Soundmanager::~Soundmanager()
{
	Release();
}

void Soundmanager::Release()
{

}

void Soundmanager::SetSound(std::string _filename)
{
	std::shared_ptr<KdSoundEffect>sound2d;
	sound2d = std::make_shared<KdSoundEffect>();
	sound2d->Load(_filename);//�t�@�C�����ǂݍ���
	auto instance = sound2d->CreateInstance(false);
	instance->SetVolume(0.2f);//���ʒ���
	instance->Play();

}
