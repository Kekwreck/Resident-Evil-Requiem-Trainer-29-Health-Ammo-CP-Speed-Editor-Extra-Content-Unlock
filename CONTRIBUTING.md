# Contributing to RE Requiem Trainer

First off, thank you for considering contributing to RE Requiem Trainer! 🎉

## 📋 Table of Contents

- [Code of Conduct](#code-of-conduct)
- [How Can I Contribute?](#how-can-i-contribute)
- [Development Setup](#development-setup)
- [Pull Request Process](#pull-request-process)
- [Coding Standards](#coding-standards)
- [Commit Messages](#commit-messages)

---

## Code of Conduct

This project adheres to a Code of Conduct. By participating, you are expected to uphold this code.

**Be respectful, inclusive, and constructive.**

---

## How Can I Contribute?

### 🐛 Reporting Bugs

Before creating bug reports, please check existing issues. When creating a bug report, include:

- **Clear title and description**
- **Steps to reproduce**
- **Expected vs actual behavior**
- **Your environment** (OS, trainer version, game version)
- **Screenshots** if applicable

### ✨ Suggesting Features

Feature requests are welcome! Include:

- **Use case** - Why is this feature needed?
- **Proposed solution** - How should it work?
- **Alternatives** - Other options you've considered

### 💻 Code Contributions

1. **Fork the repository**
2. **Create a feature branch**
   ```bash
   git checkout -b feature/my-new-feature
   ```
3. **Make your changes**
4. **Test thoroughly**
5. **Commit with clear messages**
6. **Push and create PR**

---

## Development Setup

### Prerequisites

- Visual Studio 2019/2022
- Windows SDK 10.0+
- Git

### Setup Steps

```bash
# 1. Clone your fork
git clone https://github.com/YOUR_USERNAME/resident-evil-requiem-Trainer-sourse.git
cd resident-evil-requiem-Trainer-sourse

# 2. Add upstream remote
git remote add upstream https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse.git

# 3. Create branch
git checkout -b feature/my-feature

# 4. Build
.\build_standalone.bat
```

### Build Options

```powershell
# Quick build (test)
.\build_standalone.bat

# Signed build (release)
.\build_signed_only.ps1

# Full build with certificate
.\build_with_certificate.ps1
```

---

## Pull Request Process

### Before Submitting

- [ ] Code follows project style
- [ ] All tests pass
- [ ] Documentation updated
- [ ] Commits are clear and atomic
- [ ] PR description explains changes

### PR Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Testing
How did you test these changes?

## Checklist
- [ ] Code compiles without errors
- [ ] Follows coding standards
- [ ] Documentation updated
- [ ] Tested on Windows 10/11
```

### Review Process

1. **Automated checks** run (if configured)
2. **Maintainer reviews** code
3. **Feedback addressed** by contributor
4. **Merged** when approved

---

## Coding Standards

### C++ Style

```cpp
// Use clear naming
static bool g_enabled[15] = {false};  // Good
static bool e[15] = {false};          // Bad

// Comments for complex code
// Calculate delta time for smooth animations
float deltaTime = (float)(now.QuadPart - last.QuadPart) / freq.QuadPart;

// Consistent indentation (4 spaces)
void MyFunction() {
    if (condition) {
        // Code here
    }
}
```

### File Organization

```
project/
├── main.cpp              # Main application
├── resource.rc           # Resources
├── *.md                  # Documentation
├── build_*.ps1          # Build scripts
└── .github/             # GitHub files
```

---

## Commit Messages

### Format

```
type(scope): brief description

Longer explanation if needed.

Fixes #123
```

### Types

- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation
- `style`: Formatting
- `refactor`: Code restructure
- `test`: Testing
- `chore`: Maintenance

### Examples

```bash
# Good
git commit -m "feat(ui): add draggable window support"
git commit -m "fix(process): handle UNICODE conversion correctly"
git commit -m "docs(readme): update installation steps"

# Bad
git commit -m "fixed stuff"
git commit -m "update"
```

---

## Code Review Checklist

### For Reviewers

- [ ] Code is clear and maintainable
- [ ] No security issues
- [ ] Performance is acceptable
- [ ] Documentation is updated
- [ ] Tests are included (if applicable)

### For Contributors

- [ ] Addressed all review comments
- [ ] Resolved merge conflicts
- [ ] Re-tested after changes
- [ ] Updated PR description

---

## Areas Needing Help

### High Priority

- 🔍 Real memory address finding for RE Requiem
- 🧪 Testing on different Windows versions
- 📖 Documentation improvements

### Medium Priority

- 🌐 Multi-language support (RU, CN)
- 🎨 UI improvements
- ⚙️ Configuration system

### Low Priority

- 🔄 Auto-update system
- 📊 Usage analytics (privacy-respecting)
- 🎮 Support for other RE games

---

## Getting Help

### Questions?

- 💬 [GitHub Discussions](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/discussions)
- 📧 Email: [your-email]
- 💭 Discord: [your-server]

### Resources

- [ImGui Documentation](https://github.com/ocornut/imgui)
- [DirectX 11 Guide](https://docs.microsoft.com/en-us/windows/win32/direct3d11)
- [Windows API Reference](https://docs.microsoft.com/en-us/windows/win32/api/)

---

## Recognition

Contributors are recognized in:

- 📝 CHANGELOG.md
- 🙏 README.md credits section
- 🏆 GitHub contributors page

---

## License

By contributing, you agree that your contributions will be licensed under the MIT License.

---

**Thank you for contributing! 🎉**

Questions? Feel free to ask in [Discussions](https://github.com/ModEngineLabs/resident-evil-requiem-Trainer-sourse/discussions)!
