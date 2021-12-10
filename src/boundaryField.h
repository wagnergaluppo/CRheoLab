#ifndef boundaryField_H
#define boundaryField_H

#include "IODictionary.h"
#include "Mesh.h"
#include "RunTime.h"
#include "boundary.h"

template< typename vectorType>
class boundaryField
{
    public:

        // Default constructor
        boundaryField(std::string fileName, const Mesh& mesh, const RunTime& time, fileAction action);

        // Destructor
        virtual ~boundaryField(){} ;

    private:
        const Mesh& mesh_;
        const RunTime& runTime_;
        vector<boundary<vectorType>> boundaryField_;
        const int& nPatches_ ;
        fileAction action_;

};

#endif
