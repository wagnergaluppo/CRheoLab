#include "FVMatrix.h"

FVMatrix::FVMatrix(const Mesh& mesh, Solver solver, double solverParam):
nCells_(mesh.nCells_), 
selectedSolver_(solver),
residualNormFactor_(0.0) 
{
    if (selectedSolver_ == SOR) wSOR_=solverParam;    
}

inline double FVMatrix::axMultiplication(const std::vector<double>& aMatrix_, const std::vector<double>& x0Vector, const unsigned int& i)
{
        double x = 0.0;

        for(unsigned int j = 0; j < i ; j++)
        {
            x += aMatrix_[j + i * x0Vector.size()] * x0Vector[j];
        }

        for(unsigned int j = i + 1; j < x0Vector.size() ; j++)
        {
            x += aMatrix_[j + i * x0Vector.size()] * x0Vector[j];
        }
    
    return x;
}

inline double FVMatrix::axMultiplicationFullLine(const std::vector<double>& aMatrix_, const std::vector<double>& x0Vector, const unsigned int& i)
{
        double x = 0.0;

        for(unsigned int j = 0; j < x0Vector.size() ; j++)
        {
            x += aMatrix_[j + i * x0Vector.size()] * x0Vector[j];
        }
    
    return x;
}

inline double FVMatrix::normalizedResidualValue(const std::vector<double>& aMatrix_, const std::vector<double>& x0Vector, const std::vector<double>& bVector)
{
    normalizedResidualValue_ = 0.0;

    for(unsigned int i = 0; i < x0Vector.size() ; i++)
    {
        normalizedResidualValue_ += abs(bVector[i] - axMultiplicationFullLine(aMatrix_, x0Vector, i));
    }

    if(residualNormFactor_ == 0)
    {
        residualNormFactor_ = normalizedResidualValue_;
    }

    return normalizedResidualValue_;
}

inline double FVMatrix::relativeResidualValue()
{
    return normalizedResidualValue_ / residualNormFactor_; 
}