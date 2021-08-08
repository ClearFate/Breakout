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

	rotateDirection(maxAdditionalRotation * sideForce );
}

double DirectionVector::getUpUnitVector(){
	return _y;
}

double DirectionVector::getRightUnitVector(){
	return _x;
}

//void DirectionVector::rotateBounce(double steepnessInterval, Side direction)
//{
//	// to mirror it back
//	perfectBounce(Side::UP);
//
//	// now we can do calculations to find out mirrored angle
//	double bounceOffAngle;
//	double r = getVectorLength();
//	double x = moveRight;
//	double y = moveUp;
//
//	// x = r * cos(fi) => fi = acos(x/r) * pi/180
//	double fi = acos(x / r) * PI / 180;   // * PI/180 je da dobijemo stupnjeve a ne radiane
//	double angleDiff;
//
//	if (direction == Side::LEFT) {
//		bounceOffAngle = 175;
//		angleDiff = abs(bounceOffAngle - fi);
//	}
//	else if (direction == Side::RIGHT) {
//		bounceOffAngle = 5;
//		angleDiff = -abs(fi - bounceOffAngle);
//	}
//
//	double resultingAngle = steepnessInterval * angleDiff;
//
//	double newX = x * cos(resultingAngle) - y * sin(resultingAngle);
//	double newY = x * sin(resultingAngle) + y * cos(resultingAngle);
//
//	upDirection = newY;
//	rightDirection = newX;
//	normalize();
//
//}

