# 🔒 РУКОВОДСТВО ПО СЕРТИФИКАТАМ И МЕТАДАННЫМ

## Что было добавлено

### 1. **resource.rc** - Метаданные файла
Содержит:
- Версия файла: 1.0.5.0
- Название продукта: "RE Requiem Trainer"
- Компания: "Professional Gaming Tools"
- Описание: "Game Trainer for Resident Evil Requiem"
- Copyright: "Copyright (C) 2025 Professional Gaming Tools"

### 2. **trainer.manifest** - Манифест приложения
- Совместимость: Windows 7/8/8.1/10/11
- DPI Awareness: PerMonitorV2 (правильное отображение на разных DPI)
- Права: asInvoker (не требует администратора)

### 3. **build_with_certificate.ps1** - Автоматическая сборка с подписью
Автоматически:
- Компилирует resource.rc
- Собирает trainer.exe с метаданными
- Создаёт самоподписанный сертификат
- Подписывает .exe файл (если доступен signtool)
- Сжимает UPX

---

## 🚀 Быстрый старт

### Простая сборка (с метаданными)
```powershell
.\build_with_certificate.ps1
```

Скрипт сделает всё автоматически!

---

## 📋 Проверка метаданных

### Способ 1: Через Properties
1. Правый клик на `trainer.exe`
2. Properties → Details
3. Увидите:
   - Product name: RE Requiem Trainer
   - File version: 1.0.5.0
   - Company: Professional Gaming Tools
   - Copyright: Copyright (C) 2025

### Способ 2: PowerShell
```powershell
(Get-Item .\trainer.exe).VersionInfo
```

Вывод:
```
ProductVersion   FileVersion      FileName
--------------   -----------      --------
1.0.5.0          1.0.5.0          C:\...\trainer.exe
```

---

## 🔐 Цифровая подпись

### Автоматическая подпись (самоподписанный сертификат)

Скрипт `build_with_certificate.ps1` автоматически:

1. **Создаёт сертификат:**
   - Субъект: "CN=Professional Gaming Tools, O=PGT, C=US"
   - Тип: Code Signing Certificate
   - Срок действия: 5 лет
   - Алгоритм: RSA 2048, SHA256

2. **Подписывает trainer.exe** (если установлен Windows SDK)

3. **Экспортирует сертификат** в `ProfessionalGamingTools.cer`

### Проверка подписи

```powershell
Get-AuthenticodeSignature .\trainer.exe | Format-List
```

Если подписан:
```
Status:         Valid
StatusMessage:  Signature verified.
SignerCertificate: ...
```

### Установка сертификата в Trusted Root (чтобы Windows доверяла)

**ВНИМАНИЕ:** Делайте это только на собственном ПК для тестирования!

```powershell
# Импорт в Trusted Root Certification Authorities
Import-Certificate -FilePath "ProfessionalGamingTools.cer" -CertStoreLocation Cert:\LocalMachine\Root
```

После этого Windows будет доверять вашему сертификату.

---

## 🛠️ Ручная сборка (без PowerShell)

### Шаг 1: Компиляция ресурсов
```cmd
rc.exe resource.rc
```
Создаст `resource.res`

### Шаг 2: Компиляция кода
```cmd
cl.exe /O1 /Os /MT /GS- /GR- /DNDEBUG /D_UNICODE /DUNICODE /EHsc /c main.cpp imgui.cpp ...
```

### Шаг 3: Линковка с ресурсами
```cmd
link.exe /SUBSYSTEM:WINDOWS /MACHINE:X64 /OPT:REF /OPT:ICF ^
  /OUT:trainer.exe ^
  main.obj imgui.obj ... resource.res ^
  d3d11.lib user32.lib gdi32.lib dxgi.lib psapi.lib
```

### Шаг 4: Создание сертификата (PowerShell)
```powershell
$cert = New-SelfSignedCertificate `
  -Type CodeSigningCert `
  -Subject "CN=Your Name" `
  -CertStoreLocation "Cert:\CurrentUser\My" `
  -NotAfter (Get-Date).AddYears(5)
```

### Шаг 5: Подпись
```cmd
signtool.exe sign /fd SHA256 /sha1 <THUMBPRINT> /t http://timestamp.digicert.com trainer.exe
```

Замените `<THUMBPRINT>` на отпечаток вашего сертификата.

---

## 📜 Получение настоящего сертификата

