#ifndef PATCH_H
#define PATCH_H

#include <string>
#include <cstring>

class Patch
{
    public:
        // Constructor
        Patch(std::string, std::string, int, int, int);

        // Destructor
        virtual ~Patch(){};

        const std::string& name() const;

        // Returns the number of faces in the boundary patch
        int nFaces() const;

        // Returns the index of a patch in the boundary patch list
        int index() const;

    protected:

    private:
        std::string name_;
        std::string type_;
        int nFaces_;
        int startFace_;
        int index_;

};

#endif // PATCH_H
