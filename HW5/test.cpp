#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

/*void stringCheck(const char*);
int main()
{
/*	string test = "racecar";
	string temp;

	for(int x = test.length()-1; x>= 0; x--)
	{
		temp+= test[x];
	}

	if(temp == test)
		cout << "This works!" << endl;
	else
		cout << "pls" << endl;
	

	string death = "Hello";
	stringCheck(death.c_str());
	return 0;
}

void stringCheck(const char* charact)
{
	cout << charact << endl;
}*/

	/* Dynamic Programming solution to find length of the longest common substring */
 
// A utility function to find maximum of two integers
/*int max(int a, int b)
{   return (a > b)? a : b; }
 
 Returns length of longest common substring of X[0..m-1] and Y[0..n-1] 
int LCSubStr(string X, string Y, int m, int n)
{
    // Create a table to store lengths of longest common suffixes of
    // substrings.   Notethat LCSuff[i][j] contains length of longest
    // common suffix of X[0..i-1] and Y[0..j-1]. The first row and
    // first column entries have no logical meaning, they are used only
    // for simplicity of program
    int LCSuff[m+1][n+1];
    int result = 0;  // To store length of the longest common substring
 
    /* Following steps build LCSuff[m+1][n+1] in bottom up fashion. 
    for (int i=0; i<=m; i++)
    {
        for (int j=0; j<=n; j++)
        {
            if (i == 0 || j == 0)
                LCSuff[i][j] = 0;
 
            else if (X[i-1] == Y[j-1])
            {
                LCSuff[i][j] = LCSuff[i-1][j-1] + 1;
                result = max(result, LCSuff[i][j]);
            }
            else LCSuff[i][j] = 0;
        }
    }
    return result;
}
 
/* Driver program to test above function */

string preProcess(string s) {
  int n = s.length();
  if (n == 0) return "^$";
  string ret = "^";
  for (int i = 0; i < n; i++)
    ret += "#" + s.substr(i, 1);
 
  ret += "#$";
  return ret;
}
 
string longestPalindrome(string s) {
  string T = preProcess(s);
  int n = T.length();
  int *P = new int[n];
  int C = 0, R = 0;
  for (int i = 1; i < n-1; i++) {
    int i_mirror = 2*C-i; // equals to i' = C - (i-C)
    
    P[i] = (R > i) ? min(R-i, P[i_mirror]) : 0;
    
    // Attempt to expand palindrome centered at i
    while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
      P[i]++;
 
    // If palindrome centered at i expand past R,
    // adjust center based on expanded palindrome.
    if (i + P[i] > R) {
      C = i;
      R = i + P[i];
    }
  }
 
  // Find the maximum element in P.
  int maxLen = 0;
  int centerIndex = 0;
  for (int i = 1; i < n-1; i++) {
    if (P[i] > maxLen) {
      maxLen = P[i];
      centerIndex = i;
    }
  }
  delete[] P;
  
  return s.substr((centerIndex - 1 - maxLen)/2, maxLen);
}

string longPalinString(string s);
int main()
{
	string bigData, line, palCheck, biggestPal,bigDataRev;
	vector<string> palindromes;
	char dataChar;
	int palSize = 2;
	bool found;
	int posStart, posEnd, numMatch, lenData, checkLen, yIT;
	int largest = 0;

	cout << "Reading in bigData..." << endl;
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
	}
	cout << "Done!" << endl;
	cout << "Reversing..." << endl;
	/*for(int x = lenData-1; x >= 0; x--)

	{
		bigDataRev.push_back(bigData[x]);
	} */

	//bigData = "omfgbananasyo";
	cout << "Done!" << endl;

    cout << "Hm..." << endl;

    cout << longPalinString(bigData) << endl;
    //cout << longestPalindrome(preProcess(bigData)) << endl;
 

    return 0;
}
 
string longPalinString(string s)
{
    int n = s.length(), high, low;
    cout << n << endl;
    int start = 0;
 
    int max_length = 1;
 
    for (int i = 1; i < n; i++) {
        high = i;
        low = i - 1;
 
        while (low >= 0 && high < n && s[low] == s[high]) {
            if (high - low + 1 > max_length) {
                max_length = high - low + 1;
                start = low;
            }
 
            high++;
            low--;
        }
 
        high = i + 1;
        low = i - 1;
 
        while (low >= 0 && high < n && s[low] == s[high]) {
            if (high - low + 1 > max_length) {
                max_length = high - low + 1;
                start = low;
            }
 
            high++;
            low--;
        }
    }
 
    return s.substr(start, max_length);   
}

 