Самоподписанные сертификаты подходят для тестирования, но для публичного распространения нужен сертификат от Certificate Authority (CA).

### Популярные CA для Code Signing:

1. **DigiCert** (~$300-500/год)
   - https://www.digicert.com/signing/code-signing-certificates

2. **Sectigo (Comodo)** (~$150-300/год)
   - https://sectigo.com/ssl-certificates-tls/code-signing

3. **GlobalSign** (~$250-400/год)
   - https://www.globalsign.com/en/code-signing-certificate

### Процесс получения:
1. Подать заявку на сайте CA
2. Подтвердить личность/компанию (документы)
3. Оплатить
4. Получить сертификат (.pfx файл)
5. Установить и использовать для подписи

### Использование купленного сертификата:
```cmd
signtool.exe sign /f certificate.pfx /p PASSWORD /fd SHA256 /t http://timestamp.digicert.com trainer.exe
```

---

## 🔍 Отличия: Self-Signed vs Trusted CA

| Параметр | Self-Signed | Trusted CA |
|----------|-------------|------------|
| **Цена** | Бесплатно | $150-500/год |
| **Windows доверяет** | ❌ Нет (можно добавить вручную) | ✅ Да (автоматически) |
| **SmartScreen** | ⚠️ Предупреждение | ✅ Без предупреждений (после репутации) |
| **Публичная дистрибуция** | ❌ Не рекомендуется | ✅ Да |
| **Валидация** | Нет | Да (проверка компании) |

---

## 📦 Что видит пользователь

### С метаданными (resource.rc):
- Правый клик → Properties → Details:
  - Product name: RE Requiem Trainer
  - File version: 1.0.5.0
  - Company: Professional Gaming Tools
  - Copyright: Copyright (C) 2025

### С самоподписанным сертификатом:
- Правый клик → Properties → Digital Signatures:
  - Signer: Professional Gaming Tools
  - Status: Unknown (не доверенный)

### С trusted сертификатом:
- Properties → Digital Signatures:
  - Signer: Your Company Name
  - Status: ✅ Valid
- Windows не показывает предупреждений при запуске

---

## ⚠️ Windows SmartScreen

Даже с trusted сертификатом новые файлы могут вызывать предупреждение SmartScreen:
```
"Windows protected your PC"
```

**Причина:** Новый .exe без "репутации" в Microsoft.

**Решение:**
- Накопить репутацию (много загрузок без жалоб)
- Отправить на анализ в Microsoft (процесс может занять недели)

**Для тестирования:**
Пользователи могут нажать "More info" → "Run anyway"

---

## 🎯 Рекомендации

### Для тестирования:
✅ Используйте самоподписанный сертификат  
✅ Метаданные (resource.rc) обязательны  
✅ Подписывайте локально для проверки  

### Для публичной дистрибуции:
✅ Купите Code Signing Certificate от CA  
✅ Используйте EV Certificate (Extended Validation) для немедленного доверия  
✅ Всегда используйте timestamp сервер при подписи  
✅ Храните private key в безопасности  

---

## 🔧 Troubleshooting

### "signtool.exe not found"
**Решение:** Установите Windows SDK
```
https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/
```

### "The signature is invalid"
**Решение:** Проверьте срок действия сертификата
```powershell
$cert = Get-ChildItem Cert:\CurrentUser\My | Where-Object { $_.Subject -like "*Professional Gaming*" }
$cert.NotAfter
```

### "Resource compilation failed"
**Решение:** Проверьте, что Visual Studio установлен и `rc.exe` доступен в PATH

---

## 📚 Дополнительные ресурсы

- [Microsoft: Intro to Code Signing](https://docs.microsoft.com/en-us/windows-hardware/drivers/install/introduction-to-code-signing)
- [SignTool.exe Documentation](https://docs.microsoft.com/en-us/dotnet/framework/tools/signtool-exe)
- [Windows Authenticode](https://docs.microsoft.com/en-us/windows/win32/seccrypto/cryptography-tools)

---

## ✅ Итог

После выполнения `build_with_certificate.ps1` у вас будет:

✅ `trainer.exe` с метаданными (версия, компания, описание)  
✅ Самоподписанный сертификат для локального тестирования  
✅ `ProfessionalGamingTools.cer` для установки на других ПК  
✅ Профессионально выглядящий .exe файл  

**Запуск:**
```powershell
.\build_with_certificate.ps1
```

Готово! 🎉
