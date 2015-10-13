#include <string>
#include <iostream>
#include <cctype>
using namespace std;
int main()
{
	string hello;
	while(true)	
	{
		cout << "GIVE ME YOUR FUCKING STRING" << endl;
		cin >> hello;

		string alpha = "qwertyuiopasdfghjklzxcvbnm";

		for(int x = 0; x  < hello.length(); x++)
		{
			for(int y = 0; y < alpha.length(); y++)
			{
				if(alpha[y] == hello[x])
				{
					alpha.erase(y,1);
				}
			}
		}
		cout << "You need " << alpha.size() << " more letters: " << alpha << endl;

	}
}
