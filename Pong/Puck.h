#pragma once
#include "CVector3.h"

class Puck
{
public:
	Puck();
	void Draw(HDC& m_hdcFrameBuffer, ULONG Color);
	float m_Speed;
	CVector3 m_Position;
	CVector3 m_Velocity;

};

