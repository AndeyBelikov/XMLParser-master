#pragma once

#include <fstream>

class readWritter
{
public:

	std::fstream fs;

	readWritter();
	~readWritter();

	readWritter(const readWritter&) = delete;
	readWritter& operator= (const readWritter&) = delete;

};

