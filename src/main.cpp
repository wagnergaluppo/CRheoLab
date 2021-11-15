#include <iostream>
#include "Mesh.h"
#include "IODictionaryI.h"
#include "volFieldI.h"



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
    
    RunTime time;

    Mesh polyMesh;
    
    volField<scalarField> p ("p", polyMesh, time);
    std::vector<Boundary<scalarField>>& pBoundary = p.boundaryField();
    
    // for (int i=0; i< 20; i++)

    // {
    // scalarField& valueOfField  = pBoundary[i].boundary();
    // scalarField& valueOfField  = pBoundary[i][j];
    // }       

   // volField<vectorField> U ("U", polyMesh);

   // boundaryField<scalarField> tst ("p", polyMesh, time);

    // TODO main > volField>boundaryfield> boundary> patch
    volField<scalarField> pBC ("p", polyMesh, time);
    


    return 0;
}

