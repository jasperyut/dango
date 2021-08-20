#include"CompleteScene.h"
#include"Game.h"
#include"TitelScene.h"
#include"SceneManager.h"
#include"System/KeySystem.h"

CompleteScene::CompleteScene()
{
	Init();
}

CompleteScene::~CompleteScene()
{
	Release();
}

void CompleteScene::Init()
{
	SHADER.m_cb8_Light.Work().DL_Dir = { 1,-1,0 };
	SHADER.m_cb8_Light.Work().DL_Dir.Normalize();
	SHADER.m_cb8_Light.Work().DL_Color = { 2,2,2 };
	SHADER.m_cb8_Light.Work().AmbientLight = { 0.5f,0.5f,0.5f };
	SHADER.m_cb8_Light.Write();



	m_ModelManager = std::make_shared<ModelManager>();
	m_BlockManager = std::make_shared<BlockManager>(m_ModelManager);
	m_Ground = std::make_unique<C_ground>();
	m_Background = std::make_unique<C_Background>();
	m_Backitem = std::make_unique<C_Backitem>();
	m_Coal = std::make_unique<C_coal>(Math::Vector3(-5.0f, 10.0f, 53.0f));
	m_CamPos[0] = Math::Vector3(0, 15, 65);
	set = 0;
	txtalpha = 0.0f;
	scalevalue = 2.0f;
	waittime = 60;
	changeflg = false;
	playonceTurnsound = false;
	playonce2Dtxt = false;
	playoncegrill = false;
	playonceFlysound = false;
	//最初の動画シーン
	for (int i = 0; i < 3; i++)
	{
		m_PinDefault[i].Load("Data/model/pindefault.gltf");
		m_PinSmile[i].Load("Data/model/pinsmile.gltf");
		frame_start[i] = DirectX::XMMatrixTranslation(i * 2.0f, 7.0f, 87.0f);
		m_PinMat[i] = frame_start[i];
		Math::Matrix m_Trans;
		m_Trans = DirectX::XMMatrixTranslation(i * 2.0f, 100.0f, 87.0f);

		frame_end[i] = m_Trans;
	}

	m_animeProgress = 0;
	m_Bbqnet.Load("Data/model/bbqnet.gltf");
	m_NetMat = DirectX::XMMatrixTranslation(2.0f, 13.0f, 60.0f);
	m_Complete.Load("Data/Texture/complete.png");
	m_ComMat = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	SYSTEM.GetSoundManager().SetSound("Data/music/completescene.wav");

}

void CompleteScene::Update()
{
	//次の動画シーン
	if (set == 1)
	{
		for (int n = 0; n < 3; n++)
		{
			frame_start[n] = DirectX::XMMatrixTranslation(n * 2.0f, 40.0f, 67.0f);
			m_PinMat[n] = frame_start[n];
			Math::Matrix m_Trans;
			Math::Matrix m_Rot;
			m_Rot = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(90)) * DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(180));
			m_Trans = DirectX::XMMatrixTranslation(n * 2.0f, 15.0f, 65.0f);

			frame_end[n] = m_Rot * m_Trans;
		}

	}

	m_Coal->Update();
	Math::Matrix scalemat;

	m_ComMat = scalemat * m_ComMat;

	m_CamPos[0].z += 0.1f;
	if (m_CamPos[0].z >= 75.0f)
	{
		m_CamPos[0].z = 75.0f;
	}
	//第一カメラが指定の位置に行ったら
	if (m_CamPos[0].z >= 75.0f)
	{
		if (playonceFlysound == false)
		{
			playonceFlysound = true;
			SYSTEM.GetSoundManager().SetSound("Data/music/fly.wav");
		}
		//第一カメラ、団子の動画
		for (int i = 0; i < 3; i++)
		{
			m_animeProgress += 0.003f;
			if (m_animeProgress >= 1.0f)
			{
				m_animeProgress = 1.0f;
			}

			AnimeProc(i);

		}
	}
	//第二カメラ、団子の動画
	if (set == 1)
	{
		for (int n = 0; n < 3; n++)
		{
			m_animeProgress += 0.003f;
			if (m_animeProgress >= 1.0f)
			{
				m_animeProgress = 1.0f;
				if (playoncegrill == false)
				{
					//団子が焼いてサウンド
					SYSTEM.GetSoundManager().SetSound("Data/music/grillsound.wav");
					playoncegrill = true;
				}
			}

			AnimeProc(n);

		}
	}
	//カメラ2動き
	if (set == 1 && m_animeProgress >= 1.0f)
	{
		Math::Vector3 tmpPos;
		tmpPos = Math::Vector3(1.9f, 20.0f, 62.0f);
		Math::Vector3 camVec;
		float camlen;
		camVec = tmpPos - m_CamPos[1];
		camlen = camVec.Length();
		camVec.Normalize();

		if (camlen >= 0.2f)
		{
			m_CamMove += camVec * 0.1f;
		}
		else//カメラが指定の位置に行ったら 
		{

			m_CamMove += {0.0f, 0.0f, 0.0f};
			changeflg = true;////顔変えるフラグ

			waittime--;
			if (waittime <= 0)
			{
				waittime = 0;
			}
			//顔変えるサウンド
			if (playonceTurnsound == false)
			{
				SYSTEM.GetSoundManager().SetSound("Data/music/change.wav");
				playonceTurnsound = true;
			}
		}
	}


	for (int i = 0; i < 3; i++)
	{
		if (changeflg == false)
		{
			m_PinContainer[i] = m_PinDefault[i];
		}
		else//顔変わるとき
		{
			m_PinContainer[i] = m_PinSmile[i];

		}
	}
	//一定時間後、文字が出る
	if (waittime == 0)
	{
		scalevalue *= 0.9f;
		if (scalevalue <= 0.7f)
		{
			scalevalue = 0.7f;
			if (playonce2Dtxt == false)
			{
				//2D文字サウンド
				SYSTEM.GetSoundManager().SetSound("Data/music/completetxt.wav");
				playonce2Dtxt = true;
			}
		}
		Math::Matrix scale;
		Math::Matrix trans;
		trans = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);//文字の位置
		scale = DirectX::XMMatrixScaling(scalevalue, scalevalue, scalevalue);//文字の大きさ
		//文字のアルファ値
		txtalpha += 0.05f;
		if (txtalpha >= 1.0f)
		{
			txtalpha = 1.0f;
		}
		m_ComMat = scale * trans;


		//メニューに戻る
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (SYSTEM.GetEnterKeyFlg() == false)
			{
				SYSTEM.GetSoundManager().SetSound("Data/music/button.wav");
				SYSTEM.SetEnterKeyFlg(true);
				SYSTEM.GetSceneManager().ChangeScene(new TitleScene());

			}
		}
		else
		{
			SYSTEM.SetEnterKeyFlg(false);
		}
	}




}

