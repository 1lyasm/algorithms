#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template <typename T, typename U>
void initializeArr(T &blankPos, U defaultVal) {
  for (int i = 0; i < blankPos.size(); i++)
    blankPos[i] = defaultVal;
}

void rightAdjust(int lineNum, std::ostream *oStream) {
  if (lineNum < 10)
    (*oStream) << "  ";
  else if (lineNum >= 10 && lineNum < 100)
    (*oStream) << ' ';
}

void fillBlankPos(std::vector<int> &blankPos, std::string line) {
  int nextIndex = 0, lastNonWhiteCharacterIndex = line.size() - 1;
  do {
    lastNonWhiteCharacterIndex--;
  } while (line[lastNonWhiteCharacterIndex] == ' ');
  for (int i = 1; i < lastNonWhiteCharacterIndex; i++) {
    if (line[i] == ' ' && line[i - 1] != ' ') {
      blankPos[nextIndex] = i - 1;
      nextIndex++;
    }
  }
}

void fillInsertPos(std::vector<int> &insertPos, std::vector<int> blankPos,
                   std::vector<int> gapLengthArr) {
  int prevIndex = 0, currentIndex = 0, filledSize = 0, indexToInsert = 0;
  for (int i = 0; i < blankPos.size() && blankPos[i] >= 0; i++)
    filledSize++;
  for (int i = 0; i < filledSize;) {
    while ((blankPos[i] < 72 + prevIndex + gapLengthArr[i]) && i < filledSize) {
      currentIndex = blankPos[i];
      i++;
    }
    prevIndex = currentIndex;
    insertPos[indexToInsert] = currentIndex;
    indexToInsert++;
  }
}

void fillGapLengthArr(std::vector<int> &gapLengthArr, std::vector<int> blankPos,
                      std::string line) {
  int gapLength(0), gapIndex(0), indexToAddLength(0);
  for (int i = 0; i < blankPos.size() - 1; i++) {
    if (blankPos[i] < 0)
      break;
    gapIndex = blankPos[i] + 1;
    while (line[gapIndex] == ' ')
      gapIndex++, gapLength++;
    gapLengthArr[indexToAddLength] = gapLength;
    indexToAddLength++;
    gapLength = 0;
  }
}

void fillMultipleLines(std::vector<std::string> &multipleLines,
                       std::vector<int> insertPos, std::string line) {
  int filledSize(0), leftSideIndex(0), i(0);
  for (int i = 0; i < insertPos.size() && insertPos[i] >= 0; i++)
    filledSize++;
  for (; i < filledSize; i++) {
    multipleLines[i] =
        line.substr(leftSideIndex, insertPos[i] - leftSideIndex + 1);
    leftSideIndex = insertPos[i] + 1;
  }
  multipleLines[i] = line.substr(insertPos[i - 1] + 1);
}

void removeBlanks(std::vector<std::string> &multipleLines) {
  int deleteAmt = 0;
  for (int i = 0; i < multipleLines.size(); i++) {
    deleteAmt = 0;
    for (int j = 0; j < multipleLines[i].size(); j++) {
      if (multipleLines[i][j] != ' ')
        break;
      deleteAmt++;
    }
    if (deleteAmt > 0) {
      multipleLines[i].erase(0, deleteAmt);
      if (multipleLines[i][multipleLines[i].size() - 1] == '\n')
        multipleLines[i].erase(multipleLines[i].begin() +
                               multipleLines[i].size() - 1);
    }
  }
}

void copyWithLineNumber(std::ifstream *iFile, std::ostream *oStream) {
  char c{};
  int lineNum = 1, multipleLinesFilledSize = 0;
  std::string line{};
  std::vector<int> blankPos(50), insertPos(10), gapLengthArr(49);
  std::vector<std::string> multipleLines(10);
  while (1) {
    (*iFile).get(c);
    if ((*iFile).eof())
      break;
    line.push_back(c);
    if (c == '\n') {
      if (line.size() >= 72) {
        initializeArr(blankPos, -1);
        initializeArr(insertPos, -1);
        initializeArr(gapLengthArr, 0);
        initializeArr(multipleLines, "null");
        multipleLinesFilledSize = 0;
        fillBlankPos(blankPos, line);
        fillGapLengthArr(gapLengthArr, blankPos, line);
        fillInsertPos(insertPos, blankPos, gapLengthArr);
        fillMultipleLines(multipleLines, insertPos, line);
        for (int i = 0; i < multipleLines.size() && multipleLines[i] != "null";
             i++)
          multipleLinesFilledSize++;
        removeBlanks(multipleLines);
        for (int i = 0; i < multipleLinesFilledSize; i++) {
          rightAdjust(lineNum, oStream);
          (*oStream) << lineNum << ". " << multipleLines[i] << '\n';
          lineNum++;
        }
      } else {
        rightAdjust(lineNum, oStream);
        (*oStream) << lineNum << ". " << line;
        lineNum++;
      }
      line = "";
    }
  }
}

int main() {
  std::string iFileName{}, oFileName{};
  std::cout << "\nQuestion 2\nInput file name(ex: 'input.txt'): ";
  std::cin >> iFileName;
  std::cout << "\nOutput file name(ex: 'output.txt'): ";
  std::cin >> oFileName;
  std::ifstream iFile(iFileName);
  if (iFile.fail()) {
    std::cout << "\nInput file could not be opened\n";
    exit(1);
  }
  std::ofstream oFile(oFileName);
  if (oFile.fail()) {
    std::cout << "\nOutput file could not be opened\n";
    exit(1);
  }
  copyWithLineNumber(&iFile, &std::cout);
  iFile.close();
  iFile.open(iFileName);
  if (iFile.fail()) {
    std::cout << "\nInput file could not be opened\n";
    exit(1);
  }
  copyWithLineNumber(&iFile, &oFile);
  std::cout << "\nOutput file was written.\n";
  iFile.close();
  oFile.close();
  return 0;
}
