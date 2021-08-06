#include "DirectionVector.h"
#include <cmath>
#include <iostream>
#include <numbers>

#define PI 3.141592653589793238462643383279502884197169399375105820974944 // it's also in std::numbers::pi in C++20 (here defined will lose precision)

void DirectionVector::perfectBounce(Side pointOfContact)
{
	if (pointOfContact == Side::UP || pointOfContact == Side::DOWN){
		upDirection = -upDirection;
	}
	else {
		rightDirection = -rightDirection;
	}
	
	normalize();
}

double DirectionVector::getVectorLength()
{
	if (upDirection == 0 && rightDirection == 0) {
		return 0.00001;
	}

	return sqrt(upDirection * upDirection + rightDirection * rightDirection);
}

void DirectionVector::rotateBounce(double steepnessInterval, Side direction)
{
	// to mirror it back
	perfectBounce(Side::UP);

	// now we can do calculations to find out mirrored angle
	double bounceOffAngle;
	double r = getVectorLength();
	double x = moveRight;
	double y = moveUp;

	// x = r * cos(fi) => fi = acos(x/r) * pi/180
	double fi = acos(x / r) * PI / 180;   // * PI/180 je da dobijemo stupnjeve a ne radiane
	double angleDiff;

	if (direction == Side::LEFT) {
		bounceOffAngle = 175;
		angleDiff = abs(bounceOffAngle - fi);
	}
	else if (direction == Side::RIGHT) {
		bounceOffAngle = 5;
		angleDiff = -abs(fi - bounceOffAngle);
	}

	double resultingAngle = steepnessInterval * angleDiff;

	double newX = x * cos(resultingAngle) - y * sin(resultingAngle);
	double newY = x * sin(resultingAngle) + y * cos(resultingAngle);

	upDirection = newY;
	rightDirection = newX;
	normalize();

}

void DirectionVector::setUpDirection(double upVelocity)
{
	upDirection = upVelocity;
	normalize();
}

void DirectionVector::setRightDirection(double rightVelocity)
{
	rightDirection = rightVelocity;
	normalize();
}



void DirectionVector::normalize()
{
	if (upDirection == 0 && rightDirection == 0) {  // if both are 0 then length would be 0 and later we would be dividing with 0 
		moveUp = 0;
		moveRight = 0;
		return;  // to avoid divide by 0 runtime error we return from normalize function if both directions are 0
	}
	double length = getVectorLength();

	moveUp = 1. * upDirection / length;
	moveRight = 1. * rightDirection / length;

}

double DirectionVector::getUpUnitVector()
{
	return moveUp;
}

double DirectionVector::getRightUnitVector()
{
	return moveRight;
}
