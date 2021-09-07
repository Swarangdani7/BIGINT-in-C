#include "implement.h"

// Compares two bigints
// Returns 1 if bigint1 > bigint2
// Returns -1 if bigint1 < bigint2
// Returns 0 if bigint1 == bigint2
int CompareBigint(const char* big1, const char* big2);

// Performs addition of two bigints and returns a new bigint
// The Bigints passed to this function must be positive
char* BigintAdder(const char* ptr1,const char* ptr2);

// Performs subtraction of two bigints and returns a new bigint
// The Bigints passed to this function must be positive
char* BigintDiffer(const char* ptr1, const char* ptr2);

// Multiplies two bigints and returns a new bigint
// Multiplication is done using elementary school mutiplication algorithm
char* BigintMultiplier(const char* ptr1,const char* ptr2);

// Finds the factorial of a given number and returns the result as a bigint
char* BigintFactorial(unsigned int n);

// Finds the nth fibonnaci number and returns the result as a bigint
char* BigintFibonacci(unsigned int n);