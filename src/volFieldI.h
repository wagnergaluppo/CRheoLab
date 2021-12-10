#include "readVolField.h"

template <typename vectorType>
volField<vectorType>::volField(std::string fileName, const Mesh &mesh, const RunTime &time, fileAction action)
    : IODictionary(time.Path(), fileName),
      mesh_(mesh),
      runTime_(time),
      action_(action)
{

  // Check action
  if (action  == MUST_READ)
  {
     internalField_=readInternalField();

     for (unsigned int i = 0; i < mesh_.nPatches_; i++)
     {
       boundaryField_.push_back(Boundary<vectorType>
       (
           fileName,
           mesh_.patchList_[i],
           mesh_,
           runTime_,
           action
       ));
     }

  }
  else if (action == NO_READ)
  {
      internalField_.resize(mesh.nCells_);

      for (unsigned int i = 0; i < mesh_.nPatches_; i++)
      {
        boundaryField_.push_back(Boundary<vectorType>
        (
            fileName,
            mesh_.patchList_[i],
            mesh_,
            runTime_,
            action
        ));
      }
  }
  else
  {
        std::cerr << "Unrecognized action for internalField!" << std::endl;
  }

}

// Give access to the boundary entities
template <typename vectorType>
std::vector<Boundary<vectorType>>& volField<vectorType>::boundaryField()
{
  return boundaryField_;
}

