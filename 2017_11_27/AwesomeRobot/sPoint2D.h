#ifndef _sPoint2D_HG_
#define _sPoint2D_HG_

struct sPoint2D
{
	// a struct is a class, except it's public
	sPoint2D() : x(0.0), y(0.0) {};
	sPoint2D(double x_, double y_) : x(x_), y(y_) {};
	double x;
	double y;
};

#endif