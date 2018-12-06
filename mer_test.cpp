#include "mer.hpp"

#include <sstream>
#include <cassert>
#include <gtest/gtest.h>

plane fromString(const std::string& s)
 {
    std::stringstream stream{s};
    return readPlane(stream);
}

TEST(MaximumEmptyRectangle, SimpleTest)
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

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}