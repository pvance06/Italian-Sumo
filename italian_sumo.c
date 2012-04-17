#include <Servo.h>

// Initialize servos
Servo servoLeft;
Servo servoRight;
servoLeft.attach(10);
servoRight.attach(11);

const int CW = 0;
const int CCW = 180;
const int STOP = 90;

// Initialize line sensors
const int lineSensorLeft = 0;
const int lineSensorRight = 1;
pinMode(lineSensorLeft, INPUT);
pinMode(lineSensorRight, INPUT);

// Movement functions
const float DEGREES_PER_PULSE = 5.0;

void forward(int pulses = 1) {
	for(int i = 0; i < pulses; i++) {
	}
}

void reverse(int pulses = 1) {
}

void turnLeft(int degrees = 90) {
}

void adjustLeft(int pulses = 1) {
	for(int i = 0; i < pulses; i++) {
		if(i % 2 == 1) { servoLeft.write(STOP); }
		else { servoLeft.write(CCW); }
		servoRight.write(CW);
	}
}

void turnRight(int degrees = 90) {
	int pulses = degrees / DEGREES_PER_PULSE;
	servoLeft.write(CCW);
	servoRight.write(CCW);
}

void adjustRight(int pulses = 1) {
	for(int i = 0; i < pulses; i++) {
		if(i % 2 == 1) { servoRight.write(STOP); }
		else { servoRight.write(CW); }
		servoLeft.write(CCW);
	}
}

// Detection functions
int lookForLine() {
	boolean seeLineLeft = digitalRead(lineSensorLeft);
	boolean seeLineRight = digitalRead(lineSensorRight);
	
	if(seeLineLeft && seeLineRight) {
		reverse(3);
		right(135);
	}
	else if(seeLineLeft) {
		reverse(3);
		right(45);
	}
	else if(seeLineRight) {
		reverse(3);
		left(45);
	}
}

void loop() {
}