#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <thread>
#include <sys/types.h>
#include "dirent.h"

void search_thread(std::string *output, std::string filepath, std::string filename, std::string keyword, int *num) {
	// open the file to find keyword in lines, if found write in the output pointer
	std::string line;
	std::ifstream file;
	file.open(filepath);
	if (file.is_open()) {
		while (getline(file, line)) {
			if (line.find(keyword) != std::string::npos) {
				*output = *output + line + "\n";
				*num++;
			}
		}
	}
	file.close();
}

std::string search_algorithm(std::string keyword, std::string folderpath) {
	// open dir and find all files, thread search_thread function to read in them
	int num = 1;
	std::string output;
	std::vector<std::thread> threads;
	struct dirent* en;
	DIR* dr;
	dr = opendir("db/");
	if (dr) {
		while ((en = readdir(dr)) != NULL) {
			std::string filename = en->d_name;
			std::string filepath = folderpath + filename;
			if (filename == "." || filename == "..") {
			}
			else {
				threads.push_back(std::thread(search_thread, &output, filepath, filename, keyword, &num));
			}
		}
	}

	for (auto& thread : threads) {
		thread.join();
	}

	return output;
}

void write_output(std::string *output, std::string output_name) {
	std::ofstream file;
	file.open(output_name);
	file << *output;
	file.close();
}

int main(int argc, char** argv) {
	std::string keyword = argv[1];
	std::string output_name = argv[2];
	std::string output = search_algorithm(keyword, "db/");
	if (output == "") {
		output = "didn't found anything";
		write_output(&output, output_name);
	}
	else {
		write_output(&output, output_name);
	}
	return 1;
}
