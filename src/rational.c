#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rational.h"

int find_gcd(int a, int b) {
  a = labs(a);
  b = labs(b);
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

Rational rational_normalize(Rational r) {

  if (r.denominator == 0) {
    r.numerator = 0;
    r.denominator = 1;
    return r;
  }
    
  int gcd = find_gcd(r.numerator, r.denominator);
  if (gcd > 0) {
    r.numerator /= gcd;
    r.denominator /= gcd;
  }
  
  if (r.denominator < 0) {
    r.numerator = -r.numerator;
    r.denominator = -r.denominator;
  }
    
  return r;
}

Rational rational_create(int numerator, int denominator) {
  Rational r = {numerator, denominator};
  return rational_normalize(r);
}

Rational rational_add(Rational a, Rational b) {
  Rational result;
  result.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
  result.denominator = a.denominator * b.denominator;
  return rational_normalize(result);
}

Rational rational_subtract(Rational a, Rational b) {
  Rational result;
  result.numerator = a.numerator * b.denominator - b.numerator * a.denominator;
  result.denominator = a.denominator * b.denominator;
  return rational_normalize(result);
}

Rational rational_multiply(Rational a, Rational b) {
  Rational result;
  result.numerator = a.numerator * b.numerator;
  result.denominator = a.denominator * b.denominator;
  return rational_normalize(result);
}

Rational rational_divide(Rational a, Rational b) {
  Rational result;
  result.numerator = a.numerator * b.denominator;
  result.denominator = a.denominator * b.numerator;
  return rational_normalize(result);
}

int rational_equals(Rational a, Rational b) {
  a = rational_normalize(a);
  b = rational_normalize(b);
  return a.numerator == b.numerator && a.denominator == b.denominator;
}

int rational_compare(Rational a, Rational b) {
  Rational diff = rational_subtract(a, b);
  if (diff.numerator < 0) return -1;
  if (diff.numerator > 0) return 1;
  return 0;
}

char* rational_to_string(Rational r) {
  r = rational_normalize(r);
  char* str = malloc(64);
  if (!str) return NULL;
    
  if (r.denominator == 1) {
    snprintf(str, 64, "%i", r.numerator);
  } else {
    snprintf(str, 64, "%i/%i", r.numerator, r.denominator);
  }
    
  return str;
}
