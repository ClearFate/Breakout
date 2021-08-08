#include "DirectionVector.h"
#include <cmath>
#include <iostream>
#include <numbers>

#define PI 3.141592653589793238462643383279502884197169399375105820974944 // it's also in std::numbers::pi in C++20 (here defined will lose precision)

double DirectionVector::vectorLength(){
	return sqrt(_x * _x + _y * _y);
}

void DirectionVector::normalize(){
	if (_x == 0 && _y == 0)
		return;  // to avoid division with 0 error

	double length = vectorLength();

	_x = 1. * _x / length;
	_y = 1. * _y / length; // make them unit vectors
}

double DirectionVector::degToRad(double kutD) {
	double kutR = (PI / 180) * kutD;
	return kutR;
}

double DirectionVector::radToDeg(double kutR) {
	double kutD = kutR * 180 / PI;
	return kutD;
}

void DirectionVector::rotateDirection(double kutD) {
	double kutR = degToRad(kutD);

	double transX = _x * cos(kutR) - _y * sin(kutR);
	double transY = _x * sin(kutR) + _y * cos(kutR);

	_x = transX;
	_y = transY;
}

void DirectionVector::invertSideDirection(){
	_x = -_x;
}

double DirectionVector::vectorDirectionAngle()
{
	double kutR = acos(_x);
	double kutD = radToDeg(kutR);

	return kutD; // returns angle where it should bounce on [0,PI] interval
}

void DirectionVector::bounce(double sideForce){  // sideforce is in interval [-1,1] -1 for max left additional rotation, 1 for right
	_y = -_y;
	normalize();

	// when ball exits it will never have angle less than 10 or greater than 170
	int maxSideRotation = 80; // pad can rotate max 80 to left and 80 deg to right (160 deg cone from pad normal)

	//rotation made from pad normal
	double exitRotationDone = abs(vectorDirectionAngle() - 90);
	double maxAdditionalRotation = maxSideRotation - exitRotationDone;

	if (sideForce < 0 && vectorDirectionAngle() < 90) {  // if ball is going down right and lands on left side of pad
		maxAdditionalRotation = 90 + maxSideRotation - vectorDirectionAngle();
	}
	else if (sideForce > 0 && vectorDirectionAngle() > 90 ) {  // if ball is going down left and lands on right side of pad
		maxAdditionalRotation = vectorDirectionAngle();
	}

	rotateDirection(maxAdditionalRotation * sideForce );
}

double DirectionVector::getUpUnitVector(){
	return _y;
}

double DirectionVector::getRightUnitVector(){
	return _x;
}



