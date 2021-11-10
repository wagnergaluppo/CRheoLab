#include "boundaryField.h"
#include "readBoundary.h"

template <typename vectorType>
boundary<vectorType>::boundary(std::string fileName, const Patch& patch, const Mesh& mesh, const RunTime& time)
    : IODictionary(time.Path(), fileName),
      mesh_(mesh),
      runTime_(time),
      patch_(patch),
      boundary_(readBoundaryField( patch_.name() ))
{}
