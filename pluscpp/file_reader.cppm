module;
#include <iostream>
#include <string>
#include <fstream>
export module file_reader;

export class FileReader {
  static void read(std::string &fileName, std::string *fileAsStr) {
    std::ifstream sourceFile(fileName);
    return;
  }
};
