#include "Graph.h"
#include <iostream>
#include <utility>
#include <ctime>
#include <random>
#include <stdlib.h>

using namespace std;

typedef set<int,int>::iterator edgeIT;

Graph::Graph()
{

}

string Graph::print() 
{
	stringstream result;
	for (vertexIterator vert1=vertices.begin(); vert1 != vertices.end(); vert1++) 
	{
		result << *vert1 << "[" << getColor(*vert1) << "]: ";
		for (vertexIterator vert2 = vertices.begin(); vert2 != vertices.end(); vert2++)
		{
			if (isEdge (directedEdge(*vert1, *vert2)))
				result << *vert2 << " ";
		}
		result << endl;
	}
		return result.str();
}

int Graph::addVertex(int color)
{
	int size = colors.size()+1;
	colors.insert(pair<int,int>(size,color));
	vertices.insert(size);

	return size;
}

void Graph::addEdge(directedEdge newedge)
{
	bool vert1,vert2;
	for(vertexIterator vertex = vertices.begin(); vertex != vertices.end(); vertex++)
	{
		if(*vertex == get<0>(newedge))
			vert1 = true;
		if(*vertex == get<1>(newedge))
			vert2 = true;
	}

	if(vert1 && vert2)
	{
		edges.insert(newedge);
	}
}

int Graph::getColor(int vertex)
{
	return colors[vertex];
}

bool Graph::isEdge(directedEdge newedge)
{
	bool vert1,vert2;

	if(edges.find(newedge) != edges.end())
		return true;
	else
		return false;
}

Graph* Graph::generateRandom(int num)
{
	Graph graph;
	for(int x = 0; x < num; x++)
	{
		graph.addVertex(1);
	}

	for(int x = 1; x <= num; x++)
	{
		for(int y = x; y <= num; y++)
		{
			srand (time(0));
			if(rand() % 2)
				graph.addEdge(pair<int,int>(x,y));
		}
	}

	
	Graph* graphPtr = new Graph;
	*graphPtr = graph;

	return graphPtr;
}

int main()
{
	Graph a;
	a.addVertex(1);
	a.addVertex(2);
	a.addVertex(3);
	a.addVertex(1);
	a.addEdge(pair<int,int>(1,2));
	a.addEdge(pair<int,int>(1,3));
	a.addEdge(pair<int,int>(1,4));
	a.addEdge(pair<int,int>(2,3));
	a.addEdge(pair<int,int>(2,2));
	a.addEdge(pair<int,int>(3,1));
	a.addEdge(pair<int,int>(4,2));
	
	cout << a.print();
	return 0;
}