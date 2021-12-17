#include "readVolField.h"
#include <typeinfo>

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

// Give access to the internal Field entities
template <typename vectorType>
vectorType& volField<vectorType>::internalField()
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

    volField<vectorType> result = vf1;
    //TODO - remove the results2 function from this fuction
    volField<vectorType> result2 = vf2;

    result.internalField() = result.internalField() + result2.internalField();    
    
    for(unsigned int i = 0 ; i < result.boundaryField().size(); i++)
    {
        if (result.boundaryField()[i].valImposed())
        {
         result.boundaryField()[i].boundary() = result.boundaryField()[i].boundary() + result2.boundaryField()[i].boundary();        
        }  
    } 

    return result;
}

// subtract two volFields
template <typename vectorType>
inline volField<vectorType> operator-(const volField<vectorType> & vf1, const volField<vectorType> & vf2)
{    
    volField<vectorType> result = vf1;
    //TODO - remove the results2 function from this fuction
    volField<vectorType> result2 = vf2;

    result.internalField() = result.internalField() + result2.internalField();    
    
    for(unsigned int i = 0 ; i < result.boundaryField().size(); i++)
    {

        if (result.boundaryField()[i].valImposed())
        {
          
          //result.boundaryField_[i].boundary() = vf1.boundaryField_[i].boundary() + vf2.boundaryField_[i].boundary();        
          result.boundaryField()[i].boundary() = result.boundaryField()[i].boundary() - result2.boundaryField()[i].boundary();        

        }  
    } 

    return result;
}

//ShiftField+ outside the class
template< typename vectorType,typename primitiveType >
volField<vectorType> operator+(const volField<vectorType> & volF, const primitiveType v2)
{
    //Create a copy of volF
    volField<vectorType> resVolField = volF;

    std::string newName = resVolField.Name()+"shiftedSum";

    resVolField.setName(newName);
    
    resVolField.internalField() = resVolField.internalField() + v2;    
    
    for(unsigned int i = 0 ; i < resVolField.boundaryField().size(); i++){
        if (resVolField.boundaryField()[i].valImposed()) {            
          resVolField.boundaryField()[i].boundary() = resVolField.boundaryField()[i].boundary() + v2;                         
        }
    }

    return resVolField;
}

//ShiftField- outside the class
template< typename vectorType,typename primitiveType >
volField<vectorType> operator-(const volField<vectorType> & volF, const primitiveType v2)
{
    //Create a copy of volF
    volField<vectorType> resVolField = volF;

    std::string newName = resVolField.Name()+"shiftedSubtraction";

    resVolField.setName(newName);
    
    resVolField.internalField() = resVolField.internalField() - v2;    
    
    for(unsigned int i = 0 ; i < resVolField.boundaryField().size(); i++){
        if (resVolField.boundaryField()[i].valImposed()) {            
          resVolField.boundaryField()[i].boundary() = resVolField.boundaryField()[i].boundary() - v2;                         
        }
    }

    return resVolField;
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
//template<typename primitiveType>
void volField<vectorType>::shiftMaxField()
{
    // New operations defined into scalarOperations.h 
        // inline double maxField(const scalarField& v1)
    // New operations defined into vectorOperations.h 
        // inline vector3 maxField(const vectorField& v1)
    // New operations defined into tensorOperations.h 
        // inline tensor maxField(const tensorField& t1)
    // New operations defined into symmTensorOperations.h 
        // inline tensor maxField(const tensorField& t1)
    typename vectorType::value_type maxFieldValue = maxField(internalField_);
    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        // just compute if value is imposed and the size of the boundary is > 0
        if (boundaryField_[i].valImposed() & (boundaryField_[i].boundary().size() > 0 )) {
            typename vectorType::value_type maxBndFieldValue = maxField(boundaryField_[i].boundary());
            if (maxBndFieldValue > maxFieldValue) maxFieldValue = maxBndFieldValue;            
        }
    }
    //shift the field with the maximum value
    shiftField(maxFieldValue);
}

