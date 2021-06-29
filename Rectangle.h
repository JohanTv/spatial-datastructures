#pragma once

namespace utec
{
namespace spatial
{

template<typename Point>
struct Rectangle{
    Rectangle(Point min, Point max):_min(min),_max(max){}
    Point _min;
    Point _max;

    bool isInside(Point point){
        const int x=0, y=1;
        if(_min.get(x) <= point.get(x) && point.get(x) <= _max.get(x) &&
            _min.get(y) <= point.get(y) && point.get(y) <= _max.get(y))
            return true;
        return false;
    }
};

} //spatial
} //utec