#ifndef boundary_H
#define boundary_H

#include "IODictionary.h"
#include "Mesh.h"
#include "RunTime.h"


template< typename vectorType>
class boundary
:
    public IODictionary
{
    public:
    
        // Default constructor
        boundary(std::string fileName, const Patch& patch, const Mesh& mesh, const RunTime& time);

        // Destructor
        virtual ~boundary(){} ;

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

        // Read boundary field
        patchBoundaryConditions readBoundaryField(const std::string& patchName);

    private:
        const Mesh& mesh_;
        const RunTime& runTime_;
        const Patch& patch_;
        patchBoundaryConditions boundary_;

};

#endif 