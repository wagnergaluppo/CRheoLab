#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "mathOperations.h"

double randScalar()
{
  
  // initialize random seed:
  //srand((unsigned) time(0));
  
  int min = -1000;
  int max =  1000;

  double rndScalar;
  rndScalar = static_cast<double>(rand() % (max-min) + min);
  
  //std::cout << rndVector << std::endl;
  return rndScalar;
}

//Random Scalar Field
volField<scalarField> randScalarField (std::string name, Mesh& polyMesh, RunTime& time)
{
  volField<scalarField> sField (name,polyMesh,time,NO_READ);


  for (unsigned int i= 0; i < sField.internalField().size(); i++)
  {
      sField.internalField()[i] = randScalar();
  }

  for(unsigned int i = 0; i < polyMesh.nPatches_; i++)
  {
      sField.boundaryField()[i].type() = "fixedValue";
      sField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < sField.boundaryField()[i].boundary().size(); j++)
      {
          sField.boundaryField()[i].boundary()[j] = randScalar();  
      }
  }
  return sField;
}

// Off line Scalar Field sum
volField<scalarField> offLineScalarFieldSum(volField<scalarField>& s1, volField<scalarField>& s2)
{
  std::string name = "sum_" + s1.Name() + s2.Name();
  volField<scalarField> resScalarField = s1;


  for (unsigned int i= 0; i < resScalarField.internalField().size(); i++)
  {
      resScalarField.internalField()[i] = s1.internalField()[i] + s2.internalField()[i];
  }

  for(unsigned int i = 0; i < resScalarField.boundaryField().size(); i++)
  {
      resScalarField.boundaryField()[i].type() = "fixedValue";
      resScalarField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resScalarField.boundaryField()[i].boundary().size(); j++)
      {
          resScalarField.boundaryField()[i].boundary()[j] = s1.boundaryField()[i].boundary()[j] +  s2.boundaryField()[i].boundary()[j];  
      }
  }
  return resScalarField;
}

// Off line Scalar Field sub
volField<scalarField> offLineScalarFieldSub(volField<scalarField>& s1, volField<scalarField>& s2)
{
  std::string name = "sub_" + s1.Name() + s2.Name();
  volField<scalarField> resScalarField = s1;


  for (unsigned int i= 0; i < resScalarField.internalField().size(); i++)
  {
      resScalarField.internalField()[i] = s1.internalField()[i] - s2.internalField()[i];
  }

  for(unsigned int i = 0; i < resScalarField.boundaryField().size(); i++)
  {
      resScalarField.boundaryField()[i].type() = "fixedValue";
      resScalarField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resScalarField.boundaryField()[i].boundary().size(); j++)
      {
          resScalarField.boundaryField()[i].boundary()[j] = s1.boundaryField()[i].boundary()[j] -  s2.boundaryField()[i].boundary()[j];  
      }
  }
  return resScalarField;
}



// Off line Vector Field Shift
volField<scalarField> offLineScalarFieldShft(volField<scalarField>& s1, double& scalarShft)
{
  std::string name = "shift_" + s1.Name();
  volField<scalarField> resScalarField = s1;


  for (unsigned int i= 0; i < resScalarField.internalField().size(); i++)
  {
      resScalarField.internalField()[i] = s1.internalField()[i] + scalarShft;
  }

  for(unsigned int i = 0; i < resScalarField.boundaryField().size(); i++)
  {
      resScalarField.boundaryField()[i].type() = "fixedValue";
      resScalarField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resScalarField.boundaryField()[i].boundary().size(); j++)
      {
          resScalarField.boundaryField()[i].boundary()[j] = s1.boundaryField()[i].boundary()[j] + scalarShft;  
      }
  }
  return resScalarField;
}


// Off line Scalar Field Scale
volField<scalarField> offLineScalarFieldScale(volField<scalarField>& s1, double& scaleFactor)
{
  std::string name = "scale_" + s1.Name();
  volField<scalarField> resScalarField = s1;


  for (unsigned int i= 0; i < resScalarField.internalField().size(); i++)
  {
      resScalarField.internalField()[i] = scaleFactor * s1.internalField()[i];
  }

  for(unsigned int i = 0; i < resScalarField.boundaryField().size(); i++)
  {
      resScalarField.boundaryField()[i].type() = "fixedValue";
      resScalarField.boundaryField()[i].valImposed() = true;
      for(unsigned int j = 0; j < resScalarField.boundaryField()[i].boundary().size(); j++)
      {
          resScalarField.boundaryField()[i].boundary()[j] = scaleFactor * s1.boundaryField()[i].boundary()[j];  
      }
  }
  return resScalarField;
}

