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
    boundaryField_.push_back
    (
      Boundary<vectorType>
      ( 
        fileName,
        mesh_.patchList_[i],
        runTime_
      )
    );
  }
}

#include "readVolField.h"

// Give access to the boundary entities
template <typename vectorType>
std::vector<Boundary<vectorType>>& volField<vectorType>::boundaryField()
{
  return boundaryField_;
}

// TODO Group4 // Returns the ID for a given named patch, if not found returns null (-1)    
// template <typename vectorType>
// int volField<vectorType>::patchID(std::string patchName) const
// {
//   // This is to avoid any nonexisting patch to be returned
//   patchID = -1;
//   for (unsigned int i = 0; i < mesh_.nPatches_; i++)
//   {
//     bool foundName(mesh_.patchList_[i].patchID(patchName));
//     if( foundName )
//     {
//       patchID = i;
//     } 
//   }
//   return patchID;
// }


// template <typename vectorType>
// void volField<vectorType>::test()
// {
//   vectorType& vectorBCFieldTest = boundaryField_[0].boundary();

//   for (unsigned int i =0; i< vectorBCFieldTest.size(); i++)
//   {
//       vectorBCFieldTest[i]=2;
//   }
// }
// template <typename vectorType>
// std::vector<Boundary<vectorType>>& volField<vectorType>::boundaryField()
// {
//   return boundaryField_;
// }
template <typename vectorType>
int volField<vectorType>::patchID(std::string patchName)
{
  int pId=-1;

  for(long unsigned int i=0;i<boundaryField_.size();i++)
  {
    if(boundaryField_[i].patchName()==patchName)
      {
        pId=i;
        break;
      }
  }
  if (pId<0)
    {
      std::cout<<"Could not find the Patch: "<<patchName<<std::endl;
    }  
  return pId;
}