
void setupLights() {
  neoPixelLights.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)

  neoPixelLights.setBrightness(100);
}

void loopLights() {

  if (gyroIsReady) {

    for (uint16_t i = 0; i < ledCount; i++) {
      neoPixelLights.setPixelColor(i, colorOff);
    }
    neoPixelLights.setPixelColor(6, colorRed);


  }else{
    for (uint16_t i = 0; i < ledCount; i++) {
      neoPixelLights.setPixelColor(i, colorYellow);
    }
  }
  neoPixelLights.show();
}
