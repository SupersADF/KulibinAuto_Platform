#include <KulibinAuto_Platform.h>

//создаем объект класса KulibinAuto_Platform
//имя обекта может быть любым
//в примере это - robot

KulibinAuto_Platform robot;

void setup() {
  //никакая настройка моторов не нужна,
  //так как все рутиную работу делает библиотека
}

void loop() {
  //включим левый мотор на время и остановим его
  robot.moveMotor(MOVE_mSECONDS, MOTOR_LEFT, 50, 1000, true);
  //пусть мотор немного постоит в выключенном состоянии
  delay(1000);
}
