#include "Face.h"

Cell::Cell()
:
ID_(-1),
volume_(-1),
centerOfMass_({-1,-1,-1}),
skewness_(-1),
cellFaces_()
{
}


void Cell::setCellID(const int& ID)
{
    ID_ = ID;
}


void Cell::setCellFaces(const vector<Face*>& cellFaces)
{
    // Deep copy of points
    cellFaces_=cellFaces;   
}

std::vector<Face*> Cell::getCellFaces()
{
    return  cellFaces_;
}


const vector3& Cell::getCenterOfMass() const
{
    return centerOfMass_;
}

double Cell::getNonOrthogonalityCell()
{
    return nonOrthogonality_;
}

void Cell::setNonOrthogonalityCell(double)
{
    for (auto &face : this->cellFaces_)
        {
            if (face->getNonOrthogonalityFace() > this->getNonOrthogonalityCell())
            {
                nonOrthogonality_=face->getNonOrthogonalityFace();
            }

        }
}

