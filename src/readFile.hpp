#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "include/filelib.hpp"

void readFile(std::string file, bool p, bool s, bool b, std::string m) {
    /*if(m == "hex"){
        std::cout << readFilehex(file.c_str());
    }
    else if(m == "bin"){
        std::vector<char> data = ReadAllBytes(file.c_str());
        for(int i=0; i<data.size(); ++i)
            std::cout << std::hex << (int)data[i];
    }
    else*/ if(m == "utf8"){
        std::wcout << readFile8(file.c_str());
    }
    else if(m == "utf16"){
        std::wcout << readFile16(file.c_str());
    }
    else {
        std::cout << "Invalid format";
    }
}
