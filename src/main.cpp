#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

enum shell_command {
    exit0,
    type,
    echo
};

int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::unordered_map<std::string, shell_command> commands;
    commands.insert({"exit", exit0}); 
    commands.insert({"type", type}); 
    commands.insert({"echo", echo});

    while(true) {
        std::cout << "$ ";
        
        std::string input;
        std::getline(std::cin, input);
        
        std::stringstream ss = std::stringstream(input);
        std::string str_command;
        std::getline(ss, str_command, ' ');
        std::string message;
        std::getline(ss, message);

        if (!commands.contains(str_command)) {
            std::cout << str_command << ": command not found\n";
            continue;
        }

        auto command = commands[str_command];
        
        switch (command) {

            case exit0: {
                return 0;
                break;
            };

            case type: {
                if (commands.contains(message)) {
                    std::cout << message << " is a shell builtin\n";
                } else {
                    std::cout << message << ": not found\n";
                }
                break;
            };

            case echo: {
                std::cout << message << std::endl;
                break;
            };
        }
    }
}
