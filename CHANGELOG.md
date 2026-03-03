# 📋 Changelog

All notable changes to **RE Requiem Trainer** will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [1.0.6] - 2025-01-XX 🚀

### ✨ Added - 5 NEW FEATURES!

#### 🖱️ Draggable Window
- Click and drag **anywhere** in the window to move it
- No more fixed position!

#### 🎯 Real Process Detection
- Automatically finds `ResidentEvilRequiem.exe`
- Shows **real PID** and connection status
- Cheats only work when game is detected

#### 📊 Status Bar
- Real-time **CPU** and **Memory** usage monitoring
- Updates every 0.5 seconds

#### 🆕 NEW FEATURE 1: Opacity Control (F7/F8)
- **F7** - Decrease window opacity (more transparent)
- **F8** - Increase window opacity (more solid)
- Range: 20% to 100%
- Visual feedback on change

#### 🆕 NEW FEATURE 2: Always On Top Toggle (F9)
- **F9** - Toggle always-on-top mode
- When OFF, window can go behind other windows
- Sound notification on toggle

#### 🆕 NEW FEATURE 3: Profile System (F10/F11)
- **F10** - Save current profile
- **F11** - Load saved profile
- **Ctrl+1/2/3** - Switch between 3 profiles
- Saves: all cheat states, opacity, always-on-top, timer
- Sound notification on save/load

#### 🆕 NEW FEATURE 4: Cheat Timer (F12)
- **F12** - Start/Stop 60-second timer
- Auto-disables ALL cheats when timer expires
- Visual countdown in UI
- Sound notification when timer expires

#### 🆕 NEW FEATURE 5: Minimize to Tray (Ctrl+M)
- **Ctrl+M** - Minimize trainer to system tray
- Double-click tray icon to restore
- Right-click tray icon for menu (Restore/Exit)
- Trainer continues running in background

### 🔧 Improved
- Window can now be moved by clicking anywhere (WM_NCHITTEST)
- Process check every 1 second instead of manual refresh
- Cheats only work when game process is attached
- Error messages when trying to activate cheats without game
- Better documentation and guides
- Optimized build scripts

### 📦 Build System
- Added `build_signed_only.ps1` for signed releases
- Added `build_with_certificate.ps1` for full automation
- UPX compression for smaller file size
- Static linking (/MT) for standalone distribution

### 📚 Documentation
- Added `DRAGGABLE_WINDOW.md` - Guide for window dragging feature
- Added `SIGNING_STATUS.md` - Digital signature information
- Added `CERTIFICATE_GUIDE.md` - Code signing instructions
- Added `TESTING_GUIDE.md` - Process detection testing
- Updated `README.md` with quick start guide

### 🐛 Fixed
- Fixed UNICODE/char conversion in process name detection
- Fixed process handle cleanup on exit
- Fixed UPX removing digital signature (separate builds now)

---

## [1.0.5] - 2025-01-XX

### ✨ Added
- Process detection system
- Self-signed certificate support
- Metadata in resource file

---

## [1.0.0] - 2025-01-XX (Initial Release)

### ✨ Features
- 15 Game modification cheats
- Hotkey support (Num 1-9, F1-F6)
- Master toggle (Num *)
- Always-on-top window
- Semi-transparent UI
- Dark professional theme
- ImGui-based interface
- DirectX 11 rendering
- Static linking for portability

### 🎮 Cheats
1. God Mode / Ignore Hits
2. Infinite Health
3. Infinite Ammo
4. No Reload
5. Infinite Items
6. Infinite Grenades / Throwables
7. Infinite Knife Durability
8. One Hit Kill
9. Freeze Enemies
10. Super Speed
11. Super Jump
12. No Recoil
13. No Spread
14. Game Speed Modifier
15. Infinite Money / Upgrade Points

---

## 📝 Notes

### Version Format
`MAJOR.MINOR.PATCH.BUILD`
- **MAJOR**: Breaking changes
- **MINOR**: New features
- **PATCH**: Bug fixes
- **BUILD**: Internal builds

### Release Types
- **trainer.exe**: UPX compressed, ~200 KB
- **trainer_signed.exe**: Digitally signed, ~420 KB

---

## 🔗 Links

- [GitHub Repository](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse)
- [Latest Release](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/releases/latest)
- [Download v1.0.6](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/releases/download/v1.0.6/RE_Requiem_Trainer_v1.0.6.rar)

---

## 🙏 Credits

- **ImGui**: Dear ImGui by Omar Cornut
- **DirectX 11**: Microsoft DirectX SDK
- **UPX**: Ultimate Packer for eXecutables
- **Visual Studio**: Microsoft Visual C++ Compiler

---

**For support and updates, visit our [GitHub Discussions](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/discussions)**
