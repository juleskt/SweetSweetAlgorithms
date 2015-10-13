#include "Graph.h"
#include <iostream>
#include <utility>

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

//Some unit tests
int main()
{
	/*Graph a;
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
	
	cout << a.print() << endl;*/
	return 0;
}
