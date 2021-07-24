#include "pch.h"
#include "Puck.h"

Puck::Puck()
{
	m_Speed = 0.0f;

}

void Puck::Draw(HDC& m_hdcFrameBuffer, ULONG Color)
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
	Ellipse(m_hdcFrameBuffer, (m_Position.mX - 10), (m_Position.mY - 10), (m_Position.mX + 10), (m_Position.mY + 10));

	// Destroy rendering pen
	::SelectObject(m_hdcFrameBuffer, hOldPen);
	::SelectObject(m_hdcFrameBuffer, hOldBrush);
	::DeleteObject(hPen);
	::DeleteObject(hBrush);
}
