#ifndef FACE_H
#define FACE_H

#include <vector>
using std::vector;

class Face
{
    public:

        // Constructor  
        Face(int, vector<int>& , int , int );

        // Destructor
        virtual  ~Face(){};
       
        // Member Functions      
        void setOwner(int);
        void setNeighbour(int);

         
    protected:

    private:
        int nPointsInFace_;
        vector<int> facePoints_;
        int owner_;
        int neighbour_;  
  
};

#endif // FACE_H
