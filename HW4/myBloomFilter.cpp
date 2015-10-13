#include "myBloomFilter.h"
#include <iostream>

using namespace std;

myBloomFilter::myBloomFilter(int mm) : BloomFilter(mm) 
{
	for(int x = 0; x < mm; x++)
	{
		filter.push_back('0');
	}
	
	length = mm;
}

myBloomFilter::myBloomFilter(string input) : BloomFilter(input) 
{
	length = input.length();
	for(int x = 0; x < length; x++)
	{
		filter.push_back(input[x]);
	}
}

int myBloomFilter::djb2(string item)
{
	unsigned long hash = 5381;
	char c;
	for(int i=0; i<item.size(); i++)
	{
        	c=item[i];
		hash = ((hash << 5) + hash) ^ c; //+  hash * 33 +c;
    	}	
    return hash%length;
}

void myBloomFilter::insert(string item)
{
	filter[djb2(item)] = '1';
} 

bool myBloomFilter::exists(string item)
{
	if(filter[djb2(item)] == '1')
		return true;
	else
		return false;
}

string myBloomFilter::output()
{
	return filter;
}


/*int main()
{
	myBloomFilter lessObscene(15);
	cout << lessObscene.output() << endl;
	lessObscene.insert("clean");
	cout << lessObscene.output() << endl;
	lessObscene.insert("more clean");
	cout << lessObscene.output() << endl;
	if(lessObscene.exists("clean"))
		cout << "Lol woo" << endl;
	myBloomFilter supTrachten(lessObscene.output());
	cout << supTrachten.output() << endl;
	return 0;
}*/
