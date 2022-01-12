#include "FVMatrix.h"

FVMatrix::FVMatrix(const Mesh& mesh, Solver solver, double solverParam):
nCells_(mesh.nCells_), selectedSolver_(solver) 
{
    if (selectedSolver_ == SOR) wSOR_=solverParam;    
}

