#include "FVMatrix.h"

FVMatrix::FVMatrix(const Mesh& mesh, Solver solver, double absNormResidual, double relNormResidual,  double solverParam ):
selectedSolver_(solver),
absNormResidual_(absNormResidual),
relNormResidual_(relNormResidual),
nCells_(mesh.nCells_), 
residualNormFactor_(-1.0)
{
    if (selectedSolver_ == SOR) wSOR_=solverParam;    
}

inline double FVMatrix::axMultiplicationNoDiagonal(const std::vector<double>& aMatrix_, const std::vector<double>& x0Vector, const unsigned int& lineI)
{
        double x = 0.0;

        for(unsigned int j = 0; j < lineI ; j++)
        {
            x += aMatrix_[j + lineI * nCells_] * x0Vector[j];
        }

        for(unsigned int j = lineI + 1; j < nCells_ ; j++)
        {
            x += aMatrix_[j + lineI * nCells_] * x0Vector[j];
        }
    
    return x;
}

inline double FVMatrix::axMultiplication(const std::vector<double>& aMatrix_, const std::vector<double>& x0Vector, const unsigned int& lineI)
{
        double x = 0.0;

        for(unsigned int j = 0; j < nCells_ ; j++)
        {
            x += aMatrix_[j + lineI * nCells_] * x0Vector[j];
        }
    
    return x;
}

inline double FVMatrix::normalizedResidualValue(const std::vector<double>& aMatrix_, const std::vector<double>& x0Vector, const std::vector<double>& bVector)
{
    double residualMagnitude = 0.0;  

    for(unsigned int i = 0; i < nCells_ ; i++)
    {
        residualMagnitude += abs(bVector[i] - axMultiplication(aMatrix_, x0Vector, i));
    }

    if(residualNormFactor_ > 0.0) //in the constructor is initilized with -1.0 then we can check if it was initialized or not.
        return (residualMagnitude/residualNormFactor_);
    else 
    {
        residualNormFactor_ = residualMagnitude;
        return 1.0;
    }
}
