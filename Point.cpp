#include "Point.h"

Point::Point(double x, double y, double z)
:   x_(x),
    y_(y),
    z_(z)
{

}

void Point::setCoord(double x, double y, double z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}

