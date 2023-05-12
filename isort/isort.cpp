#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

void insertion_sort(int arr[], int size);
void print_arr(const int arr[], int size);
void fill_arr(int arr[], int size, int *used_size, std::istream *input_place);
void fill_count_arr(int count_arr[], const int arr[], int size);
int count(int target, const int arr[], int size);
void print_results(const int arr[], const int count_arr[], int size);
char inp_input_place(void);
std::string inp_file_name(void);
int get_number(std::string str, int size);
int str_length(std::string str);
void inp_str(std::string *empty_str, std::istream *input_place);
struct StringArray {
  std::string str_arr[50]{};
  int sizes_arr[50]{}, used_size = 0;
};
void make_arr(std::string big_str, std::size_t big_str_size,
              StringArray *str_arr_object);

int main() {
  const int MAX_SIZE = 50;
  int arr[MAX_SIZE];
  char input_place = inp_input_place();
  std::string file_name;
  int used_size;
  if (input_place == 'f') {
    std::ifstream ifile(inp_file_name());
    if (ifile.fail()) {
      exit(1);
    }
    fill_arr(arr, MAX_SIZE, &used_size, &ifile);
  } else {
    fill_arr(arr, MAX_SIZE, &used_size, &std::cin);
  }
  insertion_sort(arr, used_size);
  int count_arr[50];
  fill_count_arr(count_arr, arr, used_size);
  print_results(arr, count_arr, used_size);

  std::cout << '\n';
  return 0;
}

void fill_arr(int arr[], int size, int *used_size, std::istream *input_place) {
  StringArray str_arr_obj;
  std::string big_str;
  inp_str(&big_str, input_place);
  int str_len = str_length(big_str);
  make_arr(big_str, str_len, &str_arr_obj);
  (*used_size) = str_arr_obj.used_size;
  for (int i = 0; i < (*used_size); i++)
    arr[i] = get_number(str_arr_obj.str_arr[i], str_arr_obj.sizes_arr[i]);
  return;
}

void insertion_sort(int arr[], int size) {
  int i = size - 1, key, insert_pos;
  while (i > 0) {
    key = arr[i];
    insert_pos = -1;
    for (int j = i; j >= 0; j--) {
      if (arr[i] > arr[j]) {
        arr[i] = arr[j];
        insert_pos = j;
      }
    }
    if (insert_pos < 0) {
      i--;
    } else {
      arr[insert_pos] = key;
    }
  }
  return;
}

void print_arr(const int arr[], int size) {
  for (int i = 0; i < size; i++) std::cout << arr[i] << '\n';
  return;
}

void fill_count_arr(int count_arr[], const int arr[], int size) {
  for (int i = 0; i < size; i++) count_arr[i] = count(arr[i], arr, size);
  return;
}

int count(int target, const int arr[], int size) {
  int duplicate_num = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] == target) duplicate_num++;
  }
  return duplicate_num;
}

void print_results(const int arr[], const int count_arr[], int size) {
  std::cout.setf(std::ios::right);
  std::cout << std::setw(5) << "N"
            << "    "
            << "Count\n";
  std::cout << std::setw(5) << arr[0] << "    " << count_arr[0] << '\n';
  for (int i = 0; i < size; i++) {
    if (i > 0 && arr[i] != arr[i - 1])
      std::cout << std::setw(5) << arr[i] << "    " << count_arr[i] << '\n';
  }
  return;
}

char inp_input_place(void) {
  std::string input_place;
  std::cout << "Input place: ";
  std::cin >> input_place;
  return input_place[0];
}

std::string inp_file_name(void) {
  std::string file_name;
  std::cout << "File name: ";
  std::cin >> file_name;
  return file_name;
}

void make_arr(std::string big_str, std::size_t big_str_size,
              StringArray *str_arr_object) {
  int i(0), j(0);
  std::string substr;
  char str_element;
  while (i < big_str_size) {
    substr = "";
    str_element = big_str[i];
    while (str_element != ' ' && i < big_str_size) {
      substr.push_back(str_element);
      (*str_arr_object).sizes_arr[j] += 1;
      str_element = big_str[++i];
    }
    i++;
    (*str_arr_object).str_arr[j++] = substr;
    (*str_arr_object).used_size++;
  }
  return;
}

int get_number(std::string str, int size) {
  int number = 0;
  for (int i = size - 1; i >= 0; i--) {
    if (str[i] == '-')
      number *= -1;
    else
      number += (str[i] - 48) * static_cast<int>(pow(10, size - 1 - i));
  }
  return number;
}

int str_length(std::string str) {
  int i;
  for (i = 0; str[i] != NULL; i++)
    ;
  return i;
}

void inp_str(std::string *empty_str, std::istream *input_place) {
  char inp_char;
  (*input_place) >> inp_char;
  while (inp_char != '.') {
    (*empty_str).push_back(inp_char);
    (*input_place).get(inp_char);
  }
  return;
}