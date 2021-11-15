#ifndef VOLFIELD_H
#define VOLFIELD_H

#include "IODictionary.h"
#include "RunTime.h"

typedef std::array<double, 3> vector3;
typedef std::array<double, 6> symmTensor;
typedef std::array<double, 9> tensor;

typedef std::vector<double> scalarField;
typedef std::vector<vector3> vectorField;
typedef std::vector<symmTensor> symmTensorField;
typedef std::vector<tensor> tensorField;

template< typename vectorType>
class volField
:
    public IODictionary
{
    public:
    
        // Default constructor
        volField(std::string fileName, const Mesh& mesh, const RunTime& time);

        // Destructor
        virtual ~volField(){} ;

        // Member Functions
        vectorType readInternalField();
        
        // Read Data
        template <typename primitiveType>
        primitiveType readData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter);

        // Boundary condition structure
        struct patchBoundaryConditions
        {
            std::string type;
            vectorType fieldValue;
            std::map<std::string, std::string> otherInfo;
        };

        // Read boundary field
        patchBoundaryConditions readBoundaryField(std::string& patchName);

    private:
        const Mesh&     mesh_;
        const RunTime&  runTime_;
        vectorType internalField;

};

#endif 