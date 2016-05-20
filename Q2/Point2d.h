#pragma once

//well.. a 2d point 
struct Point2d
{
	Point2d() : X(0.0), Y(0.0){}

	Point2d(double x, double y)
		: X(x),
		  Y(y)
	{
	}

	double X;
	double Y;
};

