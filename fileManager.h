#pragma once
#include "Header.h"
#include "Statistics.h"

class fileManager
{
public:
	sf::String statsfromfile(std::string);
	void statsToVarFile(std::string, Statistics*, int);
	void sortFile(std::string, int);
};

