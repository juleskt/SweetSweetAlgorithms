#ifndef bigNUM
#define bigNUM

// Written by Prof. Ari Trachtenberg for EC330
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class bigNum {
  // a class to represent arbitrarily large positive numbers
        
public:
  bigNum(string num="");
  /* %R: num contains only characters 0-9 and represents a positive integer > 0
  **     (zero is used internally, but not supported publicly)
  ** %E: constructs a bigNum containing the integer num in base 10
  */
        
  bigNum& operator=(const bigNum& otherNum);
  /* %R: otherNum is an initialized bigNum
  ** %E: makes this number be a copy of otherNum
  */
        
  bigNum& operator+(bigNum& addend);
  /* %R: otherNum is an initialized bigNum
  ** %E: returns the sum of this number and addend
  */
        
  bigNum& operator*(int cc);
  /* %R: cc>0
  ** %E: returns the product of this number and cc
  */
        
  bigNum& operator*(bigNum& multiplicand);
  /* %R: otherNum is an initialized bigNum
  ** %E: returns the product of this number and multiplicand
  */

  bigNum& operator/(bigNum& divisor);
  /* %R: otherNum is an initialized bigNum
  ** %E: returns the division of this number by divisor
  */
        
  bool operator==(bigNum& otherNum);
  /* %R: otherNum is an initialized bigNum
  ** %E: returns true iff this bigNum is exactly equal to otherNum
  */

  bool operator<=(const bigNum& otherNum);
  /* %R: otherNum is an initialized bigNum
  ** %E: returns true iff this number is <= other number
  */
    
  string print();
  /* %E: returns a human-readable string version this number
   */
        
protected:
   vector<int> digits; // stores the digits of the current number
  
private:
  const static int base=10;        // the base of the number
  void operator<<(int cc);
  /* %R: cc>=0
  ** %E: multiplies the current number by 10^cc
  */
};
#endif