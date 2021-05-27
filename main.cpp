
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


#include "Mesh.cpp"
#include "findFiles.h"


using namespace std;


int main()
{
      
    checkCaseStructure();
    
    Mesh polyMesh;

    cout << "my directory is " << getExecutablePath() << endl;

    return 0;
}


