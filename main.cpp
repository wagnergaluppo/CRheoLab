
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


// Write vectors to stream
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
    }
    os << "]\n";
    return os;
}


template <typename T>
std::vector<T> operator+(const std::vector<T>& v1, const std::vector<T>& v2)
{
   std::vector<T> result(v1.size());

   for(unsigned int i = 0 ; i < v1.size(); i++)
   {
        result[i] = v1[i] + v2[i];
   }

   return result;
}

#include "Mesh.cpp"
#include "findFiles.h"


using namespace std;


int main()
{
      
    checkCaseStructure();
    
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

    cout << "my directory is " << getExecutablePath() << endl;

    return 0;
}


