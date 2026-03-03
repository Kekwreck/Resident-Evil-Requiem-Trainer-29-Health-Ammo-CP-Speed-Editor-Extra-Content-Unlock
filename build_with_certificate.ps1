# ====================================================================
# СОЗДАНИЕ САМОПОДПИСАННОГО СЕРТИФИКАТА И ПОДПИСЬ TRAINER.EXE
# ====================================================================

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Certificate & Metadata Builder" -ForegroundColor Yellow
Write-Host "========================================`n" -ForegroundColor Cyan

# ====================================================================
# ШАГ 1: КОМПИЛЯЦИЯ RESOURCE FILE
# ====================================================================

Write-Host "[1/5] Compiling resource file..." -ForegroundColor Green

# Инициализация Visual Studio environment
$vsPath = "C:\Program Files\Microsoft Visual Studio\18\Community"
cmd /c "`"$vsPath\VC\Auxiliary\Build\vcvars64.bat`" && rc.exe /nologo resource.rc"

if (Test-Path "resource.res") {
    Write-Host "✓ Resource compiled: resource.res" -ForegroundColor Green
} else {
    Write-Host "✗ Resource compilation failed!" -ForegroundColor Red
    exit 1
}

Write-Host ""

# ====================================================================
# ШАГ 2: ЗАГРУЗКА IMGUI И КОМПИЛЯЦИЯ
# ====================================================================

Write-Host "[2/5] Downloading ImGui..." -ForegroundColor Green
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
    Write-Host "✓ ImGui downloaded" -ForegroundColor Green
} else {
    Write-Host "✓ ImGui already present" -ForegroundColor Green
}

Write-Host ""
Write-Host "[3/5] Compiling with metadata..." -ForegroundColor Green

cmd /c "`"$vsPath\VC\Auxiliary\Build\vcvars64.bat`" && cl.exe /nologo /O1 /Os /MT /GS- /GR- /DNDEBUG /D_UNICODE /DUNICODE /EHsc /W2 /c main.cpp imgui.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp imgui_impl_win32.cpp imgui_impl_dx11.cpp" | Out-Null

if ($LASTEXITCODE -ne 0) {
    Write-Host "✗ Compilation failed!" -ForegroundColor Red
    exit 1
}

Write-Host "✓ Compilation successful" -ForegroundColor Green
Write-Host ""
Write-Host "[4/5] Linking with resource..." -ForegroundColor Green

