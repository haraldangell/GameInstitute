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
    
	LRESULT DisplayWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
	bool InitInstance(HANDLE hInstance, LPCTSTR lpCmdLine, int iCmdShow);
	int BeginGame();
	bool ShutDown();
    
    private:
	bool BuildObjects();
	void FrameAdvance();
	bool CreateDisplay();
	void SetupGameState();
	void AnimateObjects();
	void PresentFrameBuffer();
	void ProccessInput();
	void ClearFrameBuffer(ULONG Color);
	bool BuildFrameBuffer(ULONG Width, ULONG Height);
	void DrawPrimitive(CPolygon* pPoly, D3DXMATRIX* pmtxWorld);
	void DrawLine(const D3DXVECTOR3 & vtx1, const D3DXVECTOR3 & vtx2, ULONG Color);
    
	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
    
	D3DXMATRIX m_mtxView; //View Matrix
	D3DXMATRIX m_mtxProjection; // Projection matrix
    
    CMesh m_Mesh;
	CMesh m_Mesh2; //Mesh to be rendered
	CObject m_pObject[2]; //Objects stroing mesh instances
    
	CTimer m_Timer; //Game Timer
    
	HWND m_hWnd; //Main window HWND
	HDC m_hdcFrameBuffer; // Frame Buffers Device Context
	HBITMAP m_hbmFrameBuffer; //Frame buffers Bitmap
	HBITMAP m_hbmSelectOut;
    
	bool m_bRotation1; //Object 1 rotation enabled / disabled
	bool m_bRotation2; //Object 2 rotation enabled / disabled
    
	ULONG m_nViewX; // X Position of render viewport
	ULONG m_nViewY; // Y Position of render viewport
	ULONG m_nViewWidth; // Width of render viewport
	ULONG m_nViewHeight; // Height of render viewport
	float m_nObject;
};

