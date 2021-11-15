#include "volField.h"

template <typename vectorType>
volField<vectorType>::volField(std::string fileName, const Mesh &mesh, const RunTime &time)
    : IODictionary(time.Path(), fileName),
      mesh_(mesh),
      runTime_(time),
      internalField_(readInternalField())
{
  for (unsigned int i = 0; i < mesh_.nPatches_; i++)
  {
    boundaryField_.push_back(Boundary<vectorType>
    ( 
        fileName,
        mesh_.patchList_[i],
        mesh_,
        runTime_
    ));
  }
  
  // test();
}

#include "readVolField.h"

// Give access to the boundary entities
template <typename vectorType>
std::vector<Boundary<vectorType>>& volField<vectorType>::boundaryField()
{
  return boundaryField_;
}

// template <typename vectorType>
// void volField<vectorType>::test()
// {
//   vectorType& banana = boundaryField_[0].boundary();

//   for (unsigned int i =0; i< banana.size(); i++)
//   {
//       banana[i]=2;
//   }
// }