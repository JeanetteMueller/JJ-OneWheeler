
void writeCPUFreq() {
  uint32_t cpuFreq = getCpuFrequencyMhz();
  Serial.print("CPU speed is ");
  Serial.print(cpuFreq);
  Serial.println(" mHz");
}