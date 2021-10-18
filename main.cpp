#include <iostream>
//#include "Mesh.h"
#include <typeinfo>
#include <string.h>
//#include "writeDictFunction.h"
#include <sys/stat.h>
//#include <boost/lexical_cast.hpp>       
#include <vector>                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               


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
        
  //std::cout << "Current path is : " << getExecutablePath() << std::endl;

   //checkCaseStructure();
    
    //Mesh polyMesh;

    /*// Print single point
    cout << polyMesh.pointList_[0] << endl;

    // Sums points coordinates between two meshes
    auto a = polyMesh.pointList_ + polyMesh.pointList_;

    cout << "my directory is " << getExecutablePath() << endl;*/

   /* for(unsigned int i = 0 ; i < polyMesh.nCells_ ; i++)
    {
        std::cout << polyMesh.cellList_[i].getSkewness() << std::endl;
        std::cout << typeid(polyMesh.cellList_[i]).name() << endl;
    }
    */
    
   /* std::vector<int> dims ={0,0,0,1,0,0,0};
    std::vector<int> dimsv3 ={0,1,-1,0,0,0,0};
    std::vector<int> dimst = {1,2,-2,0,0,0,0};

    scalarField internalFElem ={300,325,350,375,400,425,450,475,500,525}; 
    vectorField internalFElemv3={{3,3.25,3.50},{3.75,4.00,4.25},{4.50,4.75,5.00}}; 
    vectorField internalFElemv3={{3,3.25,3.50}};
    tensorField internalFElemt ={{20,30,40,12,34,12}};
    std::vector<Patch> Patchs={{"sides","zeroGradient",100,200},{"empty","empty",100,200}};
    
    writeDictFunction writeDFunction;
    
    std::cout <<"\n\n\n\n"<< std::endl;
    std::cout <<"-----For scalarField--------------\n\n"<<std::endl;
    writeDFunction.writeHeader("volField",0.001,"T");
    writeDFunction.writeDimensions(dims);
    writeDFunction.writeInternalFieldScalarElem(internalFElem);
    writeDFunction.writeBoundaryFieldElem(Patchs);

    std::cout <<"\n\n\n\n"<< std::endl;
    std::cout <<"-----For vectorField--------------\n\n"<<std::endl;
    writeDFunction.writeHeader("volField",0.001,"U");
    writeDFunction.writeDimensions(dimsv3);
    writeDFunction.writeInternalFieldVectorElem(internalFElemv3);
    writeDFunction.writeBoundaryFieldElem(Patchs); 

    std::cout <<"-----For tensorField--------------\n\n"<<std::endl;
    writeDFunction.writeHeader("volField",0.001,"sigma");
    writeDFunction.writeDimensions(dimst);
    writeDFunction.writeInternalFieldTensorElem(internalFElemt);
    writeDFunction.writeBoundaryFieldElem(Patchs);

   */
    // Creating a directory
    // 0777 stands for the permision type
     
    std::vector<double> locations = {0.001,0.002,0.003};
    std::vector<string> listOfObjetcs = {"T","U","sigma"};
    for(int i = 0 ; i<locations.size();i++){
         std::string str = to_string(locations[i]);
         str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
         char const *c = str.data();
    }
    

    

    std::cout <<"\n\n\nI am done\n\n\n" << std::endl;

    //std::cout << polyMesh.patchList_[0].name() << endl;

    return 0;
}


