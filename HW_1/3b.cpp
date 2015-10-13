/*

Referenced Time libraries discovered here: 

http://stackoverflow.com/questions/12937963/get-local-time-in-nanoseconds

Documentation:

http://www.cplusplus.com/reference/chrono/

NOTE: Requires -std=c++0x argument while compiling into object code
*/

#include <iostream>
#include <ctime>
#include "bigNum.h"
#include <sstream>
#include <sys/time.h>
#include <chrono>

using namespace std;

bigNum unknown(bigNum);

int main()
{
	for(int x = 10; x < 10001; x++)
	{
	//	stringstream ss; //Creates string stream (located INSIDE the loop to avoid overloading the buffer)
	//	ss << x; //Streams x, or n in T(n) into the stream
	//	string str = ss.str(); //Takes the "value" held by stringstream into a string called str)
		bigNum num(to_string((long long int)(x))); //Creates a bigNum with the value of x or n in the correct string format
		
		auto begin = chrono::high_resolution_clock::now(); //Gets localtime before running
		unknown(num); //Runs unknown(n)
		auto end = chrono::high_resolution_clock::now(); //Gets localtime after running
	
		cout << chrono::duration_cast<chrono::nanoseconds>(end-begin).count()/100 << endl;  
	}
return 0;
}
