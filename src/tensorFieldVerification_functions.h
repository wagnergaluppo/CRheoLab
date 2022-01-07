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

//random tensor
tensor randTensor()
{
  
  // initialize random seed:
  //srand((unsigned) time(0));
  
  int min = -1000;
  int max =  1000;

  tensor rndTensor;
  rndTensor = {static_cast<double>(rand() % (max-min) + min), static_cast<double>(rand() % (max-min) + min), static_cast<double>(rand() % (max-min) + min),
               static_cast<double>(rand() % (max-min) + min), static_cast<double>(rand() % (max-min) + min), static_cast<double>(rand() % (max-min) + min),
               static_cast<double>(rand() % (max-min) + min), static_cast<double>(rand() % (max-min) + min), static_cast<double>(rand() % (max-min) + min)};
  
  //std::cout << rndTensor << std::endl;
  return rndTensor;
}

//Random Tensor Field
volField<tensorField> randTensorField (std::string name, Mesh& polyMesh, RunTime& time)
{
  volField<tensorField> tensField (name,polyMesh,time,NO_READ);


  for (unsigned int i= 0; i < tensField.internalField().size(); i++)
  {
      tensField.internalField()[i] = randTensor();
  }

  for(unsigned int i = 0; i < polyMesh.nPatches_; i++)
  {
      tensField.boundaryField()[i].type() = "fixedValue";
      tensField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < tensField.boundaryField()[i].boundary().size(); j++)
      {
          tensField.boundaryField()[i].boundary()[j] = randTensor();  
      }
  }
  return tensField;
}

// Off line Tensor Field sum
volField<tensorField> offLineTensorFieldSum(volField<tensorField>& T1, volField<tensorField>& T2)
{
  std::string name = "sum_" + T1.Name() + T2.Name();
  volField<tensorField> resTensorField = T1;


  for (unsigned int i= 0; i < resTensorField.internalField().size(); i++)
  {
      resTensorField.internalField()[i] = T1.internalField()[i] + T2.internalField()[i];
  }

  for(unsigned int i = 0; i < resTensorField.boundaryField().size(); i++)
  {
      resTensorField.boundaryField()[i].type() = "fixedValue";
      resTensorField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resTensorField.boundaryField()[i].boundary().size(); j++)
      {
          resTensorField.boundaryField()[i].boundary()[j] = T1.boundaryField()[i].boundary()[j] +  T2.boundaryField()[i].boundary()[j];  
      }
  }
  return resTensorField;
}

// Off line Tensor Field sub
volField<tensorField> offLineTensorFieldSub(volField<tensorField>& T1, volField<tensorField>& T2)
{
  std::string name = "sub_" + T1.Name() + T2.Name();
  volField<tensorField> resTensorField = T1;


  for (unsigned int i= 0; i < resTensorField.internalField().size(); i++)
  {
      resTensorField.internalField()[i] = T1.internalField()[i] - T2.internalField()[i];
  }

  for(unsigned int i = 0; i < resTensorField.boundaryField().size(); i++)
  {
      resTensorField.boundaryField()[i].type() = "fixedValue";
      resTensorField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resTensorField.boundaryField()[i].boundary().size(); j++)
      {
          resTensorField.boundaryField()[i].boundary()[j] = T1.boundaryField()[i].boundary()[j] - T2.boundaryField()[i].boundary()[j];  
      }
  }
  return resTensorField;
}

// Off line Tensor Field Shift
volField<tensorField> offLineTensorFieldShft(volField<tensorField>& T1, tensor& tensorShft)
{
  std::string name = "shift_" + T1.Name();
  volField<tensorField> resTensorField = T1;


  for (unsigned int i= 0; i < resTensorField.internalField().size(); i++)
  {
      resTensorField.internalField()[i] = T1.internalField()[i] + tensorShft;
  }

  for(unsigned int i = 0; i < resTensorField.boundaryField().size(); i++)
  {
      resTensorField.boundaryField()[i].type() = "fixedValue";
      resTensorField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resTensorField.boundaryField()[i].boundary().size(); j++)
      {
          resTensorField.boundaryField()[i].boundary()[j] = T1.boundaryField()[i].boundary()[j] + tensorShft;  
      }
  }
  return resTensorField;
}

