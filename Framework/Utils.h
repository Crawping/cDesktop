#pragma once

#include <cstdlib>
#include <vector>
#include <iostream>

class Utils
{
public:
	static inline int GetRandom()
	{
		return rand();
	}

	// Utils.cpp
	static std::string getTime();
	static std::vector<std::string> split(const std::string& s, char delim, int limit = INT_MAX);
	static sf::Color lerp(const sf::Color& first, const sf::Color& second, float value);
	static float distance(const float& x1, const float& y1, const float& x2, const float& y2);
	static int round(const float& number);

private:
	static std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems, int limit = INT_MAX);
};