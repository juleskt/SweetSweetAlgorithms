#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <sstream> 
#include <fstream>
#include <exception>
using namespace std;
//exec JulianTrinh 

vector < vector <double> > adjMatrix(100);

string sendCode(int);
void process(string, ClientSocket&);

int main ()
{
	
		/*try
		{ 
	     		ClientSocket client_socket ("128.197.185.27", 8001);
			string send = exec;
			send+= "getAllRates"; 
			string reply;
			string dicks;
			double dafuq;
	      
			//while (send!="done") 
			{
				client_socket << send+"\n";
				//sleep(5);
				sleep(1);
				int prevDick = 0;
				while(true)
				{
					prevDick = dicks.size();
					client_socket >> reply;
					dicks += reply;
					
					if(prevDick - dicks.size() == 0)
						break;	
				}
				//cout << reply;
				dicks.erase(0,50);
				//cout << dicks;
				//process(dicks,client_socket);
			}
		}
		catch ( SocketException& e )
		{
			cout << "Exception was caught:" << e.description() << "\n";
		}*/
		
		try
		{ 
	     		ClientSocket client_socket ("128.197.185.27", 8001);
			string send = exec;
			send+= "getStatus"; 
			string reply;
			string dicks;
			double dafuq;
	      
			//while (send!="done") 
			{
				while(true)
				{
				client_socket << send+"\n";
				//sleep(5);
					sleep(1);
					client_socket >> reply;
					cout << reply << endl;
				}
			}
		}
		catch ( SocketException& e )
		{
			cout << "Exception was caught:" << e.description() << "\n";
		}
return 0;
} 
	
void process(string reply, ClientSocket& s)
{
	int count = 0;
	int size;
	stringstream ss;
	for (int x = 0; x < reply.length(); x++)
	{
		if (reply[x] == ' ')
		{
			try
			{
				adjMatrix[count].push_back(stod(ss.str()));
			}
			catch(exception& e)
			{
				
			}
			ss.str(string());
			ss.clear();
		}
		else if (reply[x] == '\n')
		{
			count++;
			ss.str(string());
			ss.clear();
			//cout << count;
		}
		else
		{
			ss << reply[x];
		}
	}

	double largest = 0;
	int bigIndex = 0;
	double xChange = 0;

	for (int x = 0; x < adjMatrix[0].size(); x++)
	{
		if (adjMatrix[0][x] * adjMatrix[x][0] > largest)
		{
			if (adjMatrix[0][x] * 15 < 1000)
			{
				largest = adjMatrix[0][x] * adjMatrix[x][0];
				bigIndex = x;
				xChange = (adjMatrix[0][x]);
			}
		}
	}
	cout << bigIndex << " : " << largest << endl;
	if (largest > 1.001 && bigIndex != 0)
	{
		string reply;
		string thing;
		string send = "JulianTrinh 5b7d331ff1ed9776 exchange 0 15 ";
		send += to_string((long long int)bigIndex);
		s << send;
		string send2 = "JulianTrinh 5b7d331ff1ed9776 exchange ";
		xChange = (xChange * 15)*1.0005;
		send2 += to_string((long long int)bigIndex); send2 += " "; send2 += to_string((long double)xChange); send2 += " "; send2 += "0";
		s << send;
	}
	string line;
	s >> line;
	cout << line << endl;
}
