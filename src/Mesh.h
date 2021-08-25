#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include <limits.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <algorithm> 

#include "Point.h"
#include "Face.h"
#include "Cell.h"
#include "Patch.h"
#include "findFiles.h"

class Mesh {

public:

  // Constructor
  Mesh();

  // Destructor
  virtual ~Mesh(){};
              
  std::vector<Point> pointList_;

  std::vector<Face>  faceList_;

  std::vector<Cell>  cellList_;

  std::vector<Patch> patchList_;

  int nPoints_;

  int nFaces_;

  int nInteriorFaces_;

  int nBoundaryFaces_;
  
  int nCells_;

  int nPatches_;

private:


  void readMesh();

  int getNEntitites(std::ifstream& file);

  void readPoints(std::string path);

  void readFaces(std::string path);

  vector<int> readOwners(std::string path);

  vector<int> readNeighbours(std::string path);

  void updateCellAndFaceData(std::string pathOwners, std::string pathNeighbours);

  void readBoundary(std::string path);

} ;

#endif // MESH_H


