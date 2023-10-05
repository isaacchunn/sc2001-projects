#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <string>
#include <fstream>
#include <vector>

using namespace std;

class DataHandler
{
	public:
		 //Handle the fstream stuff.
		static void WriteCSV(string fileName, vector<string> colName, vector<string> edgeData);
		static void ReadCSV(string fileName);
};


#endif