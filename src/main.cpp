#include <iostream>
#include "Mesh.h"
#include "IODictionary.h"
#include "volField.h"
#include "FVMatrix.h"



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

    volField<scalarField> p ("p", polyMesh, time, MUST_READ);
    std::vector<Boundary<scalarField>>& pBoundary = p.boundaryField();
    //std::cout << ">> criar vector " << std::endl;
    std::vector<double> T1(polyMesh.nCells_,0.);
    std::vector<double> T2(polyMesh.nCells_,0.);
    std::vector<double> T3(polyMesh.nCells_,0.);
    //std::cout << "T: " << T << std::endl;
    FVMatrix TEquation1(polyMesh, T1, jacobi, 1E-15, 1E-15);
    FVMatrix TEquation2(polyMesh, T2, gaussSidel, 1E-15, 1E-15);
    FVMatrix TEquation3(polyMesh, T3, SOR, 1E-15, 1E-15, 1.2);
    //std::cout << ">> solve " << std::endl;
    std::cout << ">> Jacobi " << std::endl;
    TEquation1.solve();
    std::cout << ">> Gauss-Siedel " << std::endl;
    TEquation2.solve();
    std::cout << ">> SOR, w=1.2 " << std::endl;
    TEquation3.solve();

    //std::cout << "ncell: " << polyMesh.nCells_ << std::endl;
   

    // for (int i=0; i< 20; i++)

    // {
    // scalarField& valueOfField  = pBoundary[i].boundary();
    // scalarField& valueOfField  = pBoundary[i][j];
    // }

   // volField<vectorField> U ("U", polyMesh);

   // boundaryField<scalarField> tst ("p", polyMesh, time);

    // TODO main > volField>boundaryfield> boundary> patch
    volField<scalarField> pBC ("p", polyMesh, time, MUST_READ);

         

    return 0;
}
