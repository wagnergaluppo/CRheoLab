#ifndef VOLFIELD_H
#define VOLFIELD_H

#include "IODictionary.h"
#include "RunTime.h"

typedef std::array<double, 3>   vector3;
typedef std::array<double, 9>   tensor;

typedef std::vector<double>     scalarField;
typedef std::vector<vector3>    vectorField;
typedef std::vector<tensor>     tensorField;

template< typename vectorType>
class volField
:
    public IODictionary
{
    public:
        // Default constructor
        volField(std::string fileName, const Mesh& mesh);

        // Destructor
        virtual ~volField(){} ;

        // Member Functions
        vectorType readInternalField();
        
        template <typename primitiveType>
        primitiveType readData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter);

        struct patchBoundaryConditions
        {
            std::string type;
            vectorType fieldValue;
            std::map<std::string, std::string> otherInfo;
        };

        patchBoundaryConditions readBoundaryField(std::string& patchName);

    private:
        const Mesh& mesh_;
        vectorType internalField;

};

#endif 