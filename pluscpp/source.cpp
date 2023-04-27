#include "source.h"

Source::Source(std::string fileName)
{
  this->fileName = fileName;
}

std::string Source::getFileName()
{
  return fileName;
}

std::string Source::getFileAsStr()
{
  return fileAsStr;
}

void Source::readSourceFile()
{
}
