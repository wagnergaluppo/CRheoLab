#ifndef MESH_H
#define MESH_H

#include "Point.cpp"
#include "Face.cpp"
#include "Patch.cpp"

class Mesh {

public:

  // Constructor
  Mesh();

  // Destructor
  virtual ~Mesh(){};
              
  std::vector<Point>  pointList_;

  std::vector<Face>   faceList_;

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
  
  std::string getExecutablePath();

  int getNEntitites(std::ifstream& file);

  void readPoints(std::string path);

  void readFaces(std::string path);

  void readOwners(std::string path);

  void readNeighbour(std::string path);

  void readBoundary(std::string path);

} ;

#endif // MESH_H


