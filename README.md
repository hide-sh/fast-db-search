# Fast db search
* Fast db search is a tool coded in C++ usefull for search keywords in a lot of databases.

## How does it works theoretically
Fast db search is using threads to open all files in the same time (Not CPU friendly), so the program is able to read multiple files at the same time.

## How does it really works
The program lists all files in a db/ folder.
```c++
struct dirent* en;
	DIR* dr;
	dr = opendir("db/");
	if (dr) {
		while ((en = readdir(dr)) != NULL) {
			std::string filename = std::string(en->d_name);
```
then create a thread, stocked in a vector
```c++
std::vector<std::thread> threads;
threads.push_back(std::thread(search_thread, &output, filepath, filename, keyword, &num));
```
and then append in the output var the lines where keywords are located in the files.
```c++
while (getline(file, line)) {
			if (line.find(keyword) != std::string::npos) {
				*output = *output + line + "\n";
				*num++;
```
