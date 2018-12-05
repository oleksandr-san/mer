
#pragma once

#include <iostream>
#include <random>
#include <vector>

struct point
{
    int x = 0, y = 0;
};

struct rect
{
    point ll, ur;
};

struct plane
{
    plane(int width, int height) : points(height, std::vector<bool>(width, false)) {}
    int height() const { return points.size(); }
    int width() const { return points.empty() ? 0 : points[0].size(); }
    bool has_point(const point& p) const { return points[p.y][p.x]; }
    void add_point(const point& p) { points[p.y][p.x] = true; }

    std::vector<std::vector<bool>> points;
};

struct point_generator
{
    std::mt19937 engine;
    std::uniform_int_distribution<> dist;

    point_generator(int seed, int min, int max)
        :	engine(seed)
        ,	dist(min, max)
    {}

    point generate()
    {
        auto x = dist(engine);
        auto y = dist(engine);
        return { x, y };
    }
};

plane readPlane(std::istream& stream)
{
    int numColumns, numRows;
    std::cin >> numColumns >> numRows;

    plane plane{ numColumns, numRows };
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numColumns; ++col)
        {
            char b;
            std::cin >> b;

            if (b == '0')
                plane.add_point({ col, row });
        }
    }

    return plane;
}

auto writePlane(std::ostream& stream, const plane& plane)
{
    const auto numRows = plane.height();
    const auto numColumns = plane.width();

    stream << numColumns << ' ' << numRows << '\n';

    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numColumns; ++col)
        {
            if (col != 0)
                stream << ' ';
            stream << plane.has_point({ col, row }) ? '1' : '0';
        }

        stream << '\n';
    }
}

void generatePoints(plane& plane, int seed, int n)
{
    point_generator generator{ seed, 1, plane.width() - 1 };
    for (int i = 0; i < n; ++i)
        plane.add_point(generator.generate());
}

rect findMaximumEmptyRectangle(const plane& plane)
{
    rect bestRect;
    int bestArea = 0;

    const int numRows = plane.height();
    const int numColumns = plane.width();

    std::vector<int> cachedWidths(numColumns + 1);
    std::vector<point> stack;
    stack.reserve(numColumns + 1);

    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numColumns; ++col)
        {
            if (plane.has_point({ col, row }))
                cachedWidths[col] = 0;
            else
                ++cachedWidths[col];
        }

        int openWidth = 0;
        for (int col = 0; col <= numColumns; ++col)
        {
            const auto cachedWidth = cachedWidths[col];
            if (cachedWidth > openWidth)
            {
                stack.push_back({ col, openWidth });
                openWidth = cachedWidth;
            }
            else if (cachedWidth < openWidth)
            {
                bool recStartFound = false;
                point recStart;
                do
                {
                    recStartFound = true;
                    recStart = stack.back();
                    stack.pop_back();

                    const auto area = openWidth * (col - recStart.x);
                    if (area > bestArea)
                    {
                        bestArea = area;
                        bestRect = rect{ point{ recStart.x, row }, point{ col - 1, row - openWidth + 1 } };
                    }

                    openWidth = recStart.y;
                } while (cachedWidth < openWidth);

                openWidth = cachedWidth;
                if (recStartFound)
                    stack.push_back(recStart);
            }
        }
    }

    return bestRect;
}
