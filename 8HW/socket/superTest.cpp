#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#define exec "JulianTrinh 5b7d331ff1ed9776 "
using namespace std;

vector < vector <string> > adjMatrix(101);

const char* sendCode(int);
void process(string);

int main()
{
	string lol;
	system("telnet algorithmics.bu.edu 8001");
	system(sendCode(0));
	//cout << sendCode(0);
	return 0;
}

const char* sendCode(int code)
{
	string command;

	switch(code)
	{
		case 0: 
			command = "getStatus"; 
			break;
		case 1: 
			command = "getAllRates";
			break;
	}

	return (exec + command).c_str();
}

void process(string reply)
{
	int count = 0;
	int size;
	stringstream ss;
	for(int x = 0; x < reply.length(); x++)
	{	
		if(reply[x] == ' ')
		{
			adjMatrix[count].push_back(ss.str());
			ss.str(string());
			ss.clear();
		}
		else if(reply[x] == '\n')
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

	size = adjMatrix.size();

	if(size%3 == 0)
	{

	}
	else if(size%3 == 1)
	{

	}
	else
	{

	}
}