#pragma once

#include "CPaddle.h"
#include "main.h"
#include "Puck.h"

class Player
{ 
public:
	Player();
	
	void Draw(HDC& m_hdcFrameBuffer, ULONG Color);
	void UpdateUp();
	void UpdateDown();
	bool Collistion(Puck & puck);

	CPaddle m_Paddle;
	ULONG m_X;
	ULONG m_Y;
	int m_Score;
};

