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
        

    private:
        std::vector<double> aMatrix_;
        std::vector<double> bVector_;
        int nCells_;
        double absResidual_;
        double relResidual_;
        double residualNormFactor_;
        double wSOR_;
        Solver selectedSolver_;      
  

};

#endif
