#pragma once
#include "GameUtilityFunctions.h"

class DirectionVector
{
public:

	void perfectBounce(Side pointOfContact);
	void setUpDirection(double upVelocity);
	void setRightDirection(double rightVelocity);

	double getUpUnitVector();
	double getRightUnitVector();

private:
	double upDirection = 0;     //  if -1 it's down  
	double rightDirection = 0;  //  if -1 it's left

	double moveUp = 0;     // unit vector of current movement direction
	double moveRight = 0;  // here so the information about original direction where ball is heading is retained in up and right Direction

	void normalize();

};

