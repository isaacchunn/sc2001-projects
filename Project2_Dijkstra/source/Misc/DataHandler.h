#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

class DataHandler
{
	public:
		 //Handle the fstream stuff.
		static void WriteCSV(string fileName, vector<string> colName, vector<string> edgeData);
		static bool ReadCSV(string fileName, vector<std::pair<int, int>>& data, vector<int>& weights, int& graphSize);
};


#endif