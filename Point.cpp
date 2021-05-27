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

// Setter
double& Point::operator[](int entry)
{
    if (entry==0)
        return x_;
    else if(entry==1)
        return y_;
    else if(entry==2)
        return z_;
    else
        throw std::out_of_range("Point does not have index " + std::to_string(entry));
}

// Getter
double Point::operator[](int entry) const 
{
    if (entry==0)
        return x_;
    else if(entry==1)
        return y_;
    else if(entry==2)
        return z_;
    else
        throw std::out_of_range("Point does not have index " + std::to_string(entry));
}


Point Point::operator+(Point const &obj)
{
    Point result;
    result.x_ = x_ + obj.x_;
    result.y_ = y_ + obj.y_;
    result.z_ = z_ + obj.z_;

    return result;
}

Point Point::operator-(Point const &obj)
{
    Point result;
    result.x_ = x_ - obj.x_;
    result.y_ = y_ - obj.y_;
    result.z_ = z_ - obj.z_;
    
    return result;
}


std::ostream& operator<<(std::ostream& os, const Point& p)
{
os << "[ " << p[0] << ", " << p[1] << ", " << p[2] << " ]" << std::endl;
return os;
}