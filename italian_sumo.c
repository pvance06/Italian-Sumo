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

// Initialize distance sensors
#define distSensorLeft A0
#define distSensorRight A1

const int THRESHOLD_FAR = 30;
const int THRESHOLD_CLOSE = 50;

// Movement functions
const float DEGREES_PER_PULSE = 5.0;

void forward() {
	servoLeft.write(CW);
	servoRight.write(CCW);
}

void reverse() {
	servoLeft.write(CCW);
	servoRight.write(CW);
}

void turnLeft() {
	servoLeft.write(CW);
	servoRight.write(CW);
}

void adjustLeft() {
	servoLeft.write(CW);
	servoRight.write(STOP);
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
int seeLineLeft = 0;
int seeLineRight = 0;
void lookForLine() {
	if(digitalRead(lineSensorLeft) == HIGH) { seeLineLeft = currentPulse; }
	if(digitalRead(lineSensorRight) == HIGH) { seeLineRight = currentPulse; }
}

int seeEnemyLeft_far = 0;
int seeEnemyLeft_close = 0;
int seeEnemyRight_far = 0;
int seeEnemyRight_close = 0;
void lookForEnemy() {
	int leftLevel = analogRead(distSensorLeft) / 10;
	switch() {
		case leftLevel > THRESHOLD_NEAR:
			seeEnemyLeft_close = currentPulse;
			break;
		case leftLevel > THRESHOLD_FAR:
			seeEnemyLeft_far = currentPulse;
			break;
	}
	
	int rightLevel = analogRead(distSensorRight) / 10;
	switch() {
		case rightLevel > THRESHOLD_CLOSE:
			seeEnemyRight_close = currentPulse;
			break;
		case rightLevel > THRESHOLD_FAR:
			seeEnemyRight_far = currentPulse;
			break;
	}
}

// Loop
int currentPulse = 0;

int timeSince(int timer, int limit) {
	return currentPulse - timer < limit;
}

void loop() {
	lookForLine();
	if(!timeSince(seeEnemyLeft_close, 10) && !timeSince(seeEnemyRight_close, 10)) {
		lookForEnemy();
	}
	
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
