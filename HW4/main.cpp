#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "hash.h"
#include "sha1.h"
using namespace std;

int main()
{
	bool cracked = false;
	vector<string> start;
	vector<string> end;
	string line;
	ifstream myfile;
//	myfile.open("RainbowTable.txt");

	string hashes [10] = 
	{
		"65f9f0d2a264928e55e21d0991c2dd223f5a3e8d",
		" ", " ", " ", " ", " ", " ", " ", " ", " "
	}; 	
	
/*	if(myfile.is_open())
	{
		while (getline (myfile,line))
		{
			start.push_back(line.substr(0,5));
			end.push_back(line.substr(6,5));
		}
		myfile.close();
	}	
*/	
	myfile.open("table.txt");
	if(myfile.is_open())
	{
		while(getline (myfile,line))
		{
			start.push_back(line.substr(4,5));
			end.push_back(line.substr(14,5));
		}
		myfile.close();
	}
	
	//Loop through hashes to crack	
	for(int x = 0; x < 1; x++)
	{
		string hashed = hashes[x];
		cracked = false;
		while(!cracked)
		{
			//Get reduction and check with all the end-chains
			string reduction = reduce(hashed,5);	
			for(int y = 0; y < end.size(); y++)
			{
				//If it matches the end, go to beginning and check
				if(reduction == end[y])
				{
					cout << end[y] << endl;
					//Start at beginning
					reduction = start[y];
					while(true)
					{
					//	cout << hashes[x] << endl;
					//	Start with the hash of the first of the chain and keep hashing everyloop
						hashed = hash(reduction);
						//If the hashes match, the previous reduction is the password
						if(hashed == hashes[x])
						{
							//Print the password, set flag and break out
							cout << "pw: " << reduction << endl;
							cout << "Sanity: " << hash(reduction) << endl;
							cracked = true;
							return 0;
							break;
						}
						else if(reduction == end[y])
						{
							//Reached the end, wrong chain. Break.
							cout << "Reached end using hash: " << hashes[x] << " " << hashed << endl;
							break;
						}
						//If the hash did not match, reduce so it can be hashed and checked again
						reduction = reduce(hashed,5);
					}					
				} 
			}
			//Hash for the next reduction
			hashed = hash(reduction);	
			//If you find the pw, move on to the next one
			if(cracked)
				break;
		}	
	}
	return 0;
}
