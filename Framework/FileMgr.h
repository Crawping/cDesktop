#pragma once

#include <string>
#include <vector>

class FileMgr
{
	typedef std::vector<std::string> Lines;
public:
	static bool clearFile(std::string path);

	static bool	write  (std::string path, std::string line);
	static bool	write  (std::string path, Lines lines);
	static bool	writeln(std::string path, std::string text) { return write(path, text + "\n"); }

	static int	search (std::string path, std::string text); // Found Text or not and how many (counter not implemented yet)

	static Lines getFile(std::string path);
};