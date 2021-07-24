#include "pch.h"
#include "CGameApp.h"
#include <string>

CGameApp::CGameApp()
{
	m_hWnd = nullptr;
	m_hdcFrameBuffer = nullptr;
	m_hbmSelectOut = nullptr;
	m_hbmFrameBuffer = nullptr;

	m_Rect.left = 0;
	m_Rect.top = 0;
	m_Rect.right = 0;
	m_Rect.bottom = 0;

	m_nViewX = 0;
	m_nViewY = 0;
	m_nViewWidth = 0;
	m_nViewHeight = 0;
	m_DoneBefore = false;

	mSpeedX = 0.0f;
	mSpeedY = 0.0f;
	mSpeedZ = 0.0f;

	calmdown = 0;
	m_AI = nullptr;
	m_Player = nullptr;

}
CGameApp::~CGameApp()
{
	ShutDown();
}
bool CGameApp::ShutDown()
{
	delete m_Player;
	delete m_AI;
	delete m_Puck;
	if (m_hdcFrameBuffer && m_hbmFrameBuffer)
	{
		::SelectObject(m_hdcFrameBuffer, m_hbmSelectOut);
		::DeleteObject(m_hbmFrameBuffer);
		::DeleteDC(m_hdcFrameBuffer);

	} // End if
	if (m_hWnd) DestroyWindow(m_hWnd);

	// Clear all variables
	m_hWnd = nullptr;
	m_hdcFrameBuffer = nullptr;
	m_hbmFrameBuffer = nullptr;

	// Shutdown Success
	return true;
}
LRESULT CALLBACK
CGameApp::DisplayWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		break;

	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:

		// Store new viewport sizes
		m_nViewWidth = LOWORD(lParam);
		m_nViewHeight = HIWORD(lParam);

		// Set up new perspective projection matrix


		// Rebuild the new frame buffer
		BuildFrameBuffer(m_nViewWidth, m_nViewHeight);

		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) DestroyWindow(hWnd);
		return 0;

	}


	return DefWindowProc(hWnd, msg, wParam, lParam);
}
bool CGameApp::Init()
{
	if (!BuildDisplay()) return false;

	SetupGameState();
}
bool CGameApp::BuildDisplay()
{
	LPTSTR  WindowTitle = (LPTSTR)"Grafikk";
	USHORT  Width = 1470;
	USHORT  Height = 900;
	HDC     hDC = nullptr;
	RECT    rc;


	//MessageBox(0, "Testing box", "First Box", MB_OK);
	WNDCLASS			wc;
	wc.style = CS_BYTEALIGNCLIENT | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = StaticWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = (HINSTANCE)GetModuleHandle(nullptr);
	wc.hIcon = ::LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = WindowTitle;
	RegisterClass(&wc);

	m_hWnd = CreateWindowA(WindowTitle, WindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, Width, Height, nullptr, nullptr, wc.hInstance, this);

	if (m_hWnd == 0) return false;

	::GetClientRect(m_hWnd, &rc);
	m_nViewX = rc.left;
	m_nViewY = rc.top;
	m_nViewWidth = rc.right - rc.left;
	m_nViewHeight = rc.bottom - rc.top;

	if (!BuildFrameBuffer(Width, Height)) return false;

	ShowWindow(m_hWnd, SW_SHOW);
	return true;
}
bool CGameApp::BuildFrameBuffer(ULONG Width, ULONG Height)
{
	// Obtain window's HDC.
	HDC hDC = ::GetDC(m_hWnd);

	// Create Frame Buffers Device Context if not already existant
	if (!m_hdcFrameBuffer) m_hdcFrameBuffer = ::CreateCompatibleDC(hDC);

	// If an old FrameBuffer bitmap has already been generated then delete it
	if (m_hbmFrameBuffer)
	{
		// Select the frame buffer back out and destroy it
		::SelectObject(m_hdcFrameBuffer, m_hbmSelectOut);
		::DeleteObject(m_hbmFrameBuffer);
		m_hbmFrameBuffer = nullptr;
		m_hbmSelectOut = nullptr;

	} // End if

	  // Create the frame buffer
	m_hbmFrameBuffer = CreateCompatibleBitmap(hDC, Width, Height);

	if (!m_hbmFrameBuffer) return false;

	// Select this bitmap into our Frame Buffer DC
	m_hbmSelectOut = (HBITMAP)::SelectObject(m_hdcFrameBuffer, m_hbmFrameBuffer);

	// Release windows HDC.
	::ReleaseDC(m_hWnd, hDC);

	// Set up initial DC states
	::SetBkMode(m_hdcFrameBuffer, TRANSPARENT);

	// Success!!
	return true;
}
void CGameApp::FrameAdvance()
{
	ClearFrameBuffer(0x00FFFFFF);


	m_Timer.Tick(60.0f);
	


	Background();	
	Playground();
	

	PresentFrameBuffer();
}
void CGameApp::Background()
{	
	DrawRetangle(m_Rect, RGB(0, 0, 0));
	std::string lpszPlayerScore;
	std::string lpszAIScore;

	lpszPlayerScore = std::to_string(m_Player->m_Score);
	lpszAIScore = std::to_string(m_AI->m_Score);

	//Draw the court
	
	std::string str = m_Timer.GetFrameRate();
	std::string middle = "|";
	DrawToScreen(str, 5, 5, 30, RGB(0,0,0));
	DrawToScreen(lpszPlayerScore, m_Rect.right / 2 - 200, m_Rect.top + 30, 80, RGB(255, 255, 255));
	DrawToScreen(lpszAIScore,	  m_Rect.right / 2 + 150, m_Rect.top + 30, 80, RGB(255, 255,255));

	DrawToScreen(middle, m_Rect.right / 2, m_Rect.top + 30, 80, RGB(255, 255, 255));
	DrawToScreen(middle, m_Rect.right / 2, m_Rect.top + 120, 80, RGB(255, 255, 255));
	DrawToScreen(middle, m_Rect.right / 2, m_Rect.top + 210, 80, RGB(255, 255, 255));
	DrawToScreen(middle, m_Rect.right / 2, m_Rect.top + 300, 80, RGB(255, 255, 255));
	DrawToScreen(middle, m_Rect.right / 2, m_Rect.top + 390, 80, RGB(255, 255, 255));
	DrawToScreen(middle, m_Rect.right / 2, m_Rect.top + 480, 80, RGB(255, 255, 255));
	DrawToScreen(middle, m_Rect.right / 2, m_Rect.top + 570, 80, RGB(255, 255, 255));
	DrawToScreen(middle, m_Rect.right / 2, m_Rect.top + 660, 80, RGB(255, 255, 255));
}
void CGameApp::PresentFrameBuffer()
{
	HDC hDC = nullptr;

	// Retrieve the DC of the window
	hDC = ::GetDC(m_hWnd);

	// Blit the frame buffer to the screen
	::BitBlt(hDC, m_nViewX, m_nViewY, m_nViewWidth, m_nViewHeight, m_hdcFrameBuffer, m_nViewX, m_nViewY, SRCCOPY);

	// Clean up
	::ReleaseDC(m_hWnd, hDC);
}
void CGameApp::Playground()
{

	
	m_Player->Draw(m_hdcFrameBuffer, RGB(0,255,255));
	m_AI->Draw(m_hdcFrameBuffer,RGB(0, 255, 255));
	m_Puck->Draw(m_hdcFrameBuffer, RGB(0, 255, 255));

	GamePlay();
	ProcessInput();
	//DrawPoint(m_Puck.m_Dir, RGB(0, 255, 255));
}
void CGameApp::ProcessInput()
{
	// Simple strafing
	if (GetKeyState(VK_UP) & 0x800 || GetKeyState('W') & 0x800)
	{
		if(m_Rect.top < m_Player->m_Y)
			m_Player->UpdateUp();
	}
		
	if (GetKeyState(VK_DOWN) & 0x800 || GetKeyState('S') & 0x800) 
		if ((m_Rect.bottom - 66) > m_Player->m_Y)
			m_Player->UpdateDown();

}
void CGameApp::ProcessAI()
{
	if(m_Puck->m_Velocity.mX > 0)
	{
		if (m_AI->m_Y+30 != m_Puck->m_Position.mY)
		{
			if (m_AI->m_Y + 30 > m_Puck->m_Position.mY - 40)
				if(m_Rect.top+10 <= m_AI->m_Y)
					m_AI->UpdateUp();

			if (m_AI->m_Y + 30 < m_Puck->m_Position.mY)
				if(m_Rect.bottom -68 >= m_AI->m_Y)
					m_AI->UpdateDown();
		}

	 }
	
}
void CGameApp::GamePlay()
{
	if (m_Player->m_Score >= 10 || m_AI->m_Score >= 10)
	{
		m_Puck->m_Velocity.mX = 0.0f;
		m_Puck->m_Velocity.mY = 0.0f;
		m_Puck->m_Velocity.mZ = 0.0f;
		GameResult();
	}
	else
	{
		if (m_Puck->m_Position.mY <= m_Rect.top || m_Puck->m_Position.mY >= m_Rect.bottom)
			m_Puck->m_Velocity.mY *= -1.0f;
		
		if (m_Puck->m_Position.mX <= m_Rect.left || m_Puck->m_Position.mX >= m_Rect.right)
			m_Puck->m_Velocity.mX *= -1.0f;

		
	}
		if (calmdown == 0)
		{	
			if (m_Player->Collistion(*m_Puck) || m_AI->Collistion(*m_Puck))
			{
				m_Puck->m_Velocity.mX *= -1.0f;
				calmdown = 5;

			}
		}
		else
			calmdown--;	

		ProcessAI();

		if (m_Puck->m_Position.mX >= m_Rect.right)
		{
			m_Player->m_Score++;
			Reset();
		}
			
		if (m_Puck->m_Position.mX <= m_Rect.left)
		{
			m_AI->m_Score++;
			Reset();
		}
			

		//m_Paddle.m_Rect.left + m_X, 
		//m_Paddle.m_Rect.top + m_Y, 
		//m_Paddle.m_Rect.right + m_X,  
		//m_Paddle.m_Rect.bottom + m_Y );

	m_Puck->m_Position += m_Puck->m_Velocity * m_Timer.GetTimeElapsed();

}
void CGameApp::Reset()
{
	m_Puck->m_Position.mX = m_Rect.right / 2;
	m_Puck->m_Position.mY = m_Rect.top + 50;
	m_Puck->m_Position.mZ = 0;

	mSpeedX = 6.0f;
	mSpeedY = 2.0f;
	mSpeedZ = 0.0f;
	m_Puck->m_Speed = 100.0f;

	m_Puck->m_Velocity.mX = mSpeedX * m_Puck->m_Speed;
	m_Puck->m_Velocity.mY = mSpeedY * m_Puck->m_Speed;
	m_Puck->m_Velocity.mZ = mSpeedZ;

}
void CGameApp::GameResult()
{
	std::string lpszPlayerScore;
	std::string lpszAIScore;
	std::string PressP;

	lpszPlayerScore = "Player Wins!!!";
	lpszAIScore = "AI Wins!!!";
	PressP = "Press P for a new game";

	if(m_Player->m_Score > m_AI->m_Score)
		DrawToScreen(lpszPlayerScore, m_Rect.right / 2 -320, m_Rect.bottom/2 -100, 120, RGB(255, 255, 255));
	else
		DrawToScreen(lpszAIScore,     m_Rect.right / 2 -200, m_Rect.bottom/2 - 100, 120, RGB(255, 255, 255));

    DrawToScreen(PressP, m_Rect.right / 2 - 350, m_Rect.bottom/2 + 100, 80, RGB(255, 255, 255));
	if (GetKeyState('P') & 0x800)
	{
		
		Reset();
		m_Player->m_Score = 0;
		m_AI->m_Score = 0;
	}
}
void CGameApp::DrawLine(const CVector3& vtx1, const CVector3& vtx2, ULONG Color)
{
	LOGPEN logPen;
	HPEN   hPen = nullptr, hOldPen = nullptr;


	// Set up the rendering pen
	logPen.lopnStyle = PS_SOLID;
	logPen.lopnWidth.x = 1;
	logPen.lopnWidth.y = 1;


	// Set up the colour, converted to BGR & stripped of alpha
	logPen.lopnColor = 0x00FFFFFF & RGB2BGR(Color);

	// Create the rendering pen
	hPen = ::CreatePenIndirect(&logPen);


	if (!hPen) return;


	// Select into the frame buffer DC
	hOldPen = (HPEN)::SelectObject(m_hdcFrameBuffer, hPen);

	// Draw the line segment
	MoveToEx(m_hdcFrameBuffer, (long)vtx1.mX, (long)vtx1.mY, nullptr);
	LineTo(m_hdcFrameBuffer, (long)vtx2.mX, (long)vtx2.mY);

	// Destroy rendering pen
	::SelectObject(m_hdcFrameBuffer, hOldPen);

	::DeleteObject(hPen);

}
void CGameApp::DrawPoint(const CVector3& vtx1, ULONG Color)
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


	// Destroy rendering pen
	::SelectObject(m_hdcFrameBuffer, hOldPen);
	::SelectObject(m_hdcFrameBuffer, hOldBrush);
	::DeleteObject(hPen);
	::DeleteObject(hBrush);
}
void CGameApp::DrawRetangle(const RECT& rect, ULONG Color)
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
	Rectangle(m_hdcFrameBuffer, rect.left, rect.top, rect.right, rect.bottom);

	// Destroy rendering pen
	::SelectObject(m_hdcFrameBuffer, hOldPen);
	::SelectObject(m_hdcFrameBuffer, hOldBrush);
	::DeleteObject(hPen);
	::DeleteObject(hBrush);
}
void CGameApp::DrawToScreen(std::string& text, int x, int y, int fontSize, int Color)
{
	auto hFont =  CreateFont(fontSize, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,	CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("ARIEL"));
	SelectObject(m_hdcFrameBuffer, hFont);
	SetTextColor(m_hdcFrameBuffer, Color);
	TextOut(m_hdcFrameBuffer, x, y, text.c_str(), text.size());
	::DeleteObject(hFont);
}
void CGameApp::SetupGameState()
{
	m_Player = new Player;
	m_AI = new Player;
	m_Puck = new Puck;

	m_Rect.left = 30;
	m_Rect.top = 30;
	m_Rect.right = 1430;
	m_Rect.bottom = 830;

	m_Player->m_Score = 0;
	m_AI->m_Score = 0;

	m_Player->m_Paddle.m_Speed = 10.0f;
	m_Player->m_X = m_Rect.left + 150;
	m_Player->m_Y = (m_Rect.bottom /2);
	m_Player->m_Paddle.m_Speed = 10.0f;
	m_Player->m_Paddle.m_Rect.left = 0;
	m_Player->m_Paddle.m_Rect.top = 0;
	m_Player->m_Paddle.m_Rect.right = 15;
	m_Player->m_Paddle.m_Rect.bottom = 65;

	m_AI->m_Paddle.m_Speed = 6.5f;
	m_AI->m_X = m_Rect.right - 150;
	m_AI->m_Y = (m_Rect.bottom /2);
	m_AI->m_Paddle.m_Speed = 10.0f;
	m_AI->m_Paddle.m_Rect.left = 0;
	m_AI->m_Paddle.m_Rect.top = 0;
	m_AI->m_Paddle.m_Rect.right = 15;
	m_AI->m_Paddle.m_Rect.bottom = 65;

	m_Puck->m_Position.mX = m_Rect.right / 2;
	m_Puck->m_Position.mY = m_Rect.bottom / 2;
	m_Puck->m_Position.mZ = 0;

	Reset();


	calmdown = 5;

}
void CGameApp::ClearFrameBuffer(ULONG Color)
{
	LOGBRUSH logBrush;
	HBRUSH   hBrush = nullptr, hOldBrush = nullptr;

	// Set up the rendering brush
	logBrush.lbStyle = BS_SOLID;

	// Set up the colour, converted to BGR & stripped of alpha
	logBrush.lbColor = 0x00FFFFFF & RGB2BGR(Color);

	// Create the rendering brush
	hBrush = ::CreateBrushIndirect(&logBrush);
	if (!hBrush) return;

	// Select into the frame buffer DC
	hOldBrush = (HBRUSH)::SelectObject(m_hdcFrameBuffer, hBrush);

	// Draw the rectangle
	Rectangle(m_hdcFrameBuffer, m_nViewX, m_nViewY, m_nViewWidth, m_nViewHeight);

	// Destroy rendering brush
	::SelectObject(m_hdcFrameBuffer, hOldBrush);
	::DeleteObject(hBrush);
}
int CGameApp::GameLoop()
{
	MSG		msg;

	// Start main loop
	while (1)
	{
		// Did we recieve a message, or are we idling ?
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Advance Game Frame.
			FrameAdvance();

		} // End If messages waiting

	} // Until quit message is receieved

	return 0;
}
LRESULT CGameApp::StaticWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	// NOTE: Added 64bit compatibility casts using 'LONG_PTR' to prevent compatibility warnings

	//    The call to SetWindowLongPtr here may generate a warning when
	//    the compiler has been instructed to inform us of 64-bit
	//    portability issues.
	//
	//        warning C4244: 'argument' :
	//          conversion from 'LONG_PTR' to 'LONG', possible loss of data
	//
	//    It is safe to ignore this warning because it is bogus per MSDN Magazine.
	//
	//        http://msdn.microsoft.com/msdnmag/issues/01/08/bugslayer/ 

	// If this is a create message, trap the 'this' pointer passed in and store it within the window.
#pragma warning (push)
#pragma warning (disable : 4244) // inhibit ignorable warning
	if (Message == WM_CREATE) SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)((CREATESTRUCT FAR*)lParam)->lpCreateParams);
#pragma warning (pop)

	// Obtain the correct destination for this message
	CGameApp* Destination = (CGameApp*)((LONG_PTR)GetWindowLongPtr(hWnd, GWL_USERDATA));

	// If the hWnd has a related class, pass it through
	if (Destination) return Destination->DisplayWndProc(hWnd, Message, wParam, lParam);

	// No destination found, defer to system...
	return DefWindowProc(hWnd, Message, wParam, lParam);
}

