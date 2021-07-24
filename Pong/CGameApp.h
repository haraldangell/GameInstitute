#pragma once


#include "CTimer.h"
#include "Player.h"
#include "Puck.h"

class CGameApp
{
public:
	CGameApp();
	~CGameApp();

	LRESULT CALLBACK DisplayWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool Init();
	bool BuildDisplay();
	int GameLoop();
	void FrameAdvance();
	void PresentFrameBuffer();
	void ClearFrameBuffer(ULONG Color);
	void Playground();
	void Background();
	void ProcessInput();
	void ProcessAI();
	void GamePlay();
	void Reset();
	void GameResult();
	void DrawLine(const CVector3& vtx1, const CVector3& vtx2, ULONG Color);
	void DrawPoint(const CVector3& vtx1, ULONG Color);
	void DrawRetangle(const const RECT& rect, ULONG color);
	void DrawToScreen(std::string& text, int x, int y, int fontSize, int Color);
	void SetupGameState();
	bool BuildFrameBuffer(ULONG Width, ULONG Height);
	bool ShutDown();

	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);

	bool m_DoneBefore;

	RECT m_Rect;
	Player* m_Player;
	Player* m_AI;
	Puck* m_Puck;
	float mSpeedX;
	float mSpeedY;
	float mSpeedZ;
	int calmdown;
	CTimer m_Timer; //Game Timer

	HWND m_hWnd; //Main window HWND
	HDC m_hdcFrameBuffer; // Frame Buffers Device Context
	HBITMAP m_hbmFrameBuffer; //Frame buffers Bitmap
	HBITMAP m_hbmSelectOut;

	ULONG m_nViewX; // X Position of render viewport
	ULONG m_nViewY; // Y Position of render viewport
	ULONG m_nViewWidth; // Width of render viewport
	ULONG m_nViewHeight; // Height of render viewport
};
