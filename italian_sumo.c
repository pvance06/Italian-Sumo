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

void forward() {
	servoLeft.write(CCW);
	servoRight.write(CW);
}

void reverse() {
	servoLeft.write(CW);
	servoRight.write(CCW);
}

void turnLeft() {
	servoLeft.write(CW);
	servoRight.write(CW);
}

void adjustLeft() {
	servoLeft.write(STOP);
	servoRight.write(CW);
}

void turnRight() {
	servoLeft.write(CCW);
	servoRight.write(CCW);
}

void adjustRight() {
	servoRight.write(STOP);
	servoLeft.write(CCW);
}

// Detection functions
void lookForLine() {
	if(digitalRead(lineSensorLeft) == HIGH) { seeLineLeft = currentPulse; }
	if(digitalRead(lineSensorRight) == HIGH) { seeLineRight = currentPulse; }
}

// Loop
int currentPulse = 0;
int seeLineLeft = 0;
int seeLineRight = 0;
int enemySeen = 0;

int timeSince(int timer, int limit) {
	return currentPulse - timer < limit;
}

void loop() {
	lookForLine();
	lookForEnemy();
	
	switch() {
		case timeSince(seeLineLeft, 20) && timeSince(seeLineRight, 20): reverse(); break;
		case timeSince(seeLineLeft, 40) && timeSince(seeLineRight, 40): turnRight(); break;
		
		case timeSince(seeLineLeft, 20): reverse(); break;
		case timeSince(seeLineLeft, 40): turnRight(); break;
		
		case timeSince(seeLineRight, 20): reverse(); break;
		case timeSince(seeLineRight, 40): turnLeft(); break;
		
		case timeSince(enemySeen, 20): /* Charge at enemy */ break;
		
		case timeSince(start, 5): forward(); break;
		case timeSince(start, 10): adjustLeft(); break;
		case timeSince(start, 15): adjustRight(); break;
		
		case currentPulse / 100 % 2 == 0: forward();
		case currentPulse / 100 % 2 == 1: turnRight();
	}
	
	currentPulse++;
}
