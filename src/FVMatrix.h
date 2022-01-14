#ifndef FVMATRIX_H
#define FVMATRIX_H

#include "Mesh.h"

//internal data
enum Solver {jacobi, gaussSidel, SOR};


class FVMatrix
{
    public:

        // Default constructor
        FVMatrix(const Mesh& mesh, Solver solver, double solverParam = 0.);

        // Destructor
        virtual ~FVMatrix(){} ;

        // Member Functions
        inline double axMultiplication(const std::vector<double>& aMatrix_, const std::vector<double>& x0Vector, const unsigned int& i);
        inline double axMultiplicationFullLine(const std::vector<double>& aMatrix_, const std::vector<double>& x0Vector, const unsigned int& i);
        inline double normalizedResidualValue(const std::vector<double>& aMatrix_, const std::vector<double>& x0Vector, const std::vector<double>& bVector);
        inline double relativeResidualValue();

    private:
        std::vector<double> aMatrix_;
        std::vector<double> bVector_;
        int nCells_;
        double absResidual_;
        double relResidual_;
        double residualNormFactor_;
        double wSOR_;
        Solver selectedSolver_; 
        double normalizedResidualValue_;     
  

};

#endif
