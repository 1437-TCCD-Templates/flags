// flags.cpp - Stream State Flag Lab
// Build: g++ -std=c++17 -Wall -Wextra flags.cpp -o flags
// Run:   ./flags
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

void write_file(const std::string &path, const std::string &text) {
  std::ofstream out(path);
  out << text;
}

void show(int step, const std::string &what, const std::ios &s) {
  std::cout << std::setw(2) << step << "  " << std::left << std::setw(36)
            << what << std::right << " good=" << s.good() << " eof=" << s.eof()
            << " fail=" << s.fail() << " bad=" << s.bad() << '\n';
}

int main() {
  write_file("three.txt", "alpha\nbeta\ngamma\n");
  write_file("numbers.txt", "42\nabc\n7\n");
  write_file("no_newline.txt", "one\ntwo");

  std::string line;
  int n = 0;
  int step = 0;

  std::cout
      << "--- File A: three.txt (alpha, beta, gamma, each ending in newline)\n";
  {
    std::ifstream in("three.txt");
    show(++step, "open the file", in);
    std::getline(in, line);
    show(++step, "getline -> \"" + line + "\"", in);
    std::getline(in, line);
    show(++step, "getline -> \"" + line + "\"", in);
    std::getline(in, line);
    show(++step, "getline -> \"" + line + "\"", in);
    std::getline(in, line);
    show(++step, "getline (a 4th time) -> \"" + line + "\"", in);
  }

  std::cout << "\n--- File B: numbers.txt (42, abc, 7)\n";
  {
    std::ifstream in("numbers.txt");
    in >> n;
    show(++step, "read int -> " + std::to_string(n), in);
    in >> n;
    show(++step, "read int (next text is abc)", in);
    in >> n;
    show(++step, "read int again", in);
    in.clear();
    show(++step, "clear()", in);
    in >> n;
    show(++step, "read int after clear()", in);
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    show(++step, "clear() then ignore rest of line", in);
    in >> n;
    show(++step, "read int -> " + std::to_string(n), in);
  }

  std::cout
      << "\n--- File C: no_newline.txt (one, two; NO newline after two)\n";
  {
    std::ifstream in("no_newline.txt");
    std::getline(in, line);
    show(++step, "getline -> \"" + line + "\"", in);
    std::getline(in, line);
    show(++step, "getline -> \"" + line + "\"", in);
    std::getline(in, line);
    show(++step, "getline (one more time)", in);
  }

  std::cout << "\n--- File D: a file that does not exist\n";
  {
    std::ifstream in("no_such_file.txt");
    show(++step, "open no_such_file.txt", in);
    std::cout << "    is_open() = " << in.is_open() << '\n';
  }

  std::cout << "\n--- Loop experiment\n";
  const std::vector<std::string> files = {"three.txt", "no_newline.txt"};
  for (const std::string &path : files) {
    {
      std::ifstream in(path);
      int count = 0;
      std::cout << path << "  while (!in.eof()):  ";
      while (!in.eof()) {
        std::getline(in, line);
        ++count;
        std::cout << "[" << line << "]";
      }
      std::cout << "  -> " << count << " records\n";
    }
    {
      std::ifstream in(path);
      int count = 0;
      std::cout << path << "  while (getline):    ";
      while (std::getline(in, line)) {
        ++count;
        std::cout << "[" << line << "]";
      }
      std::cout << "  -> " << count << " records\n";
    }
  }
  return 0;
}
