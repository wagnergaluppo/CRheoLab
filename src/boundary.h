#ifndef Boundary_H
#define Boundary_H

#include "IODictionary.h"
#include "Mesh.h"
#include "RunTime.h"


template< typename vectorType>
class Boundary
:
    public IODictionary
{
    public:
    
        // Default constructor
        Boundary(std::string fileName, const Patch& patch, const Mesh& mesh, const RunTime& time);

        // Destructor
        virtual ~Boundary(){} ;

        // Boundary condition structure
        struct patchBoundaryConditions
        {
            std::string type;
            vectorType fieldValue;
            std::map<std::string, std::string> otherInfo;
        };

        // Read Data
        template <typename primitiveType>
        primitiveType readData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter);

        // Read Boundary field
        patchBoundaryConditions readBoundaryField(const std::string& patchName);

        // Returning the field value for the Boudary
        vectorType& boundary();

    private:
        const Mesh& mesh_;
        const RunTime& runTime_;
        const Patch& patch_;
        patchBoundaryConditions boundary_;

};

#endif 