// Off line Vector Field Scale
volField<tensorField> offLineTensorFieldScale(volField<tensorField>& T1, double& scaleFactor)
{
  std::string name = "scale_" + T1.Name();
  volField<tensorField> resTensorField = T1;


  for (unsigned int i= 0; i < resTensorField.internalField().size(); i++)
  {
      resTensorField.internalField()[i] = scaleFactor * T1.internalField()[i];
  }

  for(unsigned int i = 0; i < resTensorField.boundaryField().size(); i++)
  {
      resTensorField.boundaryField()[i].type() = "fixedValue";
      resTensorField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resTensorField.boundaryField()[i].boundary().size(); j++)
      {
          resTensorField.boundaryField()[i].boundary()[j] = scaleFactor * T1.boundaryField()[i].boundary()[j];  
      }
  }
  return resTensorField;
}

//offline Projection of a Tensor Field to Vector Field in one direction
volField<vectorField> offLineTensorFieldProj( volField<tensorField>& T1, vector3& projVect, Mesh& polyMesh, RunTime& time)
{
  std::string name = "proj_" + T1.Name();
  volField<vectorField> resVectField (name,polyMesh,time,NO_READ);

  vector3 normprojVect = projVect / mag(projVect);

  for (unsigned int i= 0; i < resVectField.internalField().size(); i++)
  {
      resVectField.internalField()[i][0] = T1.internalField()[i][0] * normprojVect[0] +
                                           T1.internalField()[i][1] * normprojVect[1] + 
                                           T1.internalField()[i][2] * normprojVect[2] ;
      resVectField.internalField()[i][1] = T1.internalField()[i][3] * normprojVect[0] +
                                           T1.internalField()[i][4] * normprojVect[1] + 
                                           T1.internalField()[i][5] * normprojVect[2] ;
      resVectField.internalField()[i][2] = T1.internalField()[i][6] * normprojVect[0] +
                                           T1.internalField()[i][7] * normprojVect[1] + 
                                           T1.internalField()[i][8] * normprojVect[2] ;                           
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
          resVectField.boundaryField()[i].boundary()[j][1] = T1.boundaryField()[i].boundary()[j][3] * normprojVect[0] +
                                                             T1.boundaryField()[i].boundary()[j][4] * normprojVect[1] + 
                                                             T1.boundaryField()[i].boundary()[j][5] * normprojVect[2] ;
          resVectField.boundaryField()[i].boundary()[j][2] = T1.boundaryField()[i].boundary()[j][6] * normprojVect[0] +
                                                             T1.boundaryField()[i].boundary()[j][7] * normprojVect[1] + 
                                                             T1.boundaryField()[i].boundary()[j][8] * normprojVect[2] ;
      }
  }
  return resVectField;
}

// Scalar Field with the Tensor Invariants I1
volField<scalarField> offLineTensorFieldI1(volField<tensorField>& T1, Mesh& polyMesh, RunTime& time)
{
  
  std::string name = "magof_" + T1.Name();
  volField<scalarField> resScalarField (name,polyMesh,time,NO_READ);


  for (unsigned int i= 0; i < T1.internalField().size(); i++)
  {
      resScalarField.internalField()[i] = T1.internalField()[i][0] + T1.internalField()[i][4] + T1.internalField()[i][8];
  }

  for(unsigned int i = 0; i < T1.boundaryField().size(); i++)
  {
      resScalarField.boundaryField()[i].type() = "fixedValue";
      resScalarField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resScalarField.boundaryField()[i].boundary().size(); j++)
      {
          resScalarField.boundaryField()[i].boundary()[j] = 
                        T1.boundaryField()[i].boundary()[j][0] +
                        T1.boundaryField()[i].boundary()[j][4] + 
                        T1.boundaryField()[i].boundary()[j][8];  
      }
  }
  return resScalarField;
}


