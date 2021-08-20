#include "playerManager.h"
#include "Application/define.h"

PlayerManager::PlayerManager()
{

	soundwait = 0;

	m_State = std::make_unique<C_playermove0>();

}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::Update(std::unique_ptr<BlockManager>& _blockManager)
{
	//ƒpƒ^[ƒ“1‚ÉØ‚è‘Ö‚¦‚é
	if (SYSTEM.Getcolormode() == 1)
	{
		if (SYSTEM.Getplayframe() ==false)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && SYSTEM.Getjumping() == false)
			{
				SYSTEM.Setplayframe(true);
				if (SYSTEM.GetChangeFlg() == false)
				{
					SYSTEM.SetChangeFlg(true);
					SYSTEM.Setstate(SYSTEM.Getstate() + 1);
					if (SYSTEM.Getstate() > 3)
					{
						SYSTEM.Setstate(1);
					}
				}
			}
			else if (GetAsyncKeyState(VK_RBUTTON) & 0x8000 && SYSTEM.Getjumping() == false)
			{
				SYSTEM.Setplayframe(true);
				if (SYSTEM.GetChangeFlg() == false)
				{
					SYSTEM.SetChangeFlg(true);
					SYSTEM.Setstate(SYSTEM.Getstate() - 1);
					if (SYSTEM.Getstate() < 1)
					{
						SYSTEM.Setstate(3);
					}
				}
			}
			else
			{
				SYSTEM.SetChangeFlg(false);
			}

			if (SYSTEM.GetChangeFlg() == true)
			{
				switch (SYSTEM.Getstate())
				{
				case 1:
					m_State.reset(new C_playermove0());
					break;
				case 2:
					m_State.reset(new C_playermove1());
					break;
				case 3:
					m_State.reset(new C_playermove2());
					break;

				default:
					break;
				}
			}
		}
		else
		{
			if (soundwait == 0)
			{
				//Ø‘Ö‚Ì‰¹
				SYSTEM.GetSoundManager().SetSound("Data/music/change.wav");
				soundwait = 30;
			}
		}
	}
	soundwait--;
	if (soundwait <= 0)
	{
		soundwait = 0;
	}

	m_State->Update(_blockManager, m_Mat, m_ang);

}

void PlayerManager::Draw()
{

	m_State->Draw(m_Mat);

}
