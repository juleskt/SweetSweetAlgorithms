#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

int main()
{
	string quote,build;
	vector <string> quoteSubs;
	char parts;
	
	ifstream myFile("quote.txt");
		
	while(getline(myFile,quote))
	{	
		for(int x = 0; x < quote.length(); x++)
		{
			if(quote[x] == '[')
			{
				quoteSubs.push_back(quote.substr(x+1,5));
				x+=6;
			}	
		}
	}	
	myFile.close();	

	build = quoteSubs[0];
	quoteSubs.erase(quoteSubs.begin());
	
	while(quoteSubs.size() != 0)
	{
		for(int y = 0; y < quoteSubs.size(); y++)
		{
			for(int z = 0; z <= 1; z++)
			{
				string temp;
				if(z == 0)
					temp = build.substr(z,4);
				else
					temp = build.substr(build.length()-4,4);
				
				for(int zz = 0; zz < 2; zz++)
				{
					if(temp == quoteSubs[y].substr(zz,4))
					{
						if(z == 1 && zz == 0)
						{
								build+=quoteSubs[y][4];
								quoteSubs.erase(quoteSubs.begin()+y);
						}						
						else if (z == 0 && zz == 1)
						{
							build.insert(build.begin(),quoteSubs[y][0]);
							quoteSubs.erase(quoteSubs.begin()+y);
						}
						break;
					}
				}
			}
		}
		
	}
	cout << build << endl;
}
