#include "CGameApp.h"
#include "resource.h"
#include <string>

/*
Exercises
The current demo does not allow the camera to be moved and the view matrix is left as an identity
matrix. In this exercise, try adding user input to the demo so that the user can strafe the camera left or
right in response to the left and right cursor keys being pressed.
Tips:
a) You will need to add key handlers in the DisplayWndProc function .

b) You can set the view matrix to an identity matrix at application start up as we have done
in our code, but you will need to modify the view matrix in response to the left or right
keys being pressed. It is the translation information (the last row) of the view matrix that
will have to be updated.

c) In order to strafe the camera, you will need to move the camera along its RIGHT
VECTOR. Refer back to the diagram of the view matrix to see how to extract the right
vector. (hint: look at column 1)

d) Remember that multiplying the right vector with a negative distance value will move the
camera left.

e) Remember to store the newly translated vector back into the translation row of the view
matrix before rendering the scene.
*/

CGameApp::CGameApp()
{
	m_hWnd = nullptr;
	m_hdcFrameBuffer = nullptr;
	m_hbmSelectOut = nullptr;
	m_hbmFrameBuffer = nullptr;
}


CGameApp::~CGameApp()
{
	ShutDown();
}

LRESULT CGameApp::DisplayWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	float fAspect;

	// Determine message type
	switch (Message)
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
		fAspect = (float)m_nViewWidth / (float)m_nViewHeight;
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(60.0f), fAspect, 1.01f, 1000.0f);

		// Rebuild the new frame buffer
		BuildFrameBuffer(m_nViewWidth, m_nViewHeight);

		break;

	case WM_KEYDOWN:

		// Which key was pressed?
		switch (wParam)
		{
		case 'A':
			m_nObject -= 1.0f; // X Position of render viewport

			break;
		case 'D':
			m_nObject += 1.0f; // X Position of render viewport
			break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;

		} // End Switch

		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case 'A':
		case 'D':
			m_nObject = 0.0f; // X Position of render viewport
			break;
		}
	case WM_COMMAND:

		// Process Menu Items
		switch (LOWORD(wParam))
		{
		case ID_OBJECT01_ROTATION:
			// Disable / enable rotation
			m_bRotation1 = !m_bRotation1;
			::CheckMenuItem(::GetMenu(m_hWnd), ID_OBJECT01_ROTATION,
				MF_BYCOMMAND | (m_bRotation1) ? MF_CHECKED : MF_UNCHECKED);
			break;

		case ID_OBJECT02_ROTATION:
			// Disable / enable rotation
			m_bRotation2 = !m_bRotation2;
			::CheckMenuItem(::GetMenu(m_hWnd), ID_OBJECT02_ROTATION,
				MF_BYCOMMAND | (m_bRotation2) ? MF_CHECKED : MF_UNCHECKED);
			break;

		case ID_FILE_EXIT:
			// Recieved key/menu command to exit app
			SendMessage(m_hWnd, WM_CLOSE, 0, 0);
			return 0;

		} // End Switch

	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);

	} // End Message Switch

	return 0;
}

bool CGameApp::InitInstance(HANDLE hInstance, LPCTSTR lpCmdLine, int iCmdShow)
{
	// Create the primary display device
	if (!CreateDisplay())
	{
		ShutDown();
		return false;
	}

	// Build Objects
	if (!BuildObjects())
	{
		ShutDown();
		return false;
	}

	// Set up all required game states
	SetupGameState();

	// Success!
	return true;
}

int CGameApp::BeginGame()
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

bool CGameApp::ShutDown()
{
	if (m_hdcFrameBuffer && m_hbmFrameBuffer)
	{
		::SelectObject(m_hdcFrameBuffer, m_hbmSelectOut);
		::DeleteObject(m_hbmFrameBuffer);
		::DeleteDC(m_hdcFrameBuffer);

	} // End if

	  // Destroy the render window
	if (m_hWnd) DestroyWindow(m_hWnd);

	// Clear all variables
	m_hWnd = nullptr;
	m_hdcFrameBuffer = nullptr;
	m_hbmFrameBuffer = nullptr;

	// Shutdown Success
	return true;
}

