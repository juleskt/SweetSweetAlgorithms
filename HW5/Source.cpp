/*
CURRENT TOTALS:
	BUIDs: 60257
	Unique English words: 443220102 with space delimited entries
	Longest Palindrome so far: "  BRpmpRB  ", size 11
	Longest Palindrome if read-in space delimited: A00CkC00A, size 9
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <ctime>
using namespace std;

vector<int> data;
string palindrome;
void twoA();
void twoB();
void twoC();
void three();
void twoCWords();

int main()
{
	data.push_back(0);
	data.push_back(0);
	data.push_back(0);

	string selection;
	while (true)
	{
		cout << "Please select a function to run [a,b,c,3,cw], s for status, or q to quit" << endl;
		cin >> selection;

		if (selection == "A" || selection == "a")
		{
			twoA();
		}
		else if(selection == "B" || selection == "b")
		{
			twoB();
		}
		else if(selection == "C" || selection == "c")
		{
			twoC();
		}
		else if (selection == "3")
		{
			three();
		}
		else if(selection == "CW" || selection == "cw")
		{
			twoCWords();
		}
		else if (selection == "S" || "s")
		{
			for (int x = 0; x < 3; x++)
			{
				if (x == 0)
				{
					cout << "Number of eligible BU IDs in BigData.txt is: " << data[0] << endl;
				}
				else if (x == 1)
				{
					cout << "Number of english words that do not end with t in BigData.txt is: " << data[1] << endl;
				}
				else if (x == 2)
				{
					cout << "Biggest palindrome in BigData.txt is: " << palindrome << " with size of: " << data[2] << endl;
				}
			}
		}
		else if (selection == "Q" || selection == "q")
		{
			break;
		}
		cout << endl;
	}
	return 0;
}

void twoA()
{
	string inWord;
	int sum;
	int count = 0;
	bool nonNum = false;

	//Opens the file stream
	ifstream dataFeed("BigData.txt");
	while (dataFeed)
	{
		//Feed space delimited strings into inWord
		dataFeed >> inWord;

		//Loop through the string to check for U
		for(int x = 0; x < inWord.size(); x++)
		{
			//Found a U
			if(inWord[x] == 'U')
			{
				//Set sum and flags to 0
				sum = 0;		
				nonNum = false;
				//Check the next 8 elements to check if they are digits
				for(int y = x+1; y < x+9; y++)
				{
					//If one of the next 8 are not digits, break and move x (because we already checked across y)
					if(!isdigit(inWord[y]))
					{
						x = y;
						nonNum = true;
						break;
					}
					//if they are digits, find the running sum
					sum+= inWord[y] - '0';
				}
				
				//If all 8 were digits, go into the final check
				if(!nonNum)
				{
					//Makes sure the 9th element is a non-digit
					if(isdigit(inWord[x+9]))
					{
						break;
					}
										
					//If the sum of the ID meets criteria, increment the count
					if (sum > 26)
					{
						count++;
					}			
					
					//Since everything across 9 was checked, jump the x iterator by 9
					if(x+9 < inWord.size())
						x+=9;
				}			
			}
		}
	}
	cout << "There exists " << count << " BU IDs up in hurr" << endl;
}

void twoB()
{
	vector<string> words, capWords;
	string bigData, line, substrs;
	int count = 0;
	int max, min, binaryCut, wordsLen, capWordsLen;
	ifstream myFile;
	bool hasCaps = false;
	bool notAlpha = false;
	bool hasCapsDos = false;	
	//Opens the stream
	myFile.open("dictionary.txt");
	
	cout << "Reading in dictionary..." << endl;

	if (myFile.is_open())
	{
		while (getline(myFile, line))
		{
			//Removes all words that end in h
			if(line[line.length()-1] != 'h' && line[line.length()-1] != 'H')
			{
				hasCaps = false;
				for(int x = 0; x < line.length(); x++)
				{
					//Checks for capital letters, as it messes with the binary search
					if(isupper(line[x]))
					{
						hasCaps = true;				
						break;
					}			
				}
				//Throws the word into a separate vector if it has caps		
				if(!hasCaps)	
					words.push_back(line);
				else
					capWords.push_back(line);
							
			}		
		}
		myFile.close();
	}

	cout << "Finished reading!" << endl;

	//Declaring sizes now to avoid recalculation	
	wordsLen = words.size();
	capWordsLen = capWords.size();
	
	time_t now = time(0);
	char* dt = ctime(&now);
	cout << "Scanning bigData.txt... " <<  dt << endl;

	//Open the stream
	ifstream dataFeed("BigData.txt");
	if(dataFeed.is_open())
	{
		while(dataFeed)
		{
			//Read in space delimited strings
			//'Scrolling window' technique on each string, find all the substrings of the string
			int windowSize = 1;
			//Loop while the window is less than or equal to the length of the string
			while(windowSize <= bigData.length())
			{
				//Scrolling through with the current window
				for(int x = 0; x <= bigData.length()-windowSize; x++)
				{
					substrs = bigData.substr(x,windowSize);
					notAlpha = false;
					hasCapsDos = false;
					
					//checking for non-letters and caps
					for(int y = 0; y < substrs.length(); y++)					
					{
						if(!isalpha(substrs[y]))
						{
							notAlpha = true;
							break;
						}
						if(isupper(substrs[y]))
							hasCapsDos = true;					
					}
						
					//Only search if the substring is strictly alphabetic characters 					
					if(!notAlpha)
					{
						//If it is all lowercase
						if(!hasCapsDos)
						{							
							//Binary search the lowercase vector				
							max = wordsLen-1;
							min = 0;
							binaryCut = min + ((max-min)/2);
							while(max >= min)
							{
								binaryCut = min + ((max-min)/2);			
								if(substrs == words[binaryCut])
								{
									cout << "Found: " << substrs << endl;
									count++;
									break;
								}
								else if(substrs < words[binaryCut])
								{
									max = binaryCut-1;
								}
								else 
								{
									min = binaryCut+1;
								}
							}
						}
						//If it contains any caps, and the first character is capital
						else if(hasCapsDos && isupper(substrs[0]))
						{						
							//Binary search the uppercase vector
							max = capWordsLen-1;
							min = 0;
							binaryCut = min + ((max-min)/2);
							while(max >= min)
							{
								binaryCut = min + ((max-min)/2);				
								if(substrs == capWords[binaryCut])
								{
									count++;
									break;
								}
								else if(substrs < capWords[binaryCut])
								{
									max = binaryCut-1;
								}
								else 
								{
									min = binaryCut+1;
								}
							}
						}				
					}				
				}	
				//Increment the window size	
				windowSize++;		
				//cout << count << endl;
			}				
		}	
	}
	now = time(0);
	dt = ctime(&now);
	cout << count << " " << "words found" << dt<< endl;
}

void twoC()
{
	string bigData, line, palCheck, biggestPal,bigDataRev;
	vector<string> palindromes;
	char dataChar;
	int palSize = 2;
	bool found;
	int posStart, posEnd, numMatch, lenData, checkLen, yIT;
	int largest = 0;

/*	cout << "Reading in bigData..." << endl;
	ifstream dataFeed("BigData.txt");
	if(dataFeed.is_open())
	{
		while(dataFeed)
		{
			//Read in everything!
			dataFeed >> dataChar;
			bigData.push_back(dataChar);
		}
		dataFeed.close();
	}*/
	
	bigData = "omfgbananasyo";

	lenData = bigData.length();
	cout << "Finished reading!" << endl;
	cout << lenData << endl;

	for(int x = lenData-1; x >= 0; x--)
	{
		bigDataRev.push_back(bigData[x]);
	} 

	cout << bigDataRev.length() << endl;

	for(int x = 0; x < lenData; x++)
	{
		for(int y = 0; y < lenData; y++)
		{			
			//Find first letter of word
			if(bigDataRev[y] == bigData[x])
			{
				numMatch = 1;
				yIT = 1+y;

				//Iterate to see if its the full word
				for(int IT = x+1; IT < lenData; IT++)
				{
					if(bigData[IT] == bigDataRev[yIT])
					{
						numMatch++;
						yIT++;
						//cout << bigData[IT] << " : " << bigDataRev[yIT] << endl;
					}
					else 
					{			
						break;
					}
				} 		
			}
		}	
		if(numMatch > largest)
		{
			largest = numMatch;	
			cout << bigData.substr(x,numMatch) << " size: " << numMatch << endl;
		}	
	}

             
	cout << "Largest palindrome size: " << largest << endl;//biggestPal.length() << endl;
