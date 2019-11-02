#include <KulibinAuto_Platform.h>

//создаем объект класса KulibinAuto_Platform
//имя обекта может быть любым
//в примере это - robot

KulibinAuto_Platform robot;

void setup() {
  //никакая настройка моторов не нужна,
  //так как все рутиную работу делает библиотека
  Serial.begin(9600);
  delay(1000);
  //сбрасываем показания энкодера
  robot.resetTicksEncoder();
}

void loop() {
  //считываем тики энкодера
  Serial.println(String("L: ") + robot.getTicksEncoder(MOTOR_LEFT) + String("  R: ") + robot.getTicksEncoder(MOTOR_RIGHT));
  delay(100);
}
