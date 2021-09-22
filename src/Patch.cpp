#include "Patch.h"


Patch::Patch(std::string name, std::string type, int nFaces, int startFace)
:   name_(name),
    type_(type),
    nFaces_(nFaces),
    startFace_(startFace)
{

}


std::string Patch::name()
{
    return name_;
}
