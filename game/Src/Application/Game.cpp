#define _CRTDBG_MAP_ALLOC
#include "main.h"
#include "define.h"
#include"SceneManager.h"
#include"TitelScene.h"
#include"Game.h"
#include"ClearScene.h"
#include"GameOverScene.h"
#include"System/KeySystem.h"
#include"ModelIntersects.h"

GameScene::GameScene()
{
	Init();
}
GameScene::~GameScene()
{
	Release();
}

//=============================================================================================================================================

//カメラ設定
void GameScene::SetCamera()
{
	//カメラの移動設定
	//-----------------------------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------ギミック動く後カメラの移動する場合
	if (SYSTEM.Getstagecam() == true)
	{
		//第一ステージのカメラ
		if (SYSTEM.GetnowStage() == 1)
		{
			//カメラ最初の位置
			if (cameraProgress == 0)
			{
				camLook = m_StatePos;
			}
			cameraProgress += 0.01f;//カメラ動きの時間線
			if (cameraProgress > 0.0f && cameraProgress <= 1.0f)
			{
				camPos.z -= 0.1f;
				camLook.x -= 0.2f;
				camLook.y += 0.3f;
			}
			if (cameraProgress > 1.0f && cameraProgress <= 2.0f)
			{
				camLook.y -= 0.3f;
			}
			if (cameraProgress > 2.0f&& cameraProgress <= 2.5f)
			{
				//カメラ注目用だけ
			}
			if (cameraProgress >= 2.5f)
			{
				cameraProgress = 2.5f;
				SYSTEM.Setstagecam(false);
			}
		}

		//第二ステージのカメラ
		if (SYSTEM.GetnowStage() == 2)
		{
			//カメラ最初の位置
			if (cameraProgress == 0)
			{
				camPos = Math::Vector3(-40, 0, 20);
				camLook = Math::Vector3(-10, 10, 20);
			}
			cameraProgress += 0.01f;//カメラ動きの時間線
			//最初の移動
			if (cameraProgress > 0.0f && cameraProgress <= 0.5f)
			{
				camPos.y += 0.5f;
				camPos.x += 0.1f;
				camLook.x += 0.5f;
			}
			//次の移動
			if (cameraProgress > 0.5f && cameraProgress <= 1.5f)
			{
				camPos.y += 0.1f;
				camPos.x += 0.4f;
				camLook.x -= 0.1f;
				camLook.z += 0.3f;
			}
			//最後の移動
			if (cameraProgress > 1.5f && cameraProgress <= 3.0f)
			{
				camPos.x -= 0.1f;
				camPos.z += 0.1f;
				camLook.x -= 0.2f;
				camLook.z += 0.2f;
			}

			if (cameraProgress >= 3.0f)
			{
				cameraProgress = 3.0f;
				SYSTEM.Setstagecam(false);
			}

			camHead = Math::Vector3(0, 1, 0);

		}
		//第三ステージのカメラ
		if (SYSTEM.GetnowStage() == 3)
		{
			if (cameraProgress == 0)
			{
				camLook = m_BBQcam;
			}

			if (cameraProgress > 0.0f && cameraProgress <= 2.0f)
			{
				camPos.x -= 0.05f;
				camPos.y += 0.05f;
				camPos.z -= 0.08f;
				camLook += {0.1f, 0.05f, -0.05f};
			}
			if (cameraProgress > 2.0f && cameraProgress <= 4.0f)
			{
				Math::Vector3 GreenToWhiteLook,GreenToWhitePos;
				GreenToWhiteLook = m_PlayerManager->Getmat().Translation() - camLook;
				
				Math::Matrix tmpRotY, tmpRotX, tmpRot;
				Math::Vector3 tmpCamPos;

				tmpRotY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_camAngY));
				tmpRotX = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_camAngX));
				tmpRot = tmpRotX * tmpRotY;

				tmpCamPos = DirectX::XMVector3TransformNormal(Math::Vector3(0, 5, camZ), tmpRot);
				tmpCamPos += m_PlayerManager->Getmat().Translation();
				GreenToWhitePos = tmpCamPos - camPos;

				camPos += GreenToWhitePos * 0.025f;
				camLook += GreenToWhiteLook * 0.025f;

			}

			cameraProgress += 0.01f;//カメラ動きの時間線

			camHead = Math::Vector3(0, 1, 0);

			if (cameraProgress >= 4.0f)
			{
				cameraProgress = 4.0f;
				SYSTEM.Setstagecam(false);
				SYSTEM.Setcolormode(1);//白い団子に戻る
			}
		}
	//-------------------------------------------------------------ギミック動く後カメラの移動する場合

	}
	else
	{
		if (intro == true)
		{
			camPos = m_Goalpin->GetMat().Translation() + Math::Vector3(0, 10, -10);

			camPos += m_GPcamPos;
			m_GoalPos = m_Goalpin->GetMat().Translation();
			camLook = m_GoalPos;
			camLook += m_GPcamLook;

			camHead = Math::Vector3(0, 1, 0);

			//ステージ最初カメラの動き設定
			Math::Vector3 PcamPos;//プレイヤカメラの位置
			PcamPos = Math::Vector3(0, 5, camZ);
			Math::Vector3 GPCamVec;//ゴールカメラからプレイヤカメラまでのベクトル
			GPCamVec = PcamPos - camPos;
			float GPCamlen;
			GPCamlen = GPCamVec.Length();
			GPCamVec.Normalize();
			float sang = 0.0f;
			sang += 15;
			if (sang >= 90)
			{
				sang = 90;
			}
			GPCamVec.y *= sin(DirectX::XMConvertToRadians(sang));
			float movespeed;
			movespeed = 0.5f;
			if (GPCamlen <= 20.0f)
			{
				movespeed *= 0.5f;
			}
			if (GPCamlen <= 0.025f)
			{
				movespeed = 0.0f;
				startalpha += 0.05f;
				if (startalpha >= 1.0f)
				{
					startalpha = 1.0f;
				}
				startwait--;
				if (startwait <= 0)
				{
					startwait = 0;
					intro = false;
				}
				if (startFlg == false)
				{
					startFlg = true;
					SYSTEM.GetSoundManager().SetSound("Data/music/startgame.wav");
				}
			}

			Math::Vector3 camLookmove;
			float len;
			camLookmove = m_StatePos - camLook;
			len = camLookmove.Length();
			camLookmove.Normalize();
			if (len >= 0.1f)
			{
				m_GPcamLook += camLookmove * movespeed * 0.8f;

			}

			m_GPcamPos += GPCamVec * movespeed;
		}
		else
		{
			Math::Matrix tmpRotY, tmpRotX, tmpRot;

			tmpRotY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_camAngY));
			tmpRotX = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_camAngX));
			tmpRot = tmpRotX * tmpRotY;

			camPos = DirectX::XMVector3TransformNormal(Math::Vector3(0, 5, camZ), tmpRot);

			camPos += m_StatePos;
			camLook = m_StatePos;
			camHead = Math::Vector3(0, 1, 0);
			if (camPos.y <= 0)
			{
				camPos.y = 0;
			}
			Math::Vector3 cam_Vec;
			float camlen = 0;
			float hitdis;
			Math::Vector3 returnVec;
			float range = 1.0f;

			cam_Vec = camPos - camLook;
			camlen = cam_Vec.Length();
			cam_Vec.Normalize();

			//カメラの当たり判定/////////////////////////////////////////////////////////////////////////////

			//物体に当たったらカメラのベクトルを入れる（透過判定用）
			m_CameraVec = (m_BlockManager->CheckHit(camLook, cam_Vec, hitdis, returnVec, camlen)) ? cam_Vec : Math::Vector3::Zero;
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------


	SHADER.m_cb7_Camera.Work().mV = DirectX::XMMatrixLookAtLH(
		camPos,	// カメラの座標
		camLook, // カメラの注視点
		camHead);	// カメラの頭の方向
	SHADER.m_cb7_Camera.Work().CamPos = SHADER.m_cb7_Camera.Work().mV.Invert().Translation();

	//射影行列
	SHADER.m_cb7_Camera.Work().mP = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60), (float)ScrW / (float)ScrH, 0.01f, 1000.0f);

	//ビュー行列・射影行列をGPUに転送
	SHADER.m_cb7_Camera.Write();

}

