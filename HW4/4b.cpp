#include "hash.h"
#include "sha1.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class StringPair
{
public:
	StringPair() {}

	StringPair(string in_a, string in_b)
	{
		A = in_a;
		B = in_b;
	}

	string A;
	string B;
};

int main()
{
	const int NUM_PASSWORDS = 10;
	const int PASSWORD_LENGTH = 5;
	const int TABLE_ROWS = 5871;
	const int MIN = 33;
	const int MAX = 126;

	//hashes to crack
	string passwordHashes[NUM_PASSWORDS] = {
	"dc31170d029df869794a9a8dbe515e873048392f",
"27fad73b6e2c5aa9d4dfe002d3cd6c17cb7f002a",
"05553c640284aaa4cd5cb0c639968ed7b1b71761",
"b75c52169980998ba8ac93da57bd7bcf59390b8b",
"0dfb8c76e6c92480f875453f99f6e51cdee0fb7a",
"8bda99642e781243b1a1b15571797fc98312f22c",
"f779e47788751aff04da3c8100dd47a596ea25cc",
"440f1853f63b2f59e41352340ac2c0cef9cd4ff5",
"6eff35ae47651f8aa6ded0e8359451a222f054fb",
"898b7a869bba59c78a3068cefc254bfdb468fe04"
	

	};
	//array to store final answers
	string passwords[NUM_PASSWORDS];
	StringPair table[TABLE_ROWS];	
	ifstream inFile("table.txt");
	
	int lineNum = 0;
	string line, key, val;
	while(getline(inFile, line))
	{
		key = line.substr(4, PASSWORD_LENGTH);
		val = line.substr(14, PASSWORD_LENGTH);

		table[lineNum] = StringPair(key, val);
		lineNum++;
	}
	
	string reduced, hashed;
	bool found;
	//loop through each password hash
	for(int pass = 0; pass < NUM_PASSWORDS; pass++)
	{
		found = false;
		while(!found)
		{
			//get reduction of password hash
			reduced = reduce(passwordHashes[pass], PASSWORD_LENGTH);
			for(int i = 0; i < TABLE_ROWS; i++)
			{
				//if the password hash reduction gets a match
				if(reduced == table[i].B)
				{
					cout << "End: " << reduced << endl;
					//hash and reduce along that row until found
					reduced = table[i].A;
					while(reduced != table[i].B)
					{
						hashed = hash(reduced);
						if(hashed == passwordHashes[pass])
						{
							passwords[pass] = reduced;
							cout << reduced << endl;
							found = true;
							break;
						}
						reduced = reduce(hashed, PASSWORD_LENGTH);
					}
//					if(found) break;
				}
			}
			passwordHashes[pass] = hash(reduce(passwordHashes[pass], PASSWORD_LENGTH));
		}
	}
	
//	for(int i = 0; i < NUM_PASSWORDS; i++)
//		cout << passwords[i] << endl;

	return 0;
}
