/*
  @file     BigInt.h
  @authors  David Hausner
  @date     2016-12-25
  @version  1.0
  Prototypes of functions for BigInt class
  
  UNTESTED

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
      while(biginta.length() < size)
        biginta += "0";
      while(bigintb.length() < size)
        bigintb += "0";
      // initialize answer string
      string answer = "";
      // initialize temporary sum and carry ints to 0
      int carry = 0, sum_mod = 0;
      for(size_t i = 0; i < size; i++)
      {
        // add each place of the string values and previous carry int
        sum_mod = atoi(biginta.at(i)) + atoi(bigintb.at(i)) + carry;
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
      while(biginta.length() < size)
        biginta += "0";
      while(bigintb.length() < size)
        bigintb += "0";
      // initialize answer string
      string answer = "";
      // initialize temporary sum and carry ints to 0
      int borrow = 0, diff = 0, a, b;
      for(size_t i = 0; i < size; i++)
      {
        //
        a = atoi(biginta.at(i));
        b = atoi(bigintb.at(i));
        // compare to see if borrowing will be done
        if(a >= (b + borrow)) // no borrowing necessary
        {
          // subtract b and the previous round's borrow from a
          diff = a - (b + borrow);
          // no borrowing this round
          borrow = 0;
        }
        else  // borrowing necessary
        {
          // subtract b and the prev. round's borrow from a + 10
          diff = (a + 10) - (b + borrow);
          // borrowing this round, set for next round
          borrow = 1;
        }
        // turn the diff into a character before adding it to the answer string
        answer += IntToChar(diff);
      }
      // get rid of any remaining zeroes at the end of the string,
      // which would be leading zeroes since it's currently reversed
      CleanUpString(answer);
      // reverse it, orienting it correctly
      Reverse(answer);
      // create a BigInt instance to hold the answer string and return it
      BigInt difference = new BigInt(answer);
      return difference;
    }
    BigInt operator * (const BigInt& a, const BigInt& b)
    {
      BigInt product = new BigInt("0");
      BigInt layer = new BigInt();
      size_t size_a = Size(a);
      size_t size_b = Size(b);
      size_t offset = 0;
      int carry = 0;
      // reverse strings to put "ones place" in position 0
      Reverse(biginta);
      Reverse(bigintb);
      // for each digit i of a, multiply all digits of b by i
      for(size_t size = 0; size < size_a; size++)
      {
        // clear layer
        layer.Clear();
        // initialize layer
        for(size_t s = 0; s < offset; s++)
          layer.Offset();
        // multiply b by a[i]
        for(size_t s = 0; s < size_b; s++)
        {
          // each individual multiplication
          carry = a.At(size) * b.At(s) + carry;
          // add "one's place" to layer
          layer.AddDigit(IntToChar(carry % 10));
          // move "ten's place" of carry to "one's place"
          carry = carry / 10;
        }
        // add each place's product to BigInt product
        product += layer;
        // increase offset by one (annex a zero)
        offset++;
      }
      return product;
    }
    BigInt operator / (const BigInt& a, const BigInt& b)
    {
      string q;
        BigInt quotient = new BigInt("0");
      if(a < b)
      { /* do nothing, just return "0" */ }
      else
      {
        while(a > (b * quotient))
        {
          quotient++;
        }
        // while loop always goes one too far
        quotient--;
      }
      return quotient;
    }
    BigInt operator % (const BigInt& a, const BigInt& b)
    {
      BigInt mod = new BigInt();
      mod = a - ((a / b) * b);
      return mod;
    }
    BigInt operator ^ (const BigInt& a, const BigInt& b)
    {
      BigInt value = new BigInt("1");
      for(size_t s = 0; s < b; s++)
      {
        value *= a;
      }
      return value;
    }
    BigInt& operator += (const BigInt& a, const BigInt& b)
    {
      BigInt sum = new BigInt();
      sum = a + b;
      return *sum;
    }
    BigInt& operator -= (const BigInt& a, const BigInt& b)
    {
      BigInt difference = new BigInt();
      difference = a - b;
      return *difference;
    }
    BigInt& operator *= (const BigInt& a, const BigInt& b)
    {
      BigInt product = new BigInt();
      product = a * b;
      return *product;
    }
    BigInt& operator /= (const BigInt& a, const BigInt& b)
    {
      BigInt quotient = new BigInt();
      quotient = a / b;
      return *quotient;
    }
    BigInt& operator %= (const BigInt& a, const BigInt& b)
    {
      BigInt mod = new BigInt();
      mod = a % b;
      return *mod;
    }
    BigInt& operator ++ ()
    {
      BigInt one = new BigInt("1");
      this = this + one;
      return *this;
    }
    BigInt operator++(BigInt)
    {
      BigInt temp(*this);
      operator++();
      return temp;
    }
    BigInt operator -- (const BigInt& a)
    {
      BigInt one = new BigInt("1");
      this = this - one;
      return *this;
    }
    BigInt operator++(BigInt)
    {
      BigInt temp(*this);
      operator--();
      return temp;
    }
    bool operator < (const BigInt& a)
    {
      if(Size() < a.Size())
        return true;
      if(Size() > a.Size())
        return false;
      for(size_t i = Size() - 1; i >= 0; i--)
      {
        if(At(i) < a.At(i))
          return true;
      }
      return false;
    }
    bool operator > (const BigInt& a)
    {
      if(Size() > a.Size())
        return true;
      if(Size() < a.Size())
        return false;
      for(size_t i = Size() - 1; i >= 0; i--)
      {
        if(At(i) > a.At(i))
          return true;
      }
      return false;
    }
    bool operator <= (const BigInt& a)
    {
      return (this < a) || (this == a);
    }
    bool operator >= (const BigInt& a)
    {
      return (this > a) || (this == a);
    }
    bool operator == (const BigInt& a, const BigInt& b)
    {
      if(a.Size() == b.Size())
        return a.bint == b.bint;
      return false;
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
    int At(size_t s)
    {
      if(s < Size())
        return atoi(bint.at(s));
    }
    void Offset()
    {
      bint = "0" + bint;
    }
    void Clear()
    {
      bint = "";
    }
    void AddDigit(char c)
    {
      bint += c;
    }
}

#endif
