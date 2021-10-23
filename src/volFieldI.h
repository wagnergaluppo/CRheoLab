#include "volField.h"

template< typename vectorType>
volField<vectorType>::volField(std::string fileName, const Mesh& mesh)
:
    IODictionary(mesh.runTime().Path(), fileName),
    mesh_(mesh),
    internalField( readInternalField() )
{}


#include "readVolField.h"