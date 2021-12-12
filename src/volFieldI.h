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

// Give access to the boundary entities
template <typename vectorType>
std::vector<vectorType>& volField<vectorType>::internalField()
{
  return internalField_;
}

///////////////////////////////////////
// Useful Functions- Outside the class
///////////////////////////////////////
// sum two volFields
template <typename vectorType>
inline volField<vectorType> operator+(const volField<vectorType> & vf1, const volField<vectorType> & vf2)
{    
    //volField<scalarField> pBB ("p", polyMesh, time, MUST_READ);
    //volField<T> result(vf1.internalField.size());

    volField<vectorType> result = vf1;
    //TODO - remove the results2 function from this fuction
    volField<vectorType> result2 = vf2;

    result.internalField_ = vf1.internalField_ + vf2.internalField_;    
    
    for(unsigned int i = 0 ; i < vf1.boundaryField_.size(); i++)
    {
        if (result.boundaryField_[i].valImposed())
        {
          
          //result.boundaryField_[i].boundary() = vf1.boundaryField_[i].boundary() + vf2.boundaryField_[i].boundary();        
          result.boundaryField_[i].boundary() = result.boundaryField_[i].boundary() + result2.boundaryField_[i].boundary();        

        }  
    } 

    return result;
}

// subtract two volFields
template <typename vectorType>
inline volField<vectorType> operator-(const volField<vectorType> & vf1, const volField<vectorType> & vf2)
{    
    //volField<scalarField> pBB ("p", polyMesh, time, MUST_READ);
    //volField<T> result(vf1.internalField.size());

    volField<vectorType> result = vf1;
    //TODO - remove the results2 function from this fuction
    volField<vectorType> result2 = vf2;

    result.internalField_ = vf1.internalField_ + vf2.internalField_;    
    
    for(unsigned int i = 0 ; i < vf1.boundaryField_.size(); i++)
    {
        if (result.boundaryField_[i].valImposed())
        {
          
          //result.boundaryField_[i].boundary() = vf1.boundaryField_[i].boundary() + vf2.boundaryField_[i].boundary();        
          result.boundaryField_[i].boundary() = result.boundaryField_[i].boundary() - result2.boundaryField_[i].boundary();        

        }  
    } 

    return result;
}

///////////////////////////////////////
// Useful Functions- Inside the class
///////////////////////////////////////
template<typename vectorType>
template<typename primitiveType>
void volField<vectorType>::shiftField(const primitiveType& shiftQuantity)
{       
    for(unsigned int i = 0 ; i < internalField_.size(); i++){
         internalField_[i] = internalField_[i] + shiftQuantity;    
    }
    
    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
         if (boundaryField_[i].valImposed()) {
            for(unsigned int j = 0 ; j < boundaryField_[i].boundary().size(); j++){
                boundaryField_[i].boundary()[j] =  boundaryField_[i].boundary()[j] + shiftQuantity;
            }               
        } 
    }     
}

// Scale the volField
template<typename vectorType>
void volField<vectorType>::scaleField(const double& scaleQuantity)
{   
    
    for(unsigned int i = 0 ; i < internalField_.size(); i++){
         internalField_[i] = internalField_[i] * scaleQuantity;    
    }

    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        if (boundaryField_[i].valImposed()) {
            for(unsigned int j = 0 ; j < boundaryField_[i].boundary().size(); j++){
                boundaryField_[i].boundary()[j] =  boundaryField_[i].boundary()[j] * scaleQuantity;
            }
        }
    }     
}

// shift max field
// TODO remove dummyQuantity detect primtive type automatically
template<typename vectorType>
template<typename primitiveType>
void volField<vectorType>::shiftMaxField(const primitiveType& dummyQuantity)
{
    // New operations defined into scalarOperations.h 
        // inline double maxField(const scalarField& v1)
    // New operations defined into vectorOperations.h 
        // inline vector3 maxField(const vectorField& v1)
        // TODO ">" for vector3 
    // New operations defined into tensorOperations.h 
        // TODO ">" for tensor
        // inline tensor maxField(const tensorField& t1)
    // New operations defined into symmTensorOperations.h 
        // TODO ">" for symmTensor
        // inline tensor maxField(const tensorField& t1)
    primitiveType maxFieldValue = maxField(internalField_);
    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        // just compute if value is imposed and the size of the boundary is > 0
        if (boundaryField_[i].valImposed() & (boundaryField_[i].boundary().size() > 0 )) {
            primitiveType maxBndFieldValue = maxField(boundaryField_[i].boundary());
            if (maxBndFieldValue > maxFieldValue) maxFieldValue = maxBndFieldValue;            
        }
    }
    //shift the field with the maximum value
    shiftField(maxFieldValue);
}

// shift min field
// TODO remove dummyQuantity detect primtive type automatically
template<typename vectorType>
template<typename primitiveType>
void volField<vectorType>::shiftMinField(const primitiveType& dummyQuantity)
{
    // New operations defined into scalarOperations.h 
        // inline double maxField(const scalarField& v1)
    // New operations defined into vectorOperations.h 
        // inline vector3 maxField(const vectorField& v1)
        // TODO "<" for vector3 
    // New operations defined into tensorOperations.h 
        // TODO "<" for tensor
        // inline tensor maxField(const tensorField& t1)
    // New operations defined into symmTensorOperations.h 
        // TODO "<" for symmTensor
        // inline tensor maxField(const tensorField& t1)
    primitiveType minFieldValue = minField(internalField_);
    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        // just compute if value is imposed and the size of the boundary is > 0
        if (boundaryField_[i].valImposed() & (boundaryField_[i].boundary().size() > 0 )) {
            primitiveType minBndFieldValue = minField(boundaryField_[i].boundary());
            if (minBndFieldValue < minFieldValue) minFieldValue = minBndFieldValue;            
        }
    }
    //shift the field with the minimum value
    shiftField(minFieldValue);
}
