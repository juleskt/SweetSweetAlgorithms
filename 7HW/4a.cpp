#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	string quote,build;
	vector <string> quoteSubs;
	char parts;
	
	ifstream myFile("quote.txt");
	
	//Streams the text
	while(getline(myFile,quote))
	{	
		//Loop through the entire quote and break it up into appropriate substrings
		for(int x = 0; x < quote.length(); x++)
		{
			//Every substring starts with a [
			if(quote[x] == '[')
			{
				quoteSubs.push_back(quote.substr(x+1,5));
				x+=6;
			}	
		}
	}	
	myFile.close();	

	//We begin building the quote with the first substring and erasing it
	build = quoteSubs[0];
	quoteSubs.erase(quoteSubs.begin());
	
	//Loop until we have included every substring
	while(quoteSubs.size() != 0)
	{
		//Loop through each remaining substring
		for(int y = 0; y < quoteSubs.size(); y++)
		{
			//Builds a temp string of first and last substrings of size 4 from the constructed quote
			for(int z = 0; z <= 1; z++)
			{
				string temp;
				if(z == 0)
					temp = build.substr(z,4);
				else
					temp = build.substr(build.length()-4,4);
				
				//Gets both substrings of size 4 from the quote
				for(int zz = 0; zz < 2; zz++)
				{
					//If the substrings match
					if(temp == quoteSubs[y].substr(zz,4))
					{
						//If the match is at the end of the quote, append the new piece to the end of the quote
						if(z == 1 && zz == 0)
						{
								build+=quoteSubs[y][4];
								quoteSubs.erase(quoteSubs.begin()+y);
						}						
						//If the match is at the beginning, prepend the new piece
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
	return 0;
}