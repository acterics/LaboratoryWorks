#pragma once
#include "Point.h"
#include <math.h>
class Line
{
private:
	float lineLength;
	Point axisProjections;
	float calculateLineLength();
public:
	Line();
	Line(Line &line);
	Line(Point &axisProjection);
	Line(Point &start, Point &end);
	void operator=(Line &line);
	void operator*=(float factor);
	void operator/=(float factor);
	float operator*(Line &line);
	Line operator*(float factor);
	Line operator/(float factor);
	float angle(Line &line);
	void normalize();
	Point projection();
	float length();
	

};