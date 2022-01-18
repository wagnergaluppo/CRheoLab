#ifndef VOLFIELD_H
#define VOLFIELD_H

#include "IODictionary.h"
#include "RunTime.h"
#include "boundaryField.h"

typedef std::array<double, 3> vector3;
typedef std::array<double, 6> symmTensor;
typedef std::array<double, 9> tensor;

typedef std::vector<double> scalarField;
typedef std::vector<vector3> vectorField;
typedef std::vector<symmTensor> symmTensorField;
typedef std::vector<tensor> tensorField;

template< typename vectorType>
class volField
:
    public IODictionary
{
    public:

        // Default constructor
        volField(std::string fileName, const Mesh& mesh, const RunTime& time, fileAction action);

        // Constructor with a default value passed by argument
        volField(std::string fileName, const Mesh& mesh, const RunTime& time, fileAction action, const typename vectorType::value_type& defaultValue);

        // Destructor
        virtual ~volField(){} ;

        // Member Functions
        vectorType readInternalField();

        // Read Data
        template <typename primitiveType>
        primitiveType readData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter);

        // // Give access to the boundary entities
        // boundaryField<vectorType>& boundaryField();

    private:
        const Mesh& mesh_;
        const RunTime& runTime_;
        vectorType internalField_;
        boundaryField<vectorType> boundaryField_;
        // std::vector<Boundary<vectorType>> boundaryField_;
        // boundaryField<vectorType> boundaryField_; //error: ‘boundaryField’ does not name a type
        // typename boundaryField<vectorType> boundaryField_; //error: ‘boundaryField’ does not name a type
        // typename boundaryField<vectorType>;  // expected nested-name-specifier
        // template < typename boundaryField<vectorType>> boundaryField_; expected nested-name-specifier
        fileAction action_;

};

#include "volFieldI.h"

#endif
