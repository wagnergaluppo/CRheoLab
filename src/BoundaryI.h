#include "Boundary.h"
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
Boundary<vectorType>::Boundary(std::string fileName, const Patch& patch, const Mesh& mesh, const RunTime& time, fileAction action, const typename vectorType::value_type& defaultValue)
    : IODictionary(time.Path(), fileName),
      mesh_(mesh),
      runTime_(time),
      patch_(patch),
      action_(action)
{
    boundary_.type="calculated";
    boundary_.fieldValue.resize(patch_.nFaces(),defaultValue);
}


template <typename vectorType>
vectorType& Boundary<vectorType>::boundary()
{
  return boundary_.fieldValue;
}

template <typename vectorType>
typename vectorType::value_type& Boundary<vectorType>::operator[](unsigned int posI)
{
  if (posI >= boundary_.fieldValue.size())
  {
      std::cout << "The given index " << posI << " is out of bound, exiting" << std::endl;
      exit(0);
  }
  return boundary_.fieldValue.at(posI);
}


template <typename vectorType>
typename vectorType::value_type Boundary<vectorType>::operator[](unsigned int posI) const
{
  if (posI >= boundary_.fieldValue.size())
  {
      std::cout << "The given index " << posI << " is out of bound, exiting" << std::endl;
      exit(0);
  }
  return boundary_.fieldValue.at(posI);
}
