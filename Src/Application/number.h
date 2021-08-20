#pragma once
//タイマー機能
class C_number
{
public:
	C_number();
	~C_number();
	void Draw();
	void Update();

private:
	KdTexture m_Tex;

	Math::Matrix m_timemat;
	
	DWORD nowTime, prevTime;
	
	int StartTime = 0;
};