// **************************************

// Provide project identification here.
// Eric Le
// Project: Estimating Pi via Numerical Integration

//  Instructions to build/run program:
//  - To build, type: make all
//  - To run pi.c, type: ./pi
//  - To remove/clean, type: make clean 

// **************************************


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#ifndef M_PI 
#define M_PI 3.14159265358979323846264338327950288
#endif

long double trap(long double(*f)(long double), 
		 long double a, long double b, int n) {
  const long double h = (b - a)/n;

// Complete the function.
  long double sum = 0.0;
  long double x = a + h;

  // Get sum; f(x_1) + f(x_2) + ... + f(x_n-1)
  for(int i = 1; i < n; i++, x=a+i*h) { 
    sum += f(x);
  }
  return h*((f(a) + f(b))/2 + sum);
}

long double simpsons(long double (*f)(long double), 
		     long double a, long double b, unsigned n) {
  assert((n & 1) == 0);// n must be even
  const long double h = (b - a)/n;
 
// Complete the function.
  long double sum = 0.0;
  long double x = a + h;

  // Get sum
  for(int i = 1; i < n; i++, x=a+i*h) {
    if(i % 2 == 0) { // Points between subinterval (weight = 2)
      sum += 2*f(x);
    }
    else { // Middle point of subinternal (weight = 4)
      sum += 4*f(x);
    }
  }
  return (h/3)*(f(a) + f(b) + sum);
}

long double simpsons38(long double (*f)(long double), 
		       long double a, long double b, unsigned n) {
  assert((n % 3) == 0);// n must be a multiple of 3
  const long double h = (b - a)/n;

// Complete the function.
  long double sum = 0.0;
  long double x = a + h;

  // Get sum
  for(int i = 1; i < n; i++, x=a+i*h) {
    if(i % 3 == 0) { //Subinternval multiples of 3 (weight = 2)
      sum += 2*f(x);
    }
    else { // Otherwise weight = 3
      sum += 3*f(x); 
    }
  }
  return (3*h/8)*(f(a) + f(b) + sum);
}

long double booles(long double (*f)(long double), 
		   long double a, long double b, unsigned n) {
  assert((n % 4) == 0);// n must be a multiple of 4
  const long double h = (b - a)/n;

// Complete the function.
  long double sum = 0.0;
  long double x = a + h;

  // Get sum
  for(int i = 1; i < n; i++, x=a+i*h) {
    // Determine weights (excluding x_0 and x_n)
    if(i % 4 == 0) {
      sum += 14*f(x);
    }
    else if (i % 4 == 1) { 
      sum += 32*f(x);
    }
    else if (i % 4 == 2) {
      sum += 12*f(x);
    }
    else {
      sum += 32*f(x);
    }
  }
  return (2*h/45)*(7*(f(a) + f(b)) + sum);
}

long double f(long double x) {
  return 4.0L/(1.0L + x*x);
}

int main(void) {
  const unsigned maxn = 800004;
  for (unsigned n = 12; n <= maxn; n *= 2) {
    const long double I_trap = trap(f, 0, 1, n);
    const long double error_trap = fabsl(M_PI - I_trap);
    const long double I_simp = simpsons(f, 0, 1, n);
    const long double error_simp = fabsl(M_PI - I_simp);
    const long double I_simp38 = simpsons38(f, 0, 1, n);
    const long double error_simp38 = fabsl(M_PI - I_simp38);
    const long double I_booles = booles(f, 0, 1, n);
    const long double error_booles = fabsl(M_PI - I_booles);
    printf("%5d %0.10Le %0.10Le %0.10Le %0.10Le\n", n, 
	   error_trap, error_simp, error_simp38, error_booles);
  }
  return 0;
}
