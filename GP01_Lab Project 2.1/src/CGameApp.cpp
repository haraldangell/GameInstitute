#include "CGameApp.h"



CGameApp::CGameApp()
{
    m_hWnd = NULL;
    m_pD3D = NULL;
    m_pD3DDevice = NULL;
    m_bLostDevice = false;
    
}

CGameApp::~CGameApp()
{
    ShutDown();
}

bool CGameApp::InitInstance(HANDLE hInstance, LPCSTR lpCmdLine, int iCmdShow)
{
	if (!CreateDisplay()) { ShutDown(); return false; }
    
	if (!BuildObjects()) { ShutDown(); return false; }
    
	SetupGameState();
    
	SetupRenderStates();
    
	return true;
}

bool CGameApp::CreateDisplay()
{
	LPTSTR WindowsTitle = (LPTSTR)"Software Render";
	USHORT Width = 800;
	USHORT Height = 600;
	HDC hDC = NULL;
	RECT rc;
    
    
	WNDCLASS wc;
	wc.style = CS_BYTEALIGNCLIENT | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = StaticWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = (HINSTANCE)GetModuleHandle(nullptr);
	wc.hIcon = (HICON)LoadImage(NULL, "icon1.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
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
    
    
    // Show the window
    ShowWindow(m_hWnd, SW_SHOW);
    
    if(!InitDirect3D()) return false;
    
    // Success!
    return true;
}

bool CGameApp::InitDirect3D()
{
	HRESULT               hRet;
	D3DPRESENT_PARAMETERS PresentParams;
	D3DCAPS9              Caps;
	D3DDISPLAYMODE        CurrentMode;
    
	// First of all create our D3D Object
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_pD3D)
	{
		MessageBox(m_hWnd, _T("No compatible Direct3D object could be created."), _T("Fatal Error!"), MB_OK | MB_ICONSTOP | MB_APPLMODAL);
		return false;
        
	} // End if failure
    
    // Fill out a simple set of present parameters
	ZeroMemory(&PresentParams, sizeof(D3DPRESENT_PARAMETERS));
    
	// Select back buffer format etc
	m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &CurrentMode);
	PresentParams.BackBufferFormat = CurrentMode.Format;
    
	// Setup remaining flags
	PresentParams.AutoDepthStencilFormat = FindDepthStencilFormat(D3DADAPTER_DEFAULT, CurrentMode, D3DDEVTYPE_HAL);
	PresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	PresentParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	PresentParams.Windowed = true;
	PresentParams.EnableAutoDepthStencil = true;
    
	// Set Creation Flags
	unsigned long ulFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
    
	// Check if Hardware T&L is available
	ZeroMemory(&Caps, sizeof(D3DCAPS9));
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &Caps);
	if (Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) ulFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
    
	// Attempt to create a HAL device
	if (FAILED(hRet = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, ulFlags, &PresentParams, &m_pD3DDevice)))
	{
		MessageBox(m_hWnd, _T("Could not create a valid HAL Direct3D device object.\r\n\r\n")
                   _T("The system will now attempt to create a device utilising the 'Reference Rasterizer' (D3DDEVTYPE_REF)"),
                   _T("Fatal Error!"), MB_OK | MB_ICONINFORMATION | MB_APPLMODAL);
        
		// Find REF depth buffer format
		PresentParams.AutoDepthStencilFormat = FindDepthStencilFormat(D3DADAPTER_DEFAULT, CurrentMode, D3DDEVTYPE_REF);
        
		// Check if Hardware T&L is available
		ZeroMemory(&Caps, sizeof(D3DCAPS9));
		ulFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, &Caps);
		if (Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) ulFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
        
		// Attempt to create a REF device
		if (FAILED(hRet = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, m_hWnd, ulFlags, &PresentParams, &m_pD3DDevice)))
		{
			MessageBox(m_hWnd, _T("Could not create a valid REF Direct3D device object.\r\n\r\nThe system will now exit."),
                       _T("Fatal Error!"), MB_OK | MB_ICONSTOP | MB_APPLMODAL);
            
			// Failed
			return false;
            
		} // End if Failure (REF)
        
	} // End if Failure (HAL)
    
    // Store the present parameters
	m_D3DPresentParams = PresentParams;
    
	// Success!!
	return true;
    
}
D3DFORMAT CGameApp::FindDepthStencilFormat(ULONG AdapterOrdinal, D3DDISPLAYMODE Mode, D3DDEVTYPE DevType)
{
    if(!SUCCEEDED(m_pD3D->CheckDeviceFormat(AdapterOrdinal, DevType, Mode.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D32)))
    {
        if(SUCCEEDED(m_pD3D->CheckDepthStencilMatch(AdapterOrdinal, DevType, Mode.Format, Mode.Format, D3DFMT_D32))) return D3DFMT_D32;
    }
    if(SUCCEEDED(m_pD3D->CheckDeviceFormat(AdapterOrdinal, DevType, Mode.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24X8))) 
    {
        if(SUCCEEDED(m_pD3D->CheckDepthStencilMatch(AdapterOrdinal, DevType, Mode.Format, Mode.Format, D3DFMT_D24X8))) return D3DFMT_D24X8;
    }
    if(SUCCEEDED(m_pD3D->CheckDeviceFormat(AdapterOrdinal, DevType, Mode.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D16)))
    {
        if(SUCCEEDED(m_pD3D->CheckDepthStencilMatch(AdapterOrdinal, DevType, Mode.Format, Mode.Format, D3DFMT_D16))) return D3DFMT_D16;
    }
    
    return D3DFMT_UNKNOWN;
}