//=============================================================================================================================================

//動作処理
void GameScene::Update()
{

	//目標紹介のカメラが作動している時、マウスの座標が変わらないようにする
	if (intro == true)
	{
		SetCursorPos(m_basept.x, m_basept.y);
	}


	//目標紹介のカメラが作動していない場合
	if (intro == false)
	{
		//マウスでカメラを回転する設定
		POINT pt;
		GetCursorPos(&pt);
		if (APP.m_window.GetWndHandle() == GetActiveWindow())
		{
			m_camAngY += (pt.x - m_basept.x) / 4.0f;
			m_camAngX += (pt.y - m_basept.y) / 4.0f;
			if (m_camAngX > 30)
			{
				m_camAngX = 30;
			}
			if (m_camAngX < -30)
			{
				m_camAngX = -30;
			}

			//ラメラの角度に反映し終えたらマウス座標を基準座標に戻す
			SetCursorPos(m_basept.x, m_basept.y);
		}
		//3Dアイテム
		m_BlockManager->Update();
		//プレイヤ
		m_PlayerManager->Update(m_BlockManager);
		//プレイヤの回転情報
		m_Rot = m_PlayerManager->Getrot();
		//プレイヤの角度情報
		playerAng = m_PlayerManager->Getang();
		m_TransWait->Update();

		//第一ステージの場合
		if (SYSTEM.GetnowStage() == 1)
		{
			//缶のボタン
			m_Canbt->Update();
		}

		//第二ステージの場合
		if (SYSTEM.GetnowStage() == 2)
		{
			//水面の処理
			m_Water->Update();
		}


		//第三ステージ団子の切替
		//-------------------------------------------------------------------------------------団子1パターンの切り替え
		Math::Matrix tmpMat;
		//白い団子の出番
		if (SYSTEM.Getcolormode() == 1)
		{
			tmpMat = m_PlayerManager->Getmat();
			m_Mat = tmpMat;
			m_StatePos = tmpMat.Translation();
		}

		//ピンク団子の出番（第三ステージのみ）
		if (SYSTEM.Getcolormode() == 2)
		{
			m_Mat = m_Fellow1->Getmat();
			float tmplen;
			Math::Vector3 tmpVec;
			tmpVec = m_Mat.Translation() - m_StatePos;
			tmplen = tmpVec.Length();
			tmpVec.Normalize();

			if (m_StatePos != m_Mat.Translation())
			{
				SYSTEM.SetbuttonCam(false);
			}

			switch (SYSTEM.GetbuttonCam())
			{
			case false:
				m_StatePos += tmpVec * 0.3f;
				if (tmplen <= 0.3)
				{
					SYSTEM.SetbuttonCam(true);
					m_StatePos = m_Mat.Translation();
				}
				break;
			case true:
				m_StatePos = m_Mat.Translation();
				break;
			}

		}

		//緑団子の出番（第三ステージのみ）
		if (SYSTEM.Getcolormode() == 3)
		{
			m_Mat = m_Fellow2->Getmat();
			float tmplen;
			Math::Vector3 tmpVec;
			tmpVec = m_Mat.Translation() - m_StatePos;
			tmplen = tmpVec.Length();
			tmpVec.Normalize();
			if (m_StatePos != m_Mat.Translation())
			{
				SYSTEM.SetbuttonCam(false);
			}

			switch (SYSTEM.GetbuttonCam())
			{
			case false:
				m_StatePos += tmpVec * 0.3f;
				if (tmplen <= 0.3)
				{
					SYSTEM.SetbuttonCam(true);
					m_StatePos = m_Mat.Translation();
				}
				break;
			case true:
				m_StatePos = m_Mat.Translation();
				
				break;
			}

			m_BBQcam = m_StatePos;//緑団子の位置を入れる
		}
		//-------------------------------------------------------------------------------------団子1パターンの切り替え

		//第一パターン後ろついている団子たち
		if (SYSTEM.Getstagecam() == false)
		{
			m_Fellow1->Update(m_StatePos, m_BlockManager);
			m_Fellow2->Update(m_Fellow1->GetPos(), m_BlockManager);
		}

		//第三ステージの場合の処理
		if (SYSTEM.GetnowStage() == 3)
		{
			for (UINT i = 0; i < m_Coal.size(); i++)
			{
				//炭
				m_Coal[i]->Update();
			}

			//第三ステージ機関が起動した場合
			if (SYSTEM.GetHotState() == true)
			{
				m_Smoke.push_back(new C_Smoke(Math::Vector3(rand() % 11 - 5.0f, 10.0f, rand() % 46 + 25.0f)));

				for (UINT i = 0; i < m_Smoke.size(); i++)
				{
					m_Smoke[i]->Update();
				}
				//第三ステージの煙を消す設定
				for (UINT i = 0; i < m_Smoke.size(); i++)
				{
					if (m_Smoke[i]->Update() == false)
					{
						delete m_Smoke[i];
						m_Smoke.erase(m_Smoke.begin() + i);
						i--;
					}
				}
			}
		}

		//目標紹介カメラ作動完了
		if (startwait <= 0)
		{
			//スタート2D文字の設定
			startalpha -= 0.02f;
			if (startalpha <= 0.0f)
			{
				startalpha = 0.0f;
			}
			startgame_mat *= DirectX::XMMatrixScaling(1.02f, 1.02f, 1.02f);
		}

		//ゴールに着いたらの処理
		if ((m_Mat.Translation() - m_Goalpin->GetMat().Translation()).Length() < m_Goalpin->GetRange())
		{
			SYSTEM.GetSoundManager().SetSound("Data/music/warp.wav");
			
			SYSTEM.GetSceneManager().ChangeScene(new Clearscene);
			ShowCursor(TRUE);
			SYSTEM.SetnowStage(0);
		}

		//ゲームオーバーになったら、カウントダウンして、オーバーシーンに入る
		if (SYSTEM.GetoverFlg() == true)
		{
			overCountDown--;
			if (overCountDown <= 0.0f)
			{
				SYSTEM.GetSceneManager().ChangeScene(new GameOver);
				ShowCursor(TRUE);
			}
		}
	}
}

