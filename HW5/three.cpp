#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

void three();

int main()
{

	three();
	return 0;
}

void three()
{
	string line, revWord;
	string alphaSet = "qwertyuiopasdfghjklzxcvbnm";
	ifstream myFile;
	vector<string> selfPal, twoPal, words, kPals;
	vector<int> matchSet, selfSet;
	int lenDict, lenWord, binaryCut, max, min, set;
	bool hasCaps;

	myFile.open("dictionary.txt");
	if(myFile.is_open())
	{
		while(getline (myFile,line))
		{
			hasCaps = false;
			for(int x = 0; x < line.length(); x++)
			{
				//If it has an uppercase, discard it.
				if(isupper(line[x]))
				{
					hasCaps = true;				
					break;
				}			
			}	
			//If it is all lowercase, add it	
			if(!hasCaps)	
				words.push_back(line);	
		}
 		myFile.close();
	}

	lenDict = words.size();

	//Loop through dictionary
	for(int x = 0; x < lenDict; x++)
	{
		lenWord = words[x].size();
		//If the word is at least 3 characters		
		if(lenWord > 2)
		{
			//Reverse the word
			for(int y = lenWord-1; y >= 0; y--)
			{
				revWord.push_back(words[x][y]);
			}
			//Checks if it is a palindrome if it is, put it in the array
			if(words[x] == revWord)
			{
				selfPal.push_back(words[x]);
			}
			//If the word is not a self-palindrome, binary search for its palindrome in the dictionary
			else
			{
				max = lenDict-1;
				min = 0;
				binaryCut = min + ((max-min)/2);
				while(max >= min)
				{
					binaryCut = min + ((max-min)/2);
					//cout << revWord << " : " << words[binaryCut] << endl;
					if(revWord == words[binaryCut])
					{
						twoPal.push_back(revWord);
						//cout << "Found: " << revWord << endl;
						break;
					}
					else if(revWord < words[binaryCut])
					{
						max = binaryCut-1;
					}
					else if (revWord > words[binaryCut])
					{
						min = binaryCut+1;
					}
				}
			}
		}
		revWord.clear();
	}

	//Gets the number of unique letters in the word and adds to vector
	for(int x = 0; x < twoPal.size(); x++)
	{
		alphaSet = "qwertyuiopasdfghjklzxcvbnm";
		set = 0;
		for(int y = 0; y  < twoPal[x].length(); y++)
		{
			for(int z = 0; z < alphaSet.length(); z++)
			{
				if(alphaSet[z] == twoPal[x][y])
				{
					set++;
					alphaSet.erase(z,1);
				}
			}
		}
		matchSet.push_back(set);
	}
	
	//Does the same as above but with self palindromes
	for(int x = 0; x < selfPal.size(); x++)
	{
		alphaSet = "qwertyuiopasdfghjklzxcvbnm";
		set = 0;
		for(int y = 0; y  < selfPal[x].length(); y++)
		{
			for(int z = 0; z < alphaSet.length(); z++)
			{
				if(alphaSet[z] == selfPal[x][y])
				{
					set++;
					alphaSet.erase(z,1);
				}
			}
		}
		selfSet.push_back(set);
	}

	int largest = 0;

	//Getting largest number of unique letters
	for(int x = 0; x < matchSet.size(); x ++)
	{
		if(matchSet[x] > largest)
		{
			largest = matchSet[x];
		}
	}
	
	//Adds them in to begin chain
	for(int x = 0; x < matchSet.size(); x++)
	{
		if(matchSet[x] == largest)
		{
			kPals.push_back(twoPal[x]); 
		//	cout << twoPal[x] << endl;
		}
	}

//*********************************HORRIFIC PALINDROME BUILDER*******************************************
	 for(int x = 0; x < kPals.size(); x++)
        {
                //Declares a set to check against
                alphaSet = "qwertyuiopasdfghjklzxcvbnm";
                
                //Grabs the first in the vector of beginning of chains to see how many are unique
                for(int y = 0; y < kPals[x].length(); y++)
                {
                        for(int z = 0; z < alphaSet.length(); z++)
                        {
                                if(alphaSet[z] == kPals[x][y])
                                {
                                        alphaSet.erase(z,1);
                                }
                        }
                }
                bool stuck = false;
                
                //Loop until the requirements are met
                while(alphaSet.size() > 6)
                {
                        int sizeCheck = alphaSet.length();
                        int total;
                        int largestTotal = 0;
                        vector<int> indices;
                        vector<int> better;
                        
                        //Loops through the reflecting words
                        for(int y = 0; y < twoPal.size(); y++)
                        {
                                //Keep track of best
                                total = 0;
                                //If first character = to the last character of last in chain
                                if(kPals[x][kPals[x].length()-1] == twoPal[y][0])
                                {
                                        //Check how many unique entries there will be from the word
                                        for(int z = 0; z < twoPal[y].length(); z++)
                                        {
                                                for(int zz = 0; zz < alphaSet.length(); zz++)
                                                {
                                                        if(alphaSet[zz] == twoPal[y][z])
                                                        {
                                                                //Track the uniqueness
                                                                total++;
                                                        }				
                                                }								
                                        }
                                        
                                        //If it is a never-before seen uniqueness, add it to indices
                                        if(total > largestTotal)
                                        {
                                                largestTotal = total;
                                                indices.push_back(y);
                                        }						
                                }
                        }
                        
                        //Same as above but with self palindromes
                        for(int y = 0; y < selfPal.size(); y++)
                        {
                                total = 0;
                                if(kPals[x][kPals[x].length()-1] == selfPal[y][0])
                                {
                                        for(int z = 0; z < selfPal[y].length(); z++)
                                        {
                                                for(int zz = 0; zz < alphaSet.length(); zz++)
                                                {
                                                        if(alphaSet[zz] == selfPal[y][z])
                                                        {
                                                                total++;
                                                        }				
                                                }								
                                        }
                                        
                                        //If these ones are MORE unique, add to better vector
                                        if(total > largestTotal)
                                        {
                                                largestTotal = total;
                                                better.push_back(y);
                                        }						
                                }
                        }
                        
                        //If the indices are empty, the chains are stuck, leave
                        if(indices.size() == 0 && better.size() == 0)
                        {
                                stuck = true;
                                break;
                        }			
                        
                        //If self palindromes have failed us, attach the best reflecting word
                        if(better.size() == 0)
                        {
                                kPals[x] += " ";
                                kPals[x] += twoPal[indices[indices.size()-1]];
                        }
                        //Otherwise attach the best self-palindrome
                        else
                        {
                                kPals[x] += " ";
                                kPals[x] += selfPal[better[better.size()-1]];
                        }
                        //Update the set
                        for(int y = 0; y < kPals[x].length(); y++)
                        { 
                                for(int z = 0; z < alphaSet.length(); z++)
                                {
                                        if(alphaSet[z] == kPals[x][y])
                                        {
                                                alphaSet.erase(z,1);
                                        }
                                }
                        }		
                        
                        //If the size of the set has not changed from the beginning, the chain is stuck
                        if(alphaSet.length() == sizeCheck)
                        {
                                stuck = true;			
                                break;		
                        }
                }	
                
                //If the chain is real, display contents
                if(!stuck)
                {
                        int count = 0;
                        for(int y = 0; y < kPals[x].length(); y++)
                        {
                                if(isalpha(kPals[x][y]))
                                count++;
                        }	
                        
                        string rev;		
                        for(int y = kPals[x].length() - 1; y >= 0; y--)
                        {
                                rev += kPals[x][y];
                        }
                        
                        cout << "Size: " << count*2 << endl;
                        cout << kPals[x] << " " << rev << endl;	
                }	
        }
}
