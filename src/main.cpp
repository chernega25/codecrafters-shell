#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <filesystem>
#include <cstdlib>
#include <optional>

namespace fs = std::filesystem;

enum shell_command {
    exit0,
    type,
    echo,
    pwd,
    cd
};

std::optional<std::string> find_file(const std::string& path, const std::string& filename) {
    std::stringstream ss = std::stringstream(path);
    std::string line;
    while (getline(ss, line, ':')) {
        fs::path directory(line);
        for (const auto& entry: fs::directory_iterator(directory)) {
            if (entry.path().filename() == filename) {
                return entry.path().string();
            }
        }
    }

    return {};
}

int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::string path = getenv("PATH");

    std::unordered_map<std::string, shell_command> commands;
    commands.insert({"exit", exit0}); 
    commands.insert({"type", type}); 
    commands.insert({"echo", echo}); 
    commands.insert({"pwd", pwd});
    commands.insert({"cd", cd});

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
            auto filepath = find_file(path, str_command);
            if (filepath.has_value()) {
                std::string exec = filepath.value() + ' ' + message;
                std::system(exec.c_str());
            } else {
                std::cout << str_command << ": command not found\n";
            }
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
                    break;
                } 

                auto filepath = find_file(path, message);
                if (filepath.has_value()) {
                    std::cout << message << " is " << filepath.value() << std::endl;
                } else {
                    std::cout << message << ": not found\n";
                }
                
                break;
            };

            case echo: {
                std::cout << message << std::endl;
                break;
            };

            case pwd: {
                std::filesystem::path current_dir = std::filesystem::current_path();
                std::cout << current_dir.string() << std::endl;
                break;
            }

            case cd: {
                try {
                    std::filesystem::current_path(message);
                } catch (fs::filesystem_error error) {
                    std::cout << "cd: " << message << ": No such file or directory\n";
                }
                break;
            }
        }
    }
}