//=============================================================================================================================================

//描画処理
void GameScene::Draw()
{
	//ラムダ式で関数を作成
	auto drawCharacters = [this]()
	{
		SHADER.m_standardShader.SetToDevice();
		//背景
		m_Background->Draw();
		//背景の飾り
		m_Backitem->Draw();

		SHADER.m_effectShader.SetToDevice();
		//地面
		m_Ground->Draw();

		//第三ステージしか写ってない
		if (SYSTEM.GetnowStage() == 3)
		{
			for (UINT i = 0; i < m_Coal.size(); i++)
			{
				m_Coal[i]->Draw();
			}
		}

		SHADER.m_standardShader.SetToDevice();
		if (m_BlockManager != nullptr)
		{
			//3Dアイテム
			m_BlockManager->Draw();
		}
	};

	//=====================================
	// IBL画像生成描画
	//=====================================
	if (m_cubeMapGen.GetCubeMap() == nullptr)
	{
		//100番目スロットのテクスチャを解除
		ID3D11ShaderResourceView* nullSRV = nullptr;
		D3D.GetDevContext()->PSSetShaderResources(
			100,	//セットするスロット番号
			1,		//セットする数
			&nullSRV
		);
		//キューブマップ生成描画

		m_cubeMapGen.Generate(512, m_StatePos, drawCharacters);

		//作成したキューブマップを、シェーダーに渡す
		D3D.GetDevContext()->PSSetShaderResources(
			100,	//セットするスロット番号
			1,		//セットする数
			m_cubeMapGen.GetCubeMap()->GetSRViewAddress()
		);
	}

	//全物体の描画
	drawCharacters();

	//パターン変換途中じゃない場合
	if (SYSTEM.Getplayframe() == false)
	{
		if (m_PlayerManager != nullptr)
		{
			m_PlayerManager->Draw();
		}
		//第一パターン
		if (SYSTEM.Getstate() == 1)
		{
			m_Fellow1->Draw();
			m_Fellow2->Draw();
		}
	}
	else//パターン変換途中
	{
		//途中変換モデル
		m_TransWait->Draw();
	}

	//ゴール
	m_Goalpin->Draw();
	//第一ステージの場合
	if (SYSTEM.GetnowStage() == 1)
	{
		//缶のボタン
		m_Canbt->Draw();
	}
	//第二ステージの場合
	if (SYSTEM.GetnowStage() == 2)
	{
		//水面
		m_Water->Draw();
	}

	if (SYSTEM.GetHotState() == true)
	{
		D3D.GetDevContext()->OMSetBlendState(blendAdd, Math::Color(0, 0, 0, 0), 0xFFFFFFFF);
		if (SYSTEM.GetnowStage() == 3)
		{
			SHADER.m_effectShader.SetToDevice();
			for (UINT i = 0; i < m_Smoke.size(); i++)
			{
				//煙
				m_Smoke[i]->Draw();
			}
		}
		D3D.GetDevContext()->OMSetBlendState(blendAlpha, Math::Color(0, 0, 0, 1), 0xFFFFFFFF);

	}

	SHADER.m_spriteShader.Begin();

	if (SYSTEM.GetoverFlg() == false)
	{

		SHADER.m_spriteShader.SetMatrix(startgame_mat);
		SHADER.m_spriteShader.DrawTex(&m_Startgame, Math::Rectangle(0, 0, 940, 300), startalpha);


		if (intro == false&&SYSTEM.GetnowStage()!=0)
		{
			SHADER.m_spriteShader.SetMatrix(clock_mat);
			SHADER.m_spriteShader.DrawTex(&m_Clock, Math::Rectangle(0, 0, 108, 108), 1.0f);
			m_Number->Draw();
			m_Icon->Draw(SYSTEM.Getstate());

			if (SYSTEM.Getstate() == 2)
			{
				SHADER.m_spriteShader.SetMatrix(presssp_mat);
				SHADER.m_spriteShader.DrawTex(&m_PressSpace, Math::Rectangle(0, 0, 320, 90), 1.0f);
			}
		}
	}
	SHADER.m_spriteShader.End();


}

