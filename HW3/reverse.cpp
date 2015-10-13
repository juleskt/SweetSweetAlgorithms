#include <iostream>

using namespace std;

int main()
{
	int array[11] = {10,9,8,7,6,5,4,3,2,1,0};
	
	for(int x = 0; x < 11/2; x++)
	{
		int temp;
		temp = array[11-1-x];
		array[11-1-x] = array[x];
		array[x] = temp;	
	}

	for(int x = 0; x < 11; x++)
	{
		cout << array[x] << " ";
	}
	return 0;
}
