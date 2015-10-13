#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <limits>
using namespace std;

class Edge
{
public:
		Edge(string start, string end, int distance)
		{
			this->start = start;
			this->end = end;
			this->distance = distance;
		}
		string start;
		string end;
		int distance;
};

int main()
{
	string thing, variable;
	vector <Edge*> edgeVec;
	set <string> verts,traversed;
	int lowCount = numeric_limits<int>::max();
	int count = 0;
	Edge* lowest;
	string node, start;
	bool zone = false;

	ifstream myFile("map.txt");

	while(getline(myFile,thing))
	{
		edgeVec.push_back(new Edge(thing.substr(0,4), thing.substr(9,4), stoi(thing.substr(15,thing.length()-15)) ) );
		verts.insert(thing.substr(0,4));
	}
	myFile.close();

	node = edgeVec[0]->start;
	start = node;
	traversed.insert(node);

	cout << node << endl;

	while(edgeVec.size() > 0)
	{
		for(int x = 0; x < edgeVec.size(); x++)
		{
			if(edgeVec[x]->start == node)
			{
				if(edgeVec[x]->distance < lowCount)
				{
					lowest = edgeVec[x];
					lowCount = edgeVec[x]->distance;
				}
			}
			
			if(edgeVec[x]->start != node && lowCount != numeric_limits<int>::max())
			{
				break;
			}
		}
		lowCount = numeric_limits<int>::max();
		
		for(int x = 0; x < edgeVec.size(); x++)
		{
			if(edgeVec[x]->end == node)
				edgeVec.erase(edgeVec.begin()+x);
		}
		count++;
		cout << lowest->end << endl;
		node = lowest->end;
		if(count > verts.size())
			break;
	}
		cout << start << endl;
}