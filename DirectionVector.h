#pragma once

enum class Side {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class DirectionVector{
public:
	
	void bounce(double sideForce);
	void rotateDirection(double kutD);
	void invertSideDirection();
	
	double getUpUnitVector();
	double getRightUnitVector();

private:
	double _x =  0;
	double _y =  1;

	void normalize();
	double vectorLength();
	double degToRad(double kutD);
	double radToDeg(double kutR);
	double vectorDirectionAngle();

};

