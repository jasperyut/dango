#include "Shell.h"
#include"Application/ModelIntersects.h"

bool C_Shell::CheckHit(const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis, Math::Vector3& _returnVec, float& _range) const
{
	Math::Vector3 blocknormal;


	if (ModelIntersects(m_Model, m_Mat, _rayPos, _rayVec, _dis, blocknormal))
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
		if (_dis*5 <= limit)
		{
			_returnVec = blocknormal * ((limit - _dis) * dot.x);
			return true;
		}
	}
	return false;
}
C_Shell::C_Shell()
{
	m_Model.Load("Data/model/background/backshell.gltf");


}

C_Shell::~C_Shell()
{
	m_Model.Release();
}

void C_Shell::Draw()
{

	SHADER.m_standardShader.SetWorldMatrix(m_Mat);
	SHADER.m_standardShader.DrawModel(&m_Model);
}

void C_Shell::Update()
{

}


