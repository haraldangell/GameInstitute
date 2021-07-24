#include "main.h"
#include "pch.h"
#include "CGameApp.h"

CGameApp GGameApp;
// Core game application processing engine

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int iCmdShow)
{

	if (!GGameApp.Init()) return -1;


	return GGameApp.GameLoop();
}