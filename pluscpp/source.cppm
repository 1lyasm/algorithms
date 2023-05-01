module;
#include <string>
export module source;
import file_reader;

export class Source {
  std::string fileName;
  std::string fileAsStr;

public:
  Source(std::string fileName) { this->fileName = fileName; }

  std::string getFileName() { return fileName; }

  std::string getFileAsStr() { return fileAsStr; }

  void readSourceFile() {}
};
