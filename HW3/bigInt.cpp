
// IMPLEMENTATION of a bigInt

#include "bigInt.h"

bigInt::bigInt(int num) {
    int ii = 0;

    while (num > 0) { // add the number, digit by digit
        int digit = num % base;
        digits.push_back(digit);
        num /= base;
    }
}

bigInt& bigInt::operator=(const bigInt& otherNum) {
    digits = otherNum.digits;
    return *this;
}

bigInt& bigInt::operator+(bigInt& otherNum) {
    bigInt *result = new bigInt(); // where the result will be stored - allocated off the heap

    // 0. put the smaller of the numbers being added in <first>, the larger number in <second>
    bigInt first, second;
    if (digits.size() > otherNum.digits.size()) {
        first = otherNum;
        second = *this;
    } else {
        first = *this;
        second = otherNum;
    }

    // 1. add the two numbers digit by digit, with a carry
    int ii;
    int carry = 0;
    for (ii = 0; ii < first.digits.size(); ii++) {
        int sum = first.digits[ii] + second.digits[ii];
        result->digits.push_back((sum + carry) % base);
        if (sum + carry > (base - 1)) {
            carry = 1;
        } else {
            carry = 0;
        }
    }
    // 2. finish up with the larger number when there are no digits left in the smaller number
    for (; ii < second.digits.size(); ii++)
        if (carry) {
            int dig = (second.digits[ii] + carry);
            result->digits.push_back(dig % base);
            carry = (dig > (base - 1) ? dig / base : 0);
        } else
            result->digits.push_back(second.digits[ii]);

    if (carry)
        result->digits.push_back(carry);

    // 3. return the sum
    return *result;
}

bigInt &bigInt::operator*(int cc) {
    int carry = 0;
    bigInt *result = new bigInt(); // where the result will be stored - allocated off the heap

    // 0.Multiply each digit by cc, recording the carry
    for (int ii = 0; ii < digits.size(); ii++) {
        int prod = digits[ii] * cc + carry;
        result->digits.push_back(prod % base);
        if (prod > (base - 1))
            carry = prod / base;
        else
            carry = 0;
    }

    // 1. Shift what is left of the carry into the result
    while (carry) {
        result->digits.push_back(carry % base);
        carry /= base;
    }

    // 2. Return the result
    return *result;
}

bigInt &bigInt::operator*(bigInt& otherNum) {
    bigInt *sum = new bigInt(0); // where the result will be stored - allocated off the heap
    int ii;

    // Multiply my entire number by each digit of otherNum (with appropriate shift), adding the results.
    for (ii = 0; ii < otherNum.digits.size(); ii++) {
        bigInt smallProd = *this * (int) otherNum.digits[ii];
        smallProd << ii;
        *sum = *sum + smallProd;
    }
    return *sum;
}

bool bigInt::operator<(bigInt& otherNum) {
    int myDigits = digits.size(); // how many digits my bigInt has
    int otherDigits = otherNum.digits.size(); // how many digits the other bigInt has

    for (int ii = (myDigits > otherDigits ? myDigits : otherDigits); // start at the larger index
            ii >= 0;
            ii--) {
        bool IHaveDigit = digits.size() >= ii + 1; // do I have a digit at this location?
        bool OtherHasDigit = otherNum.digits.size() >= ii + 1; // does the other number have a digit at this location?

        // case 1:  I have a non-zero digit here, otherNum does not => I am bigger
        if (IHaveDigit && digits[ii] != 0 && !OtherHasDigit)
            return false;
        // case 2:  otherNum has a non-zero digit here, I do not => I am smaller
        if (OtherHasDigit && otherNum.digits[ii] != 0 && !IHaveDigit)
            return true;
        // case 3:  we both have a digit=> compare the digits
        if (IHaveDigit && OtherHasDigit)
            if (digits[ii] != otherNum.digits[ii])
                return (digits[ii] < otherNum.digits[ii]);

        // in all other cases, continue onward
    }

    // if we get here, then the two bigInts are equal
    return false;

}

int bigInt::digit(int index) {
    return digits[index];
}

string bigInt::print() {
    string tmp = "";
    for (int ii = digits.size() - 1; ii >= 0; ii--)
        tmp += '0' + digits[ii];
    return tmp;
}

void bigInt::operator<<(int cc) {
    // shifts up by cc powers of ten, cc>=0
    digits.insert(digits.begin(), cc, 0);
}
