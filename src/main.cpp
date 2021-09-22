#include <iostream>
#include "Mesh.h"

//  void write_csv(std::string filename, std::string , std::vector<double> );

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << "[ \n";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i] << std::endl;
    }
    os << "]\n";
    return os;
}

using namespace std;

int main()
{
        
    std::cout << "Current path is : " << getExecutablePath() << std::endl;

   checkCaseStructure();
    
    Mesh polyMesh;


    /*// Print single point
    cout << polyMesh.pointList_[0] << endl;

    // Sums points coordinates between two meshes
    auto a = polyMesh.pointList_ + polyMesh.pointList_;

    cout << "my directory is " << getExecutablePath() << endl;*/

    for(unsigned int i = 0 ; i < polyMesh.nCells_ ; i++)
    {
        std::cout << polyMesh.cellList_[i].getSkewness() << std::endl;
    }

    std::cout << "I am done\n\n\n" << std::endl;

    std::cout << polyMesh.patchList_[0].name() << endl;

    return 0;
}


