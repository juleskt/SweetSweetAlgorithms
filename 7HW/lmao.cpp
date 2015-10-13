#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int main()
{
	string thing;
	vector <string> result,hax;

	ifstream myFile("result.txt");
	while(getline(myFile,thing))
	{
		result.push_back(thing);
	}
	myFile.close();

	ifstream File("hax.txt");
	while(getline(File,thing))
	{
		hax.push_back(thing);
	}
	File.close();

	for(int x = 0; x < hax.size(); x++)
	{
		for(int y = 0; y < result.size(); y++)
		{
			if(hax[x] == result[y])
				break;
			if(y == result.size()-1 && hax[x] != result[y])
				cout << hax[x] << endl;
		}
	}
}