#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <unordered_map>
#include <algorithm>
using namespace std;

class AdjacencyList {
private:
	map<string, float> ranks;
	map<string, unsigned int> out_degree;
	map<string, vector<string>> in_degree;

public:
	// empty constructor
	AdjacencyList() { }

	// function to insert a new edge
	void InsertEdge(string from_page, string to_page)
	{
		in_degree[to_page].push_back(from_page);
		out_degree[from_page] += 1;

		// if the key from_page key is not found in the in_degree graph
		// add a new from_page key with an empty value into the in_degree graph
		if (in_degree.find(from_page) == in_degree.end())
		{
			in_degree[from_page] = {};
		}

		// if the key to_page key is not found in the out_degree graph
		// add a new to_page key with a value of 0 into the out_degree graph
		if (out_degree.find(to_page) == out_degree.end())
		{
			out_degree[to_page] = 0;
		}
	}

	// prints the pageranks of all pages in ascending alphabetical order
	void Print()
	{
		for (map<string, float>::iterator iter = ranks.begin(); iter != ranks.end(); iter++)
		{
			cout << setprecision(2) << fixed << iter->first << " " << iter->second << endl;
		}
	}

	void PageRank(int powerCount)
	{
		// initialize new pageranks to: 1 / |V|
		for (map<string, vector<string>>::iterator pageIter = in_degree.begin(); pageIter != in_degree.end(); pageIter++)
		{
			ranks[pageIter->first] = 1.0f / (float)in_degree.size();
		}

		// perform power iteration
		for (int i = 1; i < powerCount; i++)
		{
			map<string, float> tempRanks;

			// iterate through each page
			for (map<string, vector<string>>::iterator pageIter = in_degree.begin(); pageIter != in_degree.end(); pageIter++)
			{
				// hold value of the pagerank
				float val = 0.0f;

				// calculate the pagerank of each page
				for (auto nextIter = pageIter->second.begin(); nextIter != pageIter->second.end(); nextIter++)
				{
					val += (1.0f / (float)out_degree.find(*nextIter)->second) * ranks[*nextIter];
				}
				tempRanks[pageIter->first] = val;
			}
			ranks = tempRanks;
		}
		Print();
	}
};


int main()
{
	// initialize variables 
	int lineCount = 0;
	int powerCount = 0;
	string from_page = "";
	string to_page = "";

	// take in input from user
	cin >> lineCount;
	cin >> powerCount;

	// create user's graph within the AdjacencyList class
	AdjacencyList userGraph;

	for (int i = 0; i < lineCount; i++)
	{
		// take in website input from user
		cin >> from_page;
		cin >> to_page;

		userGraph.InsertEdge(from_page, to_page);
	}

	// call PageRank() func to calculate all pageranks and print each pagerank in ascending alphabetical order
	userGraph.PageRank(powerCount);
}