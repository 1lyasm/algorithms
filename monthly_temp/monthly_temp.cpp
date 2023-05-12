#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

class Model {
 public:
  static const int N_MONTH = 12;
  static const std::string MONTHS[12];

  int month_index;
  double monthly[12], avg;
};

const std::string Model::MONTHS[12] = {
    "January", "February", "March",     "April",   "May",      "June",
    "July",    "August",   "September", "October", "November", "December"};

class Controller {
 private:
  std::ifstream *ifile_ptr = NULL;

 public:
  int version = 0;
  Controller(std::ifstream *ifile_ptr_arg) {
    Controller::ifile_ptr = ifile_ptr_arg;
  };
  Controller(){};
  void inp_version(void);
  void set_ifile_ptr(std::ifstream *ifile_ptr_arg);
  void file_inp_monthly(Model &model);
  void file_inp_avg(double &avg);
  void file_inp_month_index(int &month_index);
  std::string file_inp_ofile_name(void);
  void inp_monthly(Model &model);
  void inp_avg(double &avg);
  void inp_month_index(int &month_index);
  char inp_output_place(void);
  char inp_view_format(void);
  std::string inp_ofile_name(void);
  bool continues(void);
  int search_str_arr(std::string target, const std::string arr[], int size);
};

void Controller::set_ifile_ptr(std::ifstream *ifile_ptr_arg) {
  ifile_ptr = ifile_ptr_arg;
  return;
}
void Controller::file_inp_monthly(Model &model) {
  for (int i = 0, month_counter = model.month_index; i < Model::N_MONTH;
       i++, month_counter++) {
    if (month_counter >= Model::N_MONTH) month_counter = 0;
    (*Controller::ifile_ptr) >> model.monthly[i];
  }
  return;
}
void Controller::file_inp_avg(double &avg) {
  (*Controller::ifile_ptr) >> avg;
  return;
}
void Controller::file_inp_month_index(int &month_index) {
  std::string month;
  (*Controller::ifile_ptr) >> month;
  month_index = search_str_arr(month, Model::MONTHS, Model::N_MONTH);
}

std::string Controller::file_inp_ofile_name(void) {
  std::string file_name;
  (*Controller::ifile_ptr) >> file_name;
  return file_name;
}

void Controller::inp_monthly(Model &model) {
  for (int i = 0, month_counter = model.month_index; i < Model::N_MONTH;
       i++, month_counter++) {
    if (month_counter >= Model::N_MONTH) month_counter = 0;
    std::cout << "Rainfall for " << Model::MONTHS[month_counter]
              << "(ex: 300): ";
    std::cin >> model.monthly[i];
  }
  return;
}

void Controller::inp_avg(double &avg) {
  std::cout << "Average (ex: 9000): ";
  std::cin >> avg;
  return;
}

void Controller::inp_month_index(int &month_index) {
  std::string month;
  std::cout << "Current month(with first letter uppercase, ex: 'May'): ";
  std::cin >> month;
  month_index = search_str_arr(month, Model::MONTHS, Model::N_MONTH);
  while (month_index < 0) {
    std::cout << "Invalid input, "
              << "try again: ";
    std::cin >> month;
    month_index = search_str_arr(month, Model::MONTHS, Model::N_MONTH);
  }
  return;
}

char Controller::inp_output_place(void) {
  std::string choice;
  char first_letter;
  do {
    std::cout << "Output place (type 'f' for file"
              << "output and 's' for screen output): ";
    std::cin >> choice;
    first_letter = choice[0];
  } while (!(first_letter == 'f' || first_letter == 's'));
  return first_letter;
}

char Controller::inp_view_format(void) {
  std::string format;
  char first_letter;
  do {
    std::cout << "Format (type 'g' for graph"
              << " format and 't' for table format): ";
    std::cin >> format;
    first_letter = std::tolower(format[0]);
  } while (!(first_letter == 'g' || first_letter == 't'));
  return first_letter;
}

std::string Controller::inp_ofile_name(void) {
  std::string file_name;
  std::cout << "Output file name(ex: 'ofile.txt'): ";
  std::cin >> file_name;
  return file_name;
}

bool Controller::continues(void) {
  std::string response;
  std::cout << "Continue('y' for yes)? ";
  std::cin >> response;
  if (tolower(response[0]) == 'y')
    return true;
  else {
    return false;
  }
}

int Controller::search_str_arr(std::string target, const std::string arr[],
                               int size) {
  for (int index = 0; index < size; index++) {
    if (arr[index] == target) return index;
  }
  return -1;
}

void Controller::inp_version(void) {
  do {
    std::cout << "Choose version 1, 2, or 3 (1 and 2 are same,"
              << "enter negative number to exit): ";
    std::cin >> version;
  } while (version == 0 || version > 3);
  return;
}

class View {
 private:
  const int TABLE_WIDTH = 20;
  const int SCALE_FACTOR = 1000;

  Model *model_ptr = NULL;
  std::ostream *ostream_ptr = &std::cout;

 public:
  std::ofstream ofile;
  char format_name = 't', output_place = 's';
  std::string ofile_name = "outfile.txt";
  std::string ifile_name = "ifile.txt";

  View(Model *model_ptr_arg) { View::model_ptr = model_ptr_arg; };
  void display_data(void);
  void print_graph(void);
  void print_table(void);
  void print_table_header(void);
  void print_month_name(int month_index, int field_width);
  void set_ostream(void);
  void multiple_print(char symbol, int times);
  int scale(double num);
  void copy_arr(const double source_arr[], double destination_arr[], int size);
};

