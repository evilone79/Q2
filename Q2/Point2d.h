#pragma once

#include <ostream>

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

std::ostream& operator<< (std::ostream& os, const Point2d& point)
{
	os << "{" << point.X << "," << point.Y << "}";
	return os;
}
