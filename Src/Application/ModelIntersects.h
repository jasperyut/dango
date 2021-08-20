#pragma once

static const bool ModelIntersectsFlat(const KdModel& _model, const Math::Matrix& _mat, const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis)
{
	float nearestDist = FLT_MAX;	//FLT_MAX==float�^�̍ő�l
	for (auto&& node : _model.GetAllNodes())
	{
		//���b�V�����܂܂�Ă��Ȃ��m�[�h�Ȃ��΂�
		if (node.Mesh == nullptr)continue;

		//���̃m�[�h�̃��[���h�s����擾
		Math::Matrix worldMat = node.LocalTransform * _mat;

		//�t�s��
		Math::Matrix inv = worldMat.Invert();

		//�t�s����g���ă��[�J�����W�ɕϊ�
		Math::Vector3 localPos = DirectX::XMVector3Transform(_rayPos, inv);
		Math::Vector3 localDir = DirectX::XMVector3TransformNormal(_rayVec, inv);

		//�g��s����g���Ă��郁�b�V���p�Ƀ��C�̒������v���Ă���
		float rayLen = localDir.Length();

		//�����͕K�������P�ɂ���
		localDir.Normalize();

		//���b�V�����̑S�|���S������
		for (auto&& face : node.Mesh->GetFaces())
		{
			float dist;

			bool hit = DirectX::TriangleTests::Intersects(
				localPos,
				localDir,
				node.Mesh->GetVertexPositions()[face.Idx[0]],//�P���_�ڂ̍��W
				node.Mesh->GetVertexPositions()[face.Idx[1]],//�Q���_�ڂ̍��W
				node.Mesh->GetVertexPositions()[face.Idx[2]],//�R���_�ڂ̍��W
				dist	//���C�����������Ƃ���܂ł̋���(�Q�ƌ^)
			);

			if (hit == false)continue;

			//�g�啪�𔽉f
			dist /= rayLen;

			//�����Ƃ��߂��������c��
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
	Math::Vector3 hitVPos[3];//���C������������|���S���̒��_���W
	Math::Matrix hitMat;//���C�����������|���S���̍s��

	float nearestDist = FLT_MAX;	//FLT_MAX==float�^�̍ő�l
	for (auto&& node : _model.GetAllNodes())
	{
		//���b�V�����܂܂�Ă��Ȃ��m�[�h�Ȃ��΂�
		if (node.Mesh == nullptr)continue;

		//���̃m�[�h�̃��[���h�s����擾
		Math::Matrix worldMat = node.LocalTransform * _mat;

		//�t�s��
		Math::Matrix inv = worldMat.Invert();

		//�t�s����g���ă��[�J�����W�ɕϊ�
		Math::Vector3 localPos = DirectX::XMVector3Transform(_rayPos, inv);
		Math::Vector3 localDir = DirectX::XMVector3TransformNormal(_rayVec, inv);

		//�g��s����g���Ă��郁�b�V���p�Ƀ��C�̒������v���Ă���
		float rayLen = localDir.Length();

		//�����͕K�������P�ɂ���
		localDir.Normalize();

		//���b�V�����̑S�|���S������
		for (auto&& face : node.Mesh->GetFaces())//Face==��==��==�|���S��
		{
			float dist;

			Math::Vector3 vPos[3];

			vPos[0] = node.Mesh->GetVertexPositions()[face.Idx[0]];//�P���_�ڂ̍��W
			vPos[1] = node.Mesh->GetVertexPositions()[face.Idx[1]];//�Q���_�ڂ̍��W
			vPos[2] = node.Mesh->GetVertexPositions()[face.Idx[2]];//�R���_�ڂ̍��W

			bool hit = DirectX::TriangleTests::Intersects(
				localPos,
				localDir,
				vPos[0],//�P���_�ڂ̍��W
				vPos[1],//�Q���_�ڂ̍��W
				vPos[2],//�R���_�ڂ̍��W
				dist	//���C�����������Ƃ���܂ł̋���(�Q�ƌ^)
			);

			if (hit == false)continue;

			//�g�啪�𔽉f
			dist /= rayLen;

			//�����Ƃ��߂��������c��
			if (dist < nearestDist)
			{
				nearestDist = dist;

				//���C�����������|���S���̒��_���W��ۑ�
				hitVPos[0] = vPos[0];
				hitVPos[1] = vPos[1];
				hitVPos[2] = vPos[2];

				//���C�����������|���S���̍s���ۑ�
				hitMat = worldMat;
			}
		}
	}
	if (nearestDist == FLT_MAX)
	{
		return false;
	}
	else {
		//���C���|���S���ɂ�������
		_dis = nearestDist;

		//�|���S���̉��i�Ӂj�̂���2��\���x�N�g�������߂�
		Math::Vector3 vec1, vec2;
		vec1 = hitVPos[0] - hitVPos[2];
		vec2 = hitVPos[1] - hitVPos[2];

		//�|���S���̂Q�ӂƂ��ɐ����ȃx�N�g�����O�ςŋ��߂�
		//�Q�ӂƂ��ɐ��������|���S���ʂɐ����Ȃ̂Ŗ@���Ƃ���
		_normal = DirectX::XMVector3Cross(vec1, vec2);

		//���[�J�����W��ł̖@�������ۂ̂RD��Ԃ̌����ɕϊ�����
		_normal = DirectX::XMVector3TransformNormal(_normal, hitMat);

		//�@���͒����P�ɂ���K�v������
		_normal.Normalize();

		return true;
	}

}
