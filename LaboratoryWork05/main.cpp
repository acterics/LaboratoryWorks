#include <iostream>
#include "Parallelogram.h"

int main(int argv, char** argc)
{
	Point mutual;
	Point p1(1, 4, 3);
	Point p2(5, 1, 4);
	Parallelogram a(p1, mutual, p2);
	std::cout << a.area() << std::endl;
	a *= 2;
	std::cout << a.area() << std::endl;
	system("pause");
	return 0;
}