bool CGameApp::BuildObjects()
{
	CPolygon * pPoly = nullptr;

	// Add 6 polygons to this mesh.
	if (m_Mesh.AddPolygon(6) < 0) return false;

	// Front Face
	pPoly = m_Mesh.m_pPolygon[0];
	if (pPoly->AddVertex(4) < 0) return false;

	pPoly->m_pVertex[0] = CVertex(-2,  2, -2);
	pPoly->m_pVertex[1] = CVertex( 2,  2, -2);
	pPoly->m_pVertex[2] = CVertex( 2, -2, -2);
	pPoly->m_pVertex[3] = CVertex(-2, -2, -2);

	// Top Face
	pPoly = m_Mesh.m_pPolygon[1];
	if (pPoly->AddVertex(4) < 0) return false;

	pPoly->m_pVertex[0] = CVertex(-2, 2,  2);
	pPoly->m_pVertex[1] = CVertex( 2, 2,  2);
	pPoly->m_pVertex[2] = CVertex( 2, 2, -2);
	pPoly->m_pVertex[3] = CVertex(-2, 2, -2);

	// Back Face
	pPoly = m_Mesh.m_pPolygon[2];
	if (pPoly->AddVertex(4) < 0) return false;

	pPoly->m_pVertex[0] = CVertex(-2, -2, 2);
	pPoly->m_pVertex[1] = CVertex( 2, -2, 2);
	pPoly->m_pVertex[2] = CVertex( 2,  2, 2);
	pPoly->m_pVertex[3] = CVertex(-2,  2, 2),

	// Bottom Face
	pPoly = m_Mesh.m_pPolygon[3];
	if (pPoly->AddVertex(4) < 0) return false;

	pPoly->m_pVertex[0] = CVertex(-2, -2, -2);
	pPoly->m_pVertex[1] = CVertex( 2, -2, -2);
	pPoly->m_pVertex[2] = CVertex( 2, -2,  2);
	pPoly->m_pVertex[3] = CVertex(-2, -2,  2);

	// Left Face
	pPoly = m_Mesh.m_pPolygon[4];
	if (pPoly->AddVertex(4) < 0) return false;

	pPoly->m_pVertex[0] = CVertex(-2,  2,  2);
	pPoly->m_pVertex[1] = CVertex(-2,  2, -2);
	pPoly->m_pVertex[2] = CVertex(-2, -2, -2);
	pPoly->m_pVertex[3] = CVertex(-2, -2,  2);

	// Right Face
	pPoly = m_Mesh.m_pPolygon[5];
	if (pPoly->AddVertex(4) < 0) return false;

	pPoly->m_pVertex[0] = CVertex(2, 2, -2);
	pPoly->m_pVertex[1] = CVertex(2, 2,  2);
	pPoly->m_pVertex[2] = CVertex(2,-2,  2);
	pPoly->m_pVertex[3] = CVertex(2,-2, -2);

	// Our two objects should reference this mesh
	m_pObject[0].m_pMesh = &m_Mesh;
	m_pObject[1].m_pMesh = &m_Mesh;

	// Set both objects matrices so that they are offset slightly
	D3DXMatrixTranslation(&m_pObject[0].m_mtxWorld, -3.5, 2.0f, 14.0f);
	D3DXMatrixTranslation(&m_pObject[1].m_mtxWorld, 3.5, -2.0f, 14.0f);

	// Success!
	return true;
}

