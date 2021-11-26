#ifndef Boundary_H
#define Boundary_H

#include "IODictionary.h"
#include "Mesh.h"
#include "RunTime.h"


template<typename vectorType>
class Boundary
:
    public IODictionary
{
    public:
    
        // Default constructor
        Boundary(std::string fileName, const Patch& patch, const RunTime& time);

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

        // Returning the field value for the Boundary
        vectorType& boundary();

        // Returning the size of the boundary patch
        const int& size() const;
        
        // TODO Group4 Returning the index in the boundaryField for the patch given name 
        const bool patchID(std::string patchName) const;

        // TODO Group4 Returning the name of a patch for the given index at the boundaryField
        const std::string patchName() const;
        
        // Operator Overloading templated
        // Setter
        typename vectorType::value_type& operator[](unsigned int posI);

        // Getter
        typename vectorType::value_type operator[](unsigned int posI) const;
        
    private:
        // const Mesh& mesh_;
        const RunTime& runTime_;
        const Patch& patch_;
        patchBoundaryConditions boundary_;
        int size_;

};

#endif 