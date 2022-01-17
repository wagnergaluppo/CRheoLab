#include "lilSpmat.h"

// Constructor
// Constructs an empty sparse matrix and allocates memory for the rows
lilSpmat::lilSpmat(unsigned int numRows, unsigned int numCols)
{
  // Store number of rows and columns
  numRows_ = numRows;
  numCols_ = numCols;

  // Allocate memory for the rows since any row might be accessed at any time
  // Do not do the same for each columns_[i] and values_[i] vector since their size
  // should only increase as new entries are added
  columns_.reserve(numRows_);
  values_.reserve(numRows_);
}

// Returns the sparsity of the matrix
double lilSpmat::sparsity()
{
  return 0.0;
}
