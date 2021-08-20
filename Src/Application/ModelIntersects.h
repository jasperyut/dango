#pragma once

static const bool ModelIntersectsFlat(const KdModel& _model, const Math::Matrix& _mat, const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis)
{
	float nearestDist = FLT_MAX;	//FLT_MAX==float型の最大値
	for (auto&& node : _model.GetAllNodes())
	{
		//メッシュが含まれていないノードなら飛ばす
		if (node.Mesh == nullptr)continue;

		//そのノードのワールド行列を取得
		Math::Matrix worldMat = node.LocalTransform * _mat;

		//逆行列化
		Math::Matrix inv = worldMat.Invert();

		//逆行列を使ってローカル座標に変換
		Math::Vector3 localPos = DirectX::XMVector3Transform(_rayPos, inv);
		Math::Vector3 localDir = DirectX::XMVector3TransformNormal(_rayVec, inv);

		//拡大行列を使っているメッシュ用にレイの長さを計っておく
		float rayLen = localDir.Length();

		//方向は必ず長さ１にする
		localDir.Normalize();

		//メッシュ内の全ポリゴンを回す
		for (auto&& face : node.Mesh->GetFaces())
		{
			float dist;

			bool hit = DirectX::TriangleTests::Intersects(
				localPos,
				localDir,
				node.Mesh->GetVertexPositions()[face.Idx[0]],//１頂点目の座標
				node.Mesh->GetVertexPositions()[face.Idx[1]],//２頂点目の座標
				node.Mesh->GetVertexPositions()[face.Idx[2]],//３頂点目の座標
				dist	//レイが当たったところまでの距離(参照型)
			);

			if (hit == false)continue;

			//拡大分を反映
			dist /= rayLen;

			//もっとも近い距離を残す
			if (dist < nearestDist)
			{
				nearestDist = dist;
			}
		}
	}
	if (nearestDist == FLT_MAX)
	{
		return false;
	}
	else {
		_dis = nearestDist;

		return true;
	}

}
static const bool ModelIntersects(const KdModel& _model, const Math::Matrix& _mat, const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _normal)
{
	Math::Vector3 hitVPos[3];//レイが当たったらポリゴンの頂点座標
	Math::Matrix hitMat;//レイが当たったポリゴンの行列

	float nearestDist = FLT_MAX;	//FLT_MAX==float型の最大値
	for (auto&& node : _model.GetAllNodes())
	{
		//メッシュが含まれていないノードなら飛ばす
		if (node.Mesh == nullptr)continue;

		//そのノードのワールド行列を取得
		Math::Matrix worldMat = node.LocalTransform * _mat;

		//逆行列化
		Math::Matrix inv = worldMat.Invert();

		//逆行列を使ってローカル座標に変換
		Math::Vector3 localPos = DirectX::XMVector3Transform(_rayPos, inv);
		Math::Vector3 localDir = DirectX::XMVector3TransformNormal(_rayVec, inv);

		//拡大行列を使っているメッシュ用にレイの長さを計っておく
		float rayLen = localDir.Length();

		//方向は必ず長さ１にする
		localDir.Normalize();

		//メッシュ内の全ポリゴンを回す
		for (auto&& face : node.Mesh->GetFaces())//Face==顔==面==ポリゴン
		{
			float dist;

			Math::Vector3 vPos[3];

			vPos[0] = node.Mesh->GetVertexPositions()[face.Idx[0]];//１頂点目の座標
			vPos[1] = node.Mesh->GetVertexPositions()[face.Idx[1]];//２頂点目の座標
			vPos[2] = node.Mesh->GetVertexPositions()[face.Idx[2]];//３頂点目の座標

			bool hit = DirectX::TriangleTests::Intersects(
				localPos,
				localDir,
				vPos[0],//１頂点目の座標
				vPos[1],//２頂点目の座標
				vPos[2],//３頂点目の座標
				dist	//レイが当たったところまでの距離(参照型)
			);

			if (hit == false)continue;

			//拡大分を反映
			dist /= rayLen;

			//もっとも近い距離を残す
			if (dist < nearestDist)
			{
				nearestDist = dist;

				//レイが当たったポリゴンの頂点座標を保存
				hitVPos[0] = vPos[0];
				hitVPos[1] = vPos[1];
				hitVPos[2] = vPos[2];

				//レイが当たったポリゴンの行列を保存
				hitMat = worldMat;
			}
		}
	}
	if (nearestDist == FLT_MAX)
	{
		return false;
	}
	else {
		//レイがポリゴンにあたった
		_dis = nearestDist;

		//ポリゴンの縁（辺）のうち2つを表すベクトルを求める
		Math::Vector3 vec1, vec2;
		vec1 = hitVPos[0] - hitVPos[2];
		vec2 = hitVPos[1] - hitVPos[2];

		//ポリゴンの２辺ともに垂直なベクトルを外積で求める
		//２辺ともに垂直＝＝ポリゴン面に垂直なので法線とする
		_normal = DirectX::XMVector3Cross(vec1, vec2);

		//ローカル座標上での法線を実際の３D空間の向きに変換する
		_normal = DirectX::XMVector3TransformNormal(_normal, hitMat);

		//法線は長さ１にする必要がある
		_normal.Normalize();

		return true;
	}

}
