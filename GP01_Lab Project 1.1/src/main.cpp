#include "main.h"
#include "CGameApp.h"

CGameApp g_App;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow)
{
    int retCode;
    
    if(!g_App.InitInstance(hInstance, lpCmdLine, iCmdShow))
        return 0;
    
    retCode = g_App.BeginGame();
    
    if(!g_App.ShutDown())
        MessageBox(0,_T("Failed to shut system down correctly, please check file named 'debug.txt'.\r\n\r\nIf the problem persists, please contact technical support."), _T("Non-Fatal Error"), MB_OK | MB_ICONEXCLAMATION);
    
    
	return retCode;
}