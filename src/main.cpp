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

    while(true) {
        std::cout << "$ ";
        
        std::string input;
        std::getline(std::cin, input);
        
        std::stringstream ss = std::stringstream(input);
        std::string command;
        std::getline(ss, command, ' ');

        if (command == "exit") {
            return 0;
        } else if (command == "echo") {
            std::string message;
            std::getline(ss, message);
            std::cout << message << std::endl;
        } else {
            std::cout << command << ": command not found\n";
        }
    }
}
