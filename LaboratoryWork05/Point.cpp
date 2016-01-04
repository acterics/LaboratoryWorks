#include "Point.h"

Point::Point() :
	Point(0, 0, 0)
{
}

Point::Point(float x, float y, float z) :
	xAxisCoordinate(x), yAxisCoordinate(y), zAxisCoordinate(z)
{
}

Point::Point(Point & point) :
	xAxisCoordinate(point.x()), yAxisCoordinate(point.y()), zAxisCoordinate(point.z())
{
}

void Point::operator=(Point & point)
{
	xAxisCoordinate = point.x();
	yAxisCoordinate = point.y();
	zAxisCoordinate = point.z();
}

void Point::operator+=(Point & point)
{
	xAxisCoordinate += point.x();
	yAxisCoordinate += point.y();
	zAxisCoordinate += point.z();
}

void Point::operator-=(Point & point)
{
	xAxisCoordinate -= point.x();
	yAxisCoordinate -= point.y();
	zAxisCoordinate -= point.z();
}

void Point::operator*=(float factor)
{
	xAxisCoordinate *= factor;
	yAxisCoordinate *= factor;
	zAxisCoordinate *= factor;
}

void Point::operator/=(float factor)
{
	xAxisCoordinate /= factor;
	yAxisCoordinate /= factor;
	zAxisCoordinate /= factor;
}

Point  Point::operator*(float factor)
{
	return Point(xAxisCoordinate * factor, yAxisCoordinate * factor, zAxisCoordinate * factor);
}

Point  Point::operator/(float factor)
{
	return Point(xAxisCoordinate / factor, yAxisCoordinate / factor, zAxisCoordinate / factor);
}

Point  Point::operator+(Point & point)
{
	return Point(xAxisCoordinate + point.x(), yAxisCoordinate + point.y(), zAxisCoordinate + point.z());
}

Point  Point::operator-(Point & point)
{
	return Point(xAxisCoordinate - point.x(), yAxisCoordinate - point.y(), zAxisCoordinate - point.z());
}

float Point::x() const
{
	return xAxisCoordinate;
}

float Point::y() const
{
	return yAxisCoordinate;
}

float Point::z() const
{
	return zAxisCoordinate;
}
