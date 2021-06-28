#include "Mesh.h"


Mesh::Mesh()
: nPoints_(-2), nFaces_(-2), nPatches_(-2)
{ 
    std::cout << "I am the mesh constructor" << std::endl;
    readMesh();

}


void Mesh::readMesh()
{
    std::string pathPoints (getExecutablePath()+std::string("constant/")+std::string("polyMesh/points"));
    readPoints(pathPoints);

    std::string pathFaces (getExecutablePath()+std::string("constant/")+std::string("polyMesh/faces"));
    readFaces(pathFaces);

    std::string pathOwners(getExecutablePath()+std::string("constant/")+std::string("polyMesh/owner"));
    readOwners(pathOwners);

    std::string pathNeighbour(getExecutablePath()+std::string("constant/")+std::string("polyMesh/neighbour"));
    readNeighbour(pathNeighbour);

    std::string pathBoundary(getExecutablePath()+std::string("constant/")+std::string("polyMesh/boundary"));
    readBoundary(pathBoundary);

    std::cout << "Mesh was read successfully!" << std::endl;
}


int Mesh::getNEntitites(std::ifstream& file)
{
  int nPoints ;
  bool findNPoints (true);
  std::string line;

  while (findNPoints)
  {
    std::getline(file, line );
    if ( std::stringstream( line ) >> nPoints) 
      findNPoints=false;
  }
  return nPoints;
}

void Mesh::readPoints(std::string path)
{
  // Passes the path of points into a ifsteam
  std::ifstream in_file(path.c_str());
    
  // Checks if file is to be open correctly
  if(!in_file.is_open())
  {
      std::cerr << "The input file was not open correctly!" << std::endl;
      //return 1;
  }

  std::string line;

  // Gets number of points in file
  nPoints_ = getNEntitites(in_file);

  pointList_.resize(nPoints_);

  // Loop over the points to fill the vector 
  while ( getline(in_file, line ) && line.find("(") == std::string::npos );
  {
    char c; // Variable to catch "("
    double x, y, z; // Variables to store the x,y,z position of the points
    
    for ( int i = 0; i < nPoints_; i++ )
    {
      std::getline( in_file, line );

      std::stringstream(line ) >> c >> x >> y >> z;
      
      pointList_[i]= Point(x,y,z); // Node list
    }
  }
  // Close the file
  in_file.close();

}


void Mesh::readFaces(std::string path)
{
  // Passes the path of points into a ifsteam
  std::ifstream in_file(path.c_str());
    
  // Checks if file is to be open correctly
  if(!in_file.is_open())
  {
      std::cerr << "The input file was not open correctly!" << std::endl;
      //return 1;
  }

  std::string line;

  // Gets number of faces in file
  nFaces_ = getNEntitites(in_file);

  // Resize the vectors according to the number of faces
  faceList_.resize(nFaces_);

  // Loop over the points to fill the vector 
  while ( getline(in_file, line ) && line.find("(") == std::string::npos );
  {
    int nPointsInFace; // catch number of points in each Face
    char c; // Variable to catch "("


    for ( int i = 0; i < nFaces_; i++ )
    {
      std::getline( in_file, line );
      std::stringstream line_2(line);
      line_2 >> nPointsInFace >> c;


            
      std::vector<Point*> listOfPoints (nPointsInFace); // array to store the list of points
      int counter(0);
      int tmp;

      while(line_2 >> tmp)
      {
        listOfPoints[counter]=&pointList_[tmp];
        counter++;
      } 

      faceList_[i]=Face(nPointsInFace,listOfPoints);

    }
  }
  // Close the file
  in_file.close();

}


void Mesh::readOwners(std::string path)
{
  // Passes the path of points into a ifsteam
  std::ifstream in_file(path.c_str());
    
  // Checks if file is to be open correctly
  if(!in_file.is_open())
  {
      std::cerr << "The input file was not open correctly!" << std::endl;
      //return 1;
  }

  std::string line;

  // Gets number of owners in file
  int nOwners = getNEntitites(in_file);

  // Loop over the points to fill the vector 
  while ( getline(in_file, line ) && line.find("(") == std::string::npos );
  {
    int tmp(0); // catch number of owner

    for ( int i = 0; i < nOwners; i++ )
    {
      std::getline( in_file, line );
      std::stringstream line_2(line);
      line_2 >> tmp;
      faceList_[i].setOwner(tmp); //Set Face Owner
    }
  }
  // Close the file
  in_file.close();

}

