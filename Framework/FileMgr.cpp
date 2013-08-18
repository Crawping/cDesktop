#include "../stdafx.h"
#include "FileMgr.h"


bool FileMgr::write(std::string path, std::string line)
{
	std::fstream file(path, std::ios::app);
	if (file.good())
		file << line;
	else
	{
		file.close();
		return false;
	}
	file.close();
	return true;
}


bool FileMgr::write(std::string path, std::vector<std::string> lines)
{
	std::fstream file(path, std::ios::app);
	if (file.good())
		for(std::string line : lines)
			file << line;
	else
	{
		file.close();
		return false;
	}
	file.close();
	return true;
}


int FileMgr::search(std::string path, std::string _regex)
{
	int count = 0;
	std::fstream file;
	std::string line;
	std::regex regex(_regex);

	file.open( &path[0], std::ios::in);
	if (file.good())
	{
		getline (file, line);
		if (file.eof())
			return false;
		do
		{
			if (std::regex_match(line, regex))
				++count;
			getline (file, line);
		} while (!file.eof());
	}
	return count;
}

std::vector<std::string> FileMgr::getFile(std::string path)
{
	std::vector<std::string> lines;
	std::fstream file;
	std::string line;

	file.open( &path[0], std::ios::in);
	if (file.good())
		while(!file.eof())
		{
			getline(file, line);
			lines.push_back(line);
		}

		return lines;
}


bool FileMgr::clearFile(std::string path)
{
	bool ret = true;
	std::fstream file(path, std::ios::trunc | std::ios::out);
	if (!file.good())
		ret = false;
	return ret;
}
