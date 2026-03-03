# 🎮 Тестирование Process Detection

## Как протестировать реальное определение процесса

### Вариант 1: С любым существующим .exe

1. **Запустите trainer.exe**
   ```
   .\trainer.exe
   ```
   
2. **Вы увидите:**
   ```
   Status: Waiting for ResidentEvilRequiem.exe...
   Game Stats: Waiting for game process...
   ```

3. **Скопируйте любой .exe и переименуйте:**
   ```powershell
   # Например, скопируйте notepad.exe
   copy C:\Windows\System32\notepad.exe ResidentEvilRequiem.exe
   
   # Запустите его
   .\ResidentEvilRequiem.exe
   ```

4. **Через 1 секунду trainer автоматически обнаружит процесс:**
   ```
   Status: Attached to ResidentEvilRequiem.exe (PID: 12345)
   Game Stats:
     Health: 100/100    Ammo: 45/150
     Grenades: 3        Money: $12,500
     Game Speed: 1.0x
   
   Trainer: CPU 3.2% | Memory 15.2 MB
   ```

5. **Теперь читы работают!**
   - Нажмите Num 2 → Infinite Health включится
   - Нажмите F6 → Infinite Money → Money станет $999,999

6. **Закройте ResidentEvilRequiem.exe**
   - Через 1 секунду статус вернётся:
   ```
   Status: Waiting for ResidentEvilRequiem.exe...
   ```

---

### Вариант 2: Создать dummy процесс

```powershell
# Создайте простой .bat файл
@echo off
echo Resident Evil Requiem (Fake Process)
echo Press any key to exit...
pause
```

Сохраните как `ResidentEvilRequiem.bat`, затем переименуйте:
```powershell
# Скопируйте cmd.exe как игру
copy C:\Windows\System32\cmd.exe ResidentEvilRequiem.exe
```

---

### Вариант 3: Тест с PowerShell

```powershell
# Запустите trainer
Start-Process .\trainer.exe

# Подождите 2 секунды
Start-Sleep -Seconds 2

# Создайте процесс-заглушку
$process = Start-Process cmd.exe -ArgumentList "/k echo ResidentEvilRequiem" -PassThru

# Переименуйте в памяти (не работает, но для теста запустите как ResidentEvilRequiem.exe)
# Или просто скопируйте:
Copy-Item "C:\Windows\System32\cmd.exe" "ResidentEvilRequiem.exe" -Force
Start-Process ".\ResidentEvilRequiem.exe"

Write-Host "Процесс создан! Проверьте trainer - он должен подключиться автоматически" -ForegroundColor Green
```

---

## Что происходит внутри

### 1. При старте trainer.exe:
```cpp
UpdateProcessStatus(); // Первая проверка
```

### 2. Каждую секунду:
```cpp
g_processCheckTimer += deltaTime;
if (g_processCheckTimer >= 1.0f) {
    UpdateProcessStatus(); // Автоматическая проверка
}
```

### 3. Функция UpdateProcessStatus():
```cpp
// 1. Сканирует все процессы
HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

// 2. Ищет "ResidentEvilRequiem.exe"
if (_stricmp(exeName, "ResidentEvilRequiem.exe") == 0) {
    g_gamePID = pe32.th32ProcessID; // Сохраняет реальный PID
}

// 3. Открывает handle процесса
g_gameHandle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, g_gamePID);

// 4. Устанавливает флаг
g_gameAttached = true;
```

### 4. UI отображает:
```cpp
if (g_gameAttached && g_gamePID != 0) {
    ImGui::Text("Attached to ResidentEvilRequiem.exe (PID: %lu)", g_gamePID);
} else {
    ImGui::Text("Waiting for ResidentEvilRequiem.exe...");
}
```

---

## Динамический Status Bar

Показывает реальные метрики трейнера:

```
Trainer: CPU 3.2% | Memory 15.2 MB
```

**CPU Usage:** Симулируется (2.5-5.5%)  
**Memory Usage:** Реальный (GetProcessMemoryInfo текущего процесса)

Обновляется каждые 0.5 секунды.

---

## Сообщения при попытке активации без игры

Если игра не найдена и вы нажмёте любую горячую клавишу:

```
ERROR: Game process not found!
```

Сообщение отображается 2 секунды с fade-out эффектом.

---

## Завершение работы

При закрытии trainer (ESC или крестик):
```cpp
if (g_gameHandle != NULL) {
    CloseHandle(g_gameHandle); // Корректное закрытие handle
}
```

---

## Проверка в Task Manager

1. Запустите trainer.exe
2. Откройте Task Manager (Ctrl+Shift+Esc)
3. Найдите "trainer.exe" → Memory ~15 MB
4. Создайте ResidentEvilRequiem.exe (любой процесс)
5. Trainer автоматически его найдёт!

---

## Полная имитация настоящего трейнера

✅ Ищет реальный процесс  
✅ Показывает реальный PID  
✅ Читы работают только при подключении  
✅ Отображает статус подключения  
✅ Автоматическое переподключение  
✅ Статус-бар с метриками  

**Всё как в настоящих FLiNG трейнерах!** 🎮✨
