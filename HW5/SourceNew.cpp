/*
CURRENT TOTALS:
	BUIDs: 60257
	Unique English words: 	
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

vector<int> data;
string palindrome;
void twoA();
void twoB();
void twoC();
void three();

int main()
{
	data.push_back(0);
	data.push_back(0);
	data.push_back(0);

	string selection;
	while (true)
	{
		cout << "Please select a function to run [a,b,c,3], s for status, or q to quit" << endl;
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

	ifstream dataFeed("BigData.txt");
	while (dataFeed)
	{
		dataFeed >> inWord;
		if (inWord[0] == 'U' && inWord.length() < 11)
		{
			if (isdigit(inWord[1]) && isdigit(inWord[2]) && isdigit(inWord[3]) && isdigit(inWord[4]) && isdigit(inWord[5]) && isdigit(inWord[6]) && isdigit(inWord[7]) && isdigit(inWord[8]) && !isdigit(inWord[9]))
			{
				sum = 0;
				for (int x = 1; x < 9; x++)
				{
					sum += inWord[x] - '0';
				}
				
				if (sum > 26)
				{
				//	cout << inWord << endl;
					count++;
				}
			}

		}
	}

	data[0] = count;
	cout << "There exists " << count << " BU IDs up in hurr" << endl;
}

void twoB()
{
	vector< vector<string> > words;
	vector<string> capWords;
	string bigData, line, substrs;
	int count = 0;
	int max, min, binaryCut, wordsLen, capWordsLen;
	ifstream myFile;
	bool hasCaps = false;
	bool notAlpha = false;
	bool hasCapsDos = false;	
	//Opens the stream

	for(int x = 0; x < 26; x++)
	{
		vector<string> what;
		words.push_back(what);
	}
	
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
				{				
					(words[line[0]-'a']).push_back(line);
				}			
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
//	ifstream dataFeed("BigData.txt");
//	if(dataFeed.is_open())
//	{
	//	while(dataFeed)
	//	{
			//Read in space delimited strings
//			dataFeed >> bigData;
			//bigData = "bana%na!shello";
			//'Scrolling window' technique on each string, find all the substrings of the string
			cout << "bananashello" << endl;
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
								if(substrs == words[substrs[0]-'a'][binaryCut])
								{
									cout << "Found: " << substrs << endl;
									count++;
									break;
								}
								else if(substrs < words[substrs[0]-'a'][binaryCut])
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
				//cout << count << endl;
				windowSize++;		
			}				
//		}	
//	}
	now = time(0);
	dt = ctime(&now);
	cout << count << " " << "words found" << dt<< endl;
}

void twoC()
{
	/*string bigData, line, palCheck, biggestPal;
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

	//"Scrolling window" technique to get substrings
	//If a current largest palindrome is found at n, and the code cannot find another at n+2, there is no larger palindrome
	while(palSize <= lenData && palSize - largest < 3)
	{
		cout << "Current window size: " << palSize << endl;
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
					cout << "Biggest palindrome so far: " << biggestPal << " with size of: " << largest << endl;
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
	cout << "Biggest palindrome found: " << biggestPal << " with size: " << biggestPal.size(); << endl;*/
}

void three()
{/*
	vector<string> words, foundPals;
	string line, pal,wordMaker, temp, revCheck;
	string alphaSeen = "";
	ifstream myFile;
	bool hasTwenty, matches, seen, reversable;
	int alphaCount;
	string alphaLow = "qwertyuiopasdfghjklzxcvbnm";
	string alphaUp = "QWERTYUIOPASDFGHJKLZXCVBNM";
	int alphaSize = alphaLow.length();

	myFile.open("dictionary.txt");

	if(myFile.is_open())
	{
		while(getline (myFile,line))
		{
			words.push_back(line);
		}
 		
 		myFile.close();
	}

	for(int x = 0; x < words.size(); x++)
	{
		//Finds a word thats is at least 3 characters long
		if(words[x].length() > 2)
		{
			wordMaker = words[x];
			cout << "Word: " << words[x] << endl;
			hasTwenty = false;

			//Loop until it has twenty letters contained within
			while(!hasTwenty)
			{
				//Loop to check for additional words
				for(int y = 0; y < words.size(); y++)
				{
					//cout << "Check word: " << words[y] << endl;
					//cout << wordMaker[wordMaker.length()-1] << " " << words[y] << endl;
					matches = false;
					//cout << "words[y]: " << words[y] << endl;
					temp = words[y];
					//cout << temp << endl;
					
					//If end matches beginning
					if(wordMaker[wordMaker.length()-1] == words[y][0])
					{	
						//Append to temp string
						cout << "Words[y]: " << temp << endl;
						wordMaker+= temp;
						//cout << "Words[y]: " << temp << endl;
						//cout << wordMaker << " WHY IS " << words[y] << " THE SAME AS " << words[y][0] << "???" << endl;
						matches = true;

						//Reverse newly formed word	
						/*for(int z = temp.length()-1; z >= 0; z--)
						{
							revCheck+= pal[z];
						} 
						
						//If it is a palindrome (kissing in this case)
						if(temp == revCheck)
						{
							pal += temp;
							break;
						}
						
						//Checking for unique letters from alphabet
						alphaCount = 0;
						alphaSee104
n = "";
						for(int wordIT = 0; wordIT < wordMaker.length(); wordIT++)
						{
							for(int alphaIT = 0; alphaIT < alphaSize; alphaIT++)
							{
								if(wordMaker[wordIT] == alphaLow[alphaIT] || wordMaker[wordIT] == alphaUp[alphaIT])
								{
									seen = false;
									for(int saw = 0; saw < alphaSeen.length(); saw++)
									{
											if(alphaSeen[saw] == wordMaker[wordIT])
												seen = true;
									}
									
									if(!seen)
									{
										alphaCount++;
										alphaSeen += wordMaker[wordIT];
										break;
									}
								}
							}
						}
						
						if(alphaCount >= 20)
						{
							hasTwenty = true;
							foundPals.push_back(wordMaker);
							cout << wordMaker << endl;
							break;
						}
					}
					
					if(matches)
						break;
				}
			}
		}
	}*/
}
