#include <filesystem>
#include <string>

int main(int argc, char *argv[]) {
    std::string command;

    for (int i = 1; i<argc; i++) {
        command += argv[i];

        if (i != argc-1) command += " ";
    }

    std::filesystem::current_path(command.c_str());
}