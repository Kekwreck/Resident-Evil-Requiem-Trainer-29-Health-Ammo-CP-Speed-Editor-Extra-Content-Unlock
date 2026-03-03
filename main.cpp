// main.cpp
// Professional Trainer for Resident Evil Requiem (RE9)
// Build: Release x64 with /MT (static runtime)
// Version: 1.0.6

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <mmsystem.h>
#include <fstream>
#include <string>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "winmm.lib")

// Forward declarations
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// D3D11 resources
static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

// Window handle (global for new features)
static HWND g_hwnd = NULL;

// Trainer state
static bool g_enabled[15] = {false};
static bool g_keyPressed[15] = {false};
static bool g_masterKeyPressed = false;
static bool g_escPressed = false;
static float g_animTimer[15] = {0.0f};
static int g_lastActivated = -1;
static float g_messageTimer = 0.0f;

// =====================================================
// NEW FEATURE 1: Opacity Control (F7/F8)
// =====================================================
static int g_windowOpacity = 245;  // 0-255 (default ~96%)
static bool g_opacityUpPressed = false;
static bool g_opacityDownPressed = false;

// =====================================================
// NEW FEATURE 2: Always On Top Toggle (F9)
// =====================================================
static bool g_alwaysOnTop = true;
static bool g_topTogglePressed = false;

// =====================================================
// NEW FEATURE 3: Profile System (F10 Save, F11 Load)
// =====================================================
static int g_currentProfile = 1;  // 1-3
static bool g_savePressed = false;
static bool g_loadPressed = false;
static bool g_profileSwitchPressed = false;
static float g_profileMessageTimer = 0.0f;
static char g_profileMessage[128] = "";

// =====================================================
// NEW FEATURE 4: Cheat Timer / Auto-Disable (F12)
// =====================================================
static bool g_timerEnabled = false;
static float g_cheatTimer = 0.0f;
static float g_cheatTimerDuration = 60.0f;  // 60 seconds default
static bool g_timerTogglePressed = false;

// =====================================================
// NEW FEATURE 5: Minimize to Tray (Ctrl+M)
// =====================================================
static bool g_minimized = false;
static bool g_minimizePressed = false;
static NOTIFYICONDATA g_nid = {};
static bool g_trayIconCreated = false;
#define WM_TRAYICON (WM_USER + 1)
#define ID_TRAY_RESTORE 1001
#define ID_TRAY_EXIT 1002

// Simulated game values
static int g_health = 100;
static int g_maxHealth = 100;
static int g_ammo = 45;
static int g_maxAmmo = 150;
static int g_grenades = 3;
static int g_money = 12500;
static float g_gameSpeed = 1.0f;
static float g_updateTimer = 0.0f;

// Process detection
static DWORD g_gamePID = 0;
static HANDLE g_gameHandle = NULL;
static bool g_gameAttached = false;
static float g_processCheckTimer = 0.0f;
static const float PROCESS_CHECK_INTERVAL = 1.0f; // Check every 1 second

// Status bar
static float g_cpuUsage = 0.0f;
static float g_memoryUsage = 0.0f;
static float g_statusBarTimer = 0.0f;

// Cheat data
static const char* g_cheatNames[15] = {
    "God Mode / Ignore Hits",
    "Infinite Health",
    "Infinite Ammo",
    "No Reload",
    "Infinite Items",
    "Infinite Grenades / Throwables",
    "Infinite Knife Durability",
    "One Hit Kill",
    "Freeze Enemies",
    "Super Speed",
    "Super Jump",
    "No Recoil",
    "No Spread",
    "Game Speed",
    "Infinite Money / Upgrade Points"
};

static const char* g_hotkeys[15] = {
    "Num 1", "Num 2", "Num 3", "Num 4", "Num 5",
    "Num 6", "Num 7", "Num 8", "Num 9", "F1",
    "F2", "F3", "F4", "F5", "F6"
};

static const int g_vkeys[15] = {
    VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5,
    VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9, VK_F1,
    VK_F2, VK_F3, VK_F4, VK_F5, VK_F6
};

