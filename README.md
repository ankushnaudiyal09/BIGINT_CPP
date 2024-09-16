Hello Coders , 

Hello Coders , Here is a Small Introduction of Class "BIGINT" 

Managing large numbers in C++ can be challenging due to the limitations of standard data types. That’s where BIGINT comes in—a versatile C++ class crafted to handle and perform operations on large integers represented as strings. Whether you're working with cryptographic applications, big data BIGINT simplifies and gives access to use its functionality with ease . 🔧 

🚀 What it Gives -> 

Basically almost every function  except these two function Ispalindrome() , Compare()  . Rest all returns a string as an answer . You can use it wherever you want as in a form of a string 

🚀 What you have to do -> 

  You have to make an object of BIGINT and enters a string at the time of building object and it considered as a string , and whenever you called a function such as -> 
  Add() , Sub() , Multiply() , Divide() , Compare() , send the second string , which will treated as b , and these function return the operation based on 'A' and 'B' string . 

  The functions like Abs() , Ispalindrome() , Longest_palindrome() , SqureRoot() and Factorial() , these function run their functionlaties based on the string on the time of building object.


Key Features -> 

  Comparison: Effortlessly compare two BIGINT numbers to determine their relative sizes. ⚖️ // return 1 if a is greater , 0 if b is greater , -1 if both same

  Absolute Value (Abs): Get the non-negative version of your BIGINT. 🔢

  Addition (Add): Add two BIGINTs with precision, regardless of their size. ➕

  Subtraction (Sub): Subtract one BIGINT from another with ease. ➖

  Multiplication (Multiply): Perform multiplication on large numbers effortlessly. ✖️

  Division (Divide): Divide BIGINTs and obtain accurate results. ➗

  Palindrome Check (Ispalindrome): Check if a number or string is a palindrome. 🔄  , gives true or false as an answer . 

  Longest Palindrome: Find the longest palindromic substring within a given string. 🔍

  Square Root (SquareRoot): Compute the square root of a BIGINT number. √

  Factorial: Calculate factorials up to 1000 easily . 📈

  Reverse BIGINT: Reverse the digits of your BIGINT number. 🔄

🚀 How It Works -> 

Extract my cpp file from Github into your project and include the header file naming "BIG_INT_CLASS.cpp" , and after that you can simply build object of BIGINT and performs operations . 

A small example of making object  -> 

-------------------------------------------------------------------------------------------------------------------------------------

#include "BIG_INT_CLASS.cpp"
#include<bits/stdc++.h>
using namespace std;

int main(){

// calling function which didnt take input string at the time of function call 
BIGINT s("123456");

string ans = s.reverse_BIGINT();

// calling functions which takes a input string at the time of function call 

BIGINT b("12345");

string ans2 = b.Add("5");

cout<<"Addition of 12345 + 5 is : "<<ans2<<endl;


return 0;

}
-----------------------------------------------------------------------------------------------------------------------------------

