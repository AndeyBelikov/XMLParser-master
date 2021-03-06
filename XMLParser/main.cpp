// XMLParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <mutex>
#include <thread>
#include "XMLUtil.h"

using std::string;

string formInputFile()
{

	string sInputXmlString;
	string sIntervals = "";
	string sIntervalSubElements = "";

	// count of prime numbers
	size_t nIntervalValue = 100;

	// create elements like
	//
	//	<interval>
	//		<low>nIntervalValue</low>
	//		<high>nIntervalValue</high>
	//	</interval>
	//
	for (size_t i = 0; i < 10; i++)
	{
		sIntervalSubElements = XMLUtil::formElement( "low", std::to_string(nIntervalValue++) );
		sIntervalSubElements += XMLUtil::formElement( "high", std::to_string(nIntervalValue++) );

		sIntervals += XMLUtil::formElement( "interval", "", "", sIntervalSubElements );
	}

	sInputXmlString = XMLUtil::formElement( "intervals", "", "", sIntervals );
	sInputXmlString = XMLUtil::formElement( "root", "", "", sInputXmlString );

	return sInputXmlString;
}


std::vector<string> getAttributes(const string &text, const string &low)
{
	std::vector<string> collection;
	size_t nPos = 0, nStart = 0;

	while (nStart != string::npos)
	{
		nStart = text.find("<" + low, nPos);
		if (nStart == string::npos) { return collection; } // NRVO
		nStart = text.find(">", nStart);
		++nStart;

		nPos = text.find("</" + low, nStart);
		if (nPos == string::npos) { return collection; } // NRVO
		collection.push_back(text.substr(nStart, nPos - nStart));
	}
}


template<typename T>
void openStream(T& fstream, const string& sFileName)
{
	fstream.open(sFileName);
	if (!fstream.is_open())
	{
		std::cerr << "Error in opening the file" << std::endl;
		throw std::runtime_error("Could not open file");
	}
}


void produceInputFile(const string& sFileName)
{
	std::ofstream fout;

	openStream(fout, sFileName);

	//std::lock_guard<std::mutex> guard(writeToFileMutex);

	fout << formInputFile();
	fout.close();
}


string getDataFromFile(std::ifstream& fin)
{
	std::stringstream buffer;
	buffer << fin.rdbuf();
	return buffer.str();
}


// We keep track of all of our previously calculated primes.
// If a number is divisible by a nonprime number, 
// there is also some prime <= that divisor which it is also divisble by.
// This will reduces computation
void isPrime(int numb, std::vector<int>& primes)
{

	bool bIsPrime = true;
	for (size_t j = 0; j < primes.size() && primes[j] * primes[j] <= numb; j++)
	{
		if (numb % primes[j] == 0)
		{
			bIsPrime = false;
			break;
		}
	}
	if (bIsPrime)
	{
		//std::lock_guard<std::mutex> guard(mutex);
		primes.push_back(numb);
	}

}


void findPrimeTags(const string& sFileName)
{

	std::ifstream fin;
	std::vector<int> primes;
	std::mutex mutex;

	try 
	{

		produceInputFile(sFileName);

		openStream(fin, sFileName);

		string sInputXmlString( getDataFromFile(fin) );

		fin.close();

		auto primeTags = getAttributes(sInputXmlString, "low");

		//std::vector<std::thread> threads;

	}
	catch (std::exception &ex)
	{
		std::cerr << "Ouch! That hurts, because: " << ex.what() << "!\n";
	}
	catch (...)
	{
		std::cerr << "Unknown exception caught after call findPrimeTags.\n";
	}

}


int main()
{

	const string sFileName = "../primeTags.xml";
	findPrimeTags(sFileName);

    return 0;

}

