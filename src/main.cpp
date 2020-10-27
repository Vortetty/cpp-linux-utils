#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cerrno>

#include "readFile.hpp"
#include "dirList.hpp"
#include "include/cxxopts.hpp"
#include "include/rang.hpp"
#include "include/rang-colorblind.hpp"

void print(std::string string, std::string color){
    std::cout << string << "\n";
}

void print(std::string string){
    std::cout << string << "\n";
}

int main(int argc, char *argv[]) {
    cxxopts::Options options("ft", "File tools, can do various file operations through bash");

    options.add_options()
        ("r,read", "Read file to console")
        ("l,list", "List directory to console")
        ("f,file", "File name", cxxopts::value<std::string>()->default_value(""))
        ("m,format", "File format for reading, valid values are: utf8, and utf16", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "Verbose output")
        ("c,credits", "Lists creators and used libs")
        ("p,perms", "Used to enable showing file perms, disabled by default as the check is relative to the perms of this file not if you can execute them")
        ("s,si", "Makes filesizes use 1000B per KB instead of 1024, the same thing used by harddrive companies to inflate the size of their drives")
        ("b,colorblind", "Forces usage of colors that makes it easier for the colorblind to see the default theme colors are usually such i cant adjust for monochromats though")
    ;

    auto result = options.parse(argc, argv);

    bool verbose = result["verbose"].as<bool>();
    std::string file = result["file"].as<std::string>();
    bool list = result["list"].as<bool>();
    bool read = result["read"].as<bool>();
    bool p = result["perms"].as<bool>();
    bool s = result["si"].as<bool>();
    bool b = result["colorblind"].as<bool>();
    std::string m = result["format"].as<std::string>();

    if(file == ""){
        print("File must be defined with -f <filename>");
        return EINVAL;
    }
    else if(!list && !read){
        print("-l or -r must be used");
        return EINVAL;
    }
    else if(list && read){
        print("Cannot list and read file");
        return EINVAL;
    }
    
    if(list){
        listDir(file, p, s, b);
    }
    else if(read){
        if(m != ""){
            readFile(file, p, s, b, m);
        }
        else {
            std::cout << "Format must be specified to read a file";
        }
    }

    return 0;
}