// shift min field
// TODO remove dummyQuantity detect primtive type automatically
template<typename vectorType>
void volField<vectorType>::shiftMinField()
{
    // New operations defined into scalarOperations.h 
        // inline double maxField(const scalarField& v1)
    // New operations defined into vectorOperations.h 
        // inline vector3 maxField(const vectorField& v1)
    // New operations defined into tensorOperations.h 
        // inline tensor maxField(const tensorField& t1)
    // New operations defined into symmTensorOperations.h 
        // inline tensor maxField(const tensorField& t1)
    typename vectorType::value_type minFieldValue = minField(internalField_);
    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
        // just compute if value is imposed and the size of the boundary is > 0
        if (boundaryField_[i].valImposed() & (boundaryField_[i].boundary().size() > 0 )) {
            typename vectorType::value_type minBndFieldValue = minField(boundaryField_[i].boundary());
            if (minBndFieldValue < minFieldValue) minFieldValue = minBndFieldValue;            
        }
    }
    //shift the field with the minimum value
    shiftField(minFieldValue);
}

// project vector field
template< typename vectorType>
void volField<vectorType>::projectVectorField(const vector3& projectVector)
{   
    if (typeid(internalField_).hash_code()==typeid(projectVector).hash_code()) {
        vector3 normProjectVector = projectVector / mag(projectVector);
        // New operation defined into vectorOperations.h 
        // TODO
        // inline vectorField operator*( const scalarField& s1, const vector3& v1)
        // TODO
        // inline scalarField operator&(const vectorField& v1, const vector3& v2)
        internalField = (internalField & normProjectVector) * normProjectVector;

        for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
            if (boundaryField_[i].valImposed) {       
                boundaryField_[i].fieldValue =  (boundaryField_[i].fieldValue & normProjectVector) * normProjectVector;                     
            }
        }  
    }   
}

// calculate a scalar field to store the 1st Invariant of a tensor field
template< typename vectorType>
scalarField volField<vectorType>::I1ofTensor()
{   
    tensor t1;
    symmTensor st1;
    volField<scalarField> result;
    if (typeid(internalField).hash_code()==typeid(t1).hash_code() || typeid(internalField).hash_code()==typeid(st1).hash_code())
    {
        std::string I1FileName="I1of"+fileName_;
                
        result.fileName_=I1FileName;
        result.runTime_=runTime_;        
        
        for(unsigned int i = 0 ; i < internalField.size(); i++){
            result.internalField().push_back(I1(internalField()[i]));            
        }

        for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){

            for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
                result.boundaryField()[i].type() = "fixedValue";
                result.boundaryField()[i].valImposed = true;
                for(unsigned int j = 0 ; j < result.boundaryField()[i].boundary().size(); j++){
                    result.boundaryField()[i].boundary().push_back(I1(boundaryField()[i].boundary()[j]));
                }
            }
        }
    }
    else
    {
        std::cout << "Error: Function volField<vectorType>::I1ofTensor called for a non tensor Field";
    }    
    return result;
}


// calculate a scalar field to store the 2nd Invariant of a tensor field
template< typename vectorType>
scalarField volField<vectorType>::I2ofTensor()
{   
    tensor t1;
    symmTensor st1;
    volField<scalarField> result;
    if (typeid(internalField).hash_code()==typeid(t1).hash_code() || typeid(internalField).hash_code()==typeid(st1).hash_code()) {
       
        std::string I2FileName="I2of"+fileName_;
        
        result.fileName_=I2FileName;
        result.runTime_=runTime_;

        for(unsigned int i = 0 ; i < internalField.size(); i++){
            result.internalField().push_back(I2(internalField()[i]));   
        }

        for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){

            for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
                result.boundaryField()[i].type() = "fixedValue";
                result.boundaryField()[i].valImposed = true;
                for(unsigned int j = 0 ; j < result.boundaryField()[i].boundary().size(); j++){
                    result.boundaryField()[i].boundary().push_back(I2(boundaryField()[i].boundary()[j]));
                }
            }
        }
    }
    else
    {
        std::cout << "Error: Function volField<vectorType>::I2ofTensor called for a non tensor Field";
    }      
    return result;
}

