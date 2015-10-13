#include <iostream>
#include "bigNum.h"
#include <string>
#include <climits>

using namespace std;

//Declaring the factorial function
void fact(int); 

int main()
{
	//Calculating required factorials
	fact(8);
	fact(13);
	fact(50);

	//Unit testing all factorials from 0 until 50, checked against Wolfram Alpha
	for(int x = 0; x <= 50; x++)
	{
		fact(x);
	}	

	return 0;
}

/*The fact function takes in an int and converts it to a bigNum
 * for calculations
 */
void fact(int numNormal)
{
	bigNum num(to_string((long long int)numNormal));
	
	/*The loop uses the number to iterate as many times as needed*/
	for(int x = numNormal - 1; x > 1; x--)
	{
		//Every pass, the bigNum is multiplied by bigNum-1 until x = 1
		num = num*x;
	}

	//Returns the "factorialzed" number
	cout << numNormal << "!: " << num.print() << endl;
}
