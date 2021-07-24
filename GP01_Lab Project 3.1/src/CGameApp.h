#pragma once


#include "main.h"
#include "CTimer.h"
#include "CObject.h"
#include "CD3DSettingsDlg.h"


class CGameApp
{
public:
	CGameApp();
	virtual ~CGameApp();

	LRESULT DisplayWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
	bool InitInstance(HANDLE hInstance, LPCTSTR lpCmdLine, int iCmdShow);
	int BeginGame();
	bool ShutDown;

private:
    bool        BuildObjects();
    void        ReleaseObjects();
    void        FrameAdvance();
    bool        CreateDisplay();
    void        SetupGameState();
    void        SetupRenderStates();
    void        AnimateObjects();
    void        ProcessInput();

    //-------------------------------------------------------------------------
    D3DXMATRIX              m_mtxView;          // View Matrix
    D3DXMATRIX              m_mtxProjection;    // Projection matrix

    LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;    // Vertex Buffer to be Rendered
    CObject                 m_pObject[2];       // Objects storing mesh instances

    CTimer                  m_Timer;            // Game timer

    HWND                    m_hWnd;             // Main window HWND
    HICON                   m_hIcon;            // Window Icon
    HMENU                   m_hMenu;            // Window Menu

    bool                    m_bLostDevice;      // Is the 3d device currently lost ?
    bool                    m_bActive;          // Is the application active ?
    bool                    m_bRotation1;       // Object 1 rotation enabled / disabled 
    bool                    m_bRotation2;       // Object 2 rotation enabled / disabled 

    LPDIRECT3D9             m_pD3D;             // Direct3D Object
    LPDIRECT3DDEVICE9       m_pD3DDevice;       // Direct3D Device Object
    CD3DSettings            m_D3DSettings;      // The settings used to initialize D3D

    ULONG                   m_nViewX;           // X Position of render viewport
    ULONG                   m_nViewY;           // Y Position of render viewport
    ULONG                   m_nViewWidth;       // Width of render viewport
    ULONG                   m_nViewHeight;      // Height of render viewport
};

class CMyD3DInit : public CD3DInitialize
{
private:
    //-------------------------------------------------------------------------
    // Private Virtual Functions for This Class (CD3DInitialize)
    //-------------------------------------------------------------------------
    virtual bool        ValidateDisplayMode(const D3DDISPLAYMODE& Mode);
    virtual bool        ValidateDevice(const D3DDEVTYPE& Type, const D3DCAPS9& Caps);
    virtual bool        ValidateVertexProcessingType(const VERTEXPROCESSING_TYPE& Type);
};
