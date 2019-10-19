
#include <KulibinAuto_Platform.h>

KulibinAuto_Platform *pointerToClass_encLeft;

static void outsideInterruptHandler_encLeft(void) { 
 	pointerToClass_encLeft->__callBackInterrupt0(); 
}

KulibinAuto_Platform *pointerToClass_encRight;

static void outsideInterruptHandler_encRight(void) { 
 	pointerToClass_encRight->__callBackInterrupt1(); 
}

KulibinAuto_Platform::KulibinAuto_Platform(uint8_t enA, uint8_t enB, uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t enc1, uint8_t enc2) {
	enA_PIN = enA;
	enB_PIN = enB;
	in1_PIN = in1;
	in2_PIN = in2;
	in3_PIN = in3;
	in4_PIN = in4;
	enc1_PIN = enc1;
	enc2_PIN = enc2;

	pinMode(enA_PIN, OUTPUT);
	pinMode(enB_PIN, OUTPUT);
	pinMode(in1_PIN, OUTPUT);
	pinMode(in2_PIN, OUTPUT);
	pinMode(in3_PIN, OUTPUT);
	pinMode(in4_PIN, OUTPUT);
}

KulibinAuto_Platform::KulibinAuto_Platform() {
	pinMode(enA_PIN, OUTPUT);
	pinMode(enB_PIN, OUTPUT);
	pinMode(in1_PIN, OUTPUT);
	pinMode(in2_PIN, OUTPUT);
	pinMode(in3_PIN, OUTPUT);
	pinMode(in4_PIN, OUTPUT);

	pinMode(enc1_PIN, INPUT);
	pinMode(enc2_PIN, INPUT);

	pointerToClass_encLeft = this;
	pointerToClass_encRight = this;
  	attachInterrupt(digitalPinToInterrupt(enc1_PIN), outsideInterruptHandler_encLeft, CHANGE);
  	attachInterrupt(digitalPinToInterrupt(enc2_PIN), outsideInterruptHandler_encRight, CHANGE);
}

int32_t KulibinAuto_Platform::getDegree(uint8_t motor) {
	if (motor == MOTOR_LEFT) {
		return encLeftDegree;
	} else if (motor == MOTOR_RIGHT) {
		return encRightDegree;
	}	
}
void KulibinAuto_Platform::resetDegree(uint8_t motor = 3) {
	if (motor == 3) {
		encLeftDegree = 0;
		encRightDegree = 0;
	} else if (motor == MOTOR_LEFT) {
		encLeftDegree = 0;
	} else if (motor == MOTOR_RIGHT) {
		encRightDegree = 0;
	}
}

int32_t KulibinAuto_Platform::getTicksEncoder(uint8_t motor) {
	if (motor == MOTOR_LEFT) {
		return encLeftTicks;
	} else if (motor == MOTOR_RIGHT) {
		return encRightTicks;
	}	
}
void KulibinAuto_Platform::resetTicksEncoder(uint8_t motor = 3) {
	if (motor == 3) {
		encLeftTicks = 0;
		encRightTicks = 0;
	} else if (motor == MOTOR_LEFT) {
		encLeftTicks = 0;
	} else if (motor == MOTOR_RIGHT) {
		encRightTicks = 0;
	}
}