void CGameApp::FrameAdvance()
{
	CMesh      *pMesh = nullptr;
	TCHAR       lpszFPS[30];


	// Advance the timer
	m_Timer.Tick(60.0f);

	// Animate the two objects
	AnimateObjects();

	// Clear the frame buffer ready for drawing
	ClearFrameBuffer(0x00FFFFFF);
	if(m_nObject)	D3DXMatrixTranslation(&m_mtxView, m_mtxView._41 + m_nObject, m_mtxView._42, m_mtxView._43);

	
	//char buffer[4];
	//snprintf(buffer, sizeof(buffer), "%f\n", m_nObject);
	//OutputDebugStringA(buffer);

	// Loop through each object
	for (ULONG i = 0; i < 2; i++)
	{
		// Store mesh for easy access
		pMesh = m_pObject[i].m_pMesh;

		// Loop through each polygon
		for (ULONG f = 0; f < pMesh->m_nPolygonCount; f++)
		{
			// Render the primitive
			DrawPrimitive(pMesh->m_pPolygon[f], &m_pObject[i].m_mtxWorld);

		} // Next Polygon

	} // Next Object

	  // Display Frame Rate
	m_Timer.GetFrameRate(lpszFPS);
	TextOut(m_hdcFrameBuffer, 5, 5, lpszFPS, (int)strlen(lpszFPS));

	// Present the buffer
	PresentFrameBuffer();
}

bool CGameApp::CreateDisplay()
{
	LPTSTR  WindowTitle = (LPTSTR)"Software Render";
	USHORT  Width = 800;
	USHORT  Height = 600;
	HDC     hDC = nullptr;
	RECT    rc;
	m_nObject = 0.0f;

	// Register the new windows window class.
	WNDCLASS			wc;
	wc.style = CS_BYTEALIGNCLIENT | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = StaticWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = (HINSTANCE)GetModuleHandle(nullptr);
	wc.hIcon = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_ICON));
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = WindowTitle;
	RegisterClass(&wc);

	// Create the rendering window
	m_hWnd = CreateWindowA(WindowTitle, WindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, Width, Height, nullptr, LoadMenu(wc.hInstance, MAKEINTRESOURCE(IDR_MENU)),
		wc.hInstance, this);

	// Bail on error
	if (!m_hWnd) return false;

	// Retrieve the final client size of the window
	::GetClientRect(m_hWnd, &rc);
	m_nViewX = rc.left;
	m_nViewY = rc.top;
	m_nViewWidth = rc.right - rc.left;
	m_nViewHeight = rc.bottom - rc.top;

	// Build the frame buffer
	if (!BuildFrameBuffer(Width, Height)) return false;

	// Show the window
	ShowWindow(m_hWnd, SW_SHOW);

	// Success!
	return true;
}

void CGameApp::SetupGameState()
{
	float      fAspect;
	
	// Setup Default Matrix Values
	D3DXMatrixIdentity(&m_mtxView);

	// Generate our screen aspect ratio
	fAspect = (float)m_nViewWidth / (float)m_nViewHeight;

	// Set up a perspective projection matrix
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(60.0f), fAspect, 1.01f, 1000.0f);

	// Enable rotation
	m_bRotation1 = true;
	m_bRotation2 = true;
}

