//-----------------------------------------------------------------------------
// File: CGameApp.h
//
// Desc: Game Application class, this is the central hub for all app processing
//
// Copyright (c) 1997-2002 Adam Hoult & Gary Simmons. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef _CGAMEAPP_H_
#define _CGAMEAPP_H_

//-----------------------------------------------------------------------------
// CGameApp Specific Includes
//-----------------------------------------------------------------------------
#include "Main.h"
#include "CTimer.h"
#include "CObject.h"
#include "CD3DSettingsDlg.h"

//-----------------------------------------------------------------------------
// Main Class Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Name : CGameApp (Class)
// Desc : Central game engine, initialises the game and handles core processes.
//-----------------------------------------------------------------------------
class CGameApp
{
    public:
    //-------------------------------------------------------------------------
    // Constructors & Destructors for This Class.
    //-------------------------------------------------------------------------
    CGameApp();
    virtual ~CGameApp();
    
    //-------------------------------------------------------------------------
    // Public Functions for This Class
    //-------------------------------------------------------------------------
    LRESULT     DisplayWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
    bool        InitInstance(HANDLE hInstance, LPCTSTR lpCmdLine, int iCmdShow);
    int         BeginGame();
    bool        ShutDown();
    
    private:
    //-------------------------------------------------------------------------
    // Private Functions for This Class
    //-------------------------------------------------------------------------
    bool        BuildObjects();
    void        FrameAdvance();
    bool        CreateDisplay();
    void        SetupGameState();
    void        SetupRenderStates();
    void        AnimateObjects();
    void        ProcessInput();
    
    //-------------------------------------------------------------------------
    // Private Static Functions For This Class
    //-------------------------------------------------------------------------
    static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
    
    //-------------------------------------------------------------------------
    // Private Variables For This Class
    //-------------------------------------------------------------------------
    D3DXMATRIX          m_mtxView;          // View Matrix
    D3DXMATRIX          m_mtxProjection;    // Projection matrix
    
    CMesh               m_Mesh;             // Mesh to be rendered
    CObject             m_pObject[2];       // Objects storing mesh instances
    
    CTimer              m_Timer;            // Game timer
    
    HWND                m_hWnd;             // Main window HWND
    HICON               m_hIcon;            // Window Icon
    HMENU               m_hMenu;            // Window Menu
    
    bool                m_bLostDevice;      // Is the 3d device currently lost ?
    bool                m_bActive;          // Is the application active ?
    bool                m_bRotation1;       // Object 1 rotation enabled / disabled 
    bool                m_bRotation2;       // Object 2 rotation enabled / disabled 
    
    LPDIRECT3D9         m_pD3D;             // Direct3D Object
    LPDIRECT3DDEVICE9   m_pD3DDevice;       // Direct3D Device Object
    CD3DSettings        m_D3DSettings;      // The settings used to initialize D3D
    
    ULONG               m_nViewX;           // X Position of render viewport
    ULONG               m_nViewY;           // Y Position of render viewport
    ULONG               m_nViewWidth;       // Width of render viewport
    ULONG               m_nViewHeight;      // Height of render viewport
    
};

//-----------------------------------------------------------------------------
// Name : CMyD3DInit (Subclass)
// Desc : Initialization class, derived from CD3DInitialize to supply any
//        validation of device settings that are deemed applicable by this
//        application.
//-----------------------------------------------------------------------------
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

#endif // _CGAMEAPP_H_OO