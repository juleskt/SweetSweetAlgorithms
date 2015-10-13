#include "Socket.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <limits>
#define exec "JulianTrinh 5b7d331ff1ed9776 "
using namespace std;

vector < vector <double> > adjMatrix(101);
string sendCode(int);
void process(string);

class Edge
{
public:
	Edge(int source, int destination, double distance)
	{
		this->destination = destination;
		this->distance = distance;
		this->source = source;
	}

	int source, destination;
	double distance;
};

class Vertex
{
public:
	mutable vector<Edge*> edgeVec;
};

int main() {

	try {
		SocketClient s("algorithmics.bu.edu", 8001);

		//while (1) 
		//{
			string reply = s.ReceiveLine();
			cout << reply << endl;
			s.SendLine("JulianTrinh 5b7d331ff1ed9776 getAllRates");
			for (int x = 0; x < 100; x++)
			{
				reply += s.ReceiveLine();
				cout << reply;
				if (reply.substr(0, 10) == "CONNECTION")
				{
					break;
				}
			}
			//if (reply.empty()) break;
			//cout << reply;
			process(reply);
			cout.flush();
		//}

	}
	catch (const char* s) {
		cerr << s << endl;
	}
	catch (std::string s) {
		cerr << s << endl;
	}
	catch (...) {
		cerr << "unhandled exception\n";
	}

	return 0;
}

string sendCode(int code)
{
	string command;

	switch (code)
	{
	case 0:
		command = "getStatus";
		break;
	case 1:
		command = "getAllRates";
		break;
	}

	return exec + command;
}

void process(string reply)
{
	int count = 0;
	int size;
	stringstream ss;
	for (int x = 0; x < reply.length(); x++)
	{
		if (reply[x] == ' ')
		{
			adjMatrix[count].push_back(-log(stod(ss.str())));
			ss.str(string());
			ss.clear();
		}
		else if (reply[x] == '\n')
		{
			//adjMatrix[count].push_back(ss.str());
			count++;
			ss.str(string());
			ss.clear();
		}
		else
		{
			ss << reply[x];
		}
	}

	adjMatrix.erase(adjMatrix.begin());
	size = adjMatrix.size();
	cout << "size: " << size << endl;
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < adjMatrix[x].size(); y++)
		{
			cout << x << " : " << adjMatrix[x][y] << endl;
		}
	}

	vector<double> bellFord(100), pi(100);

	for (int x = 0; x < size; x++)
	{
		bellFord[x] = 1000000, pi[x] = -1;
	}

	bellFord[0] = 0;

	for (int x = 0; x < size; x++)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (bellFord[i] + adjMatrix[i][j] < bellFord[j])
					bellFord[j] = bellFord[i] + adjMatrix[i][j];
					pi[j] = i;
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (bellFord[i] + adjMatrix[i][j] < bellFord[j])
			{
				//j is a part of a neg cycle
			}
		}
	}
	system("pause");

	if (size % 3 == 0)
	{

	}
	else if (size % 3 == 1)
	{

	}
	else
	{

	}
}