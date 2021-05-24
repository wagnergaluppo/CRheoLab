#include <dirent.h> 
#include <cstdio>

// Function to get the current working directory of the executable file
std::string getExecutablePath()
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );

  std::string executablePath ( result, (count > 0) ? count : 0 );

  executablePath=executablePath.substr(0, executablePath.find_last_of("/"));

  return executablePath+"/";
}

// Function to check if a folder exists withing the executable path
void checkFileStructure(std::string folderName,  std::string pathname = getExecutablePath())
{
  #include <dirent.h>
  #include <errno.h>

  std::string fullPath (pathname+folderName);

  DIR* dir = opendir(fullPath.c_str());
  if (dir) {
      std::cout << folderName <<" folder exists!" << std::endl;
      closedir(dir);
  } else if (ENOENT == errno) {
     throw std::runtime_error(folderName + std::string("/ folder does not Exist!"));
  } else {
     std::cout << "Something is wrong with file structure" << std::endl;
  }
}

// Check if case structure is Ok
void checkCaseStructure()
{

  checkFileStructure("constant");

  checkFileStructure("system");

  std::string polyMesh (std::string("constant") + std::string("/") + std::string("polyMesh"));

  checkFileStructure(polyMesh);


  std::cout << "Everything is clear!" << std::endl;
}