# Линковка с resource.res
cmd /c "`"$vsPath\VC\Auxiliary\Build\vcvars64.bat`" && link.exe /nologo /SUBSYSTEM:WINDOWS /MACHINE:X64 /OPT:REF /OPT:ICF /MANIFEST:NO /OUT:trainer.exe main.obj imgui.obj imgui_draw.obj imgui_tables.obj imgui_widgets.obj imgui_impl_win32.obj imgui_impl_dx11.obj resource.res d3d11.lib user32.lib gdi32.lib dxgi.lib psapi.lib" | Out-Null

if (-not (Test-Path "trainer.exe")) {
    Write-Host "✗ Linking failed!" -ForegroundColor Red
    exit 1
}

Write-Host "✓ Linking successful" -ForegroundColor Green
Write-Host ""

# Cleanup
Remove-Item *.obj -Force -ErrorAction SilentlyContinue

# ====================================================================
# ШАГ 3: СОЗДАНИЕ САМОПОДПИСАННОГО СЕРТИФИКАТА
# ====================================================================

Write-Host "[5/5] Creating self-signed certificate..." -ForegroundColor Green

$certName = "Professional Gaming Tools"
$certSubject = "CN=Professional Gaming Tools, O=PGT, C=US"

# Проверка существующего сертификата
$existingCert = Get-ChildItem -Path Cert:\CurrentUser\My | Where-Object { $_.Subject -eq $certSubject } | Select-Object -First 1

if ($existingCert) {
    Write-Host "✓ Certificate already exists: $($existingCert.Thumbprint)" -ForegroundColor Yellow
    $cert = $existingCert
} else {
    # Создание нового сертификата
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
    
    Write-Host "✓ Certificate created: $($cert.Thumbprint)" -ForegroundColor Green
}

# Экспорт сертификата в .cer файл
$certPath = Join-Path (Get-Location) "ProfessionalGamingTools.cer"
Export-Certificate -Cert $cert -FilePath $certPath -Type CERT | Out-Null
Write-Host "✓ Certificate exported: ProfessionalGamingTools.cer" -ForegroundColor Green

Write-Host ""

# ====================================================================
# ШАГ 4: ПОДПИСЬ TRAINER.EXE
# ====================================================================

Write-Host "Signing trainer.exe..." -ForegroundColor Cyan

# Поиск signtool.exe
$signtoolPath = Get-ChildItem -Path "C:\Program Files (x86)\Windows Kits" -Recurse -Filter "signtool.exe" -ErrorAction SilentlyContinue | Select-Object -First 1 -ExpandProperty FullName

if (-not $signtoolPath) {
    Write-Host "⚠ signtool.exe not found - skipping digital signature" -ForegroundColor Yellow
    Write-Host "  Install Windows SDK to enable code signing" -ForegroundColor Gray
} else {
    # Подпись файла
    & $signtoolPath sign /fd SHA256 /sha1 $cert.Thumbprint /t http://timestamp.digicert.com /v trainer.exe 2>&1 | Out-Null
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "✓ trainer.exe signed successfully!" -ForegroundColor Green
    } else {
        Write-Host "⚠ Signing failed (non-critical)" -ForegroundColor Yellow
    }
}

Write-Host ""

# ====================================================================
# ШАГ 5: UPX COMPRESSION
# ====================================================================

Write-Host "Compressing with UPX..." -ForegroundColor Cyan

if (Test-Path "upx.exe") {
    .\upx.exe --ultra-brute --lzma trainer.exe 2>&1 | Select-Object -Last 6
    Write-Host "✓ Compression complete" -ForegroundColor Green
} else {
    Write-Host "⚠ UPX not found - skipping compression" -ForegroundColor Yellow
}

Write-Host ""

# ====================================================================
# ФИНАЛЬНАЯ ИНФОРМАЦИЯ
# ====================================================================

Write-Host "========================================" -ForegroundColor Green
Write-Host "BUILD COMPLETE!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Green
Write-Host ""

$fileSize = (Get-Item "trainer.exe").Length / 1KB
Write-Host "📦 trainer.exe: $([math]::Round($fileSize, 2)) KB" -ForegroundColor Cyan

# Проверка метаданных
Write-Host ""
Write-Host "📋 File Properties:" -ForegroundColor Yellow
$versionInfo = (Get-Item "trainer.exe").VersionInfo
Write-Host "  Product Name:    $($versionInfo.ProductName)" -ForegroundColor White
Write-Host "  File Version:    $($versionInfo.FileVersion)" -ForegroundColor White
Write-Host "  Company:         $($versionInfo.CompanyName)" -ForegroundColor White
Write-Host "  Description:     $($versionInfo.FileDescription)" -ForegroundColor White
Write-Host "  Copyright:       $($versionInfo.LegalCopyright)" -ForegroundColor White

# Проверка подписи
Write-Host ""
Write-Host "🔒 Digital Signature:" -ForegroundColor Yellow
$signature = Get-AuthenticodeSignature "trainer.exe"
if ($signature.Status -eq "Valid") {
    Write-Host "  Status: ✓ Signed & Valid" -ForegroundColor Green
    Write-Host "  Signer: $($signature.SignerCertificate.Subject)" -ForegroundColor White
} elseif ($signature.Status -eq "NotSigned") {
    Write-Host "  Status: Not signed (signtool not available)" -ForegroundColor Gray
} else {
    Write-Host "  Status: $($signature.Status)" -ForegroundColor Yellow
}

Write-Host ""
Write-Host "========================================" -ForegroundColor Green
Write-Host ""
Write-Host "✨ Ready to use: .\trainer.exe" -ForegroundColor Cyan
Write-Host ""

# Cleanup
Remove-Item imgui*.cpp, imgui*.h, imstb*.h, imconfig.h -Force -ErrorAction SilentlyContinue

Write-Host "Press any key to exit..."
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
