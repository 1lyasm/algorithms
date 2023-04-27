#ifndef SOURCE_H
#define SOURCE_H

#include "file_reader.h"

#include <string>

class Source
{
private:
  std::string fileName;
  std::string fileAsStr;

public:
  Source(std::string);
  std::string getFileName();
  std::string getFileAsStr();
};

#endif
