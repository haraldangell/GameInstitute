#pragma once //MAIN_H


#include <Windows.h>
#include <tchar.h>
#include <D3DX9.h>


#define RGB2BGR( Color ) (Color & 0xFF000000) | ((Color & 0xFF0000) >> 16) | (Color & 0x00FF00) | ((Color & 0x0000FF) << 16)

