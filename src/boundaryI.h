#include "Boundary.h"
#include "readBoundary.h"

template <typename vectorType>
Boundary<vectorType>::Boundary(std::string fileName, const Patch& patch, const Mesh& mesh, const RunTime& time)
    : IODictionary(time.Path(), fileName),
      mesh_(mesh),
      runTime_(time),
      patch_(patch),
      boundary_(readBoundaryField( patch_.name() ))
{}


template <typename vectorType>
vectorType& Boundary<vectorType>::boundary()
{
  return boundary_.fieldValue;
}