#include "bigIntSort.h"

void bigIntSort::performSort() 
{
	for(int xx = 0; xx < data.size(); xx++)
	{
		for(int yy = xx; yy > 0; yy--)
		{
			if(*data[yy] < *data[yy-1])
			{	
				bigInt *temp = data[yy-1];
				data[yy-1] = data[yy];
				data[yy] = temp;
			}
		}
	}    
}

