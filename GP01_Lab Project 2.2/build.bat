 @echo off
 IF NOT EXIST build\ mkdir build
 pushd .\build
 cl -FC -Zi  ../src/main.cpp ../src/CGameApp.cpp ../src/CD3DInitialize.cpp ../src/CD3DSettingsDlg.cpp ../src/CObject.cpp ../src/CTimer.cpp /I"C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include" user32.lib "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x86\d3dx9.lib" "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x86\d3d9.lib" gdi32.lib  winmm.lib    
popd