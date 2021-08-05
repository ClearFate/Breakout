#include "DirectionVector.h"
#include <cmath>

void DirectionVector::perfectBounce()
{
	upDirection = -upDirection;
	rightDirection = -rightDirection;
	normalize();
}

void DirectionVector::setDirection(double upVelocity, double rightVelocity)
{
	upDirection = upVelocity;
	rightDirection = rightVelocity;
	normalize();
}

void DirectionVector::normalize()
{
	double length = sqrt(upDirection * upDirection + rightDirection * rightDirection);

	upDirection = upDirection / length;
	rightDirection = rightDirection / length;

}

double DirectionVector::getUpUnitVector()
{
	return upDirection;
}

double DirectionVector::getRightUnitVector()
{
	return rightDirection;
}
