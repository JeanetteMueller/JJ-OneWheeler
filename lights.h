
void setupLights() {
  neoPixelLights.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)

  neoPixelLights.setBrightness(100);
}

void loopLights() {

  neoPixelLights.setPixelColor(0, colorOff);
  neoPixelLights.setPixelColor(1, colorOff);
  neoPixelLights.setPixelColor(2, colorOff);

  neoPixelLights.setPixelColor(3, colorOff);
  neoPixelLights.setPixelColor(4, colorOff);
  neoPixelLights.setPixelColor(5, colorOff);
  neoPixelLights.setPixelColor(6, colorRed);

  neoPixelLights.show();
}
