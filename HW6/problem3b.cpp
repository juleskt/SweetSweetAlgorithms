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

//Adds a vertex starting from value 1 to the maps/sets
int Graph::addVertex(int color)
{
	int size = colors.size()+1;
	colors.insert(pair<int,int>(size,color));
	vertices.insert(size);

	return size;
}

/*Iterates through the vertices to make sure that the vertices specified in the newedge exist.
*If they do, add the edge
*/
void Graph::addEdge(directedEdge newedge)
{
	bool vert1,vert2;
	//Loop through vertex set and see if they are both in it
	for(vertexIterator vertex = vertices.begin(); vertex != vertices.end(); vertex++)
	{
		if(*vertex == get<0>(newedge))
			vert1 = true;
		if(*vertex == get<1>(newedge))
			vert2 = true;
	}
	//If the vertices do exist, create an edge between them, assuming it is not a multigraph
	if(vert1 && vert2 && !isEdge(newedge))
	{
		edges.insert(newedge);
	}
}

//Grabs the color of the vertex specified
int Graph::getColor(int vertex)
{
	if(colors.find(vertex) != colors.end())		
		return colors[vertex];
	else
		return 0;
}

//Checks if the edge specified exists in the edges set
bool Graph::isEdge(directedEdge newedge)
{
	//The find function returns end if something is not found
	if(edges.find(newedge) != edges.end())
		return true;
	else
		return false;
}

//Generates num vertices and creates an edge between them at a 50% chance
Graph* Graph::generateRandom(int num)
{
	//Create graph object
	Graph graph;
	//Seed the rand
	srand (time(0));
	//Add num vertices
	for(int x = 0; x < num; x++)
	{
		graph.addVertex(1);
	}
	//Loop through all vertices and add an edge at .5 probability
	for(int x = 1; x <= num; x++)
	{
		for(int y = 1; y <= num; y++)
		{
			if(rand() % 2)
				graph.addEdge(pair<int,int>(x,y));
		}
	}

	//Create a pointer to a Graph on the heap
	Graph* graphPtr = new Graph;
	//Clone the values of the local Graph
	*graphPtr = graph;
	//Return the heap pointer
	return graphPtr;
}

//Some unit tests
int main()
{
	/*Graph* graph = Graph::generateRandom(6);
	cout << "Size: 6" << endl;
	cout << graph->print() << endl;
	graph = Graph::generateRandom(24);
	cout << "Size: 24" << endl;
	cout << graph->print() << endl;
	graph = Graph::generateRandom(1);
	cout << "Size: 1" << endl;
	cout << graph->print() << endl;
	graph = Graph::generateRandom(2);
	cout << "Size: 2" << endl;
	cout << graph->print() << endl;*/
	
	return 0;
}
