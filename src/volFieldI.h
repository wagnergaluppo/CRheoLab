#include "volField.h"

template< typename vectorType>
volField<vectorType>::volField(std::string fileName, const Mesh& mesh, const RunTime& time)
:
    IODictionary(mesh.runTime().Path(), fileName),
    mesh_(mesh),
    runTime_(time),
    internalField( readInternalField() )
{}


#include "readVolField.h"