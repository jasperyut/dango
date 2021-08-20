#include"cylinder.h"
#include"Application/ModelIntersects.h"

bool C_cylinder::CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range)const
{
	Math::Vector3 blocknormal;


	if (ModelIntersects(*m_Model, m_Mat, _rayPos, _rayVec, _dis, blocknormal))
	{
		Math::Vector3 dot;
		dot = DirectX::XMVector3Dot(-_rayVec, blocknormal);

		float limit;
		limit = _range / dot.x;
		if (limit < 0)
		{
			limit *= -1;
		}
		//•Ç‚Ü‚ÅlimitˆÈ‰º‚Å“–‚½‚Á‚Ä‚¢‚½‚ç
		if (_dis <= limit)
		{
			_returnVec = blocknormal * ((limit - _dis) * dot.x);
			return true;
		}
	}
	return false;
}

C_cylinder::C_cylinder(std::shared_ptr<ModelManager>& _om, const Math::Vector3& _pos)
{
	m_Model = _om->GetModel("Data/model/cylinder.gltf");
	Math::Matrix m_RotY;
	m_RotY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90));
	m_Mat = m_RotY * DirectX::XMMatrixTranslation(_pos.x, _pos.y, _pos.z);

}



void C_cylinder::Draw()
{

	SHADER.m_standardShader.SetWorldMatrix(m_Mat);
	SHADER.m_standardShader.DrawModel(m_Model);
}

void C_cylinder::Update()
{

}


