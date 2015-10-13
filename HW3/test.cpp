#include "bigInt.h"
#include "bigIntSort.h"
#include "genericSort.h"
#include <cstdlib>
using namespace std;

int main()
{
	bigInt(1000);
	bigIntSort stuff;	
	
	for(int x = 0; x < 10; x++)
	{
		stuff.insert(new bigInt(x));
	}

	for(int x = 0; x < stuff.numItems(); x++)
	{
		cout << stuff.returnKth(x) << endl;
	}
	
	cout << "For is finished" << endl;
	stuff.performSort();

	for(int x = 0; x < stuff.numItems(); x++)
	{
		cout << stuff.returnKth(x) << endl;
	}
return 0;
}
