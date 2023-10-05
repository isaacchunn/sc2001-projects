#include "DataHandler.h"

///
void DataHandler::WriteCSV(string fileName, vector<string> columnNames, vector<string> edgeData)
{
	ofstream myFile(fileName);
	//Write column names
	for (int i = 0; i < columnNames.size(); i++)
	{
		myFile << columnNames[i];
		if(i != columnNames.size()-1) 
			myFile << ",";
	}
	myFile << "\n";
	//Then just write each line of edge data
	for (int i = 0; i < edgeData.size(); i++)
	{
		myFile << edgeData[i] << "\n";
	}
	myFile.close();
}

void DataHandler::ReadCSV(std::string fileName)
{
}
