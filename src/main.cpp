#include <iostream>
#include "Mesh.h"
#include "IODictionary.h"
#include "volField.h"

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
    
    // std::vector<Boundary<scalarField>>& pBoundary = p.boundaryField();

    boundaryField<scalarField> boundaryFieldTest("p",polyMesh,time,MUST_READ);

    // volField<scalarField> p ("p", polyMesh, time, FILE_READ);
    // std::vector< Boundary<scalarField> >& pBoundary = p.boundaryField();
    volField<vectorField> U ("U", polyMesh, time, NO_READ, vector3{1,2,3} );
    // std::vector< Boundary<vectorField> >& uBoundary = U.boundaryField();

    // volField<tensorField> tau ("tau", polyMesh, time);

    
    // std::cout << pBoundary[0].patchName() << std::endl;
    // std::cout << pBoundary[1].patchName() << std::endl;
    // std::cout << pBoundary[2].patchName() << std::endl;

    // std::cout<<"Patch ID: "<<p.patchID("banana")<<std::endl;
    // std::cout<<"Patch ID: "<<p.patchID("top")<<std::endl;
    // std::cout<<"Patch ID: "<<p.patchID("bottom")<<std::endl;
    // std::cout<<"Patch Name: "<<pBoundary[p.patchID("top")].patchName()<<std::endl;
    // std::cout<<"Patch Name: "<<pBoundary[p.patchID("banana")].patchName()<<std::endl;
    // std::cout<<"Patch ID: "<<p.patchID(pBoundary[p.patchID("banana")].patchName())<<std::endl;


    // for (int i=0; i< 20; i++)

    // {
    // scalarField& valueOfField  = pBoundary[i].boundary();
    // scalarField& valueOfField  = pBoundary[i][j];
    // }

   // volField<vectorField> U ("U", polyMesh);

   // boundaryField<scalarField> tst ("p", polyMesh, time);

    // // TODO main > volField>boundaryfield> boundary> patch
    // volField<scalarField> pBC ("p", polyMesh, time, FILE_READ);




    return 0;
}
