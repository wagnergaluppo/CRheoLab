#ifndef Boundary_H
#define Boundary_H

#include "IODictionary.h"
#include "Mesh.h"
#include "RunTime.h"


///@brief Boundary Class stores the field data for a patch (faces on domain boundary).
/// provides attributes to store patch information.

template<typename vectorType>
class Boundary
:
    public IODictionary
{
    public:
    
        // Default constructor
        ///@brief Boundary Class default constructor 
        ///@param fileName name of the file to read field data from
        ///@param patch reference to an object of class Patch
        ///@param time reference to a RunTime object
        ///@param action Enum fileAction ( MUST_READ or NO_READ)
        Boundary(std::string fileName, const Patch& patch, const RunTime& time, fileAction action);

        // Constructor with a default value passed by argument
        ///@brief Boundary Class default constructor 
        ///@param fileName name of the file to read field data from
        ///@param patch reference to an object of class Patch
        ///@param time reference to a RunTime object
        ///@param action Enum fileAction ( MUST_READ or NO_READ)
        ///@param defaultValue is a scalar, vector or a tensor with which the field must be initialized. \note Vectors and tensors must be initialized in braces like: {value1,value2, ...,etc. }.
        Boundary(std::string fileName, const Patch& patch, const RunTime& time, fileAction action, const typename vectorType::value_type& defaultValue);

        // Destructor
        virtual ~Boundary(){} ;

        // Boundary condition structure
        ///@brief This struct creates an object to store patch information.
        struct patchBoundaryConditions
        {
            std::string type;
            bool uniformField;
            vectorType fieldValue;
            std::map<std::string, std::string> otherInfo;
        };

        // Read Data
        template <typename primitiveType>
        primitiveType readData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter);

        // Read Boundary field
        ///@brief this function reads from a specified patch and returns the information as patchBoundaryConditions object.
        ///@param patchName the name of patch for reading information. 
        patchBoundaryConditions readBoundaryField( const std::string& patchName );
        // patchBoundaryConditions readBoundaryField(const std::string& patchName, bool& uniformField);

        // Returning the field value for the Boundary
        vectorType& boundary();

        // Operator Overloading templated
        // Setter
        typename vectorType::value_type& operator[](unsigned int posI);

        // Getter
        typename vectorType::value_type operator[](unsigned int posI) const;
                
    private:
        const Patch& patch_;
        patchBoundaryConditions boundaryValues_;
        // fileAction action_;

};

#include "BoundaryI.h"

#endif 