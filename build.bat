@echo off
REM Build script for Fake Trainer (if using command-line MSVC)

echo ================================================
echo Building Fake Trainer (Release x64)
echo ================================================

REM Set Visual Studio environment (adjust path if needed)
REM call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

echo.
echo Compiling...
cl.exe /nologo /O1 /Os /MD /GS- /GR- /DNDEBUG /D_UNICODE /DUNICODE ^
    /EHsc /W3 /c ^
    main.cpp ^
    imgui.cpp ^
    imgui_draw.cpp ^
    imgui_tables.cpp ^
    imgui_widgets.cpp ^
    imgui_impl_win32.cpp ^
    imgui_impl_dx11.cpp

if %ERRORLEVEL% NEQ 0 (
    echo Compilation failed!
    pause
    exit /b 1
)

echo.
echo Linking...
link.exe /nologo /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup ^
    /MACHINE:X64 /OPT:REF /OPT:ICF /LTCG /MANIFEST:NO ^
    /OUT:trainer.exe ^
    main.obj imgui.obj imgui_draw.obj imgui_tables.obj ^
    imgui_widgets.obj imgui_impl_win32.obj imgui_impl_dx11.obj ^
    d3d11.lib user32.lib gdi32.lib

if %ERRORLEVEL% NEQ 0 (
    echo Linking failed!
    pause
    exit /b 1
)

echo.
echo Cleaning up...
del *.obj

echo.
echo ================================================
echo Build successful: trainer.exe
echo ================================================
echo.
echo Next steps:
echo 1. strip trainer.exe  (if you have strip.exe)
echo 2. upx --best --lzma trainer.exe
echo.
pause