//	data[2] = biggestPal.length();
//	cout << "Palindrome is: " <<  bigData.substr(58405997,11);
}

void twoCWords()
{
	string inWord, droWni, bigPal;
	int numMatch,largest,yIT;
	numMatch = 0;
	//int count = 0;

	ifstream dataFeed("BigData.txt");
	while (dataFeed)
	{
		dataFeed >> inWord;
		
		//inWord = "bananas";
		
		for(int x = inWord.length() - 1; x >= 0; x--)
		{
			droWni.push_back(inWord[x]); 
		}			

		for(int x = 0; x < inWord.length(); x++)
		{
			for(int y = 0; y < droWni.length(); y++)
			{
				//Find first letter of word
				if(inWord[x] == droWni[y])
				{
					numMatch = 1;
					yIT = y+1;
					for(int IT = x+1; IT < inWord.size(); IT++)
					{
						if(inWord[IT] == droWni[yIT])
						{
							numMatch++;
							yIT++;
						}
						else 
						{			
							break;
						}
					} 
					if(numMatch > largest)
					{
						largest = numMatch;	
						bigPal = inWord.substr(x,numMatch); //cout << inWord.substr(x,numMatch) << " size: " << numMatch << endl;
					}		
				}
			}
		}		
		droWni.clear();	
	}
	cout << "Largest: " << bigPal << " with size of " << largest << endl;
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
