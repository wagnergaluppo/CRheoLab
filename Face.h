#ifndef FACE_H
#define FACE_H

#include "Point.h"
#include <vector>
using std::vector;

class Face
{
    public:

        // Constructor  
        Face(int, vector<Point*> , int , int );
        Face();

        // Destructor
        virtual  ~Face(){};
       
        // Member Functions      
        void setOwner(int);
        void setNeighbour(int);

        // Write to stream
        friend std::ostream& operator<<(std::ostream& , const Face& );
       
         
    protected:

    private:
        int nPointsInFace_;
        vector<Point*> facePoints_;
        int owner_;
        int neighbour_;  
  
};

#endif // FACE_H
