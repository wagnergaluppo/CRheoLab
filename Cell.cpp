#include "Cell.h"

Cell::Cell()
:
volume_(1),
centerOfMass_{1,1,1},
skewness_(1)
{
    
}


vector3 Cell::getCenterOfMass() const
{
    return centerOfMass_;
}
