
uint8_t bar_backLeft = 0;
uint8_t bar_backRight = 12;
uint8_t bar_frontRight = 24;
uint8_t bar_frontLeft = 36;

uint8_t eye_start = 48;

void setupLights() {
  FastLED.addLeds<NEOPIXEL, lightsPin>(leds, ledCount);
  FastLED.setBrightness(generalLightsBrightness);

  for (uint16_t i = 0; i < ledCount; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void setBar(uint8_t start, uint32_t color) {
  for (uint16_t i = start; i < start + barLightsCount; i++) {
    leds[i] = color;
  }
}

void setEye(uint32_t color) {
  // for (uint16_t i = eye_start; i < eye_start + eyeLedCount; i++) {
  //   leds[i] = colorOff;
  // }
  // for (uint16_t i = eye_start; i < eye_start + eyeLightsCount; i++) {
  //   leds[i] = color;
  // }

  leds[eye_start + 2] = color;
}

void loopLights() {

  if (gyroIsReady) {

    for (uint16_t i = 0; i < ledCount; i++) {

      leds[i] = CRGB::Black;
    }

    setBar(bar_backLeft, CRGB::Red);
    setBar(bar_backRight, CRGB::Red);
    setBar(bar_frontRight, CRGB::Red);
    setBar(bar_frontLeft, CRGB::Red);

    setEye(CRGB::Red);

    FastLED.show();

  } else {
    for (uint16_t i = 0; i < ledCount; i++) {

      leds[i] = CRGB::Yellow;
    }
    FastLED.show();
  }
  
}
