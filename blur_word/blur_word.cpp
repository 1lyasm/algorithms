#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void makeXString(std::string &xStr, int size) {
  xStr.clear();
  for (int i = 0; i < size; i++)
    xStr.push_back('x');
}

bool allDigit(std::string str) {
  for (int i = 0; i < str.size(); i++) {
    if (!isdigit(str[i]))
      return false;
  }
  return true;
}

template <typename T> void print(const T &val) {
  for (int i = 0; i < val.size(); i++)
    std::cout << "\nElement " << i + 1 << ": " << val[i] << '\n';
  std::cout << '\n';
}

void putPureWords(std::vector<std::string> &pureWords, std::string line) {
  std::stringstream ss(line);
  std::string word = "";
  while (getline(ss, word, ' '))
    pureWords.push_back(word);
}

void putModWords(std::vector<std::string> &modWords,
                 std::vector<std::string> pureWords) {
  std::string xStr = "null";
  for (int i = 0; i < pureWords.size(); i++) {
    if (allDigit(pureWords[i])) {
      makeXString(xStr, pureWords[i].size());
      modWords.push_back(xStr);
    } else
      modWords.push_back(pureWords[i]);
  }
}

void changeLine(std::string &line) {
  std::vector<std::string> pureWords;
  putPureWords(pureWords, line);

  std::vector<std::string> modWords;
  putModWords(modWords, pureWords);

  assert(modWords.size() == pureWords.size());

  int startPos = -1;
  int endPos = 0;
  int wordN = 1;
  for (int i = 0; i < pureWords.size(); i++) {
    if (pureWords[i].size() > 0) {
      startPos = line.find(pureWords[i], startPos + 1);
      endPos = startPos + pureWords[i].size();
      line.replace(startPos, pureWords[i].size(), modWords[i]);

      wordN++;
    }
  }
}

int main() {
  std::cout << "\nQuestion 10\n";
  std::string response = "y";
  std::string line = "";
  do {
    std::cout << "\nEnter text: ";
    getline(std::cin, line);
    changeLine(line);
    std::cout << "\nReplaced with x strings: " << line << '\n';
    std::cout << "\nContinue('y' for yes)? ";
    std::cin >> response;
    std::cin.ignore();
  } while (tolower(response[0]) == 'y');
  return 0;
}
