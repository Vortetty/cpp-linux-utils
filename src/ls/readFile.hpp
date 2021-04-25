#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "include/termLib.hpp"
#include "include/filelib.hpp"

void readFile(std::string file, bool p, bool s, bool b, std::string m) {
    if(m == "bin"){
        std::vector<char> data = readAllBytes(file.c_str());
        int tmp = 0;

        for (auto i : data){
            if (tmp + 3 >= termX) {
                std::cout << std::endl;
                tmp = 0;
            }
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)i << " ";
            tmp += 3;
        }
    }
    else if (m == "utf8"){
        std::wcout << readFile8(file.c_str());
    }
    else if (m == "utf16"){
        std::wcout << readFile16(file.c_str());
    }
    else {
        std::cout << "Invalid format";
    }
    std::cout << std::endl;
}
