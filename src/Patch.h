#ifndef PATCH_H
#define PATCH_H

#include <string>
#include <cstring>

class Patch
{
    public:
        // Constructor
        Patch(std::string, std::string, int, int);

        // Destructor
        virtual ~Patch(){};
        
        std::string name();
               
    protected:

    private:
        std::string name_;
        std::string type_;
        int nFaces_;
        int startFace_;

};

#endif // PATCH_H
