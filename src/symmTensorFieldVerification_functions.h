#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "mathOperations.h"

//random vector
vector3 randVector()
{
  
  // initialize random seed:
  //srand((unsigned) time(0));
  
  int min = -1000;
  int max =  1000;

  vector3 rndVector;
  rndVector = {static_cast<double>(rand() % (max-min) + min), static_cast<double>(rand() % (max-min) + min), static_cast<double>(rand() % (max-min) + min) };
  
  //std::cout << rndVector << std::endl;
  return rndVector;
}

//random symmTensor
symmTensor randsymmTensor()
{
  
  // initialize random seed:
  //srand((unsigned) time(0));
  
  int min = -1000;
  int max =  1000;

  symmTensor rndsymmTensor;
  rndsymmTensor = {static_cast<double>(rand() % (max-min) + min), static_cast<double>(rand() % (max-min) + min), static_cast<double>(rand() % (max-min) + min),
                   static_cast<double>(rand() % (max-min) + min), static_cast<double>(rand() % (max-min) + min), static_cast<double>(rand() % (max-min) + min)};
  
  //std::cout << rndsymmTensor << std::endl;
  return rndsymmTensor;
}

//Random symmTensor Field
volField<symmTensorField> randsymmTensorField (std::string name, Mesh& polyMesh, RunTime& time)
{
  volField<symmTensorField> symmTensField (name,polyMesh,time,NO_READ);


  for (unsigned int i= 0; i < symmTensField.internalField().size(); i++)
  {
      symmTensField.internalField()[i] = randsymmTensor();
  }

  for(unsigned int i = 0; i < polyMesh.nPatches_; i++)
  {
      symmTensField.boundaryField()[i].type() = "fixedValue";
      symmTensField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < symmTensField.boundaryField()[i].boundary().size(); j++)
      {
          symmTensField.boundaryField()[i].boundary()[j] = randsymmTensor();  
      }
  }
  return symmTensField;
}

// Off line symmTensor Field sum
volField<symmTensorField> offLinesymmTensorFieldSum(volField<symmTensorField>& T1, volField<symmTensorField>& T2)
{
  std::string name = "sum_" + T1.Name() + T2.Name();
  volField<symmTensorField> resSymmTensorField = T1;


  for (unsigned int i= 0; i < resSymmTensorField.internalField().size(); i++)
  {
      resSymmTensorField.internalField()[i] = T1.internalField()[i] + T2.internalField()[i];
  }

  for(unsigned int i = 0; i < resSymmTensorField.boundaryField().size(); i++)
  {
      resSymmTensorField.boundaryField()[i].type() = "fixedValue";
      resSymmTensorField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resSymmTensorField.boundaryField()[i].boundary().size(); j++)
      {
          resSymmTensorField.boundaryField()[i].boundary()[j] = T1.boundaryField()[i].boundary()[j] +  T2.boundaryField()[i].boundary()[j];  
      }
  }
  return resSymmTensorField;
}

// Off line symmTensor Field sub
volField<symmTensorField> offLinesymmTensorFieldSub(volField<symmTensorField>& T1, volField<symmTensorField>& T2)
{
  std::string name = "sub_" + T1.Name() + T2.Name();
  volField<symmTensorField> resSymmTensorField = T1;


  for (unsigned int i= 0; i < resSymmTensorField.internalField().size(); i++)
  {
      resSymmTensorField.internalField()[i] = T1.internalField()[i] - T2.internalField()[i];
  }

  for(unsigned int i = 0; i < resSymmTensorField.boundaryField().size(); i++)
  {
      resSymmTensorField.boundaryField()[i].type() = "fixedValue";
      resSymmTensorField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resSymmTensorField.boundaryField()[i].boundary().size(); j++)
      {
          resSymmTensorField.boundaryField()[i].boundary()[j] = T1.boundaryField()[i].boundary()[j] - T2.boundaryField()[i].boundary()[j];  
      }
  }
  return resSymmTensorField;
}

// Off line symmTensor Field Shift
volField<symmTensorField> offLinesymmTensorFieldShft(volField<symmTensorField>& T1, symmTensor& symmTensorShft)
{
  std::string name = "shift_" + T1.Name();
  volField<symmTensorField> resSymmTensorField = T1;


  for (unsigned int i= 0; i < resSymmTensorField.internalField().size(); i++)
  {
      resSymmTensorField.internalField()[i] = T1.internalField()[i] + symmTensorShft;
  }

  for(unsigned int i = 0; i < resSymmTensorField.boundaryField().size(); i++)
  {
      resSymmTensorField.boundaryField()[i].type() = "fixedValue";
      resSymmTensorField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resSymmTensorField.boundaryField()[i].boundary().size(); j++)
      {
          resSymmTensorField.boundaryField()[i].boundary()[j] = T1.boundaryField()[i].boundary()[j] + symmTensorShft;  
      }
  }
  return resSymmTensorField;
}

