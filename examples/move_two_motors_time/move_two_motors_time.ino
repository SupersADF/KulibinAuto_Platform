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
  //включим оба мотора на время и остановим их
  robot.moveSteer(MOVE_mSECONDS, 0, 50, 1000, true);
  //пусть оба мотора немного постоят в выключенном состоянии
  delay(1000);
}
