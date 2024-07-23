
#define RC_STICK_RIGHT_H (byte)0
#define RC_STICK_RIGHT_V (byte)1
#define RC_STICK_LEFT_V (byte)2
#define RC_STICK_LEFT_H (byte)3
#define RC_TURN_LEFT (byte)4
#define RC_TURN_RIGHT (byte)5
#define RC_SWITCH_LEFT_OUT (byte)6
#define RC_SWITCH_LEFT_IN (byte)7
#define RC_SWITCH_RIGHT_IN (byte)8
#define RC_SWITCH_RIGHT_OUT (byte)9

void setupInput() {

  IBus->begin(Serial, IBUSBM_NOTIMER);
}

void loopInput() {

  IBus->loop();

  if (IBus->cnt_rec > 0) {
    ibusVar00 = IBus->readChannel(RC_STICK_RIGHT_H);     // Steer
    ibusVar01 = IBus->readChannel(RC_STICK_RIGHT_V);     // Drive
    ibusVar02 = IBus->readChannel(RC_STICK_LEFT_V);      // Dome vor und zurück
    ibusVar03 = IBus->readChannel(RC_STICK_LEFT_H);      // Dome drehen
    ibusVar04 = IBus->readChannel(RC_TURN_LEFT);         // (drehregler links)
    ibusVar05 = IBus->readChannel(RC_TURN_RIGHT);        // (drehregler rechts)
    ibusVar06 = IBus->readChannel(RC_SWITCH_LEFT_OUT);   // (schalter links außen)
    ibusVar07 = IBus->readChannel(RC_SWITCH_LEFT_IN);    // (schalter links innen)
    ibusVar08 = IBus->readChannel(RC_SWITCH_RIGHT_IN);   // (schalter rechts innen)
    ibusVar09 = IBus->readChannel(RC_SWITCH_RIGHT_OUT);  // (schalter rechts außen)


    driveValueHorizontal = ibusVar00;
    driveValueVertical = ibusVar01;

    headServoTarget = ibusVar02;
  }
}