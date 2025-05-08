#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib> 

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        //lowercase only
        std::string lowerStr = "";
        for (char c : k){
          if (std::isalnum(c)){
            lowerStr += std::tolower(c);
          }
        }


        unsigned long long w[5] = {0,0,0,0,0}; 

        int strLength = lowerStr.length(); 
        int groupIndex = 4;

        for (int i = strLength-1; i >= 0 && groupIndex >= 0; --groupIndex){
          unsigned long long groupValue = 0;

          for (int j = 0; j < 6 && i >= 0; ++j, --i) {
            unsigned long long digitValue = letterDigitToNumber(lowerStr[i]);
            groupValue += digitValue * exponentiation(36, j);
          }
         
          w[groupIndex] = groupValue; 
        }


        //hash calc
        HASH_INDEX_T finalHash = 0;
        for (int i = 0; i < 5; ++i){
          finalHash += rValues[i] * w[i];
        }

        return finalHash; 


    }

    unsigned long long exponentiation(unsigned long long base, unsigned long long exponent) const {
      unsigned long long result = 1;

      while (exponent > 0){
        if (exponent % 2 == 1){ //exponent odd
          result = result * base;
        }
        base *= base; //square base
        exponent /= 2; //halve expoenent
      }
      return result; 
    }
    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        letter = std::tolower(letter); 
        if (letter >= '0' && letter <= '9'){
          return 26 + (letter - '0'); //0 indexing so 26
        }
        else if (letter >= 'a' && letter <= 'z'){
          return letter - 'a';
        }

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
