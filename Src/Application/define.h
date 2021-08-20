#pragma once

struct Vertex
{
	//DirectX::SimpleMathの中のVector3を使用
	Math::Vector3 pos;	//座標
	Math::Vector2 uv;	//テクスチャ座標
	Math::Vector4 color;//色
};

static const int ScrW = 1280;
static const int ScrH = 720;
