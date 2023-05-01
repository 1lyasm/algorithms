module;
#include <fstream>
#include <iostream>
#include <string>
export module file_reader;

export class FileReader {
  static void read(std::string &fileName, std::string *fileAsStr) {
    std::ifstream sourceFile(fileName);
    return;
  }
};