// D3D11 helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Process detection functions
DWORD FindProcessByName(const char* processName) {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE) return 0;

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnap, &pe32)) {
        do {
            // Convert WCHAR to char for comparison
            char exeName[MAX_PATH];
            WideCharToMultiByte(CP_ACP, 0, pe32.szExeFile, -1, exeName, MAX_PATH, NULL, NULL);

            // Compare process name (case-insensitive)
            if (_stricmp(exeName, processName) == 0) {
                CloseHandle(hSnap);
                return pe32.th32ProcessID;
            }
        } while (Process32Next(hSnap, &pe32));
    }

    CloseHandle(hSnap);
    return 0;
}

void UpdateProcessStatus() {
    // Try to find process
    g_gamePID = FindProcessByName("ResidentEvilRequiem.exe");

    if (g_gamePID != 0) {
        // Try to open process handle
        if (g_gameHandle == NULL || !g_gameAttached) {
            g_gameHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, g_gamePID);
            if (g_gameHandle != NULL) {
                g_gameAttached = true;
            }
        }

        // Verify process still exists
        if (g_gameHandle != NULL) {
            DWORD exitCode;
            if (!GetExitCodeProcess(g_gameHandle, &exitCode) || exitCode != STILL_ACTIVE) {
                CloseHandle(g_gameHandle);
                g_gameHandle = NULL;
                g_gameAttached = false;
                g_gamePID = 0;
            }
        }
    } else {
        // Process not found
        if (g_gameHandle != NULL) {
            CloseHandle(g_gameHandle);
            g_gameHandle = NULL;
        }
        g_gameAttached = false;
        g_gamePID = 0;
    }
}

void UpdateStatusBar() {
    // Simulate CPU usage (0-100%)
    g_cpuUsage = 2.5f + (float)(rand() % 30) / 10.0f; // 2.5-5.5%

    // Get real memory usage of trainer
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        g_memoryUsage = (float)(pmc.WorkingSetSize / 1024.0 / 1024.0); // MB
    }
}

// =====================================================
// NEW FEATURE 1: Opacity Control Implementation
// =====================================================
void UpdateOpacity() {
    if (g_hwnd) {
        SetLayeredWindowAttributes(g_hwnd, 0, (BYTE)g_windowOpacity, LWA_ALPHA);
    }
}

// =====================================================
// NEW FEATURE 2: Always On Top Toggle Implementation
// =====================================================
void UpdateAlwaysOnTop() {
    if (g_hwnd) {
        SetWindowPos(g_hwnd, g_alwaysOnTop ? HWND_TOPMOST : HWND_NOTOPMOST, 
                     0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
}

// =====================================================
// NEW FEATURE 3: Profile System Implementation
// =====================================================
void SaveProfile(int profileNum) {
    char filename[64];
    wsprintfA(filename, "trainer_profile_%d.cfg", profileNum);

    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        // Save all cheat states
        file.write((char*)g_enabled, sizeof(g_enabled));
        // Save opacity
        file.write((char*)&g_windowOpacity, sizeof(g_windowOpacity));
        // Save always on top
        file.write((char*)&g_alwaysOnTop, sizeof(g_alwaysOnTop));
        // Save timer duration
        file.write((char*)&g_cheatTimerDuration, sizeof(g_cheatTimerDuration));
        file.close();

        wsprintfA(g_profileMessage, "Profile %d saved!", profileNum);
        g_profileMessageTimer = 2.0f;

        // Play sound
        PlaySound(TEXT("SystemAsterisk"), NULL, SND_ALIAS | SND_ASYNC);
    }
}

void LoadProfile(int profileNum) {
    char filename[64];
    wsprintfA(filename, "trainer_profile_%d.cfg", profileNum);

    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        // Load all cheat states
        file.read((char*)g_enabled, sizeof(g_enabled));
        // Load opacity
        file.read((char*)&g_windowOpacity, sizeof(g_windowOpacity));
        UpdateOpacity();
        // Load always on top
        file.read((char*)&g_alwaysOnTop, sizeof(g_alwaysOnTop));
        UpdateAlwaysOnTop();
        // Load timer duration
        file.read((char*)&g_cheatTimerDuration, sizeof(g_cheatTimerDuration));
        file.close();

        wsprintfA(g_profileMessage, "Profile %d loaded!", profileNum);
        g_profileMessageTimer = 2.0f;

        // Animate all cheats
        for (int i = 0; i < 15; i++) {
            g_animTimer[i] = 0.3f;
        }

        // Play sound
        PlaySound(TEXT("SystemAsterisk"), NULL, SND_ALIAS | SND_ASYNC);
    } else {
        wsprintfA(g_profileMessage, "Profile %d not found!", profileNum);
        g_profileMessageTimer = 2.0f;
    }
}

