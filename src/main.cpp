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
        
        std::string command;
        std::getline(std::cin, command, ' ');
        std::string message;
        std::getline(std::cin, message);

        // auto commands = split_message(input, " ");

        if (command == "exit") {
            return 0;
        } else if (command == "echo") {
            std::cout << message << std::endl;
        } else {
            std::cout << command << ": command not found\n";
        }
    }
}
