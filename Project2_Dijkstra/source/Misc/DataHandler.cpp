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

bool DataHandler::ReadCSV(string fileName, vector<std::pair<int, int>>& pairData, vector<int>& weights, int& graphSize)
{
	try
	{
		std::ifstream myFile(fileName);
		if (!myFile.is_open())
		{
			throw std::runtime_error("Could not open file");
		}

		string line;
		int data;
		int verticeCount = -INT_MAX;
		if (myFile.good())
		{
			//Extract the first line in the file to get rid of column names
			getline(myFile, line);
			while (getline(myFile, line))
			{
				int idx = 0;
				std::pair<int, int> vertexPair;
				int weight;

				stringstream ss(line);
				while (ss >> data)
				{
					//0 is source
					//1 is target
					//2 is weight
					if (idx == 0)
					{
						vertexPair.first = data;					
					}
					else if (idx == 1)
					{
						vertexPair.second = data;
					}
					else
					{
						weight = data;
					}

					//Find number of vertices in the graph
					if (idx != 2 && verticeCount < data)
						verticeCount = data;

					if (ss.peek() == ',')
						ss.ignore();
					idx++;
				}
				//Append the relevant details into the vectors
				pairData.push_back(vertexPair);
				weights.push_back(weight);
			}
			//Then update graph size
			if(verticeCount != -INT_MAX)
				graphSize = verticeCount;
		}
		myFile.close();
	}
	catch (std::runtime_error e)
	{
		std::cout << "Could not find fileName of " << fileName << "!" << endl;
		return false;
	}
	return true;
}


