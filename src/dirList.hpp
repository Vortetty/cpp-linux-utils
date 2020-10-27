#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <chrono>
#include <ctime>
#include <cmath>
#include <iostream>
#include <filesystem>
#include <vector>
#include <unistd.h>
#include "include/rang.hpp"
#include "include/rang-colorblind.hpp"

namespace fs = std::filesystem;

struct SL {
	std::string size, label;
}; 

typedef struct SL sl; 

int maxfilename, maxsize = 0;

sl parseSize(long double B, bool s){
	long double KB = 0;  //Kilobytes
	long double MB = 0;  //Megabytes
	long double GB = 0;  //Gigabytes
	long double TB = 0;  //Terabytes
	long double PB = 0;  //Petabytes
	long double EB = 0;  //Exabytes
	long double ZB = 0;  //Zetabytes
	long double YB = 0;  //Yottabytes
	long double BB = 0;  //Brontobytes (not officially recognized yet)
	long double GEB = 0; //Gegobytes (also not officially recognized yet)
	int bpk = 1024;      //Bytes per Kilobyte, used to measure size of files, Not enabled as 
	if(s) {bpk = 1000;}  //It inflates the size of your files compared to the os measurement
	std::string out  = "";
	std::string out1 = "";
	sl out2;

	if (B >= bpk){
		KB = B / bpk;
		B = fmod(B, bpk);
		out = std::to_string(KB);
		out1 = "KB";
	} else {
		out = std::to_string(B);
		out1 = "B";
	} if (KB >= bpk){
		MB = KB / bpk;
		KB = fmod(KB, bpk);
		out = std::to_string(MB);
		out1 = "MB";
	} if (MB >= bpk){
		GB = MB / bpk;
		MB = fmod(MB, bpk);
		out = std::to_string(GB);
		out1 = "GB";
	} if (GB >= bpk){
		TB = GB / bpk;
		GB = fmod(GB, bpk);
		out = std::to_string(TB);
		out1 = "TB";
	} if (TB >= bpk){
		PB = TB / bpk;
		TB = fmod(TB, bpk);
		out = std::to_string(PB);
		out1 = "PB";
	} if (PB >= bpk){
		EB = PB / bpk;
		PB = fmod(PB, bpk);
		out = std::to_string(EB);
		out1 = "EB";
	} if (EB >= bpk){
		ZB = EB / bpk;
		EB = fmod(EB, bpk);
		out = std::to_string(ZB);
		out1 = "ZB";
	} if (ZB >= bpk){
		YB = ZB / bpk;
		ZB = fmod(ZB, bpk);
		out = std::to_string(YB);
		out1 = "YB";
	} if (YB >= bpk){
		BB = YB / bpk;
		YB = fmod(YB, bpk);
		out = std::to_string(BB);
		out1 = "BB";
	} if (BB >= bpk){
		GEB = BB / bpk;
		BB = fmod(BB, bpk);
		out = std::to_string(GEB);
		out1 = "GeB";
	}

	out2.size = out;

	out1.append(std::max(maxsize - (int)out1.length() - (int)out.length(), 0), ' ');
	out2.label = out1;

	return out2;
}

int largest(std::vector<int> arr) 
{ 
    int i; 
      
    // Initialize maximum element 
    int max = arr[0]; 
  
    // Traverse array elements  
    // from second and compare 
    // every element with current max  
    for (i = 1; i < arr.size()-1; i++) 
        if (arr[i] > max) 
            max = arr[i]; 
  
    return max; 
} 

void listDir(std::string path, bool p, bool s, bool b) {

	std::vector<int> names;
	std::vector<int> sizes;

	for (const auto & entry : fs::directory_iterator(path)){
		std::string file = entry.path().generic_string();
		file.replace(0, path.length()+1, "");

		names.push_back(file.length());

		if(!entry.is_directory()){
			sl size = parseSize(entry.file_size(), s);
			sizes.push_back(size.size.length() + size.label.length());
		}
	}

	maxfilename = largest(names);
	maxsize = largest(names);

	std::cout << "----------" << std::endl;
	for (const auto & entry : fs::directory_iterator(path)){
		std::string file = entry.path().generic_string();
		file.replace(0, path.length()+1, "");
		file.append(maxfilename - std::max((int)file.length(), 0), ' ');

		if(b){
			if(entry.is_directory()){
				file.append((maxfilename + maxsize) - std::max((int)file.length(), 0) + 3, ' ');
				std::cout << rangcolorblind::fgB::blue << file << rangcolorblind::fg::reset;
			} else if(access(entry.path().c_str(), X_OK) != -1){
				sl size = parseSize(entry.file_size(), s);
				std::cout << rangcolorblind::fgB::magenta << file << rangcolorblind::fg::reset << " - " << size.size << rangcolorblind::fgB::red << size.label << rangcolorblind::fg::reset;
			} else if(entry.is_regular_file()){
				sl size = parseSize(entry.file_size(), s);
				std::cout << rangcolorblind::fgB::red << file << rangcolorblind::fg::reset << " - " << size.size << rangcolorblind::fgB::red << size.label << rangcolorblind::fg::reset;
			}
		}
		else {
			if(entry.is_directory()){
				file.append((maxfilename + maxsize) - std::max((int)file.length(), 0) + 3, ' ');
				std::cout << rang::fgB::blue << file << rang::fg::reset;
			} else if(access(entry.path().c_str(), X_OK) != -1){
				sl size = parseSize(entry.file_size(), s);
				std::cout << rang::fgB::magenta << file << rang::fg::reset << " - " << size.size << rang::fgB::red << size.label << rang::fg::reset;
			} else if(entry.is_regular_file()){
				sl size = parseSize(entry.file_size(), s);
				std::cout << rang::fgB::red << file << rang::fg::reset << " - " << size.size << rang::fgB::red << size.label << rang::fg::reset;
			}
		}

		if(p) {
			std::cout << " -";
			if(access(entry.path().c_str(), R_OK) != -1) std::cout << " Read";
			if(access(entry.path().c_str(), W_OK) != -1) std::cout << " Write";
			if(access(entry.path().c_str(), X_OK) != -1) std::cout << " Execute";
		};

		std::cout << std::endl;
	}
	std::cout << "----------" << std::endl;
}
