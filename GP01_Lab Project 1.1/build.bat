@echo off

IF NOT EXIST build\ mkdir build
pushd .\build
cl -FC -Zi /FeWinGame ..\src\main.cpp ..\src\CGameApp.cpp ..\src\CTimer.cpp ..\src\CObject.cpp  user32.lib winmm.lib gdi32.lib w:\common\lib\x64\d3dx9.lib w:\common\lib\x64\d3d9.lib
popd