#include "readVolField.h"

template <typename vectorType>
volField<vectorType>::volField(std::string fileName, const Mesh &mesh, const RunTime &time, fileAction action)
    : IODictionary(time.Path(), fileName),
      mesh_(mesh),
      runTime_(time),
      action_(action),
      boundaryField_(fileName, mesh, time, action)
{

  // Check action
  if (action  == MUST_READ)
  {
    internalField_=readInternalField();
  }
  else if (action == NO_READ)
  {
    internalField_.resize(mesh.nCells_);
  }
  else
  {
    std::cerr << "Unrecognized action for internalField!" << std::endl;
  }

  // test();
}

template <typename vectorType>
volField<vectorType>::volField(std::string fileName, const Mesh &mesh, const RunTime &time, fileAction action, const typename vectorType::value_type& defaultValue)
    : IODictionary(time.Path(), fileName),
      mesh_(mesh),
      runTime_(time),
      action_(action),
      boundaryField_(fileName, mesh, time, action)
{
      internalField_.resize(mesh.nCells_, defaultValue);
}

// // Give access to the boundary entities
// template <typename vectorType>
// boundaryField<vectorType>& volField<vectorType>::boundaryField()
// {
//   return boundaryField_;
// }
