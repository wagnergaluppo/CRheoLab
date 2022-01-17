#include <iostream>
#include "Mesh.h"
#include "IODictionaryI.h"
#include "IODictionaryw.h"
#include "volFieldI.h"

//  void write_csv(std::string filename, std::string , std::vector<double> );

/*template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << "[ \n";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i] << std::endl;
    }
    os << "]\n";
    return os;
}*/

using namespace std;

int main()
{
      
    std::cout << "Current path is : " << getExecutablePath() << std::endl;

    checkCaseStructure();
    
    RunTime time;

    Mesh polyMesh;
    
    volField<scalarField> p ("p", polyMesh, time);
    std::cout << "Current path is : " << time.Path() << std::endl;

    std::string tst = "0";
    time.setFolder(tst);

    std::cout << "Current path is : " << time.Path() << std::endl;

    volField<vectorField> U("U", polyMesh, time);

    symmTensorField symmfield =  {{5e+06, -0.000144797, -0.000460091, 0.0545079, -0.00401398, 0.102309},{5e+06, -0.000115814 ,-0.000726005, 0.00996289 ,0.0168723, 0.0300389},{5e+06, -0.000115814 ,-0.000726005, 0.00996289 ,0.0168723, 0.0300389}  } ;
    patchBoundaryConditions<symmTensorField> pBCRIght = { "calculated", symmfield , {} };
    patchBoundaryConditions<symmTensorField> pBCLeft = { "empty", {} , {} };
    patchBoundaryConditions<symmTensorField> pBCTop = { "empty", symmfield , {} };

     std::cout<<"\n\n"<<std::endl;
    //std::cout << '\n'<< pBCRight << std::endl;
    boundaryField<symmTensorField> bField = {{"Right","Left","Top"},{pBCRIght,pBCLeft,pBCTop}};
     
    internalField<symmTensorField> iField =  {symmfield.size(),symmfield};

    std::cout<<iField<<std::endl;

    std::cout<< bField << std::endl;



    std::cout<<"OK"<<std::endl;


    return 0;
    
}


