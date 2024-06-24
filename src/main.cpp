#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split_message(const std::string &message, const std::string& delim) {
    std::vector<std::string> toks;
    std::stringstream ss = std::stringstream(message);
    std::string line;
    while (getline(ss, line, *delim.begin())) {
        toks.push_back(line);
        ss.ignore(delim.length() - 1);
    }
    return toks;
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;


  std::cout << "$ ";
  
  std::string input;
  std::getline(std::cin, input);

  auto commands = split_message(input, " ");
  std::cout << commands[0] << ": command not found" << std::endl;

}
