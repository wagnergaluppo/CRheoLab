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

const vector3& Cell::getCenterOfMass() const
{
    return centerOfMass_;
}

const double& Cell::getVolume() const
{
    return volume_;
}


 
void Cell::computeVolume()
{
    
     vector3 geometriCenter = computeGeometriCenter();

    double cellVolume = 0;
    
    for(int faceI = 0; faceI < cellFaces_.size(); faceI++)
    {    
      const vector3 Sf = cellFaces_[faceI]->getAreaVector();   
      const vector3 Cf = cellFaces_[faceI]->getCenterOfMass();
      //Accumulate volume-weighted face-pyramid center
      double pyrvol = computepyrVol(Sf, Cf, geometriCenter);
      cellVolume += pyrvol;
     //Accumulate volume-weighted face-pyramid center          
    }

    volume_ = cellVolume;
                                                                          
}


void Cell::computeCenter(){
        
    vector3 geometriCenter = computeGeometriCenter();
 
    vector3 cellCenter = {0,0,0};

    for(int faceI = 0; faceI < cellFaces_.size(); faceI++)
    {     
      const vector3 Sf = cellFaces_[faceI]->getAreaVector();
      
      const vector3 Cf = cellFaces_[faceI]->getCenterOfMass();

      double pyrVol  = computepyrVol(Sf, Cf, geometriCenter);
     
      vector3 pyrc = (0.75)*Cf + (0.25)*geometriCenter;

      cellCenter = cellCenter + pyrc*pyrVol;
    }



   centerOfMass_ = cellCenter/volume_;
}


double Cell::computepyrVol( vector3 Sf, vector3 Cf  , vector3 geometriCenter)const{
    double VSMALL = 1.0e-37;
    const vector3  d_gf = Cf -geometriCenter;

     if((Sf & d_gf) < 0)
     {
      Sf = (-1)*Sf;
     }
      // Each pyramid volume 
      // & stands for the inner product 
      // max is to avoid zero volumes 
      double pyrVol = std::max(Sf & d_gf, VSMALL)/3;
    
    return pyrVol;

}

vector3 Cell::computeGeometriCenter() const{

   vector3 geometriCenter {0,0,0};

    for(int faceI = 0; faceI <cellFaces_.size(); faceI++)
    {
      const vector3 Cf = cellFaces_[faceI]->getCenterOfMass();     
      geometriCenter = geometriCenter + Cf;
  
    }
    geometriCenter=geometriCenter/cellFaces_.size(); 

    return geometriCenter;
}


