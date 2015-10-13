#include "bigNumT.h"

#ifndef BIGNUMTWITHMINUS_H
#define	BIGNUMTWITHMINUS_H

//Declaring a template like bigNumT.h
template <typename STORAGE = vector<int> >

//Inheriting stuff from bigNumT
class bigNumTwithMinus: public bigNumT<STORAGE>
{
	public:
		//Declaring functions and constructors
		bigNumTwithMinus& operator-(bigNumTwithMinus<STORAGE>& subtractor);
		bigNumTwithMinus(string num);
		bigNumTwithMinus();
};

//If a bigNumTwithMinus is declared with a string, pass it into the bigNumT constructor that handles strings
template <typename T>
bigNumTwithMinus<T>::bigNumTwithMinus(string num) : bigNumT<T>(num)
{

}

//If a bigNumTwithMinus is declared without parameters, do the same as a bigNumT with no args
template <typename T>
bigNumTwithMinus<T>::bigNumTwithMinus() : bigNumT<T>()
{

}

//Definition of the function to overload the - operator
template <typename T>
bigNumTwithMinus<T>& bigNumTwithMinus<T>::operator-(bigNumTwithMinus<T>& subtractor)
{
	//Declaring useful ints for keeping track of size
	int topSize;
	int botSize;

	//Declare two bigNumTwithMinus objects to work with
	bigNumTwithMinus<T> top, bot;
	//Declared on the heap because I would get std::bad_alloc otherwise...
	bigNumTwithMinus<T> *result = new bigNumTwithMinus<T>;

	//The reason I do this because the answer is assumed to never be negative
	if(subtractor <= *this)
	{
		top = *this;
		bot = subtractor;
	}

	else
	{
		top = subtractor;
		bot = *this;
	}

	//Size of "top" and "bottom" of subtraction equation
	topSize = top.digits.size();
	botSize = bot.digits.size();

	//If the top has more digits than the bot, pad the bot with 0s to make the number of digits equal
	if(topSize > botSize)
	{
		for(int x = botSize; x < topSize; x++)
		{
			bot.digits.push_back(0);
		}
	}

	//Recalculate the size of the bot number with padded 0s
	botSize = bot.digits.size();

	//Loop to do all the carrying beforehand ;)
	for(int botIT = 0; botIT < botSize; botIT++)
	{
		//If the top digit is < the bot digit
		if(top.digits[botIT] < bot.digits[botIT])
		{
			//Search until we find a top > bot so we can carry
			for(int carryIT = botIT+1; carryIT < botSize; carryIT++)
			{
				//Finding the top > bot
				if(top.digits[carryIT] > bot.digits[carryIT])
				{
					//Do the carry operation as you would on paper
					for(int backwards = carryIT; backwards > botIT; backwards--)
					{
						top.digits[backwards] -= 1;
						top.digits[backwards-1] += 10;
					}
					//Leave the carry loop once this instance of carrying is finished
					break;
				}
			}
		}
	}

	//Does the subtraction after all the carrying
	for(int x = 0; x < botSize; x++)
	{
		result->digits.push_back(top.digits[x] - bot.digits[x]);
	}

	//If top has more digits, throw them into result
	if(topSize > botSize)
	{
		for(int x = botSize; x < topSize; x++)
		{
			result->digits.push_back(top.digits[x]);
		}
	}

	//Removing leading 0s from the answer
	for(int cleanUp = result->digits.size()-1; cleanUp > 0; cleanUp--)
	{
		if(result->digits[cleanUp] != 0)
		{
			break;
		}
		else
		{
			result->digits.pop_back();
		}
	}
	return *result;
}
#endif
