#ifndef bigNUM
#define bigNUM

#include <iostream>
#include <vector>
using namespace std;

class bigInt {
    /**
     *  A class for representing and manipulating arbitrarily large positive integers.
     */

public:
    // FRIENDS
    friend class bigIntSort;
    
    // CONSTRUCTOR
    /**
     * Constructs a bigInt containing the integer <num>
     * @param num An integer > 0.
     */
    bigInt(int num = 0);

    // INFORMATION
    /**
     * Compares this bigInt to otherNum, returning true iff this
     * bigInt is smaller.
     * @param otherNum is an initialized bigInt
     * @return true iff this bigInt is smaller than otherNum
     */
    bool operator<(bigInt& otherNum);
    
    /**
     * Provides the index-th digit of the number.
     * @param index The index of the digit to return.  Index=0 provides the least significant digit (i.e. the ones place).
     * @return The index-th digit of the number.
     */
    int digit(int index);
    
    /**
     * Print the bigInt to a string.
     * @return a human-readable string version of this bigInt.
     */
    string print();
    
    // MANIPULATION
    /**
     * Makes this bigInt be a copy of otherNum
     * @param otherNum An initialized bigInt to copy.
     * @return this bigInt (can be used for other calculations).
     */
    bigInt& operator=(const bigInt& otherNum);

    /**
     * Adds another bigInt to this one.
     * @param otherNum is an initialized bigInt
     * @return the sum of this bigInt and otherNum.
     */
    bigInt& operator+(bigInt& otherNum);


    /**
     * Multiplies this bigInt by an integer.
     * @param cc An integer > 0.
     * @return the product of this bigInt and cc.
     */
    bigInt& operator*(int cc);

    /**
     * Multiplies this bigInt by another bigInt.
     * @param otherNum is an initialized bigInt
     * @return the product of this bigInt and otherNum.
     */
    bigInt& operator*(bigInt &otherNum);


protected:
    static const int base = 10; // the base in which the number is represented.
    vector<int> digits; /** stores the digits of the current number, one digit per vector element.
												 ** The most least significant digit is in digits[0].
												 */

    /**
     * Multiplies the current bigInt by 10^cc for a C++ integer cc
     * @param cc A C++ integer >= 0.
     */
    void operator<<(int cc);
};
#endif