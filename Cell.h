#ifndef CELL_H
#define CELL_H

#include "Face.h"

class Cell
{
    public:

        // Constructor  
        Cell();

        // Destructor
        virtual  ~Cell(){};
         
    protected:

    private:

        // Cell Volume
        double volume_;

        // Cell center of Mass
        std::array<double, 3> centerOfMass_; 

        // Cell skewness
        double skewness_;


};

#endif // CELL_H
