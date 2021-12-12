#include "boundary.h"
#include "readBoundary.h"

template <typename vectorType>
Boundary<vectorType>::Boundary(std::string fileName, const Patch& patch, const Mesh& mesh, const RunTime& time, fileAction action)
    : IODictionary(time.Path(), fileName),
      mesh_(mesh),
      runTime_(time),
      patch_(patch),
      action_(action)
{
      // check action
      if (action == MUST_READ)
      {
            boundary_=readBoundaryField(patch_.name());
      }
      else if (action == NO_READ)
      {
            boundary_.type="calculated";
            boundary_.fieldValue.resize(patch_.nFaces());
      }
      else
      {
            std::cerr << "Unrecognized action for boundaryField!" << std::endl;
      }
}

template <typename vectorType>
vectorType& Boundary<vectorType>::boundary()
{
  return boundary_.fieldValue;
}

template <typename vectorType>
bool& Boundary<vectorType>::valImposed()
{
  return boundary_.valImposed;
}

template <typename vectorType>
std::string& Boundary<vectorType>::type()
{
  return boundary_.type;
}