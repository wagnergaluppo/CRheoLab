#include "Face.h"
#include "Cell.h"

Face::Face(int nPointsInFace, vector<Point*> facePoints)
:       
    ID_(-1),
    nPointsInFace_(nPointsInFace),
    facePoints_(facePoints), 
    owner_(nullptr), 
    neighbour_(nullptr),
    area_(-1),
    centerOfMass_({-1,-1,-1}),
    areaVector_({-1,-1,-1}),
    weightingFactor_(-1),
    nonOrthogonalityAngle_(-1)
{
    computeFaceArea();
    computeFaceCenterOfMass();
    computeFaceAreaVector();
}

Face::Face( )
{


}

void Face::setOwner(Cell& owner)
{
    owner_ = &owner;
}

void Face::setNeighbour(Cell& neighbour)
{
    neighbour_ = &neighbour;
}


void Face::setID(const int& ID)
{
    ID_ = ID;
}

void Face::setweightingFactor(double g_c)
{
    weightingFactor_ = g_c;
}

const Cell* Face::getOwner() const
{
    return owner_;
}

const Cell* Face::getNeighbour() const
{
    return neighbour_;
}

const vector3& Face::getCenterOfMass() const
{
    return centerOfMass_;
}

const vector3& Face::getAreaVector() const
{
    return areaVector_;
}

void Face::computeFaceArea()
{

    double a(0);
    double b(0);
    double c(0); 
    double s(0);

    // face is a triangle
    if(nPointsInFace_ == 3)
    {
        // Edge length
        a = mag(facePoints_[0]->getPoint() - facePoints_[1]->getPoint());
        b = mag(facePoints_[1]->getPoint() - facePoints_[2]->getPoint());
        c = mag(facePoints_[2]->getPoint() - facePoints_[0]->getPoint());

        // Semi-perimeter
        s = (a + b + c) / 2.0;

        // Face area
        area_ = sqrt(s * (s - a) * (s - b) * (s - c));
    }
    else
    {
        // compute face centroid
        vector3 centroid {0,0,0};

        for(int i = 0; i < nPointsInFace_; i++)
        {
            centroid = centroid + facePoints_[i]->getPoint();
        }

        centroid = centroid / nPointsInFace_;

        // face area
        area_ = 0.0;

        // compute area of each subtriangle
        for(int i = 0; i < nPointsInFace_; i++)
        {
                // all points but the last
                if(i < nPointsInFace_ - 1)
                {
                    // edges length
                    a = mag(facePoints_[i]->getPoint() - facePoints_[i+1]->getPoint());
                    b = mag(facePoints_[i]->getPoint() - centroid);
                    c = mag(facePoints_[i+1]->getPoint() - centroid);
                }
                else
                {
                    // edges length
                    a = mag(facePoints_[i]->getPoint() - facePoints_[0]->getPoint());
                    b = mag(facePoints_[i]->getPoint() - centroid);
                    c = mag(facePoints_[0]->getPoint() - centroid);
                }

                // semi-perimeter
                s = (a + b + c) / 2.0;

                // face area
                area_ = area_ + sqrt(s * (s - a) * (s - b) * (s - c));
        }

    }

}

void Face::computeFaceCenterOfMass()
{
    // face is a triangle
    if(nPointsInFace_ == 3)
    {
        // face center of mass
        centerOfMass_ = facePoints_[0]->getPoint() + facePoints_[1]->getPoint() +facePoints_[2]->getPoint();
        centerOfMass_ = centerOfMass_ / 3.0;
    }
    else
    {
        // compute face centroid
        vector3 centroid {0,0,0};

        for(int i = 0; i < nPointsInFace_; i++)
        {
            centroid = centroid + facePoints_[i]->getPoint();
        }
        centroid = centroid / nPointsInFace_;

        // numerator
        vector3 numerator({0,0,0});

        // denominator
        double denominator(0.0);

        double a(0);
        double b(0);
        double c(0);
        vector3 subcentroid ({0,0,0});

        // compute area and centroid of each subtriangle
        for(int i = 0; i < nPointsInFace_; i++)
        {
                // all points but the last
                if(i < nPointsInFace_ - 1)
                {
                    // edges length
                    a = mag(facePoints_[i]->getPoint() - facePoints_[i+1]->getPoint());
                    b = mag(facePoints_[i]->getPoint() - centroid);
                    c = mag(facePoints_[i+1]->getPoint() - centroid);

                    // subtriangle centroid
                    subcentroid = facePoints_[i]->getPoint() + facePoints_[i+1]->getPoint() + centroid;
                    subcentroid = subcentroid / 3.0;
                }
                else
                {
                    // edges length
                    a = mag(facePoints_[i]->getPoint() - facePoints_[0]->getPoint());
                    b = mag(facePoints_[i]->getPoint() - centroid);
                    c = mag(facePoints_[0]->getPoint() - centroid);

                    // subtriangle centroid
                    subcentroid = facePoints_[i]->getPoint() + facePoints_[0]->getPoint() + centroid;
                    subcentroid = subcentroid / 3.0;
                }

                // semi-perimeter
                double s = (a + b + c) / 2.0;

                // subtriangle area
                double subarea = sqrt(s * (s - a) * (s - b) * (s - c));

                // compute numerator
                numerator = numerator + subcentroid*subarea;

                // compute denominator
                denominator = denominator + subarea;

        }

        // face center of mass
        centerOfMass_ = numerator / denominator;

    }

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



void Face::computeFaceWeightingFactor()
{
    const vector3& faceCenter = getCenterOfMass();
    const vector3& C_o = owner_->getCenterOfMass();
    const vector3& C_n = neighbour_->getCenterOfMass();

    const vector3 d_Cf = C_o - faceCenter;
    const vector3 d_fF = C_n - faceCenter;
    const vector3 e_f = getAreaVector()/mag( getAreaVector() );
    setweightingFactor( (d_Cf & e_f) / ( (d_Cf & e_f) + (d_fF & e_f) ));
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