void Mesh::readNeighbour(std::string path)
{
  // Passes the path of points into a ifsteam
  std::ifstream in_file(path.c_str());
    
  // Checks if file is to be open correctly
  if(!in_file.is_open())
  {
      std::cerr << "The input file was not open correctly!" << std::endl;
      //return 1;
  }

  std::string line;

  // Gets number of faces in file
  int nNeighbours = getNEntitites(in_file);

  // Variable to store maximum value of neighbour
  int storeMax(0);

    // Loop over the points to fill the vector 
  while ( getline(in_file, line ) && line.find("(") == std::string::npos );
  {
    int tmp(0); // catch number of owner

    for ( int i = 0; i < nNeighbours; i++ )
    {
      std::getline( in_file, line );
      std::stringstream line_2(line);
      line_2 >> tmp;
      faceList_[i].setNeighbour(tmp); //setFace neighbor
     
      if(tmp > storeMax)
      {
        storeMax = tmp;
      }

    }
  }
  // Close the file
  in_file.close();

  nInteriorFaces_ = nNeighbours;
  nBoundaryFaces_ = nFaces_ - nInteriorFaces_;
  nCells_ = storeMax + 1;
}


void Mesh::readBoundary(std::string path)
{
  // Passes the path of points into a ifsteam
  std::ifstream in_file(path.c_str());
    
  // Checks if file is to be open correctly
  if(!in_file.is_open())
  {
      std::cerr << "The input file was not open correctly!" << std::endl;   
  }

  std::string line;

  // Booleans to check file reading
  bool endInnerLoop = false;
  bool firstCurly = false;
  bool secondCurly = false;

  bool checkBoundaryName = false;
  bool checkType = false;
  bool checkNFaces = false;
  bool checkStartFace = false;

  std::string words;
  std::string words2;
  int values(-1);
  int countCurly (0);

  std::string name;
  std::string type;

  int nFaces;
  int startFace;

  nPatches_ = getNEntitites(in_file);

  // Loop over the points to fill the vector 
  while ( getline(in_file, line ) && line.find("(") == std::string::npos );
  {
    for ( int i = 0; i < nPatches_; i++ )
    {
      endInnerLoop = false;

      while(!endInnerLoop && !in_file.eof())
      {
        std::getline( in_file, line );
        std::stringstream line_2(line); 

        // Extracts word from line
        line_2 >> words;

        if (words.at(0) == '{')
        {
          firstCurly = true;
          countCurly++;
        }

        if (firstCurly && words.back() == '}' && countCurly < 2)
        {
          secondCurly = true;
          countCurly = 0;
        }
        
        if (firstCurly && secondCurly)
          endInnerLoop = true;

        if(!checkBoundaryName && !firstCurly)
        {
           name = words;
           checkBoundaryName = true;
        }

        if(words == "type" && (line_2 >> words2) && words2.back() == ';' )
        {
           type = words2.substr(0, words2.size()-1);
           checkType = true;
           words2.clear();
        }

        if(words == "nFaces" && (line_2 >> values) && ( (line_2 >>  words2) && words2.back() == ';') )
        {
           nFaces = values;
           checkNFaces = true;
           words2.clear();
        }

        if(words == "startFace" && (line_2 >> values) && ( (line_2 >>  words2) && words2.back() == ';'))
        {
           startFace = values;
           checkStartFace = true;
        }

        // If the stringstream reaches the end of file some parameters are missing. 
        // Implement later
        if (endInnerLoop)
        {
            if ( !(checkBoundaryName  && checkType && checkNFaces && checkStartFace) )
            {
                throw  std::runtime_error("Some error in the boundaries");
            } 
        }

        if (in_file.eof() && !endInnerLoop)
        {
              throw  std::runtime_error("End of file!! You probably have problems with parentheses");
              
        }  
      }

      patchList_.push_back(Patch(name,type, nFaces,startFace)); //add a Patch object to the list

      checkBoundaryName = false;
      checkType = false;
      checkNFaces = false;
      checkStartFace = false;

      firstCurly = false;
      secondCurly = false;


    }
  }
  // Close the file
  in_file.close();


}

// Function to get the current working directory of the executable file
std::string Mesh::getExecutablePath()
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );

  std::string executablePath ( result, (count > 0) ? count : 0 );

  executablePath=executablePath.substr(0, executablePath.find_last_of("/"));

  return executablePath+"/";
}

void Mesh::computeFaceWeightingFactor()
{

    //std::vector<Cell>& cells = cellList_;

    std::vector<Face>& faces = faceList_;

    // This is a place holder for when the cellList is implemented
    std::vector<Cell> cells(nCells_);

    // Loop through interior faces
    for (unsigned int i = 0; i < nInteriorFaces_ ; i++ )
    {
      const int cellOwner = faces[i].getOwner();

      const int cellNeighbour = faces[i].getNeighbour();

      const vector3 faceCenter = faces[i].getCenterOfMass();

      const vector3 d_Cf = cells[cellOwner].getCenterOfMass() - faceCenter;

      const vector3 d_fF = cells[cellNeighbour].getCenterOfMass() - faceCenter;

      const vector3 e_f = faces[i].getFaceAreaVector()/mag( faces[i].getFaceAreaVector() );

      faces[i].setweightingFactor( (d_Cf & e_f) / ( (d_Cf & e_f) + (d_fF & e_f) ));
    }

    // Loop through boundary the faces
    for (unsigned int i = nInteriorFaces_ + 1; i < nFaces_  ; i++ )
    {
      faces[i].setweightingFactor(1.0);
    }



}