// =====================================================
// NEW FEATURE 4: Cheat Timer Implementation
// =====================================================
void UpdateCheatTimer(float deltaTime) {
    if (g_timerEnabled && g_gameAttached) {
        g_cheatTimer += deltaTime;

        if (g_cheatTimer >= g_cheatTimerDuration) {
            // Disable all cheats
            for (int i = 0; i < 15; i++) {
                g_enabled[i] = false;
                g_animTimer[i] = 0.3f;
            }
            g_timerEnabled = false;
            g_cheatTimer = 0.0f;

            // Show message
            g_lastActivated = -1;
            g_messageTimer = 2.0f;
            wsprintfA(g_profileMessage, "Timer expired! All cheats disabled.");
            g_profileMessageTimer = 3.0f;

            // Play sound
            PlaySound(TEXT("SystemExclamation"), NULL, SND_ALIAS | SND_ASYNC);
        }
    }
}

// =====================================================
// NEW FEATURE 5: System Tray Implementation
// =====================================================
void CreateTrayIcon() {
    if (!g_trayIconCreated && g_hwnd) {
        ZeroMemory(&g_nid, sizeof(g_nid));
        g_nid.cbSize = sizeof(NOTIFYICONDATA);
        g_nid.hWnd = g_hwnd;
        g_nid.uID = 1;
        g_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
        g_nid.uCallbackMessage = WM_TRAYICON;
        g_nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        lstrcpy(g_nid.szTip, TEXT("RE Requiem Trainer v1.0.6"));

        Shell_NotifyIcon(NIM_ADD, &g_nid);
        g_trayIconCreated = true;
    }
}

void RemoveTrayIcon() {
    if (g_trayIconCreated) {
        Shell_NotifyIcon(NIM_DELETE, &g_nid);
        g_trayIconCreated = false;
    }
}

void MinimizeToTray() {
    if (g_hwnd) {
        CreateTrayIcon();
        ShowWindow(g_hwnd, SW_HIDE);
        g_minimized = true;
    }
}

void RestoreFromTray() {
    if (g_hwnd) {
        ShowWindow(g_hwnd, SW_SHOW);
        SetForegroundWindow(g_hwnd);
        g_minimized = false;
    }
}

void ShowTrayMenu() {
    POINT pt;
    GetCursorPos(&pt);

    HMENU hMenu = CreatePopupMenu();
    AppendMenu(hMenu, MF_STRING, ID_TRAY_RESTORE, TEXT("Restore"));
    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu, MF_STRING, ID_TRAY_EXIT, TEXT("Exit"));

    SetForegroundWindow(g_hwnd);
    TrackPopupMenu(hMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, g_hwnd, NULL);
    DestroyMenu(hMenu);
}