// Off line Vector Field Scale
volField<symmTensorField> offLinesymmTensorFieldScale(volField<symmTensorField>& T1, double& scaleFactor)
{
  std::string name = "scale_" + T1.Name();
  volField<symmTensorField> resSymmTensorField = T1;


  for (unsigned int i= 0; i < resSymmTensorField.internalField().size(); i++)
  {
      resSymmTensorField.internalField()[i] = scaleFactor * T1.internalField()[i];
  }

  for(unsigned int i = 0; i < resSymmTensorField.boundaryField().size(); i++)
  {
      resSymmTensorField.boundaryField()[i].type() = "fixedValue";
      resSymmTensorField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resSymmTensorField.boundaryField()[i].boundary().size(); j++)
      {
          resSymmTensorField.boundaryField()[i].boundary()[j] = scaleFactor * T1.boundaryField()[i].boundary()[j];  
      }
  }
  return resSymmTensorField;
}

//offline Projection of a symmTensor Field to Vector Field in one direction
volField<vectorField> offLinesymmTensorFieldProj( volField<symmTensorField>& T1, vector3& projVect, Mesh& polyMesh, RunTime& time)
{
  std::string name = "proj_" + T1.Name();
  volField<vectorField> resVectField (name,polyMesh,time,NO_READ);

  vector3 normprojVect = projVect / mag(projVect);

  for (unsigned int i= 0; i < resVectField.internalField().size(); i++)
  {
      resVectField.internalField()[i][0] = T1.internalField()[i][0] * normprojVect[0] +
                                           T1.internalField()[i][1] * normprojVect[1] + 
                                           T1.internalField()[i][2] * normprojVect[2] ;
      resVectField.internalField()[i][1] = T1.internalField()[i][1] * normprojVect[0] +
                                           T1.internalField()[i][3] * normprojVect[1] + 
                                           T1.internalField()[i][4] * normprojVect[2] ;
      resVectField.internalField()[i][2] = T1.internalField()[i][2] * normprojVect[0] +
                                           T1.internalField()[i][4] * normprojVect[1] + 
                                           T1.internalField()[i][5] * normprojVect[2] ;                           
  }
 
  for(unsigned int i = 0; i < resVectField.boundaryField().size(); i++)
  {
      resVectField.boundaryField()[i].type() = "fixedValue";
      resVectField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resVectField.boundaryField()[i].boundary().size(); j++)
      {
          resVectField.boundaryField()[i].boundary()[j][0] = T1.boundaryField()[i].boundary()[j][0] * normprojVect[0] +
                                                             T1.boundaryField()[i].boundary()[j][1] * normprojVect[1] + 
                                                             T1.boundaryField()[i].boundary()[j][2] * normprojVect[2] ;
          resVectField.boundaryField()[i].boundary()[j][1] = T1.boundaryField()[i].boundary()[j][1] * normprojVect[0] +
                                                             T1.boundaryField()[i].boundary()[j][3] * normprojVect[1] + 
                                                             T1.boundaryField()[i].boundary()[j][4] * normprojVect[2] ;
          resVectField.boundaryField()[i].boundary()[j][2] = T1.boundaryField()[i].boundary()[j][2] * normprojVect[0] +
                                                             T1.boundaryField()[i].boundary()[j][4] * normprojVect[1] + 
                                                             T1.boundaryField()[i].boundary()[j][5] * normprojVect[2] ;
      }
  }
  return resVectField;
}

// Scalar Field with the symmTensor Invariants I1
volField<scalarField> offLinesymmTensorFieldI1(volField<symmTensorField>& T1, Mesh& polyMesh, RunTime& time)
{
  
  std::string name = "magof_" + T1.Name();
  volField<scalarField> resScalarField (name,polyMesh,time,NO_READ);


  for (unsigned int i= 0; i < T1.internalField().size(); i++)
  {
      resScalarField.internalField()[i] = T1.internalField()[i][0] + T1.internalField()[i][3] + T1.internalField()[i][5];
  }

  for(unsigned int i = 0; i < T1.boundaryField().size(); i++)
  {
      resScalarField.boundaryField()[i].type() = "fixedValue";
      resScalarField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resScalarField.boundaryField()[i].boundary().size(); j++)
      {
          resScalarField.boundaryField()[i].boundary()[j] = 
                        T1.boundaryField()[i].boundary()[j][0] +
                        T1.boundaryField()[i].boundary()[j][3] + 
                        T1.boundaryField()[i].boundary()[j][5];  
      }
  }
  return resScalarField;
}


