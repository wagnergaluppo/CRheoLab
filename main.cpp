
#include <iostream>
#include <math.h> 
#include <cstring>
#include <string>
#include <limits.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm> 
#include <assert.h>
#include <memory>

#include "mathOperations.h"


/*
template <typename T>
std::vector<T> operator+(const std::vector<T>& v1, const std::vector<T>& v2)
{
   std::vector<T> result(v1.size());

   for(unsigned int i = 0 ; i < v1.size(); i++)
   {
        result[i] = v1[i] + v2[i];
   }

   return result;
}*/

#include "Mesh.cpp"
#include "findFiles.h"


using namespace std;


int main()
{
      
 /*   checkCaseStructure();
    
    Mesh polyMesh;

    Mesh polyMesh2;

    // Print single point
    cout << polyMesh.pointList_[0] << endl;

    // Print Points that make up 1 face
    cout << polyMesh.faceList_[0] << endl;

    // Print all points
    cout << polyMesh.pointList_ << endl;

    // Print all faces
    cout << polyMesh.faceList_ << endl;

    // Sums points coordinates between two meshes
    auto a = polyMesh.pointList_ + polyMesh2.pointList_;

    cout << "my directory is " << getExecutablePath() << endl;*/


    vectorField teste(3);
    teste[0]={1,1,1};
    teste[1]={2,2,2};
    teste[2]={3,3,3};


    scalarField t1(3);
    t1[0]=1;
    t1[1]=2;
    t1[2]=3;

    //cout << teste*teste/t1  << endl;


    return 0;
}


