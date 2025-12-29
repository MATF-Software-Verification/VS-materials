#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// C function for extended Euclidean Algorithm
int gcdExtended(int a, int b, int *x, int *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
    // To store results of recursive call
    int x1, y1; 
    int gcd = gcdExtended(b%a, a, &x1, &y1);
 
    // Update x and y using results of recursive call
    *x = y1 - (b/a) * x1;
    *y = x1;
 
    return gcd;
}

int find_any_solution (int a, int b, int c, int *x0, int *y0, int *g) {
  *g = gcdExtended (abs(a), abs(b), x0, y0);
  if(*g == 0)
    return c == 0;
  if (c % *g != 0)
    return 0;
  *x0 *= c / *g;
  *y0 *= c / *g;
  if (a < 0)   *x0 *= -1;
  if (b < 0)   *y0 *= -1;
  return 1;
}

// Fuzz funkcija -- Prva verzija
int LLVMFuzzerTestOneInput(const uint32_t *data, size_t size){  
  if (size < 3*sizeof(int))
    return 0;

  int a,b,c;

  a = data[0];
  b = data[1];
  c = data[2];
  
  int x,y,g;
  
  if( find_any_solution(a,b,c,&x, &y, &g))
    assert(a*x+b*y == c);
  else
    assert(a*x+b*y != c);

  return 0;
}
