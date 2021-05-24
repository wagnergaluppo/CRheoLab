// Get the number of points
int getNEntitites(std::ifstream& file)
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

void readPoints(std::string path, Mesh& polyMesh)
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
  polyMesh.nPoints_ = getNEntitites(in_file);

  // Loop over the points to fill the vector 
  while ( getline(in_file, line ) && line.find("(") == std::string::npos );
  {
    char c; // Variable to catch "("
    double x, y, z; // Variables to store the x,y,z position of the points
    
    for ( int i = 0; i < polyMesh.nPoints_; i++ )
    {
      std::getline( in_file, line );

      std::stringstream(line ) >> c >> x >> y >> z;
      
      polyMesh.pointList_.push_back(Point(x,y,z)); // Node list
    }
  }
  // Close the file
  in_file.close();

}

void readFaces(std::string path, Mesh& polyMesh)
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
  polyMesh.nFaces_ = getNEntitites(in_file);

  // Resize the vectors according to the number of faces
 // polyMesh.faceList_.resize( polyMesh.nFaces_);

  // Loop over the points to fill the vector 
  while ( getline(in_file, line ) && line.find("(") == std::string::npos );
  {
    int nPointsInFace; // catch number of points in each Face
    char c; // Variable to catch "("

    for ( int i = 0; i < polyMesh.nFaces_; i++ )
    {
      std::getline( in_file, line );
      std::stringstream line_2(line);
      line_2 >> nPointsInFace >> c;
            
      std::vector<int> listOfPoints (nPointsInFace); // array to store the list of points
      int counter(0);
      int tmp;
      while(line_2 >> tmp)
      {
        listOfPoints[counter]=tmp;
        counter++;
      } 
      polyMesh.faceList_.push_back(Face(nPointsInFace,listOfPoints));

    }
  }
  // Close the file
  in_file.close();

}

void readOwners(std::string path, Mesh& polyMesh)
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
      polyMesh.faceList_[i].setOwner(tmp); //Set Face Owner
    }
  }
  // Close the file
  in_file.close();

}

void readNeighbour(std::string path, Mesh& polyMesh)
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

    // Loop over the points to fill the vector 
  while ( getline(in_file, line ) && line.find("(") == std::string::npos );
  {
    int tmp(0); // catch number of owner

    for ( int i = 0; i < nNeighbours; i++ )
    {
      std::getline( in_file, line );
      std::stringstream line_2(line);
      line_2 >> tmp;
      polyMesh.faceList_[i].setNeighbour(tmp); //setFace neighbor

    }
  }
  // Close the file
  in_file.close();

  polyMesh.nInteriorFaces_ = nNeighbours;
  polyMesh.nBoundaryFaces_ = polyMesh.nFaces_ - polyMesh.nInteriorFaces_;
}

void readBoundary(std::string path, Mesh& polyMesh)
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

  polyMesh.nPatches_ = getNEntitites(in_file);

  // Loop over the points to fill the vector 
  while ( getline(in_file, line ) && line.find("(") == std::string::npos );
  {
    for ( int i = 0; i < polyMesh.nPatches_; i++ )
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
           type = words2;
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
        polyMesh.patchList_.push_back(Patch(name,type, nFaces,startFace)); //add a Patch object to the list

      }
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
