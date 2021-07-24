#include "pch.h"
#include "Player.h"

Player::Player()
{
	m_Paddle.m_Speed = 0.0f;
	m_Paddle.m_Rect.left = 0.0f;
	m_Paddle.m_Rect.top = 0.0f;
	m_Paddle.m_Rect.right = 0.0f;
	m_Paddle.m_Rect.bottom = 0.0f;
	m_X = 0;
	m_Y = 0;
	m_Score = 0;
}


void Player::Draw(HDC & m_hdcFrameBuffer, ULONG Color)
{

	LOGPEN logPen;
	LOGBRUSH lb;
	HPEN   hPen = nullptr, hOldPen = nullptr;
	HBRUSH hBrush = nullptr, hOldBrush = nullptr;

	// Set up the rendering pen
	logPen.lopnStyle = PS_SOLID;
	logPen.lopnWidth.x = 1;
	logPen.lopnWidth.y = 1;

	lb.lbStyle = BS_SOLID;
	lb.lbHatch = 0;

	// Set up the colour, converted to BGR & stripped of alpha
	logPen.lopnColor = 0x00FFFFFF & RGB2BGR(Color);
	lb.lbColor = 0x00FFFFFF & RGB2BGR(Color);

	// Create the rendering pen
	hPen = ::CreatePenIndirect(&logPen);
	hBrush = ::CreateBrushIndirect(&lb);
	if (!hPen) return;
	if (!hBrush) return;
	// Select into the frame buffer DC
	hOldPen = (HPEN)::SelectObject(m_hdcFrameBuffer, hPen);
	hOldBrush = (HBRUSH)::SelectObject(m_hdcFrameBuffer, hBrush);
	// Draw the line segment
	Rectangle(m_hdcFrameBuffer, m_Paddle.m_Rect.left + m_X, m_Paddle.m_Rect.top + m_Y, m_Paddle.m_Rect.right + m_X,  m_Paddle.m_Rect.bottom + m_Y );

	// Destroy rendering pen
	::SelectObject(m_hdcFrameBuffer, hOldPen);
	::SelectObject(m_hdcFrameBuffer, hOldBrush);
	::DeleteObject(hPen);
	::DeleteObject(hBrush);
}
void Player::UpdateUp()
{
	m_Y -= m_Paddle.m_Speed;
}
void Player::UpdateDown()
{
	m_Y += m_Paddle.m_Speed;
}

bool Player::Collistion(Puck& puck)
{
	if ((m_X + 5 + m_Paddle.m_Rect.right)	> puck.m_Position.mX     &&
		(m_X + 5 + m_Paddle.m_Rect.left)	< puck.m_Position.mX     &&
		(m_Y + 5 + m_Paddle.m_Rect.top)     < puck.m_Position.mY     &&
		(m_Y + 5 + m_Paddle.m_Rect.bottom)  > puck.m_Position.mY
		)
		return true;
	return false;
}
