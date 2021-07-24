#include "CGameApp.h"

CGameApp::CGameApp()
{
	m_hWnd = NULL;
	m_hdcFrameBuffer = NULL;
	m_hbmSelectOut = NULL;
	m_hbmFrameBuffer = NULL;
}
CGameApp::~CGameApp()
{
	ShutDown();
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
bool CGameApp::InitInstance(HANDLE hInstance, LPCTSTR lpCmdLine, int iCmdShow)
{
	if (!CreateDisplay())
	{
        ShutDown();
        return false;
	}
    
    if(!BuildObjects())
    {
        ShutDown();
        return false;
    }
    
    SetupGameState();
    
    return true;
    
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
        
        case WM_COMMAND:
        switch(LOWORD(wParam))
        {
            case ID_FILE_EXIT:
            SendMessage(m_hWnd, WM_CLOSE, 0, 0);
            return 0;
            
        }
        
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
        
        default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
        
	} // End Message Switch
    
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
	if (Message == WM_CREATE) SetWindowLongPtr(hWnd, -21, (LONG_PTR)((CREATESTRUCT FAR*)lParam)->lpCreateParams);
#pragma warning (pop)
    
	// Obtain the correct destination for this message
	CGameApp* Destination = (CGameApp*)((LONG_PTR)GetWindowLongPtr(hWnd, -21));
    
	// If the hWnd has a related class, pass it through
	if (Destination) return Destination->DisplayWndProc(hWnd, Message, wParam, lParam);
    
	// No destination found, defer to system...
	return DefWindowProc(hWnd, Message, wParam, lParam);
}
bool CGameApp::BuildFrameBuffer(ULONG Width, ULONG Height)
{
	HDC hDC = ::GetDC(m_hWnd);
	if (!m_hdcFrameBuffer) m_hdcFrameBuffer = ::CreateCompatibleDC(hDC);
    
	if (m_hbmFrameBuffer)
	{
		::SelectObject(m_hdcFrameBuffer, m_hbmSelectOut);
		::DeleteObject(m_hbmFrameBuffer);
        
		m_hbmFrameBuffer = NULL;
		m_hbmSelectOut = NULL;
	}
    
	m_hbmFrameBuffer = CreateCompatibleBitmap(hDC, Width, Height);
	
	if (!m_hbmFrameBuffer) return false;
    
	m_hbmSelectOut = (HBITMAP)::SelectObject(m_hdcFrameBuffer, m_hbmFrameBuffer);
    
	::ReleaseDC(m_hWnd, hDC);
    
	::SetBkMode(m_hdcFrameBuffer, TRANSPARENT);
    
	return true;
}
bool CGameApp::CreateDisplay()
{
	LPTSTR WindowsTitle = (LPTSTR)"Software Render";
	USHORT Width = 800;
	USHORT Height = 600;
	HDC hDC = NULL;
	RECT rc;
	m_nObject = 0.0f;
    
	WNDCLASS wc;
	wc.style = CS_BYTEALIGNCLIENT | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = StaticWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = (HINSTANCE)GetModuleHandle(nullptr);
	wc.hIcon = (HICON)LoadImage(NULL, "directx.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = WindowsTitle;
	RegisterClass(&wc);
    
    static HMENU hMenu;
    static HMENU hMenuPopup;
    
    
    hMenu = CreateMenu();
    hMenuPopup = CreateMenu();
    
    //AppendMenu (hMenuPopup, MF_SEPARATOR, 0, NULL);
    AppendMenu (hMenuPopup, MF_STRING, ID_FILE_EXIT, TEXT("&Exit"));
    
    AppendMenu (hMenu, MF_POPUP, (UINT_PTR)hMenuPopup, "&File" );
    
    // Create the rendering window
    m_hWnd = CreateWindowA(WindowsTitle, WindowsTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, Width, Height, NULL, hMenu, wc.hInstance, this);
    
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
    
    
    if(m_Mesh2.AddPolygon(4) < 0) return false;
    
    // Front Face
    pPoly =  m_Mesh2.m_pPolygon[0];
    if(pPoly->AddVertex(3) < 0) return false;
    
    pPoly->m_pVertex[0] = CVertex( 0, 2, 0);
    pPoly->m_pVertex[1] = CVertex( 2,-2,-2);
    pPoly->m_pVertex[2] = CVertex(-2,-2,-2);
    
    // Left Face
    pPoly = m_Mesh2.m_pPolygon[1];
    if(pPoly->AddVertex(3) < 0) return false;
    
    pPoly->m_pVertex[0] = CVertex( 0, 2, 0);
    pPoly->m_pVertex[1] = CVertex(-2,-2,-2);
    pPoly->m_pVertex[2] = CVertex( 0,-2, 2);
    
    // Right Face
    pPoly = m_Mesh2.m_pPolygon[2];
    if(pPoly->AddVertex(3) < 0) return false;
    
    pPoly->m_pVertex[0] = CVertex( 0, 2, 0);
    pPoly->m_pVertex[1] = CVertex( 0,-2, 2);
    pPoly->m_pVertex[2] = CVertex( 2,-2,-2);
    
    // Bottom Face
    pPoly = m_Mesh2.m_pPolygon[3];
    if(pPoly->AddVertex(3) < 0) return false;
    
    pPoly->m_pVertex[0] = CVertex( 2,-2,-2);
    pPoly->m_pVertex[1] = CVertex(-2,-2,-2);
    pPoly->m_pVertex[2] = CVertex( 0,-2, 2);
    
    m_pObject[1].m_pMesh = &m_Mesh2;
    
    D3DXMatrixTranslation(&m_pObject[0].m_mtxWorld,-3.5, 2.0f, 14.0f);
    D3DXMatrixTranslation(&m_pObject[1].m_mtxWorld, 3.5,-2.0f, 14.0f);
    
    return true;
}
void CGameApp::SetupGameState()
{
    float fAspect;
    
    D3DXMatrixIdentity(&m_mtxView);
    
    fAspect = (float)m_nViewWidth / (float)m_nViewHeight;
    
    D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(60.0f), fAspect, 1.01f, 1000.0f);
    m_bRotation1 = true;
    m_bRotation2 = true;
}
int CGameApp::BeginGame()
{
    MSG msg;
    
    while(1)
    {
        if(PeekMessage(&msg, NULL, 0,0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            FrameAdvance();
        }
    }
    
    return 0;
}
void CGameApp::FrameAdvance()
{
    CMesh * pMesh = nullptr;
    TCHAR lpszFPS[30];
    
    m_Timer.Tick(60.0f);
    
    
    AnimateObjects();
    
    ClearFrameBuffer(0x00FFFFFF);
    
    ProccessInput();
    
    if(m_nObject)	D3DXMatrixTranslation(&m_mtxView, m_mtxView._41 + m_nObject, m_mtxView._42, m_mtxView._43);
    for(ULONG i = 0; i < 2; i++)
    {
        pMesh = m_pObject[i].m_pMesh;
        
        for(ULONG f = 0; f < pMesh->m_nPolygonCount; f++)
        {
            DrawPrimitive(pMesh->m_pPolygon[f], &m_pObject[i].m_mtxWorld);
        }
    }
    m_Timer.GetFrameRate(lpszFPS);
    TextOut(m_hdcFrameBuffer, 5, 5, lpszFPS, (int)strlen(lpszFPS));
    
    PresentFrameBuffer();
    
}
void CGameApp::AnimateObjects()
{
    D3DXMATRIX mtxYaw, mtxPitch, mtxRoll, mtxRotate;
    float RotationYaw, RotationPitch, RotationRoll;
    
    if(m_bRotation1)
    {
        RotationYaw   = D3DXToRadian(75.0f * m_Timer.GetTimeElapsed());
        RotationPitch = D3DXToRadian(50.0f * m_Timer.GetTimeElapsed());
        RotationRoll  = D3DXToRadian(25.0f  * m_Timer.GetTimeElapsed());
        
        D3DXMatrixIdentity(&mtxRotate);
        D3DXMatrixRotationY(&mtxYaw, RotationYaw);
        D3DXMatrixRotationX(&mtxPitch, RotationPitch);
        D3DXMatrixRotationZ(&mtxRoll, RotationRoll);
        
        D3DXMatrixMultiply(&mtxRotate, &mtxRotate, &mtxYaw);
        D3DXMatrixMultiply(&mtxRotate, &mtxRotate, &mtxPitch);
        D3DXMatrixMultiply(&mtxRotate, &mtxRotate, &mtxRoll);
        
        D3DXMatrixMultiply(&m_pObject[0].m_mtxWorld, &mtxRotate, &m_pObject[0].m_mtxWorld);
        
    }
    if(m_bRotation2)
    {
        RotationYaw   = D3DXToRadian(75.0f * m_Timer.GetTimeElapsed());
        RotationPitch = D3DXToRadian(50.0f * m_Timer.GetTimeElapsed());
        RotationRoll  = D3DXToRadian(25.0f  * m_Timer.GetTimeElapsed());
        
        D3DXMatrixIdentity(&mtxRotate);
        D3DXMatrixRotationY(&mtxYaw, RotationYaw);
        D3DXMatrixRotationX(&mtxPitch, RotationPitch);
        D3DXMatrixRotationZ(&mtxRoll, RotationRoll);
        
        D3DXMatrixMultiply(&mtxRotate, &mtxRotate, &mtxYaw);
        D3DXMatrixMultiply(&mtxRotate, &mtxRotate, &mtxPitch);
        D3DXMatrixMultiply(&mtxRotate, &mtxRotate, &mtxRoll);
        
        D3DXMatrixMultiply(&m_pObject[1].m_mtxWorld, &mtxRotate, &m_pObject[1].m_mtxWorld);
        
    }
}
void CGameApp::ClearFrameBuffer(ULONG Color)
{
    LOGBRUSH logBrush;
    HBRUSH hBrush = NULL, hOldBrush = NULL;
    
    logBrush.lbStyle = BS_SOLID;
    
    logBrush.lbColor = 0x00FFFFFF & RGB2BGR(Color);
    
    hBrush = ::CreateBrushIndirect(&logBrush);
    if(!hBrush) return;
    
    hOldBrush = (HBRUSH)::SelectObject(m_hdcFrameBuffer, hBrush);
    
    Rectangle(m_hdcFrameBuffer, m_nViewX, m_nViewY, m_nViewWidth, m_nViewHeight);
    
    ::SelectObject(m_hdcFrameBuffer, hOldBrush);
    ::DeleteObject(hBrush);
}
void CGameApp::ProccessInput()
{
    if (GetKeyState(VK_LEFT) & 0xFF00||GetKeyState(65) & 0xFF00) m_mtxView._41 += 25.0f * m_Timer.GetTimeElapsed();
    if (GetKeyState(VK_RIGHT) & 0xFF00||GetKeyState(68) & 0xFF00) m_mtxView._41 -= 25.0f * m_Timer.GetTimeElapsed();
    if (GetKeyState(49) & 0xFF00) m_bRotation1 = !m_bRotation1;
    if (GetKeyState(50) & 0xFF00) m_bRotation2 = !m_bRotation2;
    
    
}
void CGameApp::PresentFrameBuffer()
{
    HDC hDC = NULL;
    hDC = ::GetDC(m_hWnd);
    ::BitBlt(hDC, m_nViewX, m_nViewY, m_nViewWidth, m_nViewHeight, m_hdcFrameBuffer, m_nViewX, m_nViewY, SRCCOPY);
    ::ReleaseDC(m_hWnd, hDC);
    
}
void CGameApp::DrawPrimitive(CPolygon * pPoly, D3DXMATRIX * pmtxWorld)
{
    D3DXVECTOR3 vtxPrevious, vtxCurrent;
    
    for(USHORT v = 0; v < pPoly->m_nVertexCount + 1; v++)
    {
        
        vtxCurrent = (D3DXVECTOR3&)pPoly->m_pVertex[v % pPoly->m_nVertexCount];
        
        D3DXVec3TransformCoord(&vtxCurrent, &vtxCurrent, pmtxWorld);
        D3DXVec3TransformCoord(&vtxCurrent, &vtxCurrent, &m_mtxView);
        D3DXVec3TransformCoord(&vtxCurrent, &vtxCurrent, &m_mtxProjection);
        
        vtxCurrent.x = vtxCurrent.x * m_nViewWidth / 2 + m_nViewX + m_nViewWidth / 2;
        vtxCurrent.y = -vtxCurrent.y * m_nViewHeight / 2 + m_nViewY + m_nViewHeight / 2;
        if(v == 0) 
        {
            vtxPrevious = vtxCurrent;
            continue;
        }
        
        DrawLine(vtxPrevious, vtxCurrent, 0);
        
        vtxPrevious = vtxCurrent;
    }
}
void CGameApp::DrawLine(const D3DXVECTOR3 & vtx1, const D3DXVECTOR3 & vtx2, ULONG Color)
{
    LOGPEN logPen;
    HPEN hPen = NULL, hOldPen = NULL;
    
    logPen.lopnStyle = PS_SOLID;
    logPen.lopnWidth.x = 1;
    logPen.lopnWidth.y = 1;
    
    logPen.lopnColor = 0x00FFFFFF & RGB2BGR(Color);
    
    hPen = ::CreatePenIndirect(&logPen);
    if (!hPen) return;
    
    hOldPen = (HPEN)::SelectObject(m_hdcFrameBuffer, hPen);
    
    MoveToEx(m_hdcFrameBuffer, (long)vtx1.x, (long)vtx1.y, nullptr);
    LineTo(m_hdcFrameBuffer,   (long)vtx2.x, (long)vtx2.y);
    
    ::SelectObject(m_hdcFrameBuffer, hOldPen);
    ::DeleteObject(hPen);
}