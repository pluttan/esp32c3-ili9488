<div align="center">

# esp32c3-ili9488

**ILI9488 + XPT2046 display driver for ESP32-C3 via LovyanGFX**

</div>

Minimal driver and test firmware for KMRTM35018-SPI (ILI9488 320x480 TFT display with XPT2046 resistive touch) connected to ESP32-C3 over SPI. Uses LovyanGFX for rendering and touch input.

## ■ Features

- ❖ **ILI9488 SPI driver** — 320x480 TFT at 20 MHz write clock via LovyanGFX
- ❖ **XPT2046 touch** — resistive touchscreen with calibrated coordinate mapping
- ❖ **Self-test sequence** — red/green/blue fill + text confirmation on startup
- ❖ **Touch drawing** — touch input draws yellow dots on screen in real time
- ❖ **Heartbeat LED** — GPIO 8 blinks every 2s to confirm firmware is alive
- ❖ **Backlight control** — GPIO 8 toggled for screen backlight

## ■ Stack

<div align="center">

| Component | Technology |
|-----------|------------|
| MCU | ESP32-C3 (RISC-V) |
| Display | ILI9488 320x480 SPI (KMRTM35018-SPI) |
| Touch | XPT2046 resistive |
| Framework | Arduino |
| GFX library | LovyanGFX 1.2 |
| Build | PlatformIO |

</div>

## ■ How It Works

```
1. MCU initializes the SPI bus and configures the ILI9488 display via LovyanGFX.
2. XPT2046 touch controller starts on the same SPI bus with a dedicated CS pin.
3. On boot, the display runs a self-test: red, green, and blue full-screen fills, then prints "ILI9488 OK!".
4. Touch input via XPT2046 (GPIO 0 = Touch INT) draws a yellow dot at the calibrated screen coordinates on detection.
5. GPIO 8 blinks every 2 s as a heartbeat to confirm the firmware loop is alive.
```

## ■ Usage

```bash
# Build
pio run

# Upload
pio run -t upload

# Monitor serial
pio device monitor
```

On boot the display cycles through R/G/B fills, prints `ILI9488 OK!`, then accepts touch input for drawing.

## ■ SPI Wiring

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

## ■ License

MIT © [pluttan](https://github.com/pluttan)