void View::display_data(void) {
  if (View::format_name == 't')
    View::print_table();
  else if (format_name == 'g')
    View::print_graph();
  return;
}

void View::print_graph(void) {
  (*View::ostream_ptr) << "\nGraph: \n";
  (*View::ostream_ptr).setf(std::ios::right);
  int scaled_avg = View::scale((*View::model_ptr).avg);
  for (int i = 0, month_counter = (*View::model_ptr).month_index;
       i < Model::N_MONTH; i++, month_counter++) {
    if (month_counter >= Model::N_MONTH) month_counter = 0;
    View::print_month_name(month_counter, 12);
    View::multiple_print('*', scale((*View::model_ptr).monthly[i]));
    (*View::ostream_ptr) << '\n' << std::setw(15) << "Average | ";
    View::multiple_print('*', scaled_avg);
    (*View::ostream_ptr) << "\n\n";
  }
  return;
}

void View::print_table(void) {
  (*View::ostream_ptr) << "\nTable: \n";
  View::print_table_header();
  (*View::ostream_ptr) << std::setprecision(1);
  (*View::ostream_ptr).setf(std::ios::right);
  (*View::ostream_ptr).setf(std::ios::fixed);
  int avg = static_cast<int>((*View::model_ptr).avg);
  for (int i = 0, month_counter = (*View::model_ptr).month_index;
       i < Model::N_MONTH; i++, month_counter++) {
    if (month_counter >= Model::N_MONTH) month_counter = 0;
    View::print_month_name(month_counter, 10);
    View::multiple_print(' ', static_cast<int>(View::TABLE_WIDTH * 0.4));
    (*View::ostream_ptr) << std::setw(10) << (*View::model_ptr).monthly[i];
    View::multiple_print(' ', static_cast<int>(View::TABLE_WIDTH * 1.4));
    (*View::ostream_ptr) << std::setw(10)
                         << (*View::model_ptr).monthly[i] -
                                (*View::model_ptr).avg
                         << '\n';
  }
  return;
}

void View::print_table_header(void) {
  View::multiple_print(' ', View::TABLE_WIDTH);
  (*View::ostream_ptr) << "Monthly rainfall";
  View::multiple_print(' ', View::TABLE_WIDTH);
  (*View::ostream_ptr) << "Compared with average\n";
  View::multiple_print('_', View::TABLE_WIDTH * 4);
  (*View::ostream_ptr) << "\n\n";
  return;
}

void View::print_month_name(int month_index, int field_width) {
  (*View::ostream_ptr) << std::setw(field_width) << Model::MONTHS[month_index]
                       << " | ";
  return;
}

void View::set_ostream(void) {
  if (View::output_place == 'f') {
    View::ofile.open(View::ofile_name);
    if (View::ofile.fail()) {
      std::exit(1);
    }
    View::ostream_ptr = &(View::ofile);
  } else
    View::ostream_ptr = &std::cout;
  return;
}

void View::multiple_print(char symbol, int times) {
  for (int i = 0; i < times; i++) (*View::ostream_ptr) << symbol;
}

int View::scale(double num) {
  int int_num = static_cast<int>(num);
  if (int_num % View::SCALE_FACTOR >= View::SCALE_FACTOR / 2)
    return (int_num / View::SCALE_FACTOR + 1);
  else {
    return (int_num / View::SCALE_FACTOR);
  }
}

void View::copy_arr(const double source_arr[], double destination_arr[],
                    int size) {
  for (int i = 0; i < size; i++) destination_arr[i] = source_arr[i];
  return;
}

int main() {
  Model model;
  View view(&model);
  Controller controller;

  std::cout << "Sample input: \n\n"
            << "9000\nMay\n"
            << "7676\n4553\n6565\n"
            << "342\n34\n65\n6787\n"
            << "2323\n4334\n23223\n"
            << "65655\n\nofile.txt\n\n";

  for (;;) {
    controller.inp_version();
    if (controller.version < 0) break;
    if (controller.version == 2 || controller.version == 1) {
      controller.inp_avg(model.avg);
      controller.inp_month_index(model.month_index);
      controller.inp_monthly(model);
      view.format_name = controller.inp_view_format();
      view.output_place = controller.inp_output_place();
      if (view.output_place == 'f')
        view.ofile_name = controller.inp_ofile_name();
      view.set_ostream();
    } else {
      std::cout << "\nChoose name of"
                << " file that contains necessary data.\n"
                << "For program to work, input file"
                << " should contain first average rainfall(ex: 9000),"
                << "\nthen month name(starting with uppercase, ex: 'May'),"
                << "then 12 numbers for monthly rainfalls,"
                << "\nand at the end name of file to"
                << " write output(ex: 'ofile.txt')\n";

      std::cout << "Choose input file name(ex: 'ifile.txt'): ";
      std::cin >> view.ifile_name;
      std::ifstream ifile(view.ifile_name);
      if (ifile.fail()) {
        std::cout << "Input file could not be opened\n";
        exit(1);
      }
      controller.set_ifile_ptr(&ifile);

      controller.file_inp_avg(model.avg);
      controller.file_inp_month_index(model.month_index);
      controller.file_inp_monthly(model);
      view.ofile_name = controller.file_inp_ofile_name();
      view.output_place = 'f';
      view.set_ostream();
      view.format_name = 't';
      view.display_data();
      view.format_name = 'g';
    }
    view.display_data();
    view.ofile.close();
    if (view.output_place == 'f')
      std::cout << view.ofile_name << " was written.";
    std::cout << '\n';
  }

  return 0;
}
