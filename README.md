# Bigint In C
C library that supports very large numbers (upto 1000 digits), basic Arithmetic operations and a set of mathematical functions


# Functions: 

* CompareBigint : This function accepts two Bigints(char array) compares them and returns an integer.

``` int CompareBigint(const char* Bigint1, const char* Bigint2) ```
1.   If ``` Bigint1 > Bigint2 ``` returns 1
2.   If ``` Bigint1 < Bigint2 ``` returns -1
3.   If ``` Bigint1 = Bigint2 ``` returns 0

* BigintAdder : This Function returns Addition of two Bigints(char array), supports non-negative integers.

``` char* BigintAdder(const char* Bigint1, const char* Bigint2) ```

* BigintDiffer : This Function returns Difference of two Bigints(char array), supports non-negative integers.

``` char* BigintDiffer(const char* Bigint1, const char* Bigint2) ```

* BigintMultiplier : This function performs Multiplication of two Bigints(char array) using standard multiplication algorithm.

``` char* BigintMultiplier(const char* Bigint1, const char* Bigint2) ```

* BigintFactorial : This function returns the Factorial of a given number passed as an argument.

``` char* BigintFactorial(unsigned integer num) ```

* BigintFibonacci : This functions returns the nth Fibonacci number passed as an argument.

``` char* BigintFibonacci(unsigned integer num) ```


## test.c

*   A test case file for checking correctness of all functions and arithmetic operations.

## bigint.h

*   Header file that contains all mathematical functions and arithmetic operations.

## implement.h

*   Contains implementation of all functions.
