#ifndef boundaryField_H
#define boundaryField_H

#include "IODictionary.h"
#include "Mesh.h"
#include "RunTime.h"
#include "Boundary.h"

template< typename vectorType>
class boundaryField
{
    public:

        // Default constructor
        boundaryField(std::string fileName, const Mesh& mesh, const RunTime& time, fileAction action);

        // Destructor
        virtual ~boundaryField(){} ;

        // Returning the size of the boundary patch
        const int& size() const;
        
        // Returning the index in the boundaryField patch list for the give patch name 
        const int& patchID(const std::string& patchName) const;

        // Returning the name in the boundaryField patch list for the give patch index 
        const std::string& patchName(const int& ID) const;

    private:
        const Mesh& mesh_;
        const RunTime& runTime_;
        vector<boundary<vectorType>> boundaryField_;
        const int& nPatches_ ;
        fileAction action_;

};

#endif
