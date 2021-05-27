#ifndef POINT_H
#define POINT_H

//include "forAllOperations.h"
#include <iostream>


class Point
{
    public:
    
        // Constructor
        Point(double, double, double);
        Point();

        // Destructor
        virtual ~Point(){};

        // Member Functions
        void setCoord(double, double, double);


        // Overloaded operatores
        // Setter
        double& operator[](int entry);

        // Getter
        double operator[](int entry) const ;

        // Summation
        Point operator+(Point const &obj);

        // Subtraction
        Point operator-(Point const &obj);

        // Write to stream
        friend std::ostream& operator<<(std::ostream& , const Point& );
       
    protected:

    private:
        double x_;
        double y_;
        double z_;

};

#endif // POINT_H
