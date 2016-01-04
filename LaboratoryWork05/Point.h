#pragma once
class Point
{
private:
	float xAxisCoordinate;
	float yAxisCoordinate;
	float zAxisCoordinate;
public:
	Point();
	Point(float, float, float);
	Point(Point &point);
	void operator=(Point &point);
	void operator+=(Point &point);
	void operator-=(Point &point);
	void operator*=(float factor);
	void operator/=(float factor);
	Point operator*(float factor);
	Point operator/(float factor);
	Point operator+(Point& point);
	Point operator-(Point& point);
	float x() const;
	float y() const;
	float z() const;



};