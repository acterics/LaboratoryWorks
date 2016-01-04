#include "Line.h"

float Line::calculateLineLength()
{
	return sqrtf(axisProjections.x() * axisProjections.x() +
		axisProjections.y() * axisProjections.y() +
		axisProjections.z() * axisProjections.z());
}

Line::Line() :
	Line(Point(), Point())
{
}

Line::Line(Line & line) :
	lineLength(line.length()), axisProjections(line.projection())
{
}

Line::Line(Point & axisProjection) :
	axisProjections(axisProjection)
{
	lineLength = calculateLineLength();
}

Line::Line(Point & start, Point & end) :
	axisProjections(end - start)
{
	lineLength = calculateLineLength();
}

void Line::operator=(Line & line)
{
	axisProjections = line.projection();
	lineLength = line.length();
}

void Line::operator*=(float factor)
{
	axisProjections *= factor;
	lineLength = calculateLineLength();
}

void Line::operator/=(float factor)
{
	axisProjections /= factor;
	lineLength = calculateLineLength();
}

float Line::operator*(Line & line)
{
	return axisProjections.x() * line.projection().x() +
		axisProjections.y() * line.projection().y() +
		axisProjections.z() * line.projection().z();
}

Line Line::operator*(float factor)
{
	return Line(axisProjections * factor);
}

Line Line::operator/(float factor)
{
	return Line(axisProjections / factor);
}

float Line::angle(Line & line)
{
	return acosf(((*this) * line) / (line.length() * this->length()));
}

void Line::normalize()
{
	axisProjections /= lineLength;
	lineLength = calculateLineLength();
}

Point Line::projection()
{
	return axisProjections;
}

float Line::length()
{
	return lineLength;
}