void CGameApp::SetupGameState()
{
    D3DXMatrixIdentity(&m_mtxView);
    
    m_bRotation1 = true;
    m_bRotation2 = true;
    
    m_bActive = true;
}

void CGameApp::SetupRenderStates()
{
	float fAspect = (float)m_nViewWidth / (float)m_nViewHeight;
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(60.0f), fAspect, 1.01f, 1000.0f);
    
	// Setup our D3D Device initial states
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_DITHERENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    
	// Setup our vertex FVF code
	m_pD3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
    
	// Setup our matrices
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

int CGameApp::BeginGame()
{
    MSG msg;
    
    while(1)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
			FrameAdvance();
    }
    return 0;
}

bool CGameApp::ShutDown()
{
    if(m_pD3DDevice) m_pD3DDevice->Release();
    if(m_pD3D) m_pD3D->Release(); 
    m_pD3D = NULL;
    m_pD3DDevice = NULL;
    
    if(m_hWnd) DestroyWindow(m_hWnd);
    m_hWnd = NULL;
    
    return true;
}

LRESULT CALLBACK CGameApp::StaticWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
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
	if (Message == WM_CREATE) SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT FAR*)lParam)->lpCreateParams);
#pragma warning (pop)
    
	// Obtain the correct destination for this message
	CGameApp* Destination = (CGameApp*)((LONG_PTR)GetWindowLongPtr(hWnd, GWLP_USERDATA));
    
	// If the hWnd has a related class, pass it through
	if (Destination) return Destination->DisplayWndProc(hWnd, Message, wParam, lParam);
    
	// No destination found, defer to system...
	return DefWindowProc(hWnd, Message, wParam, lParam);
}
LRESULT CGameApp::DisplayWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
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
        
		if (wParam == SIZE_MINIMIZED)
		{
			// App is inactive
			m_bActive = false;
            
		} // App has been minimized
		else
		{
			// App is active
			m_bActive = true;
            
			// Store new viewport sizes
			m_nViewWidth = LOWORD(lParam);
			m_nViewHeight = HIWORD(lParam);
            
			if (m_pD3DDevice)
			{
				// Store new sizes
				m_D3DPresentParams.BackBufferWidth = m_nViewWidth;
				m_D3DPresentParams.BackBufferHeight = m_nViewHeight;
                
				// Reset the device
				m_pD3DDevice->Reset(&m_D3DPresentParams);
				SetupRenderStates();
                
			} // End if
            
		} // End if !Minimized
        
		break;
        
        case WM_KEYDOWN:
        
		// Which key was pressed?
		switch (wParam)
		{
            case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
            
		} // End Switch
        
		break;
        
        case WM_COMMAND:
        
		// Process Menu Items
		switch (LOWORD(wParam))
		{
            
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

bool CGameApp::BuildObjects()
{
    CPolygon * pPoly = nullptr;
    
    // Add 6 polygons to this mesh.
    if (m_Mesh.AddPolygon(6) < 0) return false;
    
    // Front Face
    pPoly = m_Mesh.m_pPolygon[0];
    if (pPoly->AddVertex(4) < 0) return false;
    
    pPoly->m_pVertex[0] = CVertex(-2,  2, -2, RANDOM_COLOR);
    pPoly->m_pVertex[1] = CVertex( 2,  2, -2, RANDOM_COLOR);
    pPoly->m_pVertex[2] = CVertex( 2, -2, -2, RANDOM_COLOR);
    pPoly->m_pVertex[3] = CVertex(-2, -2, -2, RANDOM_COLOR);
    
    // Top Face
    pPoly = m_Mesh.m_pPolygon[1];
    if (pPoly->AddVertex(4) < 0) return false;
    
    pPoly->m_pVertex[0] = CVertex(-2, 2,  2, RANDOM_COLOR);
    pPoly->m_pVertex[1] = CVertex( 2, 2,  2, RANDOM_COLOR);
    pPoly->m_pVertex[2] = CVertex( 2, 2, -2, RANDOM_COLOR);
    pPoly->m_pVertex[3] = CVertex(-2, 2, -2, RANDOM_COLOR);
    
    // Back Face
    pPoly = m_Mesh.m_pPolygon[2];
    if (pPoly->AddVertex(4) < 0) return false;
    
    pPoly->m_pVertex[0] = CVertex(-2, -2, 2, RANDOM_COLOR);
    pPoly->m_pVertex[1] = CVertex( 2, -2, 2, RANDOM_COLOR);
    pPoly->m_pVertex[2] = CVertex( 2,  2, 2, RANDOM_COLOR);
    pPoly->m_pVertex[3] = CVertex(-2,  2, 2, RANDOM_COLOR),
    
    // Bottom Face
    pPoly = m_Mesh.m_pPolygon[3];
    if (pPoly->AddVertex(4) < 0) return false;
    
    pPoly->m_pVertex[0] = CVertex(-2, -2, -2, RANDOM_COLOR);
    pPoly->m_pVertex[1] = CVertex( 2, -2, -2, RANDOM_COLOR);
    pPoly->m_pVertex[2] = CVertex( 2, -2,  2, RANDOM_COLOR);
    pPoly->m_pVertex[3] = CVertex(-2, -2,  2, RANDOM_COLOR);
    
    // Left Face
    pPoly = m_Mesh.m_pPolygon[4];
    if (pPoly->AddVertex(4) < 0) return false;
    
    pPoly->m_pVertex[0] = CVertex(-2,  2,  2, RANDOM_COLOR);
    pPoly->m_pVertex[1] = CVertex(-2,  2, -2, RANDOM_COLOR);
    pPoly->m_pVertex[2] = CVertex(-2, -2, -2, RANDOM_COLOR);
    pPoly->m_pVertex[3] = CVertex(-2, -2,  2, RANDOM_COLOR);
    
    // Right Face
    pPoly = m_Mesh.m_pPolygon[5];
    if (pPoly->AddVertex(4) < 0) return false;
    
    pPoly->m_pVertex[0] = CVertex(2, 2, -2, RANDOM_COLOR);
    pPoly->m_pVertex[1] = CVertex(2, 2,  2, RANDOM_COLOR);
    pPoly->m_pVertex[2] = CVertex(2,-2,  2, RANDOM_COLOR);
    pPoly->m_pVertex[3] = CVertex(2,-2, -2, RANDOM_COLOR);
    
    // Our two objects should reference this mesh
    m_pObject[0].m_pMesh = &m_Mesh;
    
    
    
    if(m_Mesh2.AddPolygon(4) < 0) return false;
    
    // Front Face
    pPoly =  m_Mesh2.m_pPolygon[0];
    if(pPoly->AddVertex(3) < 0) return false;
    
    pPoly->m_pVertex[0] = CVertex( 0, 2, 0, RANDOM_COLOR);
    pPoly->m_pVertex[1] = CVertex( 2,-2,-2, RANDOM_COLOR);
    pPoly->m_pVertex[2] = CVertex(-2,-2,-2, RANDOM_COLOR);
    
    // Left Face
    pPoly = m_Mesh2.m_pPolygon[1];
    if(pPoly->AddVertex(3) < 0) return false;
    
    pPoly->m_pVertex[0] = CVertex( 0, 2, 0, RANDOM_COLOR);
    pPoly->m_pVertex[1] = CVertex(-2,-2,-2, RANDOM_COLOR);
    pPoly->m_pVertex[2] = CVertex( 0,-2, 2, RANDOM_COLOR);
    
    // Right Face
    pPoly = m_Mesh2.m_pPolygon[2];
    if(pPoly->AddVertex(3) < 0) return false;
    
    pPoly->m_pVertex[0] = CVertex( 0, 2, 0, RANDOM_COLOR);
    pPoly->m_pVertex[1] = CVertex( 0,-2, 2, RANDOM_COLOR);
    pPoly->m_pVertex[2] = CVertex( 2,-2,-2, RANDOM_COLOR);
    
    // Bottom Face
    pPoly = m_Mesh2.m_pPolygon[3];
    if(pPoly->AddVertex(3) < 0) return false;
    
    pPoly->m_pVertex[0] = CVertex( 2,-2,-2, RANDOM_COLOR);
    pPoly->m_pVertex[1] = CVertex(0,-2, 2, RANDOM_COLOR);
    pPoly->m_pVertex[2] = CVertex( -2,-2, -2, RANDOM_COLOR);
    
    m_pObject[1].m_pMesh = &m_Mesh2;
    
    D3DXMatrixTranslation(&m_pObject[0].m_mtxWorld,-3.5, 2.0f, 14.0f);
    D3DXMatrixTranslation(&m_pObject[1].m_mtxWorld, 3.5,-2.0f, 14.0f);
    
    return true;
}

void CGameApp::FrameAdvance()
{
    CMesh *pMesh = NULL;
    
    m_Timer.Tick();
    
    if(!m_bActive) return;
    
    if(m_bLostDevice)
    {
        HRESULT hRet = m_pD3DDevice->TestCooperativeLevel();
        
        if(hRet == D3DERR_DEVICENOTRESET)
        {
            m_pD3DDevice->Reset(&m_D3DPresentParams);
            SetupRenderStates();
            m_bLostDevice = false;
        }
        else
        {
            return;
        }
    }
    int nFrameRate = m_Timer.GetFrameRate();
    static int nLastFrameRate = 0;
    if(nLastFrameRate != nFrameRate)
    {
        static char FPSBuffer[20];
        m_Timer.GetFrameRate(FPSBuffer);
        nLastFrameRate = nFrameRate;
        SetWindowText(m_hWnd, FPSBuffer);
    }
    
	ProcessInput();
    
    AnimateObjects();
    
    m_pD3DDevice->Clear(9, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0XFFFFFFFF, 1.0F, 0);
    m_pD3DDevice->BeginScene();
    
    for(ULONG i = 0; i < 2; i++)
    {
        pMesh = m_pObject[i].m_pMesh;
        
        m_pD3DDevice->SetTransform(D3DTS_WORLD, &m_pObject[i].m_mtxWorld);
        
        for(ULONG f = 0; f < pMesh->m_nPolygonCount; f++)
        {
            CPolygon* pPolygon = pMesh->m_pPolygon[f];
            m_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, pPolygon->m_nVertexCount - 2, pPolygon->m_pVertex, sizeof(CVertex));
        }
        
    }
    m_pD3DDevice->EndScene();
    if(FAILED(m_pD3DDevice->Present(NULL,NULL,NULL,NULL))) m_bLostDevice = true;
}
void CGameApp::ProcessInput()
{
    if (GetKeyState(VK_LEFT) & 0xFF00||GetKeyState(65) & 0xFF00) m_mtxView._41 += 25.0f * m_Timer.GetTimeElapsed();
    if (GetKeyState(VK_RIGHT) & 0xFF00||GetKeyState(68) & 0xFF00) m_mtxView._41 -= 25.0f * m_Timer.GetTimeElapsed();
    
	if (GetKeyState(49) & 0xFF00) m_bRotation1 = !m_bRotation1;
    if (GetKeyState(50) & 0xFF00) m_bRotation2 = !m_bRotation2;
    
    if(m_pD3DDevice) m_pD3DDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
void CGameApp::AnimateObjects()
{
	// Note : Expanded for the purposes of this example only.
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