#include <windows.h>
#include "resource.h"

HWND ghMainWnd = 0;
HINSTANCE ghAppInst = 0;


LRESULT CALLBACK
WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		

		ghMainWnd = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,	0, 0,500, 500, hWnd, NULL, ghAppInst, NULL);

		break;
	}

	case WM_LBUTTONDOWN:

		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(ghMainWnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR cmdLine, int showCmd)
{

	ghAppInst = hInstance;

	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = ghAppInst;
	wc.hIcon = ::LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = ::LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"MyWndClassName";

	RegisterClass(&wc);

	HMENU hMenu = LoadMenu(ghAppInst, MAKEINTRESOURCE(IDR_MENU1));
	ghMainWnd = ::CreateWindow(L"MyWndClassName", L"MyWindow",	WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, 0, hMenu, ghAppInst, 0);
	if (ghMainWnd == 0)
	{
		::MessageBox(0, L"CreateWindow - Failed", 0, 0);
		return false;
	}

	ShowWindow(ghMainWnd, showCmd);
	UpdateWindow(ghMainWnd);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}