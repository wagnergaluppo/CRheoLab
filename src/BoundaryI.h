#include "Boundary.h"
#include "readBoundary.h"

template <typename vectorType>
Boundary<vectorType>::Boundary(std::string fileName, const Patch& patch, const RunTime& time)
    : IODictionary(time.Path(), fileName),
      runTime_(time),
      patch_(patch),
      boundary_(readBoundaryField( patch_.name() )),
      size_(boundary_.fieldValue.size())
{}


template <typename vectorType>
vectorType& Boundary<vectorType>::boundary()
{
  return boundary_.fieldValue;
}

// Returning the size of the boundary patch
template <typename vectorType>
const int& Boundary<vectorType>::size() const
{
  return size_;
}

// TODO Group4 Returning the index in the boundaryField for the patch given name 
template <typename vectorType>
const bool Boundary<vectorType>::patchID(std::string patchName) const
{
  return (patchName==patch_.name())?(true):(false);
}

// TODO Group4 Returning the name of a patch for the given index at the boundaryField
template <typename vectorType>
const std::string Boundary<vectorType>::patchName() const
{
  return patch_.name();
}

// Implementation of [] operator.  This function must return a
// reference as array element can be put on left side

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
