#include "boundaryField.h"

template <typename vectorType>
boundaryField<vectorType>::boundaryField(std::string fileName, const Mesh& mesh, const RunTime& time, fileAction action)
:     mesh_(mesh),
      runTime_(time),
      nPatches_(mesh.nPatches_),
      action_(action)
{
    for (int i = 0; i < nPatches_; i++)
    {
        boundaryField_.push_back(boundary<vectorType>(fileName, mesh_.patchList_[i], mesh_, runTime_, action));
    }
}