void CompleteScene::Draw()
{
	SHADER.m_standardShader.SetToDevice();

	m_Background->Draw();
	m_Backitem->Draw();

	if (m_BlockManager != nullptr)
	{
		m_BlockManager->Draw();
	}
	for (int i = 0; i < 3; i++)
	{

		SHADER.m_standardShader.SetWorldMatrix(m_PinMat[i]);
		SHADER.m_standardShader.DrawModel(&m_PinContainer[i]);

	}

	SHADER.m_standardShader.SetWorldMatrix(m_NetMat);
	SHADER.m_standardShader.DrawModel(&m_Bbqnet);

	SHADER.m_effectShader.SetToDevice();
	
	m_Ground->Draw();
	m_Coal->Draw();

	SHADER.m_spriteShader.Begin();
	//顔変わるとき
	if (changeflg == true)
	{
		SHADER.m_spriteShader.SetMatrix(m_ComMat);
		SHADER.m_spriteShader.DrawTex(&m_Complete, Math::Rectangle(0, 0, 1450, 300), txtalpha);
	}
	SHADER.m_spriteShader.End();
}

void CompleteScene::SetCamera()
{
	m_CamLook[0] = m_PinMat[2].Translation();
	if (m_CamLook[0].y >= 70)
	{
		set = 1;
		m_animeProgress = 0;
	}
	m_CamPos[1] = Math::Vector3(7, 25, 70);
	m_CamPos[1] += m_CamMove;

	m_CamLook[1] = m_NetMat.Translation();

	SHADER.m_cb7_Camera.Work().mV = DirectX::XMMatrixLookAtLH(
		m_CamPos[set],
		m_CamLook[set],
		Math::Vector3(0, 1, 0));
	SHADER.m_cb7_Camera.Work().CamPos = SHADER.m_cb7_Camera.Work().mV.Invert().Translation();

	//射影行列(視界の設定)                                                                          //↓見える距離（最小値,最大値）
	SHADER.m_cb7_Camera.Work().mP =
		DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60), (float)ScrW / (float)ScrH, 0.01f, 1500.0f);
	//                                                         ↑視野角          　↑アスペクト比（横幅長さと縦幅の長さの比率）
	//ビュー行列・射影行列をGPUに転送
	SHADER.m_cb7_Camera.Write();
}

void CompleteScene::AnimeProc(int i)
{
	Math::Quaternion startQua;
	Math::Quaternion endQua;
	Math::Quaternion nowQua;
	Math::Vector3 startPos;
	Math::Vector3 endPos;
	Math::Vector3 nowPos;

	//アニメ最初の行列をクオータニオンに変換する
	startQua = DirectX::XMQuaternionRotationMatrix(frame_start[i]);
	//アニメ最後の行列をクオータニオンに変換する
	endQua = DirectX::XMQuaternionRotationMatrix(frame_end[i]);
	//↓最初の状態　　　↓変化の具合
	nowQua = DirectX::XMQuaternionSlerp(startQua, endQua, m_animeProgress);

	m_PinMat[i] = DirectX::XMMatrixRotationQuaternion(nowQua);


	startPos = frame_start[i].Translation();
	endPos = frame_end[i].Translation();
	//↓最初の位置　　　↓変化の具合
	nowPos = DirectX::XMVectorLerp(startPos, endPos, m_animeProgress);

	//アニメ途中の座標情報を行列に上書きする
	m_PinMat[i].Translation(nowPos);
}

void CompleteScene::Release()
{
	for (int i = 0; i < 3; i++)
	{
		m_PinDefault[i].Release();
		m_PinSmile[i].Release();
		m_PinContainer[i].Release();

	}
	m_Bbqnet.Release();
	m_Complete.Release();
}
