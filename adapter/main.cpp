/**
 * Adapter pattern
 * 
 * The Adapter pattern allows incompatible interfaces to work together. 
 * It acts as a bridge between two incompatible interfaces.
 * This pattern involves a single class called Adapter which is responsible for joining 
 * functionalities of independent or incompatible interfaces.
 * 
 * In this example, `LineToPointAdapter` and `LineToPointCachingAdapter` are adapter classes 
 * that convert a `Line` object into a series of `Point` objects.
 * The `LineToPointAdapter` generates points without caching, 
 * while the `LineToPointCachingAdapter` caches the generated points to avoid redundant calculations.
 */

#pragma once

#include <cstddef>
#include <vector>
#include <map>
#include <iostream>
#include <boost/functional/hash.hpp>

struct Point 
{
    int x, y;

    friend std::size_t hash_value(const Point& point)
    {
        std::size_t seed = 0x1E44943F;
        boost::hash_combine(seed, point.x);
        boost::hash_combine(seed, point.y);
        return seed;
    }

};

struct Line
{
    Point start, end;

    friend std::size_t hash_value(const Line& line)
    {
        std::size_t seed = 0x1E44943F;
        boost::hash_combine(seed, line.start);
        boost::hash_combine(seed, line.end);
        return seed;
    }
};

struct LineToPointAdapter
{
    typedef std::vector<Point> Points;

    LineToPointAdapter(Line& line)
    {
        static int count = 0;

        std::cout << "Generating points for line (no caching)\n" << count++ << std::endl;

        int left = std::min(line.start.x, line.end.x);
        int right = std::max(line.start.x, line.end.x);
        int top = std::min(line.start.y, line.end.y);
        int bottom = std::max(line.start.y, line.end.y);
        int dx = right - left;
        int dy = line.end.y - line.start.y;

        if (dx == 0)
        {
            for (int y = top; y <= bottom; ++y)
            {
                points.emplace_back(Point{ left, y });
            }
        }
        else if (dy == 0)
        {
            for (int x = left; x <= right; ++x)
            {
                points.emplace_back(Point{ x, top });
            }
        }
    }

    virtual Points::iterator begin() { return points.begin(); }
    virtual Points::iterator end() { return points.end(); }

private:
    Points points;
};

struct LineToPointCachingAdapter
{
    typedef std::vector<Point> Points;

    LineToPointCachingAdapter(Line& line)
    {
        boost::hash<Line> hash;
        line_hash = hash(line);

        if (cache.find(line_hash) != cache.end()) return;

        static int count = 0;

        std::cout << "Generating points for line (with caching)\n" << count++ << std::endl;

        // No interpolation
        Points points;

        int left = std::min(line.start.x, line.end.x);
        int right = std::max(line.start.x, line.end.x);
        int top = std::min(line.start.y, line.end.y);
        int bottom = std::max(line.start.y, line.end.y);
        int dx = right - left;
        int dy = line.end.y - line.start.y;

        if (dx == 0)
        {
            for (int y = top; y <= bottom; ++y)
            {
                points.emplace_back(Point{ left, y });
            }
        }
        else if (dy == 0)
        {
            for (int x = left; x <= right; ++x)
            {
                points.emplace_back(Point{ x, top });
            }
        }

        cache[line_hash] = points;

    }

    virtual Points::iterator begin() { return cache[line_hash].begin(); }
    virtual Points::iterator end() { return cache[line_hash].end(); }
private:
    std::size_t line_hash;
    static std::map<std::size_t, Points> cache;
};

void DrawPoints(LineToPointAdapter::Points::iterator begin, LineToPointAdapter::Points::iterator end)
{
    for (auto i = begin; i != end; ++i)
    {
        std::cout << "(" << i->x << "," << i->y << ")" << std::endl;
    }
}


int main()
{
    std::vector<Line> lines
    {
        Line{ Point{1, 1}, Point{1, 10} },
        Line{ Point{3, 3}, Point{3, 10} }
    };

    for (auto& line : lines)
    {
        LineToPointAdapter lpo{ line };
        DrawPoints(lpo.begin(), lpo.end());
    }

    std::cout << "Using caching adapter:" << std::endl;

    for (auto& line : lines)
    {
        LineToPointCachingAdapter lpo{ line };
        DrawPoints(lpo.begin(), lpo.end());
    }

    return 0;
}