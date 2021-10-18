#ifndef WRITEDICTFUNCTION_H
#define WRITEDICTFUNCTION_H
#include <iostream>
#include <string>
#include <vector>
#include "Patch.h"
#include "mathOperations.h"

class writeDictFunction
{
  public:
    //writing proceedments
    void  writeInternalFieldScalarElem(scalarField internalFieldElem);
    void  writeInternalFieldVectorElem(vectorField internalFieldElem);
    void  writeInternalFieldTensorElem(tensorField internalFieldElem);

    void  writeBoundaryFieldElem(std::vector<Patch> boundaryFieldElem);
    void  writeDimensions(std::vector<int> dim);
    void  writeHeader(std::string clDict, double location, std::string obj);
    
};

#endif //WRITEDICTFUNCTION_H