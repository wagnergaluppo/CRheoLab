#include "Boundary.h"
#include "readBoundary.h"

template <typename vectorType>
Boundary<vectorType>::Boundary(std::string fileName, const Patch& patch, const RunTime& time, fileAction action)
    : IODictionary(time.Path(), fileName),
      patch_(patch),
      action_(action)
{
    // check action
    if (action == MUST_READ)
    {
        boundaryValues_=readBoundaryField(patch_.name());
    }
    else if (action == NO_READ)
    {
        boundaryValues_.type="calculated";
        boundaryValues_.fieldValue.resize(patch_.nFaces());
    }
    else
    {
        std::cerr << "Unrecognized action for boundaryField!" << std::endl;
    }

    // Verifying if the patch size is in agreement with the mesh Patch size
    
    if ((!boundaryValues_.uniformField) && (boundaryValues_.type!="empty") && boundaryValues_.fieldValue.size()!=patch_.nFaces())
    {
        std::cerr << "The input data for the patch named as " << patch_.name() << " has " << boundaryValues_.fieldValue.size() << " entries, while this patch allows only " << patch_.nFaces()  << " face!" << std::endl;
    }
     

}

template <typename vectorType>
Boundary<vectorType>::Boundary(std::string fileName, const Patch& patch, const RunTime& time, fileAction action, const typename vectorType::value_type& defaultValue)
    : IODictionary(time.Path(), fileName),
      patch_(patch),
      action_(action)
{
    boundaryValues_.type="calculated";
    boundaryValues_.fieldValue.resize(patch_.nFaces(),defaultValue);
}


template <typename vectorType>
vectorType& Boundary<vectorType>::boundary()
{
  return boundaryValues_.fieldValue;
}

template <typename vectorType>
typename vectorType::value_type& Boundary<vectorType>::operator[](unsigned int posI)
{
  if (posI >= boundaryValues_.fieldValue.size())
  {
      std::cout << "The given index " << posI << " is out of bound, exiting" << std::endl;
      exit(0);
  }
  return boundaryValues_.fieldValue.at(posI);
}


template <typename vectorType>
typename vectorType::value_type Boundary<vectorType>::operator[](unsigned int posI) const
{
  if (posI >= boundaryValues_.fieldValue.size())
  {
      std::cout << "The given index " << posI << " is out of bound, exiting" << std::endl;
      exit(0);
  }
  return boundaryValues_.fieldValue.at(posI);
}
