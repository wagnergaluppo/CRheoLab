#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "mathOperations.h"

vector3 randVector()
{
  
  // initialize random seed:
  //srand((unsigned) time(0));
  
  int min = -1000;
  int max =  1000;

  vector3 rndVector;
  rndVector = {static_cast<double>(rand() % (max-min) + min), static_cast<double>(rand() % (max-min) + min ),static_cast<double>( rand() % (max-min) + min)};
  
  //std::cout << rndVector << std::endl;
  return rndVector;
}

//Random Vector Field
volField<vectorField> randVectorField (std::string name, Mesh& polyMesh, RunTime& time)
{
  volField<vectorField> vectField (name,polyMesh,time,NO_READ);


  for (unsigned int i= 0; i < vectField.internalField().size(); i++)
  {
      vectField.internalField()[i] = randVector();
  }

  for(unsigned int i = 0; i < polyMesh.nPatches_; i++)
  {
      vectField.boundaryField()[i].type() = "fixedValue";
      vectField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < vectField.boundaryField()[i].boundary().size(); j++)
      {
          vectField.boundaryField()[i].boundary()[j] = randVector();  
      }
  }
  return vectField;
}

// Off line Vector Field sum
volField<vectorField> offLineVectorFieldSum(volField<vectorField>& U1, volField<vectorField>& U2)
{
  std::string name = "sum_" + U1.Name() + U2.Name();
  volField<vectorField> resVectField = U1;


  for (unsigned int i= 0; i < resVectField.internalField().size(); i++)
  {
      resVectField.internalField()[i] = U1.internalField()[i] + U2.internalField()[i];
  }

  for(unsigned int i = 0; i < resVectField.boundaryField().size(); i++)
  {
      resVectField.boundaryField()[i].type() = "fixedValue";
      resVectField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resVectField.boundaryField()[i].boundary().size(); j++)
      {
          resVectField.boundaryField()[i].boundary()[j] = U1.boundaryField()[i].boundary()[j] +  U2.boundaryField()[i].boundary()[j];  
      }
  }
  return resVectField;
}

// Off line Vector Field sub
volField<vectorField> offLineVectorFieldSub(volField<vectorField>& U1, volField<vectorField>& U2)
{
  std::string name = "sub_" + U1.Name() + U2.Name();
  volField<vectorField> resVectField = U1;


  for (unsigned int i= 0; i < resVectField.internalField().size(); i++)
  {
      resVectField.internalField()[i] = U1.internalField()[i] - U2.internalField()[i];
  }

  for(unsigned int i = 0; i < resVectField.boundaryField().size(); i++)
  {
      resVectField.boundaryField()[i].type() = "fixedValue";
      resVectField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resVectField.boundaryField()[i].boundary().size(); j++)
      {
          resVectField.boundaryField()[i].boundary()[j] = U1.boundaryField()[i].boundary()[j] - U2.boundaryField()[i].boundary()[j];  
      }
  }
  return resVectField;
}

// Off line Vector Field Shift
volField<vectorField> offLineVectorFieldShft(volField<vectorField>& U1, vector3& vectShft)
{
  std::string name = "shift_" + U1.Name();
  volField<vectorField> resVectField = U1;


  for (unsigned int i= 0; i < resVectField.internalField().size(); i++)
  {
      resVectField.internalField()[i] = U1.internalField()[i] + vectShft;
  }

  for(unsigned int i = 0; i < resVectField.boundaryField().size(); i++)
  {
      resVectField.boundaryField()[i].type() = "fixedValue";
      resVectField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resVectField.boundaryField()[i].boundary().size(); j++)
      {
          resVectField.boundaryField()[i].boundary()[j] = U1.boundaryField()[i].boundary()[j] + vectShft;  
      }
  }
  return resVectField;
}

volField<scalarField> offLineVectorFieldMag(volField<vectorField>& U1, Mesh& polyMesh, RunTime& time)
{
  
  std::string name = "magof_" + U1.Name();
  volField<scalarField> resScalarField (name,polyMesh,time,NO_READ);


  for (unsigned int i= 0; i < U1.internalField().size(); i++)
  {
      resScalarField.internalField()[i] = mag(U1.internalField()[i]);
  }

  for(unsigned int i = 0; i < U1.boundaryField().size(); i++)
  {
      resScalarField.boundaryField()[i].type() = "fixedValue";
      resScalarField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resScalarField.boundaryField()[i].boundary().size(); j++)
      {
          resScalarField.boundaryField()[i].boundary()[j] = mag(U1.boundaryField()[i].boundary()[j]);  
      }
  }
  return resScalarField;
}



// Off line Vector Field Scale
volField<vectorField> offLineVectorFieldScale(volField<vectorField>& U1, double& scaleFactor)
{
  std::string name = "scale_" + U1.Name();
  volField<vectorField> resVectField = U1;


  for (unsigned int i= 0; i < resVectField.internalField().size(); i++)
  {
      resVectField.internalField()[i] = scaleFactor * U1.internalField()[i];
  }

  for(unsigned int i = 0; i < resVectField.boundaryField().size(); i++)
  {
      resVectField.boundaryField()[i].type() = "fixedValue";
      resVectField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resVectField.boundaryField()[i].boundary().size(); j++)
      {
          resVectField.boundaryField()[i].boundary()[j] = scaleFactor * U1.boundaryField()[i].boundary()[j];  
      }
  }
  return resVectField;
}

//offline Project of a Vector Field
volField<vectorField> offLineVectorFieldProj( volField<vectorField>& U1,  vector3& projVect)
{
  std::string name = "proj_" + U1.Name();
  volField<vectorField> resVectField = U1;

  vector3 normProjectVector = projVect / mag(projVect);

  resVectField.internalField() = (U1.internalField() & normProjectVector) * normProjectVector;


  for(unsigned int i = 0; i < resVectField.boundaryField().size(); i++)
  {
      resVectField.boundaryField()[i].type() = "fixedValue";
      resVectField.boundaryField()[i].valImposed() = true;
      resVectField.boundaryField()[i].boundary() = (U1.boundaryField()[i].boundary() & normProjectVector) * normProjectVector;  
  }
  return resVectField;
}
