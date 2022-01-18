#ifndef boundaryField_H
#define boundaryField_H

#include "IODictionary.h"
#include "Mesh.h"
#include "RunTime.h"
#include "Boundary.h"


///@brief boundaryField Class stores the field data and other information for all the patches.

template< typename vectorType>
class boundaryField
{
    public:

        // Default constructor

        ///@brief boundaryField Class default constructor 
        ///@param fileName name of the file to read field data from
        ///@param action Enum fileAction ( MUST_READ or NO_READ)
        boundaryField(std::string fileName, const Mesh& mesh, const RunTime& time, fileAction action);

        // Destructor
        virtual ~boundaryField(){} ;

        // Returning the size of the boundary patch
        ///@brief Returns the size of the boundary patch
        const int& size() const;
        

        ///@brief Returns the index in the boundaryField patch list for the give patch name 
        // Returning the index in the boundaryField patch list for the give patch name 
        const int& patchID(const std::string& patchName) const;

        // Returning the name in the boundaryField patch list for the give patch index 
        ///@brief Returns the name in the boundaryField patch list for the give patch index 
        const std::string& patchName(const int& ID) const;

        vector<Boundary<vectorType>> boundaryField_;
        
    private:
        const int& nPatches_ ;
        fileAction action_;

};

#include "boundaryFieldI.h"

#endif
