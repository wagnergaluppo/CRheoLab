#ifndef POINT_H
#define POINT_H

//include "forAllOperations.h"


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
        
    protected:

    private:
        double x_;
        double y_;
        double z_;

};

#endif // POINT_H
