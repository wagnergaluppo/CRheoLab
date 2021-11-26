#include <iostream>
#include "Mesh.h"
#include "IODictionaryI.h"
#include "volFieldI.h"

//  void write_csv(std::string filename, std::string , std::vector<double> );
typedef unsigned int pInt;

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
    volField<vectorField> U ("U", polyMesh, time);

    // volField<tensorField> tau ("tau", polyMesh, time);

    std::vector< Boundary<scalarField> >& pBoundary = p.boundaryField();
    std::vector< Boundary<vectorField> >& uBoundary = U.boundaryField();
    
    std::cout << pBoundary[0].patchName() << std::endl;
    std::cout << pBoundary[1].patchName() << std::endl;
    std::cout << pBoundary[2].patchName() << std::endl;

    // std::cout << p.patchID(pBoundary[2].patchName()) << std::endl;
    // std::cout << p.patchID("right") << std::endl;
    // std::cout << p.patchID("Jayesh") << std::endl;

    //
    unsigned int CellI = 0;
    scalar& valueOfpFieldAtPositionCellI  = pBoundary[0][CellI];
    vector3& valueOfUFieldAtPositionCellI  = uBoundary[0][CellI];

    std::cout << "Test for the pressure Field " << valueOfpFieldAtPositionCellI << std::endl;
    std::cout << "Test for the velocity Field " << valueOfUFieldAtPositionCellI << std::endl;

    // This is to load the patch data using the getter operator
    for (int i = 0 ; i < (int)pBoundary.size(); i++)
    {
        std::cout << "This is the patch " << i  << " named as " << polyMesh.patchList_[i].name() << std::endl;
        for (int j = 0; j < (int)pBoundary[i].size(); j++)
        {
            std::cout << "This is the field value at position:  " << j << " is: " << pBoundary[i][j] << std::endl;
        }
    }
    // This is to overwrite the patch data using the setter operator
    for (int i =0 ; i < (int)pBoundary.size(); i++)
    {
        std::cout << "This is the patch " << i  << " named as " << polyMesh.patchList_[i].name() << std::endl;
        for (int j = 0; j < (int)pBoundary[i].size(); j++)
        {
            std::cout << "The original field value at position:  " << j << " is: " << pBoundary[i][j] << std::endl;
            pBoundary[i][j]=10.5;
            std::cout << "The new field value at position:  " << j << " is: " << pBoundary[i][j] << std::endl;
        }
    }





    
    // // TODO Vector3 Tensors  ... This is to overwrite the patch data using the setter operator
    // for (int i =0 ; i< pBoundary.size(); i++)
    // {
    //     for (int j = 0; j < pBoundary[i].size(); j++)
    //     {
    //         scalar pressureStrength =  pBoundary[i][j];
    //         uBoundary[i][j] = pressureStrength*vector3{1.0,1.0,0.0};
    //     }
    // }

    return 0;
}