void KulibinAuto_Platform::moveTank(uint8_t mode, int8_t powerLeft = 0, int8_t powerRight = 0, int16_t mode_value = 0, uint8_t stop = false) {
	if (mode == MOVE_ON) {
		__moveLeftMotor(powerLeft);
		__moveRightMotor(powerRight);
	} else if (mode == MOVE_OFF) {
		__moveLeftMotor(powerLeft);
		__moveRightMotor(powerRight);
	} else if (mode == MOVE_mSECONDS) {
		uint32_t time_start = millis();
		__moveLeftMotor(powerLeft);
		__moveRightMotor(powerRight);
		while(millis() - time_start < mode_value) {}
		if (stop == true) {
			__moveLeftMotor(0);
			__moveRightMotor(0);
		}
	} else if (mode == MOVE_DEGREES) {
		uint32_t degree_average_ = (uint32_t)((getDegree(MOTOR_LEFT) + getDegree(MOTOR_RIGHT)) / 2);
		__moveLeftMotor(powerLeft);
		__moveRightMotor(powerRight);
		while((getDegree(MOTOR_LEFT) + getDegree(MOTOR_RIGHT)) / 2 - degree_average_ < mode_value) {}
		if (stop == true) {
			__moveLeftMotor(0);
			__moveRightMotor(0);
		}
	} else if (mode == MOVE_ROTATION) {
		uint32_t degree_average = (getDegree(MOTOR_LEFT) + getDegree(MOTOR_RIGHT)) / 2;
		__moveLeftMotor(powerLeft);
		__moveRightMotor(powerRight);
		while((getDegree(MOTOR_LEFT) + getDegree(MOTOR_RIGHT)) / 2 - degree_average < mode_value * 360) {}
		if (stop == true) {
			__moveLeftMotor(0);
			__moveRightMotor(0);
		}
	}
}
void KulibinAuto_Platform::moveSteer(uint8_t mode, int8_t steer = 0, int8_t power = 0, int16_t mode_value = 0, uint8_t stop = false) {
	if (mode == MOVE_ON) {
		__moveLeftMotor(power + steer * 2);
		__moveRightMotor(power - steer * 2);
	} else if (mode == MOVE_OFF) {
		__moveLeftMotor(power + steer * 2);
		__moveRightMotor(power - steer * 2);
	} else if (mode == MOVE_mSECONDS) {
		uint32_t time_start = millis();
		__moveLeftMotor(power + steer * 2);
		__moveRightMotor(power - steer * 2);
		while(millis() - time_start < mode_value) {}
		if (stop == true) {
			__moveLeftMotor(0);
			__moveRightMotor(0);
		}
	} else if (mode == MOVE_DEGREES) {
		uint32_t degree_average_ = (uint32_t)((getDegree(MOTOR_LEFT) + getDegree(MOTOR_RIGHT)) / 2);
		__moveLeftMotor(power + steer * 2);
		__moveRightMotor(power - steer * 2);
		while((getDegree(MOTOR_LEFT) + getDegree(MOTOR_RIGHT)) / 2 - degree_average_ < mode_value) {}
		if (stop == true) {
			__moveLeftMotor(0);
			__moveRightMotor(0);
		}
	} else if (mode == MOVE_ROTATION) {
		uint32_t degree_average = (getDegree(MOTOR_LEFT) + getDegree(MOTOR_RIGHT)) / 2;
		__moveLeftMotor(power + steer * 2);
		__moveRightMotor(power - steer * 2);
		while((getDegree(MOTOR_LEFT) + getDegree(MOTOR_RIGHT)) / 2 - degree_average < mode_value * 360) {}
		if (stop == true) {
			__moveLeftMotor(0);
			__moveRightMotor(0);
		}
	}
}
void KulibinAuto_Platform::moveMotor(uint8_t mode, uint8_t motor, int8_t power = 0, int16_t mode_value = 0, uint8_t stop = false) {
	if (mode == MOVE_ON) {
		if (motor == MOTOR_LEFT) {
				__moveLeftMotor(power);
		} else if (motor == MOTOR_RIGHT) {
			__moveRightMotor(power);
		}
	} else if (mode == MOVE_OFF) {
		if (motor == MOTOR_LEFT) {
			__moveLeftMotor(0);
		} else if (motor == MOTOR_RIGHT) {
			__moveRightMotor(0);
		}
	} else if (mode == MOVE_mSECONDS) {
		uint32_t time_start = millis();
		if (motor == MOTOR_LEFT) {
			__moveLeftMotor(power);
		} else if (motor == MOTOR_RIGHT) {
			__moveRightMotor(power);
		}
		while(millis() - time_start < mode_value) {}
		if (stop == true) {
			if (motor == MOTOR_LEFT) {
				__moveLeftMotor(0);
			} else if (motor == MOTOR_RIGHT) {
				__moveRightMotor(0);
			}
		}
	} else if (mode == MOVE_DEGREES) {
		int32_t degree_ = 0;
		if (motor == MOTOR_LEFT) {
			__moveLeftMotor(power);
			degree_ = getDegree(MOTOR_LEFT);
			while(getDegree(MOTOR_LEFT) - degree_ < mode_value) {}
		} else if (motor == MOTOR_RIGHT) {
			__moveRightMotor(power);
			degree_ = getDegree(MOTOR_RIGHT);
			while(getDegree(MOTOR_RIGHT) - degree_ < mode_value) {}
		}
		if (stop == true) {
			if (motor == MOTOR_LEFT) {
				__moveLeftMotor(0);
			} else if (motor == MOTOR_RIGHT) {
				__moveRightMotor(0);
			}
		}
	} else if (mode == MOVE_ROTATION) {
		int32_t degree_ = 0;
		if (motor == MOTOR_LEFT) {
			__moveLeftMotor(power);
			degree_ = getDegree(MOTOR_LEFT);
			while(getDegree(MOTOR_LEFT) - degree_ < mode_value * 360) {}
		} else if (motor == MOTOR_RIGHT) {
			__moveRightMotor(power);
			degree_ = getDegree(MOTOR_RIGHT);
			while(getDegree(MOTOR_RIGHT) - degree_ < mode_value * 360) {}
		}
		if (stop == true) {
			if (motor == MOTOR_LEFT) {
				__moveLeftMotor(0);
			} else if (motor == MOTOR_RIGHT) {
				__moveRightMotor(0);
			}
		}
	}
}