// Scalar Field with the symmTensor Invariants I2
volField<scalarField> offLinesymmTensorFieldI2(volField<symmTensorField>& T1, Mesh& polyMesh, RunTime& time)
{
  
  std::string name = "magof_" + T1.Name();
  volField<scalarField> resScalarField (name,polyMesh,time,NO_READ);


  for (unsigned int i= 0; i < T1.internalField().size(); i++)
  {
      resScalarField.internalField()[i] = 
                    T1.internalField()[i][0] * T1.internalField()[i][3] + 
                    T1.internalField()[i][0] * T1.internalField()[i][5] + 
                    T1.internalField()[i][3] * T1.internalField()[i][5] - 
                    T1.internalField()[i][1] * T1.internalField()[i][1] - 
                    T1.internalField()[i][4] * T1.internalField()[i][4] - 
                    T1.internalField()[i][2] * T1.internalField()[i][2];
  }

  for(unsigned int i = 0; i < T1.boundaryField().size(); i++)
  {
      resScalarField.boundaryField()[i].type() = "fixedValue";
      resScalarField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resScalarField.boundaryField()[i].boundary().size(); j++)
      {
          resScalarField.boundaryField()[i].boundary()[j] = 
                        T1.boundaryField()[i].boundary()[j][0] * T1.boundaryField()[i].boundary()[j][3] +
                        T1.boundaryField()[i].boundary()[j][0] * T1.boundaryField()[i].boundary()[j][5] + 
                        T1.boundaryField()[i].boundary()[j][3] * T1.boundaryField()[i].boundary()[j][5] -
                        T1.boundaryField()[i].boundary()[j][1] * T1.boundaryField()[i].boundary()[j][1] - 
                        T1.boundaryField()[i].boundary()[j][4] * T1.boundaryField()[i].boundary()[j][4] -
                        T1.boundaryField()[i].boundary()[j][2] * T1.boundaryField()[i].boundary()[j][2];
      }
  }
  return resScalarField;
}



// Scalar Field with the symmTensor Invariants I3
volField<scalarField> offLinesymmTensorFieldI3(volField<symmTensorField>& T1, Mesh& polyMesh, RunTime& time)
{
  
  std::string name = "magof_" + T1.Name();
  volField<scalarField> resScalarField (name,polyMesh,time,NO_READ);


  for (unsigned int i= 0; i < T1.internalField().size(); i++)
  {
      resScalarField.internalField()[i] = 
                    T1.internalField()[i][0] * T1.internalField()[i][3] * T1.internalField()[i][5] +
                    T1.internalField()[i][1] * T1.internalField()[i][4] * T1.internalField()[i][2] + 
                    T1.internalField()[i][2] * T1.internalField()[i][1] * T1.internalField()[i][4] - (
                    T1.internalField()[i][2] * T1.internalField()[i][3] * T1.internalField()[i][2] +
                    T1.internalField()[i][0] * T1.internalField()[i][4] * T1.internalField()[i][4] + 
                    T1.internalField()[i][1] * T1.internalField()[i][1] * T1.internalField()[i][5] )

                    ;
  }
 
    
  for(unsigned int i = 0; i < T1.boundaryField().size(); i++)
  {
      resScalarField.boundaryField()[i].type() = "fixedValue";
      resScalarField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resScalarField.boundaryField()[i].boundary().size(); j++)
      {
          resScalarField.boundaryField()[i].boundary()[j] =
            T1.boundaryField()[i].boundary()[j][0] * T1.boundaryField()[i].boundary()[j][3] * T1.boundaryField()[i].boundary()[j][5] -
            T1.boundaryField()[i].boundary()[j][0] * T1.boundaryField()[i].boundary()[j][4] * T1.boundaryField()[i].boundary()[j][4] - 
            T1.boundaryField()[i].boundary()[j][1] * T1.boundaryField()[i].boundary()[j][1] * T1.boundaryField()[i].boundary()[j][5] +
            T1.boundaryField()[i].boundary()[j][1] * T1.boundaryField()[i].boundary()[j][4] * T1.boundaryField()[i].boundary()[j][2] + 
            T1.boundaryField()[i].boundary()[j][2] * T1.boundaryField()[i].boundary()[j][1] * T1.boundaryField()[i].boundary()[j][4] -
            T1.boundaryField()[i].boundary()[j][2] * T1.boundaryField()[i].boundary()[j][3] * T1.boundaryField()[i].boundary()[j][2];
      }
  }
  return resScalarField;
}



