#include <filesystem>
#include <string>
#include <fstream>

int main(int argc, char *argv[]) {
    std::string filename;

    for (int i = 1; i<argc; i++) {
        filename += argv[i];

        if (i != argc-1) filename += " ";
    }

    std::ofstream ifs(filename, std::ios::binary|std::ios::ate);
    ifs << "";
    ifs.close();
}