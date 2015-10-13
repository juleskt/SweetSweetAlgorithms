#ifndef MYBLOOMFILTER_H
#define MYBLOOMFILTER_H
#include "BloomFilter.h"

class myBloomFilter : public BloomFilter
{
	public:
		myBloomFilter(int mm);
		myBloomFilter(string filter);
		void insert(string item);
		bool exists(string item);
		string output();
		int djb2(string item);
	protected:
		int length;
		string filter;

};

#endif
