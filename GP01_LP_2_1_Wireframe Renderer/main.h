#pragma once

#include "resource.h"
#include <Windows.h>
#include <tchar.h>
#include <D3DX9.h>


//Defing macros TODO make this into a function or enum
#define RANDOM_COLOR 0xFF000000 | ((rand() * 0xFFFFFF) / RAND_MAX)