#include "Face.h"

Face::Face(int nPointsInFace, vector<Point*> facePoints, int owner=-1, int  neighbour=-1 )
:   nPointsInFace_(nPointsInFace),
    facePoints_(facePoints), 
    owner_(owner), 
    neighbour_(neighbour),
    areaVector_({-2,-2,-2}),
    centerOfMass_{-2,-2,-2},
    area_(0),
    weightingFactor_(0),
    nonOrthogonalityAngle_(0)
{
    computeFaceAreaVector();
}

Face::Face( )
{


}

void Face::setNeighbour(int neighbour)
{
    neighbour_ = neighbour;
}

void Face::setOwner(int owner)
{
    owner_ = owner;
}

void Face::computeFaceAreaVector()
{
    //Creates two vectors from the center of mass and one of the points in the face
    vector3 tmp_vec1 = facePoints_[0]->getPoint() - centerOfMass_;
    vector3 tmp_vec2 = facePoints_[1]->getPoint() - centerOfMass_;

    // Computes the face normal by doing the cross product of the products (this is not the faceAreaVector)
    vector3 areaVector_tmp = (tmp_vec1^tmp_vec2);
    
    // Computes the norm of the cross product between two vectors
    double mag_vector_tmp = mag(areaVector_tmp);

    // Calculates the faceAreaVector
    areaVector_ = (areaVector_tmp/mag_vector_tmp)*area_;
    
}


void Face::setweightingFactor(double g_c)
{
    weightingFactor_ = g_c;
}



int Face::getOwner() const
{
    return owner_;
}

int Face::getNeighbour() const
{
    return neighbour_;
}

vector3 Face::getCenterOfMass() const
{
    return centerOfMass_;
}

vector3 Face::getFaceAreaVector() const
{
    return areaVector_;
}


std::ostream& operator<<(std::ostream& os, const Face& p)
{

    os << "[ " << std::endl;

    for (unsigned int i= 0; i < p.facePoints_.size() ; i++)
    {
        os << *p.facePoints_[i];
    }

    os << "]" << std::endl;

return os;
}
