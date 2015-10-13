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
	Edge(string destination, int distance)
	{
		this->destination = destination;
		this->distance = distance;
	}
	string destination;
	int distance;
};

class Vertex
{
public:
	Vertex(){}
	Vertex(string name)
	{
		this-> name = name;
	}

	mutable vector<Edge> edgeVec;
	string name;

	bool operator< (const Vertex &right) const
	{
  		return this->name < right.name;
	}

	bool operator == (const Vertex &right) const
	{
		return this->name == right.name;
	}
};

int main()
{
	string thing, variable;
	set <Vertex> Vertices;
	set <Vertex> primSet;
	//vector <string> path;
	int numVertices;

	ifstream myFile("map.txt");

	while(getline(myFile,thing))
	{
		Vertex temp(thing.substr(0,4));
		Vertices.insert(temp);
		for(set<Vertex>::iterator it = Vertices.begin(); it !=  Vertices.end(); it++)
		{
			if((it)-> name == temp.name)
			{
				Edge tempEdge(thing.substr(9,4), stoi(thing.substr(15,thing.length()-15)));
				(it)->edgeVec.push_back(tempEdge);
			}
		}
	}
	myFile.close();

	numVertices = Vertices.size();

	Vertex start;
	string node;
	for(set<Vertex>::iterator it = Vertices.begin(); it != Vertices.end(); it++)
	{
		if(it->name == "ETCW")
		{
			start = *it;
			node = it->name;
		}
	}

	cout << node << endl;
	primSet.insert(start);
	//vector<const Vertex*> lowestNodes;
	//vector<string>

	while(primSet.size() != numVertices)
	{
		int lowest = numeric_limits<int>::max();
		Vertex temp;
		for(set<Vertex>::iterator it = primSet.begin(); it!= primSet.end(); it++)
		{
			for(int x = 0; x < it->edgeVec.size(); x++)
			{
				if(it->edgeVec[x].distance < lowest)
				{
					Vertex check(it->edgeVec[x].destination);

					if(primSet.find(check) == primSet.end())
					{
						lowest = it->edgeVec[x].distance;
						node = it->edgeVec[x].destination;
						
						for(set<Vertex>::iterator it2 = Vertices.begin(); it2 != Vertices.end(); it2++)
						{
							if(*it2 == *it)
							{
								temp = *it2;
								//lowestNodes.push_back(ptr);
							}
						}
					}
				}
			}
		}
		cout << node << endl;
		primSet.insert(temp);
		Vertices.erase(temp);

		for(set<Vertex>::iterator it2 = primSet.begin(); it2!= primSet.end(); it2++)
		{
			for(int x = 0; x < it2->edgeVec.size(); x++)
			{
				if(it2->edgeVec[x].destination == node)
				{
					it2->edgeVec.erase(it2->edgeVec.begin()+x);
				}
			}
		}
	}
	cout <<"ETCW" << endl;
}

//Insert CHXN at 1365 rofl
//LSQI at 668 lmao
//XXZC at 1498