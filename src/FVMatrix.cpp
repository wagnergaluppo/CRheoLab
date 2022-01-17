#include "FVMatrix.h"
#include <vector>
#include <random>

FVMatrix::FVMatrix(const Mesh& mesh, vector<double>& xVector, Solver solver, double absNormResidual, double relNormResidual,  double solverParam):
selectedSolver_(solver),
absNormResidual_(absNormResidual),
relNormResidual_(relNormResidual),
nCells_(mesh.nCells_), // (mesh.nCells_) 
residualNormFactor_(-1.0)

{
    aMatrix_.resize(nCells_*nCells_);
    bVector_.resize(nCells_);
    createRandomaMatrixbVector();
    xVector_.resize(nCells_);
    xVector_ = xVector;
    if (selectedSolver_ == SOR) wSOR_=solverParam;    
}
 

inline double FVMatrix::axMultiplicationNoDiagonal(const unsigned int& lineI)
{
        double x = 0.0;

        for(unsigned int j = 0; j < lineI ; j++)
        {
            x += aMatrix_[j + lineI * nCells_] * xVector_[j];
        }

        for(unsigned int j = lineI + 1; j < nCells_ ; j++)
        {
            x += aMatrix_[j + lineI * nCells_] * xVector_[j];
        }
    
    return x;
}

inline double FVMatrix::axMultiplication(const unsigned int& lineI)
{
        double x = 0.0;

        for(unsigned int j = 0; j < nCells_ ; j++)
        {
            x += aMatrix_[j + lineI * nCells_] * xVector_[j];
        }
    
    return x;
}

inline double FVMatrix::normalizedResidualValue()
{
    double residualMagnitude = 0.0;  

    for(unsigned int i = 0; i < nCells_ ; i++)
    {
        residualMagnitude += abs(bVector_[i] - axMultiplication(i));
    }

    if(residualNormFactor_ > 0.0) //in the constructor is initilized with -1.0 then we can check if it was initialized or not.
        return (residualMagnitude/residualNormFactor_);
    else 
    {
        residualNormFactor_ = residualMagnitude;
        return 1.0;
    }
}

void FVMatrix::printaMatrix(std::vector<double>& mat, int n, int m)
{    
    int k=0;
    for (int i = 0; i < n; i++)    
    {
        for (int j = 0; j < m; j++) {         
            std::cout <<  mat[i+k+j+k] << " ";
        }        
        std::cout << std::endl;
        k= k+m;        
    }    
}

void FVMatrix::createRandomaMatrixbVector()
{
    std::cout << ">> entered createaMatrix " << std::endl;
    
    int maxValue = 10;
   
    for(unsigned int lineI = 0; lineI < nCells_ ; lineI++)
    {
        double diagValue = 0.0;
        for(unsigned int j = 0; j < lineI ; j++)
        {
            aMatrix_[j + lineI * nCells_] = (static_cast<double>(rand() % maxValue) *(-1));
            diagValue += abs( aMatrix_[j + lineI * nCells_]);
        }

        for(unsigned int j = lineI + 1; j < nCells_ ; j++)
        {
            aMatrix_[j + lineI * nCells_] = (static_cast<double>(rand() % maxValue) *(-1));
            diagValue += abs( aMatrix_[j + lineI * nCells_]);
        }
        aMatrix_[lineI + lineI * nCells_]= 1.1 * diagValue;
        bVector_[lineI]= (static_cast<double>(rand() % maxValue));
    }    
    std::cout << ">> leaving createaMatrix " << std::endl;        
}

std::vector<double> FVMatrix::doJacobi(){
    std::vector<double> result(nCells_);    
    
    for(unsigned int lineI = 0; lineI < nCells_; lineI++)
    {
        result[lineI] = (bVector_[lineI] - axMultiplicationNoDiagonal(lineI))/aMatrix_[lineI*nCells_+lineI];            
    }      
    return result;
}

std::vector<double> FVMatrix::doGaussSidel()
{
    std::vector<double> result(nCells_);    
    
    for(unsigned int lineI = 0; lineI < nCells_; lineI++)
    {
        result[lineI] = (bVector_[lineI] - axMultiplicationNoDiagonal(lineI))/aMatrix_[lineI*nCells_+lineI];
        xVector_[lineI] = result[lineI];
    }      
    return result; 
}

std::vector<double> FVMatrix::doSOR(){
    std::vector<double> result(nCells_);    
    
    for(unsigned int lineI = 0; lineI < nCells_; lineI++)
    {
        result[lineI] = (bVector_[lineI] - axMultiplicationNoDiagonal(lineI))/aMatrix_[lineI*nCells_+lineI];
        xVector_[lineI] =  xVector_[lineI] * (1-wSOR_) + wSOR_*result[lineI];
    }      
    return result; 
}

std::vector<double> FVMatrix::solve()
{
    std::vector<double> result(nCells_);    
    double initialResidual =  normalizedResidualValue();
    double residual = initialResidual;
    int count=0;

    if (selectedSolver_ == jacobi){
        while (residual > absNormResidual_ && residual/initialResidual > relNormResidual_)       
        {                
            result = doJacobi();
            xVector_ = result;
            residual = normalizedResidualValue();
            count++;            
        }
    }
    else if (selectedSolver_ == gaussSidel){
        while (residual > absNormResidual_ && residual/initialResidual > relNormResidual_)      
        {            
            result = doGaussSidel();
            xVector_ = result;
            residual = normalizedResidualValue();
            count++;
        }
    }
    else {
       while (residual > absNormResidual_ && residual/initialResidual > relNormResidual_)       
        {            
            result = doSOR();
            xVector_ = result;
            residual = normalizedResidualValue();
            count++;
        }
    }
    std::cout << "Num Iterations: " << count << std::endl;
    std::cout << "Initial Residual: " << std::scientific << initialResidual << " Final Residual: " << std::scientific << residual << std::endl;      
    return result;
}