void HandleHotkeys(float deltaTime) {
    // Update process check timer
    g_processCheckTimer += deltaTime;
    if (g_processCheckTimer >= PROCESS_CHECK_INTERVAL) {
        g_processCheckTimer = 0.0f;
        UpdateProcessStatus();
    }

    // Update status bar
    g_statusBarTimer += deltaTime;
    if (g_statusBarTimer >= 0.5f) {
        g_statusBarTimer = 0.0f;
        UpdateStatusBar();
    }

    // Update simulated values (only if game is attached)
    g_updateTimer += deltaTime;
    if (g_updateTimer > 0.5f && g_gameAttached) {
        g_updateTimer = 0.0f;

        // Simulate health changes
        if (g_enabled[1]) { // Infinite Health
            g_health = g_maxHealth;
        } else if (!g_enabled[0]) { // Not God Mode
            if (g_health > 60) g_health -= (rand() % 3);
        }

        // Simulate ammo changes
        if (g_enabled[2]) { // Infinite Ammo
            g_ammo = g_maxAmmo;
        } else if (g_ammo > 0 && !g_enabled[3]) {
            g_ammo -= (rand() % 2);
        }

        // Simulate grenades
        if (g_enabled[5] && g_grenades < 99) {
            g_grenades = 99;
        }

        // Simulate money
        if (g_enabled[14]) { // Infinite Money
            g_money = 999999;
        }

        // Game speed
        if (g_enabled[13]) {
            g_gameSpeed = 1.5f;
        } else {
            g_gameSpeed = 1.0f;
        }
    }

    // Individual cheats (only work if game is attached)
    for (int i = 0; i < 15; i++) {
        bool keyDown = (GetAsyncKeyState(g_vkeys[i]) & 0x8000) != 0;
        if (keyDown && !g_keyPressed[i]) {
            if (g_gameAttached) { // Only toggle if attached
                g_enabled[i] = !g_enabled[i];
                g_animTimer[i] = 0.3f;
                g_lastActivated = i;
                g_messageTimer = 2.0f;
            } else {
                // Show "Game not found" message
                g_lastActivated = -2; // Special code for error
                g_messageTimer = 2.0f;
            }
        }
        g_keyPressed[i] = keyDown;
        if (g_animTimer[i] > 0.0f) g_animTimer[i] -= deltaTime;
    }

    // Master switch (Num *)
    bool masterDown = (GetAsyncKeyState(VK_MULTIPLY) & 0x8000) != 0;
    if (masterDown && !g_masterKeyPressed) {
        bool anyOn = false;
        for (int i = 0; i < 15; i++) if (g_enabled[i]) { anyOn = true; break; }
        for (int i = 0; i < 15; i++) {
            g_enabled[i] = !anyOn;
            g_animTimer[i] = 0.3f;
        }
        g_lastActivated = -1;
        g_messageTimer = 2.0f;
    }
    g_masterKeyPressed = masterDown;

    if (g_messageTimer > 0.0f) g_messageTimer -= deltaTime;
    if (g_profileMessageTimer > 0.0f) g_profileMessageTimer -= deltaTime;

    // =====================================================
    // NEW FEATURE 1: Opacity Control (F7 decrease, F8 increase)
    // =====================================================
    bool opacityDownDown = (GetAsyncKeyState(VK_F7) & 0x8000) != 0;
    if (opacityDownDown && !g_opacityDownPressed) {
        g_windowOpacity = max(50, g_windowOpacity - 25);  // Min 50 (~20%)
        UpdateOpacity();
        wsprintfA(g_profileMessage, "Opacity: %d%%", (g_windowOpacity * 100) / 255);
        g_profileMessageTimer = 1.5f;
    }
    g_opacityDownPressed = opacityDownDown;

    bool opacityUpDown = (GetAsyncKeyState(VK_F8) & 0x8000) != 0;
    if (opacityUpDown && !g_opacityUpPressed) {
        g_windowOpacity = min(255, g_windowOpacity + 25);  // Max 255 (100%)
        UpdateOpacity();
        wsprintfA(g_profileMessage, "Opacity: %d%%", (g_windowOpacity * 100) / 255);
        g_profileMessageTimer = 1.5f;
    }
    g_opacityUpPressed = opacityUpDown;

    // =====================================================
    // NEW FEATURE 2: Always On Top Toggle (F9)
    // =====================================================
    bool topToggleDown = (GetAsyncKeyState(VK_F9) & 0x8000) != 0;
    if (topToggleDown && !g_topTogglePressed) {
        g_alwaysOnTop = !g_alwaysOnTop;
        UpdateAlwaysOnTop();
        wsprintfA(g_profileMessage, "Always On Top: %s", g_alwaysOnTop ? "ON" : "OFF");
        g_profileMessageTimer = 1.5f;
        PlaySound(TEXT("SystemAsterisk"), NULL, SND_ALIAS | SND_ASYNC);
    }
    g_topTogglePressed = topToggleDown;

    // =====================================================
    // NEW FEATURE 3: Profile System (F10 Save, F11 Load, Ctrl+1/2/3 switch)
    // =====================================================
    bool saveDown = (GetAsyncKeyState(VK_F10) & 0x8000) != 0;
    if (saveDown && !g_savePressed) {
        SaveProfile(g_currentProfile);
    }
    g_savePressed = saveDown;

    bool loadDown = (GetAsyncKeyState(VK_F11) & 0x8000) != 0;
    if (loadDown && !g_loadPressed) {
        LoadProfile(g_currentProfile);
    }
    g_loadPressed = loadDown;

    // Ctrl+1/2/3 to switch profiles
    bool ctrlDown = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
    if (ctrlDown) {
        for (int p = 1; p <= 3; p++) {
            if ((GetAsyncKeyState('0' + p) & 0x8000) != 0 && !g_profileSwitchPressed) {
                g_currentProfile = p;
                wsprintfA(g_profileMessage, "Profile %d selected", p);
                g_profileMessageTimer = 1.5f;
                g_profileSwitchPressed = true;
                PlaySound(TEXT("SystemAsterisk"), NULL, SND_ALIAS | SND_ASYNC);
            }
        }
    } else {
        g_profileSwitchPressed = false;
    }

    // =====================================================
    // NEW FEATURE 4: Cheat Timer Toggle (F12)
    // =====================================================
    bool timerToggleDown = (GetAsyncKeyState(VK_F12) & 0x8000) != 0;
    if (timerToggleDown && !g_timerTogglePressed) {
        g_timerEnabled = !g_timerEnabled;
        g_cheatTimer = 0.0f;
        wsprintfA(g_profileMessage, "Cheat Timer (%ds): %s", 
                  (int)g_cheatTimerDuration, g_timerEnabled ? "STARTED" : "STOPPED");
        g_profileMessageTimer = 2.0f;
        PlaySound(TEXT("SystemAsterisk"), NULL, SND_ALIAS | SND_ASYNC);
    }
    g_timerTogglePressed = timerToggleDown;

    // Update cheat timer
    UpdateCheatTimer(deltaTime);

    // =====================================================
    // NEW FEATURE 5: Minimize to Tray (Ctrl+M)
    // =====================================================
    bool minimizeDown = ctrlDown && (GetAsyncKeyState('M') & 0x8000) != 0;
    if (minimizeDown && !g_minimizePressed) {
        MinimizeToTray();
    }
    g_minimizePressed = minimizeDown;

    // ESC to close
    bool escDown = (GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0;
    if (escDown && !g_escPressed) {
        RemoveTrayIcon();
        PostQuitMessage(0);
    }
    g_escPressed = escDown;
}

void RenderUI() {
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                             ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                             ImGuiWindowFlags_NoSavedSettings;

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(450, 750));

    ImGui::Begin("Trainer", NULL, flags);

    // Header - large text
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 2));
    ImGui::SetWindowFontScale(1.3f);
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.25f, 1.0f), "Resident Evil Requiem");
    ImGui::SetWindowFontScale(1.0f);
    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Game Trainer v1.0.6");
    ImGui::PopStyleVar();
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // Status bar - dynamic
    if (g_gameAttached && g_gamePID != 0) {
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.25f, 1.0f), "Status: ");
        ImGui::SameLine();
        char statusText[128];
        wsprintfA(statusText, "Attached to ResidentEvilRequiem.exe (PID: %lu)", g_gamePID);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), statusText);
    } else {
        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.0f, 1.0f), "Status: ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Waiting for ResidentEvilRequiem.exe...");
    }

    // Trainer performance bar
    ImGui::Spacing();
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
    char perfText[128];
    wsprintfA(perfText, "Trainer: CPU %.1f%% | Memory %.1f MB", g_cpuUsage, g_memoryUsage);
    ImGui::Text(perfText);
    ImGui::PopStyleColor();

    ImGui::Spacing();
    ImGui::Separator();

    // Game stats display (only if attached)
    if (g_gameAttached) {
        ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.0f, 1.0f), "Game Stats:");
        ImGui::Text("Health: %d/%d", g_health, g_maxHealth);
        ImGui::SameLine(150);
        ImGui::Text("Ammo: %d/%d", g_ammo, g_maxAmmo);
        ImGui::Text("Grenades: %d", g_grenades);
        ImGui::SameLine(150);
        ImGui::Text("Money: $%d", g_money);
        ImGui::Text("Game Speed: %.1fx", g_gameSpeed);
    } else {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
        ImGui::TextColored(ImVec4(0.8f, 0.4f, 0.0f, 1.0f), "Game Stats:");
        ImGui::Text("Waiting for game process...");
        ImGui::PopStyleColor();
    }
    ImGui::Spacing();

    // Master switch
    ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "Master: Num * - Toggle ALL");
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // Cheats list
    for (int i = 0; i < 15; i++) {
        ImGui::PushID(i);
        
        // Hotkey (fixed width)
        ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "%-8s", g_hotkeys[i]);
        ImGui::SameLine();

        // Cheat name
        ImGui::Text("%s", g_cheatNames[i]);

        // Dots spacer
        ImGui::SameLine();
        float textWidth = ImGui::CalcTextSize(g_cheatNames[i]).x;
        float targetX = 360.0f;
        float currentX = ImGui::GetCursorPosX();
        if (currentX < targetX) {
            ImGui::SetCursorPosX(targetX);
        }

        // Status [ON]/[OFF]
        if (g_enabled[i]) {
            float pulse = (g_animTimer[i] > 0.0f) ? (0.7f + 0.3f * (g_animTimer[i] / 0.3f)) : 1.0f;
            ImGui::TextColored(ImVec4(0.0f, 1.0f * pulse, 0.25f * pulse, 1.0f), "[ON]");
        } else {
            ImGui::TextColored(ImVec4(0.8f, 0.0f, 0.0f, 1.0f), "[OFF]");
        }

        ImGui::PopID();
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // Activity message
    if (g_messageTimer > 0.0f) {
        float alpha = (g_messageTimer > 1.0f) ? 1.0f : g_messageTimer;
        if (g_lastActivated == -2) {
            // Error message
            ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.0f, alpha), "ERROR: Game process not found!");
        } else if (g_lastActivated >= 0) {
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.25f, alpha), "Activated: %s", g_cheatNames[g_lastActivated]);
        } else {
            bool anyOn = false;
            for (int i = 0; i < 15; i++) if (g_enabled[i]) { anyOn = true; break; }
            ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, alpha), "Master: %s", anyOn ? "ALL ON" : "ALL OFF");
        }
    } else if (g_profileMessageTimer > 0.0f) {
        // Profile/Feature message
        float alpha = (g_profileMessageTimer > 1.0f) ? 1.0f : g_profileMessageTimer;
        ImGui::TextColored(ImVec4(0.3f, 0.8f, 1.0f, alpha), "%s", g_profileMessage);
    } else {
        if (g_gameAttached) {
            ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Press hotkeys to toggle...");
        } else {
            ImGui::TextColored(ImVec4(0.8f, 0.4f, 0.0f, 1.0f), "Start ResidentEvilRequiem.exe to enable cheats");
        }
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // =====================================================
    // NEW: Display New Features Status
    // =====================================================
    ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "--- NEW FEATURES v1.0.6 ---");

    // Opacity
    ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "F7/F8");
    ImGui::SameLine();
    ImGui::Text("Opacity: %d%%", (g_windowOpacity * 100) / 255);

    // Always On Top
    ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "F9   ");
    ImGui::SameLine();
    ImGui::Text("Always On Top: ");
    ImGui::SameLine();
    if (g_alwaysOnTop) {
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.25f, 1.0f), "[ON]");
    } else {
        ImGui::TextColored(ImVec4(0.8f, 0.0f, 0.0f, 1.0f), "[OFF]");
    }

    // Profile
    ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "F10/F11");
    ImGui::SameLine();
    ImGui::Text("Save/Load Profile %d", g_currentProfile);
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "(Ctrl+1/2/3)");

    // Timer
    ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "F12  ");
    ImGui::SameLine();
    ImGui::Text("Cheat Timer: ");
    ImGui::SameLine();
    if (g_timerEnabled) {
        int remaining = (int)(g_cheatTimerDuration - g_cheatTimer);
        ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "[%ds left]", remaining);
    } else {
        ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "[OFF]");
    }

    // Minimize
    ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "Ctrl+M");
    ImGui::SameLine();
    ImGui::Text("Minimize to Tray");

    ImGui::Spacing();
    ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "ESC to close | Drag window anywhere");

    ImGui::End();
}

