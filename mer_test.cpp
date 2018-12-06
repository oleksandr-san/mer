#include "mer.hpp"

#include <sstream>
#include <cassert>
#include <gtest/gtest.h>

plane fromString(const std::string& s)
 {
    std::stringstream stream{s};
    return readPlane(stream);
}

TEST(MaximumEmptyRectangle, SimplePredefinedPlane)
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

TEST(MaximumEmptyRectangle, Generate1MillionPoints)
{
    plane plane{ 1000, 1000 };
    generatePoints(plane, 0, 1000000);
    auto rect = findMaximumEmptyRectangle(plane);

    assert(area(rect) != 0);
}

TEST(MaximumEmptyRectangle, Generate5MillionPoints)
{
    plane plane{ 1000, 1000 };
    generatePoints(plane, 0, 5000000);
    auto rect = findMaximumEmptyRectangle(plane);

    assert(area(rect) != 0);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}