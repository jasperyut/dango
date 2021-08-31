#pragma once

//====================================================
//
// キューブマップ生成
//
//====================================================
class KdCubeMapGenerator
{
public:

	// 生成されたキューブマップ取得
	std::shared_ptr<KdTexture> GetCubeMap() const { return m_cubeMap; }

	// 指定サイズのキューブマップを生成し、風景を描画する。
	// size		：キューブマップテクスチャのサイズ。
	// position	：撮影するワールド座標。
	// drawProc	：実行する描画関数。
	void Generate(int size, const Math::Vector3& position, std::function<void()> drawProc);

	// ファイルから読み込む
	void LoadFromFile(const std::string& filename);

	// ファイルへ保存する
	void SaveToFile(const std::string& filename);

private:
	// キューブマップ
	std::shared_ptr<KdTexture> m_cubeMap;
	// 描画時に使用するZバッファ
	std::shared_ptr<KdTexture> m_zBuffer;
};
