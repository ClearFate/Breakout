#include "DirectionVector.h"
#include <cmath>
#include <iostream>

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
	double bounceOffAngle;
	double r = getVectorLength();

	//TODO finish 

	if (direction == Side::LEFT) {
		bounceOffAngle = 175;
	}
	else if (direction == Side::RIGHT) {
		bounceOffAngle = 5;
	}
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
