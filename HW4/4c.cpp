#include <iostream>
#include <fstream>
#include <string>
#include "sha1.h"
#include "hash.h"
#include <cstdlib>
#include <random>
#include <chrono>
using namespace std;

int main()
{
	int count = 0;
	ofstream myFile;
	myFile.open("4cTable.txt");

	string start = "!!!!!";
	myFile << start << ",";
	string reduction;
	string hashed = start;
	
	while(true)
	{
		cout << count << endl;
		for(int x = 0; x < 1000000; x++)
		{
			reduction = reduce(hashed,5);
			hashed = hash(reduction);
		}
		string end = reduce(hashed,5);
		myFile << end << endl;
		myFile << reduce(hash(end),5) << ",";
        	string s = reduce(hash(end),5);
                
		for(int x = 0; x < 5; x++)
                {
		default_random_engine gen(seed);	
	    	   // s[x] = (rand() % 93 + 33);
                	s[x] = shuffle(33,127,gen);
		}

		hashed = hash(s);                
        	count++;

