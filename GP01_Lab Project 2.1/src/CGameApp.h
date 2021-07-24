#pragma once

#include "main.h"
#include "CTimer.h"
#include "CObject.h"

#define ID_FILE_EXIT 1001


class CGameApp
{
public:
    
    CGameApp();
    virtual ~CGameApp();
    
	LRESULT     DisplayWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
	bool        InitInstance(HANDLE hInstance, LPCTSTR lpCmdLine, int iCmdShow);
	int         BeginGame();
	bool        ShutDown();
    
private:
    
	bool        BuildObjects();
	void        FrameAdvance();
	bool        CreateDisplay();
	void        SetupGameState();
	void        SetupRenderStates();
	void        AnimateObjects();
	void        ProcessInput();
	bool        InitDirect3D();
	D3DFORMAT   FindDepthStencilFormat(ULONG AdapterOrdinal, D3DDISPLAYMODE Mode, D3DDEVTYPE DevType);

	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);

	D3DXMATRIX              m_mtxView;          // View Matrix
	D3DXMATRIX              m_mtxProjection;    // Projection matrix

	CMesh                   m_Mesh;             // Mesh to be rendered
	CMesh                   m_Mesh2;             // Mesh to be rendered
	CObject                 m_pObject[2];       // Objects storing mesh instances

	CTimer                  m_Timer;            // Game timer

	HWND                    m_hWnd;             // Main window HWND

	bool                    m_bLostDevice;      // Is the 3d device currently lost ?
	bool                    m_bActive;          // Is the application active ?
	bool                    m_bRotation1;       // Object 1 rotation enabled / disabled 
	bool                    m_bRotation2;       // Object 2 rotation enabled / disabled 

	ULONG                   m_nViewX;           // X Position of render viewport
	ULONG                   m_nViewY;           // Y Position of render viewport
	ULONG                   m_nViewWidth;       // Width of render viewport
	ULONG                   m_nViewHeight;      // Height of render viewport


	LPDIRECT3D9             m_pD3D;             // Direct3D Object
	LPDIRECT3DDEVICE9       m_pD3DDevice;       // Direct3D Device Object
	D3DPRESENT_PARAMETERS   m_D3DPresentParams; // Direct3D Present Parameters

};