#pragma once
#include "Point.h"
#include "Line.h"
class Parallelogram
{
private:
	Line firstSide, secondSide;
	Point  intersectionPoint;
public:
	Parallelogram();
	Parallelogram(Line &side1, Line &side2, Point &intersection);
	Parallelogram(Point &point1, Point &mutualPoint, Point &point2);
	void operator=(Parallelogram &p);
	void operator*=(float factor);
	void operator/=(float factor);
	Parallelogram operator*(float factor);
	Parallelogram operator/(float factor);

	float area();
	float perimeter();
	void translate(Point &translation);




};