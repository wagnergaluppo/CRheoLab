#ifndef FIELDDICTIONARY_H
#define FIELDDICTIONARY_H

#include "Dictionary.h"

template< typename vectorType>
class FieldDictionary
:
public Dictionary
{
    public:
        // Default constructor
        FieldDictionary(std::string path, std::string fileName);
        
        // Destructor
        virtual ~FieldDictionary(){} ;

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
};

#endif 