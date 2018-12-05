#include "mer.hpp"

#include <sstream>
#include <cassert>

plane fromString(const std::string& s)
 {
    std::stringstream stream{s};
    return readPlane(stream);
}

void Test_SimpleCase()
{
    const std::string planeData =
R"(10 10
0 0 0 0 0 0 0 0 0 0
0 1 1 0 0 0 0 1 0 1
0 1 1 0 1 0 0 1 1 1
0 0 1 1 1 1 1 0 1 1
0 1 1 1 1 0 1 1 1 1
0 0 0 1 1 1 1 1 0 1
0 1 1 1 1 1 0 1 0 1
0 1 1 1 1 1 0 0 1 1
0 1 1 1 0 1 1 1 1 1
0 0 1 0 0 1 1 1 1 1)";

    auto rect = findMaximumEmptyRectangle(fromString(planeData));

    assert(area(rect) == 10);
}

int main()
{
    Test_SimpleCase();
}