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

        // 
        vector3 getCenterOfMass() const;

         
    protected:

    private:

        // Cell Volume
        double volume_;

        // Cell center of Mass
        vector3 centerOfMass_; 

        // Cell skewness
        double skewness_;

        // Faces that make up a cell
        vector<Face*> cellFaces_;


};

#endif // CELL_H
