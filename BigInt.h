/*
  @file     BigInt.h
  @authors  David Hausner
  @date     2016-12-22
  @version  1.0
  Prototypes of functions for BigInt class

  Copyright 2016, D. R. Hausner
*/

#ifndef _BIGINT_H
#define _BIGINT_H

#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <string>
#include <utility>

class BigInt
{
  public:
    BigInt() : bint("") {}  // default constructor
    BigInt(string s)        // constructor w/ data
    {
      if(s.length() > 0)
      {
        for(int i = 0; i < s.length() -1; i++)
        {
          if(!isdigit(s[i]))
          {
            printf("INVALID DATA! DIGITS (0-9) ONLY!\n");
            exit(EXIT_FAILURE);
          }
        }
        bint = s;
      }
      else bint = "";
    }
    BigInt(const BigInt& b) : bint(b.bint) {} // copy constructor
    ~BigInt() {}  // destructor
    BigInt& operator = (const BigInt& b) // assignment operator
    {
      if (this != &b)
        bint = b.bint;
      return *this;
    }
    BigInt Max (const BigInt& a, const BigInt& b)
    {
      if (a > b)
        return a;
      else return b;
    }
    BigInt Min (const BigInt& a, const BigInt& b)
    {
      if (a < b)
        return a;
      else return b;
    }
    BigInt Size(const BigInt &a)
    {
      return bint.length();
    }
    BigInt operator + (const BigInt& a, const BigInt& b)
    {
      // get length of longest int for use in iterator
      size_t size = Size(Max(a,b));
      // get mutable (non-const) versions of BigInt data
      string biginta = a.bint;
      string bigintb = b.bint;
      // reverse strings to put "ones place" in position 0
      Reverse(biginta);
      Reverse(bigintb);
      // ensure that both strings are the same length by
      // concatenating "leading" zeroes on the shorter one
      while(biginta.length() > bigintb.length())
        bigintb += "0";
      while(biginta.length() < bigintb.length())
        biginta += "0";
      // initialize answer string
      string answer = "";
      // initialize temporary sum and carry ints to 0
      int carry = 0, sum_mod = 0;
      for(size_t i = 0; i < size; i++)
      {
        // add each place of the string values and previous carry int
        sum_mod = atoi(biginta[i]) + atoi(bigintb[i]) + carry;
        // new carry bit is the "tens place" of the temporary sum
        carry = sum_mod / 10;
        // the temporary sum only needs to be one digit, so make it itself % 10
        sum_mod %= 10;
        // turn the sum into a character before adding it to the answer string
        answer += IntToChar(sum_mod);
      }
      // if carry > 0 after the last temporary sum has been concatenated
      // into answer, concatenate the carry bit at the end of answer
      if(carry > 0)
      {
        answer += IntToChar(carry);
      }
      // get rid of any remaining zeroes at the end of the string,
      // which would be leading zeroes since it's currently reversed
      CleanUpString(answer);
      // reverse it, orienting it correctly
      Reverse(answer);
      // create a BigInt instance to hold the answer string and return it
      BigInt sum = new BigInt(answer);
      return sum;
    }
    BigInt operator - (const BigInt& a, const BigInt& b)
    {

    }
    BigInt operator * (const BigInt& a, const BigInt& b)
    {

    }
    BigInt operator / (const BigInt& a, const BigInt& b)
    {

    }
    BigInt operator % (const BigInt& a, const BigInt& b)
    {

    }
    BigInt operator ^ (const BigInt& a, const BigInt& b)
    {

    }
    BigInt operator += (const BigInt& a, const BigInt& b)
    {

    }
    BigInt operator -= (const BigInt& a, const BigInt& b)
    {

    }
    BigInt operator *= (const BigInt& a, const BigInt& b)
    {

    }
    BigInt operator /= (const BigInt& a, const BigInt& b)
    {

    }
    BigInt operator %= (const BigInt& a, const BigInt& b)
    {

    }
    BigInt operator ++ (const BigInt& a)
    {

    }
    BigInt operator -- (const BigInt& a)
    {

    }
    bool operator < (const BigInt& a)
    {

    }
    bool operator > (const BigInt& a)
    {

    }
    bool operator <= (const BigInt& a)
    {

    }
    bool operator >= (const BigInt& a)
    {

    }
    bool operator == (const BigInt& a, const BigInt& b)
    {
      return a.bint == b.bint;
    }
  private:
    string bint;
    void Reverse(string &s)
    {
      if(s.length() < 2)
        return;
      for(int i = 0; i < s.length() / 2; i++)
        std::swap(s[i],s[s.length()-(i+1)]);
    }
    char IntToChar(int i)
    {
      if(i >= 0 && i < 10)
        return i + 48;
      else return '\0';
    }
    void CleanUpString(string &s) // removes zeroes from the end of the string
    {
      while(s.at(s.length()-1) == '0')
        s.erase(s.length()-1);
    }
}



#endif
