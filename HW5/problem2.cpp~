#include <iostream>
#include <string>
#include <cctype>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

void twoA();
void twoB();
void twoC();

int main()
{
	twoA();
	twoB();
	twoC();
	return 0;
}

void twoA()
{
	string inWord;
        int sum;
        int count = 0;
        bool nonNum = false;

	time_t now = time(0);
	char* dt = ctime(&now);
        
	cout << "Searching for BU IDs... " << dt << endl;
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
	now = time(0);
	dt = ctime(&now);
        cout << "There are " << count << " BU IDs whose sum is > 26" << endl;
	cout << dt << endl;
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
			dataFeed >> bigData;

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
						//If there is an non alphabetic char, ignore it
						if(!isalpha(substrs[y]))
						{
							notAlpha = true;
							break;
						}
						//If there is an uppercase letter, flag it
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
									//cout << "Found: " << substrs << endl;
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
	cout << count << " " << "words found " << dt<< endl;
}

void twoC()
{
	string bigData, line, palCheck, biggestPal;
        char dataChar;
        int palSize = 2;
        int largest = 0;
        bool found;
        int posStart, posEnd, checkLen, lenData;
        
        //Open the stream and read everything into a string
        ifstream dataFeed("BigData.txt");
        getline(dataFeed,bigData);
        
        //Calculates length now to avoid recalculation later
        lenData = bigData.length();

	time_t now = time(0);
	char* dt = ctime(&now);

	cout << "Searching for largest palindrome... " << dt << endl;
        
        //"Scrolling window" technique to get substrings
        //If a current largest palindrome is found at n, and the code cannot find another at n+2, there is no larger palindrome
        while(palSize <= lenData && palSize - largest < 3)
        {
                //Scrolling through bigData with windows
                for(int x = 0; x < lenData-palSize; x++)
                {
                        //Create a substring based on the window size
                        palCheck = bigData.substr(x,palSize);
                        found = false;
                        checkLen = 0;
                        
                        //Check if it is a palindrome
                        for(int y = 0; y < palCheck.length()/2; y++)
                        {
                                //While the front and end iterators match
                                if(palCheck[y] == palCheck[palCheck.length()-y-1])
                                {
                                        checkLen++;
                                }
                                //As soon as a mismatch occurs, break (it cannot be a palindrome if it is not a mirror image)
                                else
                              	  break;
                                //If the number of mirror-matches is equal to half the length, then it is a palindrome
                                if(checkLen == palCheck.length()/2)
                                {
                                        //Set it to the biggest palindrome so far (windows determine the size)
                                        biggestPal = palCheck;
                                        found = true;
                                        largest = biggestPal.length();
                                        //Break because there is no point in checking with the same window size					
                                        break;
                                }
                        }
                        //Leave the loop to get a bigger window
                        if(found)
                        break;
                }
                //Expand the window
                palSize++;
        }

	now = time(0);
	dt = ctime(&now);

        cout << "Biggest palindrome found: " << biggestPal << " with size: " << biggestPal.size() << endl;
	cout << dt << endl;
}

