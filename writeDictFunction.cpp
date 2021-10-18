#include "writeDictFunction.h"
#include "mathOperations.h"

//header
void writeDictFunction::writeHeader(std::string clDict, double location, std::string obj){
    std::cout<<"FoamFile"<<std::endl;
    std::cout<<'{'<<std::endl;
    std::cout<<"\tversion\t\t2.0;"<<std::endl;
    std::cout<<"\tformat\t\tascii;"<<std::endl;
    std::cout<<"\tclass\t\t"<<clDict<<';'<<std::endl;
    std::cout<<"\tlocation\t\""<<location<<"\";"<<std::endl;
    std::cout<<"\tobject\t\t"<<obj<<";"<<std::endl;
    std::cout<<'}'<<std::endl;
    std::cout<<"// ************************************************************************* //\n"<< std::endl;
}

//dimensions

 void writeDictFunction::writeDimensions(std::vector<int> dims){
   
     if(dims.size() == 7){
      std::cout<<"dimensions\t[";
      for (int i = 0; i < 7; i++){
        std::cout << dims[i];
        if(i<6) std::cout<< ' ';
      }
      std::cout<<"];\n\n"<<std::endl;

    }else{
      std::cout<<"Cannot write the dimensions, since the data to write is not valid as dimensions!!!"<<std::endl;
    }
  }

// internalField

/*Function to write the InternarField elements for the following 3 types of data:
 ---scalar
 ---vector3
 ---tensor
 */

 
 void writeDictFunction::writeInternalFieldScalarElem(scalarField internalFieldElem){
     if(internalFieldElem.size()>1){
        std::cout<<"internalField\tnonuniform List<scalar>"<<std::endl;
        std::cout << internalFieldElem.size() <<std::endl;
        std::cout <<'('<< std::endl;
        for(int i = 0; i<internalFieldElem.size();i++)
            std::cout<<internalFieldElem[i]<<std::endl;
        std::cout <<')'<< std::endl;
        std::cout <<";\n"<< std::endl;
        
     }else{
                if(internalFieldElem.size()==1)
                std::cout<<"internalField\t uniform "<<internalFieldElem[0]<<";\n"<<std::endl;
                else{
                    std::cout<<"There is no internalField data elements to write!!!"<<std::endl;
                }
     }
  }

 void writeDictFunction::writeInternalFieldVectorElem(vectorField internalFieldElem){
     if(internalFieldElem.size()>1){
        std::cout<<"internalField\tnonuniform List<vector>"<<std::endl;
        std::cout << internalFieldElem.size() <<std::endl;
        std::cout <<'('<< std::endl;
        for(int i = 0; i<internalFieldElem.size();i++){
            std::cout <<'(';
            for(int j = 0; j<3;j++){
                std::cout << internalFieldElem[i][j];
                if(j<2) std::cout<< ' ';
            }
            std::cout <<')'<<std::endl;
        }
        std::cout <<')'<< std::endl;
        std::cout <<";\n"<< std::endl;
        
     }else{
                if(internalFieldElem.size()==1){
                std::cout<<"internalField\t uniform (";
                    for(int j = 0; j<3;j++){
                        std::cout << internalFieldElem[0][j];
                        if(j<2) std::cout<< ' ';
                    }
                std::cout<<");\n"<<std::endl;
                }
                
                
                else{
                    std::cout<<"There is no internalField data elements to write!!!"<<std::endl;
                }
     }    
  }

void writeDictFunction::writeInternalFieldTensorElem(tensorField internalFieldElem){
     if(internalFieldElem.size()>1){
        std::cout<<"internalField\tnonuniform List<tensor>"<<std::endl;
        std::cout << internalFieldElem.size() <<std::endl;
        std::cout <<'('<< std::endl;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
        for(int i = 0; i<internalFieldElem.size();i++){
            std::cout <<'(';
            for(int j = 0; j<internalFieldElem[i].size();j++){
                std::cout << internalFieldElem[i][j];
                if(j< internalFieldElem[i].size()-1){
                    
                } std::cout<< ' ';
            }
            std::cout <<')'<<std::endl;
        }
        std::cout <<')'<< std::endl;
        std::cout <<";\n"<< std::endl;
        
     }else{
                if(internalFieldElem.size()== 1){
                std::cout<<"internalField\t uniform (";
                    for(int j = 0; j<internalFieldElem[0].size();j++){
                       std::cout << internalFieldElem[0][j];
                       if(j< (internalFieldElem[0].size()-1)) std::cout<<' ';
            }
                std::cout<<");\n"<<std::endl;
                }
                
                
                else{
                    std::cout<<"There is no internalField data elements to write!!!"<<std::endl;
                }
     }    
  }

//boundaryField

void writeDictFunction::writeBoundaryFieldElem(std::vector<Patch> boundaryFieldElem){
    std::cout<<"boundaryField"<<std::endl;
    std::cout<<'{'<<std::endl;
    for(int i = 0; i<boundaryFieldElem.size();i++){
        std::cout<<'\t'<< boundaryFieldElem[i].name()<<std::endl;
        std::cout<<"\t{"<<std::endl;
        std::cout<<"\t\ttype\t\t"<<boundaryFieldElem[i].type()<<';'<<std::endl;
        std::cout<<"\t\tnFaces\t\t"<<boundaryFieldElem[i].nFaces()<<';'<<std::endl;
        std::cout<<"\t\tstartFace\t"<<boundaryFieldElem[i].nFaces()<<';'<<std::endl;
        std::cout<<"\t}"<<std::endl;
    }
      std::cout<<"}\n\n"<<std::endl;
      std::cout<<"// ************************************************************************* //"<< std::endl;
}





  