//private 

void KulibinAuto_Platform::__callBackInterrupt0(void) {
	encLeftTicks++;
	encLeftDegree += 9;
}

void KulibinAuto_Platform::__callBackInterrupt1(void) {
	encRightTicks++;
	encRightDegree += 9;
}

void KulibinAuto_Platform::__moveLeftMotor(int16_t power) {
	if (power < -100) {
		power = -100;
	} else if (power > 100) {
		power = 100;
	}
	if (power < 0) {
		uint8_t motorPower = (uint8_t)(power * -2.5);
		analogWrite(enB_PIN, motorPower);
		digitalWrite(in3_PIN, LOW);
		digitalWrite(in4_PIN, HIGH);
	} else if (power > 0) {
		uint8_t motorPower = (uint8_t)(power * 2.5);
		analogWrite(enB_PIN, motorPower);
		digitalWrite(in3_PIN, HIGH);
		digitalWrite(in4_PIN, LOW);
	} else if (power == 0) {
		analogWrite(enB_PIN, 255);
		digitalWrite(in3_PIN, HIGH);
		digitalWrite(in4_PIN, HIGH);
	}
}

void KulibinAuto_Platform::__moveRightMotor(int16_t power) {
	if (power < -100) {
		power = -100;
	} else if (power > 100) {
		power = 100;
	}
	if (power < 0) {
		uint8_t motorPower = (uint8_t)(power * -2.5);
		analogWrite(enA_PIN, motorPower);
		digitalWrite(in1_PIN, HIGH);
		digitalWrite(in2_PIN, LOW);
	} else if (power > 0) {
		uint8_t motorPower = (uint8_t)(power * 2.5);
		analogWrite(enA_PIN, motorPower);
		digitalWrite(in1_PIN, LOW);
		digitalWrite(in2_PIN, HIGH);
	} else if (power == 0) {
		analogWrite(enA_PIN, 255);
		digitalWrite(in1_PIN, HIGH);
		digitalWrite(in2_PIN, HIGH);
	}
}
