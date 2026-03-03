# ====================================================================
# СБОРКА И ПОДПИСЬ БЕЗ UPX (для дистрибуции)
# ====================================================================

Write-Host "`n" "=" * 70 -ForegroundColor Cyan
Write-Host "СБОРКА ПОДПИСАННОЙ ВЕРСИИ (БЕЗ UPX)" -ForegroundColor Yellow
Write-Host "=" * 70 -ForegroundColor Cyan
Write-Host ""

# ====================================================================
# ШАГ 1: КОМПИЛЯЦИЯ
# ====================================================================

Write-Host "[1/4] Компиляция resource.rc..." -ForegroundColor Green
$vsPath = "C:\Program Files\Microsoft Visual Studio\18\Community"
cmd /c "`"$vsPath\VC\Auxiliary\Build\vcvars64.bat`" && rc.exe /nologo resource.rc" | Out-Null

if (-not (Test-Path "resource.res")) {
    Write-Host "✗ Resource compilation failed!" -ForegroundColor Red
    exit 1
}
Write-Host "✓ Resource compiled" -ForegroundColor Green

Write-Host ""
Write-Host "[2/4] Загрузка ImGui..." -ForegroundColor Green
$ProgressPreference = 'SilentlyContinue'

if (-not (Test-Path "imgui.h")) {
    Invoke-WebRequest -Uri "https://github.com/ocornut/imgui/archive/refs/tags/v1.90.1.zip" -OutFile "imgui.zip" -UseBasicParsing
    Expand-Archive -Path "imgui.zip" -DestinationPath "." -Force
    Copy-Item "imgui-1.90.1\*.cpp" -Destination "." -Force
    Copy-Item "imgui-1.90.1\*.h" -Destination "." -Force
    Copy-Item "imgui-1.90.1\backends\imgui_impl_win32.*" -Destination "." -Force
    Copy-Item "imgui-1.90.1\backends\imgui_impl_dx11.*" -Destination "." -Force
    Remove-Item "imgui.zip" -Force
    Remove-Item "imgui-1.90.1" -Recurse -Force
}
Write-Host "✓ ImGui ready" -ForegroundColor Green

Write-Host ""
Write-Host "Компиляция исходников..." -ForegroundColor Cyan
cmd /c "`"$vsPath\VC\Auxiliary\Build\vcvars64.bat`" && cl.exe /nologo /O1 /Os /MT /GS- /GR- /DNDEBUG /D_UNICODE /DUNICODE /EHsc /W2 /c main.cpp imgui.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp imgui_impl_win32.cpp imgui_impl_dx11.cpp" | Out-Null

if ($LASTEXITCODE -ne 0) {
    Write-Host "✗ Compilation failed!" -ForegroundColor Red
    exit 1
}
Write-Host "✓ Compilation successful" -ForegroundColor Green

