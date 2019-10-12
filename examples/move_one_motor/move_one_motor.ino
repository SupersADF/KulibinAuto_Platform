#include <KulibinAuto_Platform.h>

KulibinAuto_Platform telega;

void setup() {
  telega.moveMotor(MOVE_ON, MOTOR_LEFT, 50);
  delay(1000);
  telega.moveMotor(MOVE_OFF, MOTOR_LEFT);
  delay(1000);
  telega.moveMotor(MOVE_mSECONDS, MOTOR_LEFT, 50, 2000, true);
  delay(1000);
  telega.moveMotor(MOVE_DEGREES, MOTOR_LEFT, 20, 720, true);
  delay(1000);
  telega.moveMotor(MOVE_ROTATION, MOTOR_LEFT, 20, 3, true);
  delay(1000);
}

void loop() {
}
