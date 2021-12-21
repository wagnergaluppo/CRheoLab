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
    std::vector<Boundary<scalarField>>& pBoundary = p.boundaryField();

    // for (int i=0; i< 20; i++)

    // {
    // scalarField& valueOfField  = pBoundary[i].boundary();
    // scalarField& valueOfField  = pBoundary[i][j];
    // }

   //volField<vectorField> U ("U", polyMesh);

   // boundaryField<scalarField> tst ("p", polyMesh, time);

    // TODO main > volField>boundaryfield> boundary> patch

    #include "scalarFieldVerification.h"
    // #include "vectorFieldVerification.h"
    // #include "tensorFieldVerification.h"
    // #include "symmTensorFieldVerification.h"


    
    volField<vectorField> UA ("U", polyMesh, time, MUST_READ);
    volField<vectorField> UB ("U", polyMesh, time, MUST_READ);
    volField<vectorField> UC = UA + UB;
    volField<vectorField> UD = UA - UB;
    //UC.shiftField(UA.internalField());
    //UC.shiftMinField(UA.internalField());
    //UC.shiftMaxField(UA.internalField());

    std::cout << "teste6" << endl; 


    return 0;
}
