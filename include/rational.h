#ifndef RATIONAL_H
#define RATIONAL_H

typedef struct {
  int numerator;
  int denominator;  
} Rational;

Rational rational_create(int numerator, int denominator);
Rational rational_normalize(Rational r);
char* rational_to_string(Rational r);

Rational rational_add(Rational a, Rational b);
Rational rational_subtract(Rational a, Rational b);
Rational rational_multiply(Rational a, Rational b);
Rational rational_divide(Rational a, Rational b);

int rational_equals(Rational a, Rational b);
int rational_compare(Rational a, Rational b);

int find_gcd(int a, int b);

#endif /* RATIONAL_H */
