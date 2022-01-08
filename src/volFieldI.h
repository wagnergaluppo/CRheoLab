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

    result.internalField() = result.internalField() - result2.internalField();    
    
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
template<typename vectorType>
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
    //std::cout << "hc1:" << typeid(internalField_[0]).hash_code() << std::endl;
    //std::cout << "hc2:" << typeid(projectVector).hash_code() << std::endl;
    
    if (typeid(internalField_[0]).hash_code()==typeid(projectVector).hash_code()) 
    {
        vector3 normProjectVector = projectVector / mag(projectVector);
        // New operation defined into vectorOperations.h 
        // inline vectorField operator*( const scalarField& s1, const vector3& v1)
        // inline scalarField operator&(const vectorField& v1, const vector3& v2)
        internalField_ = (internalField_ & normProjectVector) * normProjectVector;

        for(unsigned int i = 0 ; i < mesh_.nPatches_; i++){
            if (boundaryField_[i].valImposed()) 
            {       
                boundaryField_[i].boundary() =  (boundaryField_[i].boundary() & normProjectVector) * normProjectVector;                     
            }
        }  
    }   
}

// calculate a scalar field to store the 1st Invariant of a tensor field
template< typename vectorType>
volField<scalarField>  volField<vectorType>::I1ofTensor()
{   
    tensor t1;
    symmTensor st1;
    volField<scalarField> result(Name(),mesh_,runTime_,NO_READ);

    if (typeid(internalField()[0]).hash_code()==typeid(t1).hash_code() || typeid(internalField()[0]).hash_code()==typeid(st1).hash_code())
    {
        std::string I1FileName="I1of"+result.Name();
                
        result.setName(I1FileName);     

        result.internalField()=I1(internalField());

        for(unsigned int i = 0 ; i < mesh_.nPatches_; i++)
        {
          //  for(unsigned int i = 0 ; i < mesh_.nPatches_; i++)
            {
                result.boundaryField()[i].type() = "fixedValue";
                result.boundaryField()[i].valImposed() = true;
                result.boundaryField()[i].boundary()=I1(boundaryField()[i].boundary());
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
volField<scalarField>  volField<vectorType>::I2ofTensor()
{   
    tensor t1;
    symmTensor st1;
    volField<scalarField> result(Name(),mesh_,runTime_,NO_READ);

    if (typeid(internalField()[0]).hash_code()==typeid(t1).hash_code() || typeid(internalField()[0]).hash_code()==typeid(st1).hash_code())
    {
        std::string I2FileName="I2of"+result.Name();
                
        result.setName(I2FileName);     

        result.internalField()=I2(internalField());

        for(unsigned int i = 0 ; i < mesh_.nPatches_; i++)
        {
        //    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++)
            {
                result.boundaryField()[i].type() = "fixedValue";
                result.boundaryField()[i].valImposed() = true;
                result.boundaryField()[i].boundary()=I2(boundaryField()[i].boundary());
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
volField<scalarField>  volField<vectorType>::I3ofTensor()
{   
    tensor t1;
    symmTensor st1;
    volField<scalarField> result(Name(),mesh_,runTime_,NO_READ);

    if (typeid(internalField()[0]).hash_code()==typeid(t1).hash_code() || typeid(internalField()[0]).hash_code()==typeid(st1).hash_code())
    {
        std::string I3FileName="I3of"+result.Name();
                
        result.setName(I3FileName);     

        result.internalField()=I3(internalField());

        for(unsigned int i = 0 ; i < mesh_.nPatches_; i++)
        {
        //    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++)
            {
                result.boundaryField()[i].type() = "fixedValue";
                result.boundaryField()[i].valImposed() = true;
                result.boundaryField()[i].boundary()=I3(boundaryField()[i].boundary());
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
volField<vectorField>  volField<vectorType>::projectTensorField(const vector3& v1)
{   
    tensor t1;
    symmTensor st1;
    volField<vectorField> result(Name(),mesh_,runTime_,NO_READ);
      
    if (typeid(internalField()[0]).hash_code()==typeid(t1).hash_code() || typeid(internalField()[0]).hash_code()==typeid(st1).hash_code())
    {    
        std::string newName = "Projof"+result.Name();
        result.setName(newName);

        vector3 normv1 = v1 / mag(v1); 

        for(unsigned int i = 0 ; i < internalField_.size(); i++)
        {     
        //    result.internalField().push_back(internalField()[i] & normv1);
            result.internalField()[i][0] = internalField()[i][0] * normv1[0] + 
                                           internalField()[i][1] * normv1[1] +
                                           internalField()[i][2] * normv1[2] ;  
            result.internalField()[i][1] = internalField()[i][3] * normv1[0] + 
                                           internalField()[i][4] * normv1[1] +
                                           internalField()[i][5] * normv1[2] ;  
            result.internalField()[i][2] = internalField()[i][6] * normv1[0] + 
                                           internalField()[i][7] * normv1[1] +
                                           internalField()[i][8] * normv1[2] ; 
        }

        for(unsigned int i = 0 ; i < mesh_.nPatches_; i++)
      {
        //    for(unsigned int i = 0 ; i < mesh_.nPatches_; i++)
            {
                result.boundaryField()[i].type() = "fixedValue";
                result.boundaryField()[i].valImposed() = true;
                for(unsigned int j = 0 ; j < result.boundaryField()[i].boundary().size(); j++)
                {
                //    result.boundaryField()[i].boundary().push_back(boundaryField()[i].boundary()[j] & normv1);
                    result.boundaryField()[i].boundary()[j][0] = boundaryField()[i].boundary()[j][0] * normv1[0] + 
                                                                 boundaryField()[i].boundary()[j][1] * normv1[1] +
                                                                 boundaryField()[i].boundary()[j][2] * normv1[2] ;
                    result.boundaryField()[i].boundary()[j][1] = boundaryField()[i].boundary()[j][3] * normv1[0] + 
                                                                 boundaryField()[i].boundary()[j][4] * normv1[1] +
                                                                 boundaryField()[i].boundary()[j][5] * normv1[2] ; 
                    result.boundaryField()[i].boundary()[j][2] = boundaryField()[i].boundary()[j][6] * normv1[0] + 
                                                                 boundaryField()[i].boundary()[j][7] * normv1[1] +
                                                                 boundaryField()[i].boundary()[j][8] * normv1[2] ; 
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
// To compute a scalarField to store the magnitude of the vectorField
template <typename vectorType>
volField<scalarField> volField<vectorType>::magVector()
{
    vector3 v1;
    volField<scalarField> result (Name(),mesh_,runTime_,NO_READ);
    if (typeid(internalField_[0]).hash_code()==typeid(v1).hash_code())
    {
        std::string magfieldName="magof"+result.Name();
        
        result.setName(magfieldName);

        result.internalField() = mag(internalField_);

        for(unsigned int i = 0; i < mesh_.nPatches_; i++)
        {
    
            for(unsigned int i = 0; i < mesh_.nPatches_; i++)
            {
                result.boundaryField()[i].type() = "fixedValue";
                result.boundaryField()[i].valImposed() = true;

                result.boundaryField()[i].boundary() = mag(boundaryField()[i].boundary()); 
            }
        }
    }
        else
    {
        std::cout << "Error: Function volField<vectorType>::magVector called for a non vector Field";
    }

    return result; 
}

// G5 - Contribution
// To compute a scalarField to store the magnitude of the vectorField
template <typename vectorType>
void compareVolFields(std::string operName, volField<vectorType>& f1, volField<vectorType>& f2)
{
  double intFieldError = 0.;
  double bndFieldError = 0.;

  for (unsigned int i= 0; i < f1.internalField().size(); i++)
   {
     double errorRelAdd = abs (mag(f1.internalField()[i] - f2.internalField()[i]) / ( 0.5 * mag(f1.internalField()[i] + f2.internalField()[i])));
     intFieldError += errorRelAdd;
     if ( errorRelAdd > 1e-3){
         std::cout << "Relative Error Internal:" << errorRelAdd << std::endl;
         std::cout << "field 1:" <<  f1.internalField()[i] << std::endl;
         std::cout << "field 2:" <<  f1.internalField()[i] << std::endl << std::endl;
     }
   }

  for(unsigned int i = 0; i < f1.boundaryField().size(); i++)
  {
      for(unsigned int j = 0; j < f1.boundaryField()[i].boundary().size(); j++)
      {
          double errorRelAdd = abs (mag(f1.boundaryField()[i].boundary()[j] -  f2.boundaryField()[i].boundary()[j]) / 
                    ( 0.5 * mag(f1.boundaryField()[i].boundary()[j] +  f2.boundaryField()[i].boundary()[j])));
          bndFieldError += errorRelAdd;
          if ( errorRelAdd > 1e-3){
                std::cout << "Relative Error BND:" << errorRelAdd << std::endl;
                std::cout << "field 1:" <<  f1.internalField()[i] << std::endl;
                std::cout << "field 2:" <<  f1.internalField()[i] << std::endl << std::endl;
            }  
      }
  }
  std::cout << std::endl << "####################################" << std::endl;
  std::cout << "###### Relative Error " << operName << " #####" << std::endl;
  std::cout << "Internal Field: " << intFieldError << std::endl;
  std::cout << "Boundary Field: " << bndFieldError << std::endl;
  std::cout << "####################################" << std::endl << std::endl;
  
}
