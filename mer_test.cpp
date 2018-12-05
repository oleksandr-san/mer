#include "mer.hpp"

int main()
{
	plane plane{ 10, 10 };
	generatePoints(plane, 0, 10 );
	writePlane(std::cout, plane);
	plane = readPlane(std::cin);

	auto bestRect = findMaximumEmptyRectangle(plane);
}