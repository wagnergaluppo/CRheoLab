
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
#include "Mesh.cpp"
#include "findFiles.h"


template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << "[ \n";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
    }
    os << "]\n";
    return os;
}


using namespace std;


int main()
{
      
   /*checkCaseStructure();
    
    Mesh polyMesh;

    // Print single point
    cout << polyMesh.pointList_[0] << endl;

    // Sums points coordinates between two meshes
    auto a = polyMesh.pointList_ + polyMesh.pointList_;

    cout << "my directory is " << getExecutablePath() << endl;

*/
    vectorField test(4);
    for(int i =0 ; i<test.size(); i++)
    {
        test[i][0]=i;
        test[i][1]=i;
        test[i][2]=i;
    }

   cout << test << endl;

   auto a = test&test;
   cout << a << endl;


    return 0;
}


