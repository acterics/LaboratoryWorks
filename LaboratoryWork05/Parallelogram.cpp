#include "Parallelogram.h"

Parallelogram::Parallelogram() :
	Parallelogram(Point(), Point(), Point())
{
}

Parallelogram::Parallelogram(Line & side1, Line & side2, Point & intersection) :
	firstSide(side1), secondSide(side2), intersectionPoint(intersection)
{
}

Parallelogram::Parallelogram(Point & point1, Point & mutualPoint, Point & point2) :
	firstSide(mutualPoint, point1), secondSide(mutualPoint, point2), intersectionPoint(mutualPoint)
{
}

void Parallelogram::operator=(Parallelogram & p)
{
	firstSide = p.firstSide;
	secondSide = p.secondSide;
	intersectionPoint = p.intersectionPoint;
}

void Parallelogram::operator*=(float factor)
{
	firstSide *= factor;
	secondSide *= factor;
}

void Parallelogram::operator/=(float factor)
{
	firstSide /= factor;
	secondSide /= factor;
}

Parallelogram Parallelogram::operator*(float factor)
{
	return Parallelogram(firstSide * factor, secondSide * factor, intersectionPoint);
}

Parallelogram Parallelogram::operator/(float factor)
{
	return Parallelogram(firstSide / factor, secondSide / factor, intersectionPoint);
}

float Parallelogram::area()
{
	return firstSide.length() * secondSide.length() * sinf(firstSide.angle(secondSide));
}

float Parallelogram::perimeter()
{
	return 2 * (firstSide.length() * secondSide.length());
}

void Parallelogram::translate(Point & translation)
{
	intersectionPoint += translation;
}
