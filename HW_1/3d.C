#include <iostream>
#include "bigNum.h"
#include <string>
#include <chrono>
#include <cmath>
#include <climits>
#include <vector>
using namespace std;

bigNum unknown(bigNum);

//Class to track values a and b when the lowest sum is found
class variableTracker
{
	public:
		int coef; //Keeps track of a value of lowest sum
		double expo; //Keeps track of b value of lowest sum
		variableTracker()
		{
			coef = 0;
			expo = 0;
		}
};

int main()
{	
	//Creates variableTracker object and initializes values.
	variableTracker tracking;
	
	unsigned int timeTaken; //Variable used to keep track of T(n) for 10 <= n <= 10000
	double currDiffSum = 0; //Variable used to keep track of the sum of (T(n) - T'(n))^2
	double minimizationSum = numeric_limits<double>::max(); //Makes the newest low sum max to start with
	
	vector <unsigned int> runtime; //Creates a vector with T(n-10) because n = 10 is at element 0
	
	//Loop to calculate T(n)
	for(int x = 10; x < 10001; x++)
        {
		bigNum num(to_string((long long int)(x))); //Creates bigNum with 10 <= x <= 10001
                auto begin = chrono::high_resolution_clock::now(); //Gets localtime before running
                unknown(num); //Runs unknown(n)
                auto end = chrono::high_resolution_clock::now(); //Gets localtime after running
                timeTaken =  chrono::duration_cast<chrono::nanoseconds>(end-begin).count()/100; //Gets length of time of unknown(n) (end-begin)
                runtime.push_back(timeTaken); //Adds the time into an array
		//Quality assurance, making sure eng-grid hasn't died
		cout << x << endl;
	}
	//Calculates the size of the vector to be used later
	int runTimeSize = runtime.size();
	
	//Outermost loop checks for a values
	for(int a = 1; a < 10000; a+=1)
	{
		//Since b ends up converging with higher values of a, if a new lowest sum is not found within 300 iterations,
		//The a will increment with an increasing speed to save time
	/*	if(a - tracking.coef > 300)
		{
			a+=(a-tracking.coef);
		}
	*/	
		//Checks for b values
		for(double b = .01; b < .99; b+= .01)
		{
			//Since b converges, we don't need to check higher values of b once it stabilizes
	/*		if(b > tracking.expo && a > 10)
			{
				break;
			}
	*/		
			//Calculates T'(n) and the running sum of (T(n) - T'(n))^2
			for(int n = 0; n < runTimeSize; n++)
			{	
				//If the sum for a particular n is greater than the lowest sum, we know that
				//These values for a and b have already exceeded the bounds (not a good fit)
				if(currDiffSum > minimizationSum)
				{
					currDiffSum = 0; //Reset the sum
					break;
				}
				
				currDiffSum += pow((runtime[n] - a*pow(n+10,b)),2); //Calculates (T(n) - T'(n))^2
				
				//Once the sum from n = 10 to n = 10000 is calculated, check if the
				//current sum is the lowest sum so far
				if(n == runTimeSize-1)
				{
					if(currDiffSum < minimizationSum) //If the current sum is lower than the lowest so far..
					{
						minimizationSum = currDiffSum; //Replace the lowest sum with the new lowest
						tracking.coef = a; //Take note of the value of a
						tracking.expo = b; //Take note of the value of b
						cout << "Most accurate pair so far: " << "a: " << tracking.coef << " b: " << tracking.expo << endl;
					}
					currDiffSum = 0; //Reset the sum
				}
			}
		}
	}
	cout << "Most accurate values found: " << "a: " << tracking.coef << " b: " << tracking.expo << endl;
return 0;
}
