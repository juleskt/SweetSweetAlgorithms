#include <iostream>
#include <string>
#include "sha1.h"
#include "hash.h"
#include <ctime>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	bool cracked;
	string hashes[13] =
        {		
	"97df296ca6092b36684e54ba0ddfd2ff5827559a",	 	 	
	"f3b4081feb33444323698fae6e4dcd40c4b85236",
	"fa707e0ead886ad870dad791cbd51aa9ec5a0572",	 	 	 	 	 	 	
	"2a16fe5d1351d5a51690dbb018717da6aa985cd9",	 	 	
	"82a2488d7cceca5397626926309d8cc9fa75bf82",	 	 
	"89b393ad1ac920d66083440f6999746d71ed8fd8",	 	 	
	"9105daf1a0eb3c07f2ac239c6064a6a97f8fa605",	 	 
	"2189c9ea063bf90912358afa779925ec7a00a3b7",	 	 
	"8ef07dc783576e79dac1ce00a2ff8292cf3d3d48",	 	 
	"e11e308daf2c85589c3a4120fe35517472ff9e74",	 	 
	"08eb68ecd1831d37ed20d60e8ecb40063d2347cb",	 	 
	"701255a3dedc847979b7fe01926efdb4be72d243",	 	 
	"fe7836de55b94cfaced4cdb0e255a9788b38ea51",	 	 
        };
	
//	char start[3] = "!!!";
	
/*The loops go through each of the hashes above and brute force computes every 3-character string combination
 * and hashes it to check if it matches any of the provided hashes above. If it finds a match, it prints it and
 * begins cracking for the next hash*/
/*	cout << "3 layer brute force" << endl;
	for(int x = 0; x < 28; x++)
	{
		cracked = false;
		for(int msb = 33; msb < 127; msb++)
		{
			start[2] = (char)(msb);
			for(int mid = 33; mid < 127; mid++)
			{
				start[1] = (char)(mid);
				for(int lsb = 33; lsb < 127; lsb++)
				{
					start[0] = (char)(lsb);
					if(hash(start) == hashes[x])
					{
						cout << hashes[x] << " : " << start << endl;
						cracked = true;
						break;
					}
					if(cracked)
						break;
				}
				if(cracked)
					break;
			}
			if(cracked)
				break;
		}
		cout << "Failed" << endl;
	}*/


	string start = "0000";
	//string reset = start;
//	string pass = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"
//	int position = 0;
	while(true)
	{
		time_t now = time(0);
		char* dt = ctime(&now);
		cout << "Starting alphanumeric brute force of " << start.length() << " characters" << " " << dt;
		for(int x = 0; x < 13; x++)
		{
			for(int y = 0; y < start.length(); y++)
			{
				start[y] = '0';
			}
//		position = 0;
			while(start[start.length()-1] != '{')
			{	
				if(hash(start) == hashes[x])
				{
					now = time(0);
                			dt = ctime(&now);
					cout << hashes[x] << " : " << start << " : " << dt  << endl;
					break;
				}
	//			position++;
				start[0]++;	
	//			cout << start << endl;
				
				for(int xx = 0; xx < start.length()-1; xx++)
				{
					if(start[xx] == '9')
					{
					//	position = 0;
						start[xx] = 'A';
						//start[xx+1]++; 
					}
					else if(start[xx] == 'Z')
					{
						start[xx] = 'a';
					}
					else if(start[xx] == 'z')
					{
						start[xx] = '0';
						start[xx+1]++;
					}
				}
			}
		}
		start.push_back('0');
	}
	

/*		vector<string> words;	
		string line, crack;
		ifstream myFile;
		myFile.open("dictionary.txt");
		
		if(myFile.is_open())
		{
			while(getline (myFile,line))
			{
				words.push_back(line);
			}
		myFile.close();
		}
		//cout << "Orig size: " << words[52].length() << endl;
		for(int x = 0; x < words.size(); x++)
		{
			//words[x][words[x].length()-1] = NULL;// << " PLS" << endl;
			//cout << words[x] << " PLS" << endl;
		}
		cout << "New(?) size: " << words[52].length() << endl;
		for(int xx = 0; xx < words.size(); xx++)
		{
			crack = words[xx];
			for(int x = 0; x < 28; x++)
			{	//cout << words[xx] << " " << "PLS" << endl;
				if(hash(words[xx]) == hashes[x])
				cout << hashes[x] << " : " << words[xx] << endl;
			}
		}*/

		for(int x = 0; x < 13; x++)
		{	
			if(hash("vanquish") == hashes[x])
				cout << hashes[x] << " : " << endl;
		}
}
