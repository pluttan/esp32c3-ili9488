#include <Arduino.h>

#define LGFX_USE_V1
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
    lgfx::Panel_ILI9488 _panel_instance;
    lgfx::Bus_SPI       _bus_instance;
    lgfx::Touch_XPT2046 _touch_instance;

public:
    LGFX(void) {
        {
            auto cfg = _bus_instance.config();
            cfg.spi_host   = SPI2_HOST;
            cfg.spi_mode   = 0;
            cfg.freq_write = 20000000;
            cfg.freq_read  = 16000000;
            cfg.pin_sclk   = 6;
            cfg.pin_mosi   = 7;
            cfg.pin_miso   = -1;
            cfg.pin_dc     = 3;
            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }
        {
            auto cfg = _panel_instance.config();
            cfg.pin_cs   = 10;
            cfg.pin_rst  = 2;
            cfg.pin_busy = -1;
            cfg.panel_width  = 320;
            cfg.panel_height = 480;
            cfg.offset_x     = 0;
            cfg.offset_y     = 0;
            cfg.readable  = false;
            cfg.invert    = false;
            cfg.rgb_order = false;
            cfg.dlen_16bit = false;
            cfg.bus_shared = true;
            _panel_instance.config(cfg);
        }
        {
            auto cfg = _touch_instance.config();
            cfg.x_min      = 300;
            cfg.x_max      = 3600;
            cfg.y_min      = 300;
            cfg.y_max      = 3600;
            cfg.pin_int    = 0;
            cfg.bus_shared = true;
            cfg.offset_rotation = 6;
            cfg.spi_host = SPI2_HOST;
            cfg.freq     = 2500000;
            cfg.pin_sclk = 6;
            cfg.pin_mosi = 7;
            cfg.pin_miso = 5;
            cfg.pin_cs   = 4;
            _touch_instance.config(cfg);
            _panel_instance.setTouch(&_touch_instance);
        }
        setPanel(&_panel_instance);
    }
};

LGFX display;

void setup() {
    Serial.begin(115200);

    // Мигнуть подсветкой 3 раза — подтвердить что код запустился
    pinMode(8, OUTPUT);
    for (int i = 0; i < 3; i++) {
        digitalWrite(8, HIGH);
        delay(200);
        digitalWrite(8, LOW);
        delay(200);
    }
    digitalWrite(8, HIGH);

    delay(1000);
    Serial.println("\n=== KMRTM35018-SPI LovyanGFX ===");

    display.init();
    Serial.printf("init: %dx%d\n", display.width(), display.height());

    display.setRotation(1);

    Serial.println("RED");
    display.fillScreen(TFT_RED);
    delay(1000);

    Serial.println("GREEN");
    display.fillScreen(TFT_GREEN);
    delay(1000);

    Serial.println("BLUE");
    display.fillScreen(TFT_BLUE);
    delay(1000);

    display.fillScreen(TFT_BLACK);
    display.setTextColor(TFT_WHITE);
    display.setTextSize(3);
    display.drawString("ILI9488 OK!", 60, 100);

    Serial.println("DONE");
}

void loop() {
    // Мигаем LED на GPIO8 каждые 2 секунды — heartbeat
    static uint32_t last = 0;
    if (millis() - last > 2000) {
        last = millis();
        digitalWrite(8, LOW);
        delay(100);
        digitalWrite(8, HIGH);
        Serial.println("heartbeat");
    }

    int32_t x, y;
    if (display.getTouch(&x, &y)) {
        display.fillCircle(x, y, 3, TFT_YELLOW);
        Serial.printf("T:%d,%d\n", x, y);
    }
    delay(10);
}