bool CreateDeviceD3D(HWND hWnd) {
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2,
        D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D() {
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

void CreateRenderTarget() {
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget() {
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg) {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED) {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_NCHITTEST:
        {
            // Allow dragging window by clicking anywhere
            LRESULT hit = DefWindowProc(hWnd, msg, wParam, lParam);
            if (hit == HTCLIENT)
                return HTCAPTION; // Treat client area as title bar for dragging
            return hit;
        }
    // =====================================================
    // NEW FEATURE 5: System Tray Message Handler
    // =====================================================
    case WM_TRAYICON:
        if (lParam == WM_LBUTTONDBLCLK) {
            RestoreFromTray();
        } else if (lParam == WM_RBUTTONUP) {
            ShowTrayMenu();
        }
        return 0;
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_TRAY_RESTORE) {
            RestoreFromTray();
        } else if (LOWORD(wParam) == ID_TRAY_EXIT) {
            RemoveTrayIcon();
            PostQuitMessage(0);
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        RemoveTrayIcon();
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    // Create window class
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("FakeTrainerWnd"), NULL };
    RegisterClassEx(&wc);

    // Create borderless window, topmost, semi-transparent
    // Increased height to 750 for new features
    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED,
        wc.lpszClassName,
        _T("RE9 Trainer v1.0.6"),
        WS_POPUP,
        100, 100, 450, 750,
        NULL, NULL, wc.hInstance, NULL
    );

    // Store global handle for new features
    g_hwnd = hwnd;

    // Set opacity (245/255 = ~96% opacity)
    SetLayeredWindowAttributes(hwnd, 0, g_windowOpacity, LWA_ALPHA);

    // Initialize D3D11
    if (!CreateDeviceD3D(hwnd)) {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    // Initialize process detection
    UpdateProcessStatus();

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = NULL; // No imgui.ini

    // Setup ImGui style - dark professional theme
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding = ImVec2(15, 15);
    style.FramePadding = ImVec2(5, 3);
    style.ItemSpacing = ImVec2(8, 4);
    style.WindowRounding = 0.0f;
    style.FrameRounding = 2.0f;
    style.WindowBorderSize = 1.0f;
    
    // Dark theme colors
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.04f, 0.04f, 0.04f, 0.98f);
    colors[ImGuiCol_Border] = ImVec4(0.0f, 1.0f, 0.25f, 0.5f);
    colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
    colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    // Main loop
    MSG msg = {};
    LARGE_INTEGER freq, last, now;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&last);

    while (msg.message != WM_QUIT) {
        // Poll events
        while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                break;
        }
        if (msg.message == WM_QUIT)
            break;

        // Calculate delta time
        QueryPerformanceCounter(&now);
        float deltaTime = (float)(now.QuadPart - last.QuadPart) / (float)freq.QuadPart;
        last = now;

        // Handle hotkeys
        HandleHotkeys(deltaTime);

        // Start ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // Render UI
        RenderUI();

        // Rendering
        ImGui::Render();
        const float clear_color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0); // VSync
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    // Close process handle
    if (g_gameHandle != NULL) {
        CloseHandle(g_gameHandle);
        g_gameHandle = NULL;
    }

    CleanupDeviceD3D();
    DestroyWindow(hwnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}
