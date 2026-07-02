![Header](header.png)

<div align="center">

# esp32c3-ili9488

**Драйвер дисплея ILI9488 + XPT2046 для ESP32-C3 через LovyanGFX**

[![License](https://img.shields.io/badge/license-MIT-2C2C2C?style=for-the-badge&labelColor=1E1E1E)](LICENSE)
[![ESP32-C3](https://img.shields.io/badge/ESP32--C3-RISC--V-2C2C2C?style=for-the-badge&logo=espressif&labelColor=1E1E1E)]()
[![LovyanGFX](https://img.shields.io/badge/LovyanGFX-1.2-2C2C2C?style=for-the-badge&labelColor=1E1E1E)]()
[![PlatformIO](https://img.shields.io/badge/PlatformIO-build-2C2C2C?style=for-the-badge&logo=platformio&labelColor=1E1E1E)]()

</div>

Минимальный драйвер и тестовая прошивка для KMRTM35018-SPI (TFT-дисплей ILI9488 320x480 с резистивным тачем XPT2046), подключённого к ESP32-C3 по SPI. Использует LovyanGFX для рендеринга и обработки касаний.

## ■ Возможности

- ❖ **Драйвер ILI9488 SPI** — TFT 320x480 на частоте записи 20 МГц через LovyanGFX
- ❖ **Тач XPT2046** — резистивный сенсорный экран с калиброванным маппингом координат
- ❖ **Самотестирование** — заливка красным/зелёным/синим + текстовое подтверждение при старте
- ❖ **Рисование касанием** — касание рисует жёлтые точки на экране в реальном времени
- ❖ **Heartbeat LED** — GPIO 8 мигает каждые 2с для подтверждения работы прошивки
- ❖ **Управление подсветкой** — GPIO 8 переключает подсветку экрана

## ■ Стек

<div align="center">

| Компонент | Технология |
|-----------|------------|
| МК | ESP32-C3 (RISC-V) |
| Дисплей | ILI9488 320x480 SPI (KMRTM35018-SPI) |
| Тач | XPT2046 resistive |
| Фреймворк | Arduino |
| GFX-библиотека | LovyanGFX 1.2 |
| Сборка | PlatformIO |

</div>

## ■ Подключение SPI

<div align="center">

| ESP32-C3 | Display |
|----------|---------|
| GPIO 6 | SCLK |
| GPIO 7 | MOSI (SDA) |
| GPIO 5 | MISO (touch) |
| GPIO 10 | CS (display) |
| GPIO 4 | CS (touch) |
| GPIO 3 | DC |
| GPIO 2 | RST |
| GPIO 0 | Touch INT |
| GPIO 8 | Backlight |

</div>

## ■ Запуск

```bash
# Сборка
pio run

# Прошивка
pio run -t upload

# Мониторинг serial
pio device monitor
```

При старте дисплей проходит цикл заливки R/G/B, выводит `ILI9488 OK!`, после чего принимает касания для рисования.

## ■ License

MIT © [pluttan](https://github.com/pluttan)