void CGameApp::AnimateObjects()
{
	D3DXMATRIX mtxYaw, mtxPitch, mtxRoll, mtxRotate;
	float RotationYaw, RotationPitch, RotationRoll;

	// Rotate Object 1 by small amount
	if (m_bRotation1)
	{
		// Calculate rotation values for object 0
		RotationYaw = D3DXToRadian(75.0f * m_Timer.GetTimeElapsed());
		RotationPitch = D3DXToRadian(50.0f * m_Timer.GetTimeElapsed());
		RotationRoll = D3DXToRadian(25.0f * m_Timer.GetTimeElapsed());

		// Build rotation matrices 
		D3DXMatrixIdentity(&mtxRotate);
		D3DXMatrixRotationY(&mtxYaw, RotationYaw);
		D3DXMatrixRotationX(&mtxPitch, RotationPitch);
		D3DXMatrixRotationZ(&mtxRoll, RotationRoll);

		// Concatenate the rotation matrices
		D3DXMatrixMultiply(&mtxRotate, &mtxRotate, &mtxYaw);
		D3DXMatrixMultiply(&mtxRotate, &mtxRotate, &mtxPitch);
		D3DXMatrixMultiply(&mtxRotate, &mtxRotate, &mtxRoll);

		// Apply the rotation to our object's matrix
		D3DXMatrixMultiply(&m_pObject[0].m_mtxWorld, &mtxRotate, &m_pObject[0].m_mtxWorld);

	} // End if Rotation Enabled

	  // Rotate Object 2 by small amount
	if (m_bRotation2)
	{
		// Calculate rotation values for object 1
		RotationYaw = D3DXToRadian(-25.0f * m_Timer.GetTimeElapsed());
		RotationPitch = D3DXToRadian(50.0f * m_Timer.GetTimeElapsed());
		RotationRoll = D3DXToRadian(-75.0f * m_Timer.GetTimeElapsed());

		// Build rotation matrices 
		D3DXMatrixIdentity(&mtxRotate);
		D3DXMatrixRotationY(&mtxYaw, RotationYaw);
		D3DXMatrixRotationX(&mtxPitch, RotationPitch);
		D3DXMatrixRotationZ(&mtxRoll, RotationRoll);

		// Concatenate the rotation matrices
		D3DXMatrixMultiply(&mtxRotate, &mtxRotate, &mtxYaw);
		D3DXMatrixMultiply(&mtxRotate, &mtxRotate, &mtxPitch);
		D3DXMatrixMultiply(&mtxRotate, &mtxRotate, &mtxRoll);

		// Apply the rotation to our object's matrix
		D3DXMatrixMultiply(&m_pObject[1].m_mtxWorld, &mtxRotate, &m_pObject[1].m_mtxWorld);

	} // End if rotation enabled
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

void CGameApp::DrawPrimitive(CPolygon * pPoly, D3DXMATRIX *pmtxWorld)
{
	D3DXVECTOR3 vtxPrevious, vtxCurrent;

	// Loop round each vertex transforming as we go
	for (USHORT v = 0; v < pPoly->m_nVertexCount + 1; v++)
	{
		// Store the current vertex
		vtxCurrent = (D3DXVECTOR3&)pPoly->m_pVertex[v % pPoly->m_nVertexCount];

		// Multiply the vertex position by the World / object matrix
		D3DXVec3TransformCoord(&vtxCurrent, &vtxCurrent, pmtxWorld);

		// Multiply by View matrix
		D3DXVec3TransformCoord(&vtxCurrent, &vtxCurrent, &m_mtxView);

		// Multiply by Projection matrix
		D3DXVec3TransformCoord(&vtxCurrent, &vtxCurrent, &m_mtxProjection);

		// Convert to screen space coordinates
		vtxCurrent.x = vtxCurrent.x * m_nViewWidth / 2 + m_nViewX + m_nViewWidth / 2;
		vtxCurrent.y = -vtxCurrent.y * m_nViewHeight / 2 + m_nViewY + m_nViewHeight / 2;

		// If this is the first vertex, continue. This is the first point of our first line.
		if (v == 0) { vtxPrevious = vtxCurrent; continue; }

	
		// Draw the line
		DrawLine(vtxPrevious, vtxCurrent, 0);

		// Store this as new line's first point
		vtxPrevious = vtxCurrent;

	}
}

void CGameApp::DrawLine(const D3DXVECTOR3 & vtx1, const D3DXVECTOR3 & vtx2, ULONG Color)
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
	MoveToEx(m_hdcFrameBuffer, (long)vtx1.x, (long)vtx1.y, nullptr);
	LineTo(m_hdcFrameBuffer, (long)vtx2.x, (long)vtx2.y);

	// Destroy rendering pen
	::SelectObject(m_hdcFrameBuffer, hOldPen);
	::DeleteObject(hPen);
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
	if (Message == WM_CREATE) SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)((CREATESTRUCT FAR *)lParam)->lpCreateParams);
#pragma warning (pop)

	// Obtain the correct destination for this message
	CGameApp *Destination = (CGameApp*)((LONG_PTR)GetWindowLongPtr(hWnd, GWL_USERDATA));

	// If the hWnd has a related class, pass it through
	if (Destination) return Destination->DisplayWndProc(hWnd, Message, wParam, lParam);

	// No destination found, defer to system...
	return DefWindowProc(hWnd, Message, wParam, lParam);
}
