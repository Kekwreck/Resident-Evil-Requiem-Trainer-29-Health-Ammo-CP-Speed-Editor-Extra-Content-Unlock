@echo off
REM Automatic standalone build script for Professional Trainer
REM No dependencies required - builds fully standalone .exe with /MT

echo ================================================
echo Professional Trainer - Standalone Builder
echo ================================================
echo.

REM Download ImGui if not present
if not exist "imgui.h" (
    echo [1/5] Downloading ImGui...
    powershell -Command "$ProgressPreference = 'SilentlyContinue'; Invoke-WebRequest -Uri 'https://github.com/ocornut/imgui/archive/refs/tags/v1.90.1.zip' -OutFile 'imgui.zip' -UseBasicParsing"
    
    echo [2/5] Extracting ImGui...
    powershell -Command "Expand-Archive -Path 'imgui.zip' -DestinationPath '.' -Force"
    
    echo [3/5] Copying ImGui files...
    powershell -Command "Copy-Item 'imgui-1.90.1\*.cpp' -Destination '.' -Force; Copy-Item 'imgui-1.90.1\*.h' -Destination '.' -Force; Copy-Item 'imgui-1.90.1\backends\imgui_impl_win32.*' -Destination '.' -Force; Copy-Item 'imgui-1.90.1\backends\imgui_impl_dx11.*' -Destination '.' -Force"
    
    del imgui.zip
    rmdir /s /q imgui-1.90.1
    echo.
)

echo [4/5] Compiling with STATIC runtime (/MT)...
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1

cl.exe /nologo /O1 /Os /MT /GS- /GR- /DNDEBUG /D_UNICODE /DUNICODE ^
    /EHsc /W2 /c ^
    main.cpp ^
    imgui.cpp ^
    imgui_draw.cpp ^
    imgui_tables.cpp ^
    imgui_widgets.cpp ^
    imgui_impl_win32.cpp ^
    imgui_impl_dx11.cpp

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Compilation failed!
    pause
    exit /b 1
)

echo [5/5] Linking standalone executable...
link.exe /nologo /SUBSYSTEM:WINDOWS /MACHINE:X64 ^
    /OPT:REF /OPT:ICF /MANIFEST:NO ^
    /OUT:trainer.exe ^
    main.obj imgui.obj imgui_draw.obj imgui_tables.obj ^
    imgui_widgets.obj imgui_impl_win32.obj imgui_impl_dx11.obj ^
    d3d11.lib user32.lib gdi32.lib dxgi.lib psapi.lib

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Linking failed!
    pause
    exit /b 1
)

REM Clean up
del *.obj 2>nul

echo.
echo ================================================
echo BUILD SUCCESSFUL!
echo ================================================
echo.
echo Output: trainer.exe (STANDALONE - No DLL dependencies)
echo Size: 
dir trainer.exe | findstr trainer.exe
echo.

REM Download UPX if not present
if not exist "upx.exe" (
    echo Downloading UPX compressor...
    powershell -Command "$ProgressPreference = 'SilentlyContinue'; Invoke-WebRequest -Uri 'https://github.com/upx/upx/releases/download/v4.2.2/upx-4.2.2-win64.zip' -OutFile 'upx.zip' -UseBasicParsing; Expand-Archive -Path 'upx.zip' -DestinationPath '.' -Force; Copy-Item 'upx-4.2.2-win64\upx.exe' -Destination '.' -Force; Remove-Item 'upx.zip' -Force; Remove-Item 'upx-4.2.2-win64' -Recurse -Force"
    echo.
)

echo Compressing with UPX...
upx.exe --ultra-brute --lzma trainer.exe

echo.
echo ================================================
echo FINAL BUILD COMPLETE!
echo ================================================
echo.
echo Run: trainer.exe
echo.
pause
