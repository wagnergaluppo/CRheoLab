#ifndef IODictionary_H
#define IODictionary_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream> 
#include <algorithm>

class IODictionary
{
    public:
        // Constructor
        IODictionary(std::string path, std::string fileName);
        
        // Destructor
        virtual ~IODictionary(){} ;

        bool setPath (std::string& newPath);
        
    protected:
        int countCharactersInString(const std::string& line);
        std::vector<std::string> splitString(const std::string& line, char delimiter);
        void errorMessage(std::ifstream& in_file, std::string message, int lineCounter=0, bool turnOfLinePrinting=false);
        void checkSemiColon (std::ifstream& in_file, std::string& line, const int& lineCounter);
        void readCharacter(std::ifstream& in_file, std::istringstream& iss, const char C, const int& lineCounter);
        std::string stripSingleComment(std::string& line);
        std::string stripBlockComment(std::ifstream& in_file, std::string& line, int& lineCounter);
        std::string stripComments(std::ifstream& in_file, std::string& line, int& lineCounter);
        void newLineAndUpdateSStream(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter, bool updateStringStream=true);
        void vectorFormatError(std::ifstream& in_file, int lineCounter) ;
        bool checkExactMatch(const std::string& line,const std::string& keyWord);
        double readScalarData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int lineCounter);
        std::string readString(std::ifstream& in_file, std::istringstream& iss, std::string& line, int lineCounter, bool semiColumCheck);
        double findScalar( const std::string& path, const std::string& fileName, const std::string& keyword);
        std::string findAsString( const std::string& path, const std::string& fileName, const std::string& keyword);
        std::map<std::string, std::string> readHeader( const std::string& path, const std::string& fileName);
        
        template <typename primitiveType>
        primitiveType readVectorTensorData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int lineCounter);

        const std::string& Path() const;
        const std::string& Name() const;

    private:
        std::string path_;
        std::string fileName_;
};



#endif 