#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <typeinfo>
#include <sstream> 
#include <array>
#include <stdexcept>
#include <vector>
#include <map>

#include "Dictionary.cpp"
#include "FieldDictionary.cpp"

#include <libgen.h>         // dirname
#include <unistd.h>         // readlink
#include <linux/limits.h>   // PATH_MAX

std::string getExecutablePath()
{
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );

    std::string executablePath ( result, (count > 0) ? count : 0 );

    executablePath=executablePath.substr(0, executablePath.find_last_of("/"));
    executablePath+='/';

    return executablePath;
}



int main(int argCount, char *args[])
{

   std::string path = getExecutablePath();

   std::string filename = "U";

   std::string patch = "bottom";



/*   //std::string inlet = "left";

    // read InternalField
    vectorField internalFieldU = readInternalField<vectorField, std::array<double,3>>(path, filename);
    

    // read boundary information
    patchBoundaryConditions<vectorField> patch1(readBoundaryField<vectorField, std::array<double,3>>(path, filename, inlet));


    // Find scalar in file
    double banana = findScalar(path, filename, std::string("banana"));
    
    // Find string in file
    std::string word = findAsString(path, filename, std::string("mu"));
    
    // Find header in file. 
    std::map<std::string, std::string> header (readHeader(path, filename));*/




    FieldDictionary<vectorField> b(path, filename); 
    vectorField internalField2 (b.readInternalField());

   // FieldDictionary<tensorField> a(path, filename); 
    //tensorField internalField (a.readInternalField());


    FieldDictionary<vectorField>::patchBoundaryConditions banana (b.readBoundaryField(patch));

    return 0;

}
