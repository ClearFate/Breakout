#pragma once
class DirectionVector
{
public:

	void perfectBounce();
	void setDirection(double upVelocity, double rightVelocity);

	double getUpUnitVector();
	double getRightUnitVector();

private:
	double upDirection = 0;     // unit vector, if -1 it's down  
	double rightDirection = 0;  // unit vector, if -1 it's left

	void normalize();

};