//=============================================================================================================================================

//初期化処理
void GameScene::Init()
{

	srand(timeGetTime());

	m_basept = { ScrW / 2,ScrH / 2 };

	ClientToScreen(APP.m_window.GetWndHandle(), &m_basept);
	SetCursorPos(m_basept.x, m_basept.y);
	ShowCursor(FALSE);


	// 平行ライト設定
	SHADER.m_cb8_Light.Work().DL_Dir = { 1,-1,0 };
	SHADER.m_cb8_Light.Work().DL_Dir.Normalize();
	SHADER.m_cb8_Light.Work().DL_Color = { 0.5,0.5,0.5 };
	//SHADER.m_cb8_Light.Work().AmbientLight = { 0.5f,0.5f,0.5f };
	// ライトのデータを書き込む
	SHADER.m_cb8_Light.Write();

	//ブレンド設定
	blendAdd = D3D.CreateBlendState(KdBlendMode::Add);
	blendAlpha = D3D.CreateBlendState(KdBlendMode::Alpha);

	//モデル

	m_TransWait = std::make_unique<C_Transwait>();
	m_Ground = std::make_unique<C_ground>();
	m_Background = std::make_unique<C_Background>();
	m_Backitem = std::make_unique<C_Backitem>();
	m_Goalpin = std::make_unique<C_Warp>();
	m_Number = std::make_unique<C_number>();
	m_Icon = std::make_unique<C_icon>();
	m_Stagelimit = std::make_unique<C_Shell>();
	m_Water = std::make_unique<C_water>();
	m_Canbt = std::make_unique<C_canbt>();
	m_Fellow1 = std::make_unique<C_Fellow1>();
	m_Fellow2 = std::make_unique<C_Fellow2>();

	m_ModelManager = std::make_shared<ModelManager>();
	m_BlockManager = std::make_unique<BlockManager>(m_ModelManager);
	m_PlayerManager = std::make_unique<PlayerManager>();

	m_Coal.push_back(new C_coal(Math::Vector3(-7.0f, 10.0f, 23.0f)));
	m_Coal.push_back(new C_coal(Math::Vector3(-7.0f, 10.0f, 39.0f)));
	m_Coal.push_back(new C_coal(Math::Vector3(-7.0f, 10.0f, 55.0f)));

	transFlg = false;
	hintFlg = false;
	startFlg = false;
	intro = true;

	m_StatePos = m_Mat.Translation();
	m_camAngY = 0;
	m_camAngX = 0;
	camposZ = -15;
	startalpha = 0.0f;
	startwait = 60.0f;
	overCountDown = 120.0f;
	cameraProgress = 0.0f;

	clock_mat = DirectX::XMMatrixTranslation(-600, 300, 0);
	startgame_mat = DirectX::XMMatrixScaling(0.5f, 0.5f, 0.5f) * DirectX::XMMatrixTranslation(0, 0, 0);
	presssp_mat = DirectX::XMMatrixTranslation(0, -200, 0);

	m_Clock.Load("Data/Texture/clock.png");
	m_Startgame.Load("Data/Texture/startgame.png");
	m_PressSpace.Load("Data/Texture/pressspace.png");

	SYSTEM.SetnextStage(SYSTEM.GetnowStage() + 1);
	SYSTEM.Setstate(1);
	//BGMイニシャル
	m_Soundbgm = std::make_shared<KdSoundEffect>();
	m_Soundbgm->Load("Data/music/Stagesound.wav");
	m_BgmInst = m_Soundbgm->CreateInstance(false);
	m_BgmInst->SetVolume(0.05f);
	m_BgmInst->Play(true);
}

//=============================================================================================================================================

//リリース処理
void GameScene::Release()
{
	for (UINT i = 0; i < m_Coal.size(); i++)
	{
		delete m_Coal[i];
	}

	for (UINT i = 0; i < m_Smoke.size(); i++)
	{
		delete m_Smoke[i];
	}
	m_Coal.clear();
	m_Smoke.clear();
	m_Clock.Release();
	m_PressSpace.Release();
	m_Startgame.Release();
	m_BgmInst->Stop();

}
