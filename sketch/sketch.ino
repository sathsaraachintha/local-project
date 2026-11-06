// NORVI X1 - Simple TFT text display
// Uses LovyanGFX with the exact pinout and panel config from the official X1 test sketch

#define LGFX_USE_V1
#include <LovyanGFX.hpp>

// ===================== LovyanGFX display setup (NORVI X1) =====================
class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ST7789 _panel;
  lgfx::Bus_SPI      _bus;
public:
  LGFX(void) {
    {
      auto c = _bus.config();
      c.spi_host    = SPI2_HOST;
      c.spi_mode    = 0;
      c.freq_write  = 27000000;
      c.freq_read   = 16000000;
      c.spi_3wire   = false;
      c.use_lock    = true;
      c.dma_channel = SPI_DMA_CH_AUTO;
      c.pin_sclk    = 12;   // SPI SCLK
      c.pin_mosi    = 11;   // SPI MOSI
      c.pin_miso    = 13;   // SPI MISO
      c.pin_dc      = 46;   // TFT DC
      _bus.config(c);
      _panel.setBus(&_bus);
    }
    {
      auto c = _panel.config();
      c.pin_cs   = 45;             // TFT CS
      c.pin_rst  = 47;             // TFT RST (shared with touch RST)
      c.pin_busy = -1;
      c.panel_width  = 240;
      c.panel_height = 320;
      c.offset_x = 0;
      c.offset_y = 0;
      c.offset_rotation = 0;
      c.readable   = false;
      c.invert     = true;          // panel inversion ON
      c.rgb_order  = false;
      c.dlen_16bit = false;
      c.bus_shared = true;
      _panel.config(c);
    }
    setPanel(&_panel);
  }
};
LGFX tft;

#ifndef TFT_BLACK
#define TFT_BLACK   0x0000
#define TFT_WHITE   0xFFFF
#define TFT_RED     0xF800
#define TFT_GREEN   0x07E0
#define TFT_BLUE    0x001F
#define TFT_YELLOW  0xFFE0
#define TFT_CYAN    0x07FF
#endif
// ==================================================================

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("NORVI X1 TFT text demo starting...");

  tft.init();
  tft.setRotation(0);          // 0 = portrait 240x320
  tft.fillScreen(TFT_BLACK);

  // Title
  tft.setTextColor(TFT_CYAN);
  tft.setTextSize(2);
  tft.setCursor(20, 40);
  tft.println("NORVI X1");

  // Main message
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(20, 100);
  tft.println("Hello from");
  tft.setCursor(20, 130);
  tft.println("the TFT!");

  // Status line
  tft.setTextColor(TFT_GREEN);
  tft.setTextSize(1);
  tft.setCursor(20, 200);
  tft.println("Display OK");

  Serial.println("Text written to TFT");
}

void loop() {
  // Nothing needed - static text stays on screen
  delay(1000);
}