// calculate a scalar field to store the 3rd Invariant of a tensor field
template< typename vectorType>
scalarField volField<vectorType>::I3ofTensor()
{   
    tensor t1;
    symmTensor st1;
    volField<scalarField> result;
    if (typeid(internalField).hash_code()==typeid(t1).hash_code() || typeid(internalField).hash_code()==typeid(st1).hash_code()) {
        
        std::string newName = "I3of"+Name();

        result.setName(newName);
        result.runTime_=runTime_;        

        for(unsigned int i = 0 ; i < internalField_.size(); i++){
            result.internalField().push_back(I3(internalField()[i]));    
        }

        for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){

            for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
                result.boundaryField()[i].type() = "fixedValue";
                result.boundaryField()[i].valImposed = true;
                for(unsigned int j = 0 ; j < result.boundaryField()[i].boundary().size(); j++){
                    result.boundaryField()[i].boundary().push_back(I3(boundaryField()[i].boundary()[j]));
                }
            }
        }
    }
    else
    {
        std::cout << "Error: Function volField<vectorType>::I3ofTensor called for a non tensor Field";
    }   
    return result;
}

// Create a vector field with component of the tensor in one direction
template< typename vectorType>
vectorField volField<vectorType>::projectTensorField(const vector3& v1)
{   
    tensor t1;
    symmTensor st1;
    volField<scalarField> result;
    if (typeid(internalField).hash_code()==typeid(t1).hash_code() || typeid(internalField).hash_code()==typeid(st1).hash_code()) {
        
        std::string newName = "Projof"+result.Name();

        result.setName(newName);
        result.runTime_=runTime_;   
        
        for(unsigned int i = 0 ; i < internalField_.size(); i++){
            result.internalField().push_back(internalField[i] & v1);    
        }

        for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){

            for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
                result.boundaryField()[i].type() = "fixedValue";
                result.boundaryField()[i].valImposed = true;
                for(unsigned int j = 0 ; j < result.boundaryField()[i].boundary().size(); j++){
                    result.boundaryField()[i].boundary().push_back(boundaryField()[i].boundary()[j] & v1);
                }
            }
        }
    }
    else
    {
        std::cout << "Error: Function volField<vectorType>::projectTensorField called for a non tensor Field";
    }        
    return result;
}

// G5 - Contribution
//To compute the magnitude of a vectorField
inline double magVector(const vectorField& v1) {

for (unsigned int i=0; i < v1.size(); i++) {
       double sum = (pow(v1[i][0],2)
                    +pow(v1[i][1],2)
                    +pow(v1[i][2],2));
    double result= sqrt(sum);
              return result;
  } 
   }

// G5 - Contribution
// To compute a scalarField to store the magnitude of the vectorField
template <typename vectorType>
scalarField volField<vectorType>::magVector()
{
  vector3 v1;
  volField<scalarField> result;
  if (typeid(internalField).hash_code()==typeid(v1).hash_code()) {

 std::string magfieldName="magof"+result.Name();
     
     result.setName = magfieldName;
     result.runTime_=runTime_;
  
    for(unsigned int i= 0; i < internalField_.size(); i++){
    result.internalField().push_back(mag(internalField[i]));
   }

  for(unsigned int i = 0; i < mesh_.nPatches_; i++){
 
    for(unsigned int i = 0; i < mesh_.nPatches_; i++){
       result.boundaryField_[i].type = "fixedValue";
       result.boundaryField_[i].valImposed = true;
       for(unsigned int j = 0; j < j < result.boundaryField()[i].boundary().size(); j++){
          result.boundaryField()[i].boundary().push_back(mag(boundaryField()[i].boundary()[j]));  
      }
    }
  }
}
    else
   {
     std::cout << "Error: Function volField<vectorType>::magVector called for a non vector Field";
   }

   return result; 
}
