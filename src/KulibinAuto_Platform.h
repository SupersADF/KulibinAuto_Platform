#include <Arduino.h>
// #include 

#define MOVE_ON 		0
#define MOVE_OFF 		1
#define MOVE_mSECONDS	2
#define MOVE_DEGREES	3
#define MOVE_ROTATION	4

#define MOTOR_LEFT		1
#define MOTOR_RIGHT		2

#define COMPARE_EQUAL					1
#define COMPARE_NOT_EQUAL				2
#define COMPARE_GREATER					3
#define COMPARE_GREATER_OR_EQUAL		4
#define COMPARE_LESS					5
#define COMPARE_LESS_OR_OR_EQUAL		6

class KulibinAuto_Platform {
public:
	KulibinAuto_Platform(uint8_t enA, uint8_t enB, uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t enc1, uint8_t enc2);
	KulibinAuto_Platform();

	int32_t getDegree(uint8_t motor);
	void resetDegree(uint8_t motor = 3);

	int32_t getTicksEncoder(uint8_t motor);
	void resetTicksEncoder(uint8_t motor = 3);

	void moveSteer(uint8_t mode, int8_t steer = 0, int8_t power = 0, int16_t mode_value = 0, uint8_t stop = false);
	void moveTank(uint8_t mode, int8_t powerLeft = 0, int8_t powerRight = 0, int16_t mode_value = 0, uint8_t stop = false);
	void moveMotor(uint8_t mode, uint8_t motor, int8_t power = 0, int16_t mode_value = 0, uint8_t stop = false);

	void __callBackInterrupt0(void);
	void __callBackInterrupt1(void);

private:

	void __moveLeftMotor(int16_t power);
	void __moveRightMotor(int16_t power);

private:
	uint8_t enA_PIN = 10;
	uint8_t enB_PIN = 11;
	uint8_t in1_PIN = 12;
	uint8_t in2_PIN = 8;
	uint8_t in3_PIN = 7;
	uint8_t in4_PIN = 4;
	uint8_t enc1_PIN = 2;
	uint8_t enc2_PIN = 3;

	volatile int32_t encLeftTicks = 0;
	volatile int32_t encLeftDegree = 0;
	volatile int32_t encRightTicks = 0;
	volatile int32_t encRightDegree = 0;
};

//	2	3	4	5	6	7	8	9	10	11	12	13	A0	A1	A2	A3	A4	A5
//	x	x	x			x	x		x	x	x	
//	p 	p 	p 	s		p 	p 	bT	p 	p 	p 	bR	  	  	s1	s2	s3	s4