Write-Host ""
Write-Host "Линковка с метаданными..." -ForegroundColor Cyan
cmd /c "`"$vsPath\VC\Auxiliary\Build\vcvars64.bat`" && link.exe /nologo /SUBSYSTEM:WINDOWS /MACHINE:X64 /OPT:REF /OPT:ICF /MANIFEST:NO /OUT:trainer_signed.exe main.obj imgui.obj imgui_draw.obj imgui_tables.obj imgui_widgets.obj imgui_impl_win32.obj imgui_impl_dx11.obj resource.res d3d11.lib user32.lib gdi32.lib dxgi.lib psapi.lib" | Out-Null

if (-not (Test-Path "trainer_signed.exe")) {
    Write-Host "✗ Linking failed!" -ForegroundColor Red
    exit 1
}
Write-Host "✓ Linking successful" -ForegroundColor Green

# Cleanup
Remove-Item *.obj -Force -ErrorAction SilentlyContinue

Write-Host ""

# ====================================================================
# ШАГ 2: СОЗДАНИЕ/ПОИСК СЕРТИФИКАТА
# ====================================================================

Write-Host "[3/4] Проверка сертификата..." -ForegroundColor Green
$certSubject = "CN=Professional Gaming Tools, O=PGT, C=US"
$cert = Get-ChildItem -Path Cert:\CurrentUser\My | Where-Object { $_.Subject -eq $certSubject } | Select-Object -First 1

if (-not $cert) {
    Write-Host "Создание самоподписанного сертификата..." -ForegroundColor Yellow
    $cert = New-SelfSignedCertificate `
        -Type CodeSigningCert `
        -Subject $certSubject `
        -FriendlyName "Professional Gaming Tools Code Signing" `
        -CertStoreLocation "Cert:\CurrentUser\My" `
        -NotAfter (Get-Date).AddYears(5) `
        -KeyExportPolicy Exportable `
        -KeySpec Signature `
        -KeyLength 2048 `
        -KeyAlgorithm RSA `
        -HashAlgorithm SHA256
    Write-Host "✓ Сертификат создан" -ForegroundColor Green
} else {
    Write-Host "✓ Сертификат найден" -ForegroundColor Green
}

Write-Host "  Thumbprint: $($cert.Thumbprint)" -ForegroundColor White
Write-Host "  Expires: $($cert.NotAfter.ToString('yyyy-MM-dd'))" -ForegroundColor White

# Экспорт сертификата
Export-Certificate -Cert $cert -FilePath "ProfessionalGamingTools.cer" -Type CERT | Out-Null
Write-Host "✓ Сертификат экспортирован: ProfessionalGamingTools.cer" -ForegroundColor Green

Write-Host ""

# ====================================================================
# ШАГ 3: ЦИФРОВАЯ ПОДПИСЬ
# ====================================================================

Write-Host "[4/4] Цифровая подпись..." -ForegroundColor Green

# Поиск signtool
$signtool = Get-ChildItem -Path "C:\Program Files (x86)\Windows Kits" -Recurse -Filter "signtool.exe" -ErrorAction SilentlyContinue | Select-Object -First 1 -ExpandProperty FullName

if (-not $signtool) {
    Write-Host "✗ signtool.exe не найден!" -ForegroundColor Red
    Write-Host "  Установите Windows SDK: https://developer.microsoft.com/windows/downloads/windows-sdk/" -ForegroundColor Yellow
    Write-Host "  Файл собран, но НЕ подписан: trainer_signed.exe" -ForegroundColor Yellow
    exit 0
}

Write-Host "Подписываем trainer_signed.exe..." -ForegroundColor Cyan
$signResult = & $signtool sign /fd SHA256 /sha1 $cert.Thumbprint /t http://timestamp.digicert.com /v trainer_signed.exe 2>&1

if ($LASTEXITCODE -eq 0) {
    Write-Host "✓ Файл успешно подписан!" -ForegroundColor Green
} else {
    Write-Host "✗ Ошибка подписи!" -ForegroundColor Red
    Write-Host $signResult -ForegroundColor Gray
    exit 1
}

Write-Host ""

# ====================================================================
# ПРОВЕРКА РЕЗУЛЬТАТА
# ====================================================================

Write-Host "=" * 70 -ForegroundColor Green
Write-Host "✅ ПОДПИСАННАЯ ВЕРСИЯ ГОТОВА!" -ForegroundColor Green
Write-Host "=" * 70 -ForegroundColor Green
Write-Host ""

$fileSize = (Get-Item "trainer_signed.exe").Length / 1KB
Write-Host "📦 Файл: trainer_signed.exe" -ForegroundColor Cyan
Write-Host "📏 Размер: $([math]::Round($fileSize, 2)) KB (без UPX)" -ForegroundColor Cyan
Write-Host ""

Write-Host "📋 МЕТАДАННЫЕ:" -ForegroundColor Yellow
$versionInfo = (Get-Item "trainer_signed.exe").VersionInfo
Write-Host "  Product Name:    $($versionInfo.ProductName)" -ForegroundColor White
Write-Host "  File Version:    $($versionInfo.FileVersion)" -ForegroundColor White
Write-Host "  Company:         $($versionInfo.CompanyName)" -ForegroundColor White
Write-Host "  Description:     $($versionInfo.FileDescription)" -ForegroundColor White
Write-Host "  Copyright:       $($versionInfo.LegalCopyright)" -ForegroundColor White
Write-Host ""

Write-Host "🔒 ЦИФРОВАЯ ПОДПИСЬ:" -ForegroundColor Yellow
$signature = Get-AuthenticodeSignature "trainer_signed.exe"

if ($signature.Status -eq "Valid") {
    Write-Host "  ✅ Status: SIGNED & VALID" -ForegroundColor Green
    Write-Host "  Signer: $($signature.SignerCertificate.Subject)" -ForegroundColor White
    Write-Host "  Thumbprint: $($signature.SignerCertificate.Thumbprint)" -ForegroundColor Gray
    Write-Host "  Timestamp: $($signature.TimeStamperCertificate.NotBefore)" -ForegroundColor Gray
} elseif ($signature.Status -eq "UnknownError") {
    Write-Host "  ⚠️ Status: SIGNED (самоподписанный)" -ForegroundColor Yellow
    Write-Host "  Signer: $($signature.SignerCertificate.Subject)" -ForegroundColor White
    Write-Host "  Для доверия установите: Import-Certificate -FilePath ProfessionalGamingTools.cer -CertStoreLocation Cert:\LocalMachine\Root" -ForegroundColor Gray
} else {
    Write-Host "  ✗ Status: $($signature.Status)" -ForegroundColor Red
}

Write-Host ""
Write-Host "=" * 70 -ForegroundColor Green
Write-Host ""
Write-Host "✨ ГОТОВО К РАСПРОСТРАНЕНИЮ!" -ForegroundColor Cyan
Write-Host ""
Write-Host "📂 Файлы для дистрибуции:" -ForegroundColor Yellow
Write-Host "  • trainer_signed.exe     (подписанный, для публичной раздачи)" -ForegroundColor White
Write-Host "  • ProfessionalGamingTools.cer (сертификат, опционально)" -ForegroundColor White
Write-Host ""
Write-Host "▶ Проверка подписи:" -ForegroundColor Yellow
Write-Host "  Get-AuthenticodeSignature .\trainer_signed.exe | Format-List" -ForegroundColor Gray
Write-Host ""

# Cleanup
Remove-Item imgui*.cpp, imgui*.h, imstb*.h, imconfig.h -Force -ErrorAction SilentlyContinue

Write-Host "Нажмите любую клавишу для выхода..."
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
