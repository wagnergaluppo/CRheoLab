#include "Point.h"

Point::Point(double x, double y, double z)
:   x_(x),
    y_(y),
    z_(z)
{

}

Point::Point()
:   x_(0),
    y_(0),
    z_(0)
{

}

void Point::setCoord(double x, double y, double z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