// Scalar Field with the Tensor Invariants I2
volField<scalarField> offLineTensorFieldI2(volField<tensorField>& T1, Mesh& polyMesh, RunTime& time)
{
  
  std::string name = "magof_" + T1.Name();
  volField<scalarField> resScalarField (name,polyMesh,time,NO_READ);


  for (unsigned int i= 0; i < T1.internalField().size(); i++)
  {
      resScalarField.internalField()[i] = 
                    T1.internalField()[i][0] * T1.internalField()[i][4] + 
                    T1.internalField()[i][0] * T1.internalField()[i][8] + 
                    T1.internalField()[i][4] * T1.internalField()[i][8] - 
                    T1.internalField()[i][1] * T1.internalField()[i][3] - 
                    T1.internalField()[i][5] * T1.internalField()[i][7] - 
                    T1.internalField()[i][2] * T1.internalField()[i][6];
  }

  for(unsigned int i = 0; i < T1.boundaryField().size(); i++)
  {
      resScalarField.boundaryField()[i].type() = "fixedValue";
      resScalarField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resScalarField.boundaryField()[i].boundary().size(); j++)
      {
          resScalarField.boundaryField()[i].boundary()[j] = 
                        T1.boundaryField()[i].boundary()[j][0] * T1.boundaryField()[i].boundary()[j][4] +
                        T1.boundaryField()[i].boundary()[j][0] * T1.boundaryField()[i].boundary()[j][8] + 
                        T1.boundaryField()[i].boundary()[j][4] * T1.boundaryField()[i].boundary()[j][8] -
                        T1.boundaryField()[i].boundary()[j][1] * T1.boundaryField()[i].boundary()[j][3] - 
                        T1.boundaryField()[i].boundary()[j][5] * T1.boundaryField()[i].boundary()[j][7] -
                        T1.boundaryField()[i].boundary()[j][2] * T1.boundaryField()[i].boundary()[j][6];
      }
  }
  return resScalarField;
}



// Scalar Field with the Tensor Invariants I3
volField<scalarField> offLineTensorFieldI3(volField<tensorField>& T1, Mesh& polyMesh, RunTime& time)
{
  
  std::string name = "magof_" + T1.Name();
  volField<scalarField> resScalarField (name,polyMesh,time,NO_READ);


  for (unsigned int i= 0; i < T1.internalField().size(); i++)
  {
      resScalarField.internalField()[i] = 
                    T1.internalField()[i][0] * T1.internalField()[i][4] * T1.internalField()[i][8] -
                    T1.internalField()[i][0] * T1.internalField()[i][5] * T1.internalField()[i][7] - 
                    T1.internalField()[i][1] * T1.internalField()[i][3] * T1.internalField()[i][8] +
                    T1.internalField()[i][1] * T1.internalField()[i][5] * T1.internalField()[i][6] + 
                    T1.internalField()[i][2] * T1.internalField()[i][3] * T1.internalField()[i][7] -
                    T1.internalField()[i][2] * T1.internalField()[i][4] * T1.internalField()[i][6];
  }
    
  for(unsigned int i = 0; i < T1.boundaryField().size(); i++)
  {
      resScalarField.boundaryField()[i].type() = "fixedValue";
      resScalarField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resScalarField.boundaryField()[i].boundary().size(); j++)
      {
          resScalarField.boundaryField()[i].boundary()[j] =
            T1.boundaryField()[i].boundary()[j][0] * T1.boundaryField()[i].boundary()[j][4] * T1.boundaryField()[i].boundary()[j][8] -
            T1.boundaryField()[i].boundary()[j][0] * T1.boundaryField()[i].boundary()[j][5] * T1.boundaryField()[i].boundary()[j][7] - 
            T1.boundaryField()[i].boundary()[j][1] * T1.boundaryField()[i].boundary()[j][3] * T1.boundaryField()[i].boundary()[j][8] +
            T1.boundaryField()[i].boundary()[j][1] * T1.boundaryField()[i].boundary()[j][5] * T1.boundaryField()[i].boundary()[j][6] + 
            T1.boundaryField()[i].boundary()[j][2] * T1.boundaryField()[i].boundary()[j][3] * T1.boundaryField()[i].boundary()[j][7] -
            T1.boundaryField()[i].boundary()[j][2] * T1.boundaryField()[i].boundary()[j][4] * T1.boundaryField()[i].boundary()[j][6];
      }
  }
  return resScalarField;
}



