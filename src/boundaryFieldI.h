
template <typename vectorType>
boundaryField<vectorType>::boundaryField(std::string fileName, const Mesh& mesh, const RunTime& time, fileAction action)
:     nPatches_(mesh.nPatches_),
      action_(action)
{
    for (int i = 0; i < nPatches_; i++)
    {
        boundaryField_.push_back(Boundary<vectorType>(fileName, mesh.patchList_[i], time, action));
    }
}

// Returning the index in the boundaryField for the patch given name 
template <typename vectorType>
const int& boundaryField<vectorType>::size() const
{
    return boundaryField_.size();
}

template <typename vectorType>
const int& boundaryField<vectorType>::patchID(const std::string& patchName) const
{
    int pId=-1;
    for (unsigned int i = 0; i < nPatches_; i++)
    {
        if (boundaryField_[i].name()==patchName)
        {
            pId=boundaryField_[i].index();
        } 
    }
    return pId;
}

template <typename vectorType>
const std::string& boundaryField<vectorType>::patchName(const int& ID) const
{
    return boundaryField_[ID].name();
}

