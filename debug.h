
void debug() {
  Serial.print(F("  rX:"));
  Serial.print(ibusVar00);

  Serial.print(F("  rY:"));
  Serial.print(ibusVar01);

  Serial.print(F("  lY:"));
  Serial.print(ibusVar02);
  Serial.print(F("  lX:"));
  Serial.print(ibusVar03);
  Serial.print(F("  potiL 4:"));
  Serial.print(ibusVar04);
  Serial.print(F("  potiR 5:"));
  Serial.print(ibusVar05);

  Serial.print(F("  switch 1:"));
  Serial.print(ibusVar06);
  Serial.print(F("  switch 2:"));
  Serial.print(ibusVar07);
  Serial.print(F("  switch 3:"));
  Serial.print(ibusVar08);
  Serial.print(F("  switch 4:"));
  Serial.println(ibusVar09);
}
