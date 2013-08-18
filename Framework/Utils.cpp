#include "stdafx.h"
#include "Utils.h"

#include <iostream>
#include <ctime>

#include <climits>
#include <sstream>
#include <vector>

#include "boost/lexical_cast.hpp"
std::string Utils::getTime()
{
	std::string stime = "";
	time_t timeAsSecs;
	time( &timeAsSecs );
	std::tm tm;
	localtime_s(&tm, &timeAsSecs );

	if (tm.tm_mday < 10)
		stime += "0";
	stime += boost::lexical_cast<std::string, int>(tm.tm_mday);
	stime += tm.tm_mon < 10 ? ".0" : ".";
	stime += boost::lexical_cast<std::string, int>(tm.tm_mon + 1);
	stime += ".";
	stime += boost::lexical_cast<std::string, int>(tm.tm_year + 1900);
	stime += tm.tm_hour < 10 ? " 0" : " ";
	stime += boost::lexical_cast<std::string, int>(tm.tm_hour);
	stime += tm.tm_min < 10 ? ".0" : ":";
	stime += boost::lexical_cast<std::string, int>(tm.tm_min);
	stime += tm.tm_sec < 10 ? ".0" : ":";
	stime += boost::lexical_cast<std::string, int>(tm.tm_sec);

	return stime;
}


sf::Color Utils::lerp(const sf::Color& first, const sf::Color& second, float value)
{
	typedef unsigned __int8 _uint8;
	if(value > 1.f)value = 1.f;
	else if(value < 0.f) value = 0.f;

	return sf::Color((_uint8)(first.r + ((float)(second.r - first.r) * value)),
					 (_uint8)(first.g + ((float)(second.g - first.g) * value)),
					 (_uint8)(first.b + ((float)(second.b - first.b) * value)),
					 (_uint8)(first.a + ((float)(second.a - first.a) * value)));
}


std::vector<std::string>& Utils::split(const std::string &s, char delim, std::vector<std::string> &elems, int limit)
{
	std::stringstream ss(s);
	std::string item;
	int i = 0;
	while(std::getline(ss, item, delim))
	{
		elems.push_back(item);
		if(i++ >= limit)
			break;
	}
	return elems;
}


std::vector<std::string> Utils::split(const std::string& s, char delim, int limit)
{
	std::vector<std::string> elems;
	return split(s, delim, elems, limit);
}


float Utils::distance(const float& x1, const float& y1, const float& x2, const float& y2)
{
	return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}


int Utils::round(const float& number)
{
    return (int)(number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5));
}

bool Utils::collision(const sf::IntRect& first, const sf::IntRect& second)
{
	return first.intersects(second);
}

