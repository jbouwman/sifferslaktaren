#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "rational.h"

/*
 * Test rational number support
 */

int main(void) {

  // creating

  Rational r = rational_create(6, 9);
  ASSERT(r.numerator == 2 && r.denominator == 3,
         "6/9 normalizes to 2/3");
    
  r = rational_create(-4, 6);
  ASSERT(r.numerator == -2 && r.denominator == 3,
         "-4/6 normalizes to -2/3");
    
  r = rational_create(4, -6);
  ASSERT(r.numerator == -2 && r.denominator == 3,
         "4/-6 normalizes to -2/3");

  // manipulating
  
  r = rational_add(rational_create(1, 2), rational_create(1, 3));
  ASSERT(r.numerator == 5 && r.denominator == 6,
         "1/2 + 1/3 = 5/6");
    
  r = rational_subtract(rational_create(3, 4), rational_create(1, 4));
  ASSERT(r.numerator == 1 && r.denominator == 2,
         "3/4 - 1/4 = 1/2");
    
  r = rational_multiply(rational_create(2, 3), rational_create(3, 4));
  ASSERT(r.numerator == 1 && r.denominator == 2,
         "2/3 * 3/4 = 1/2");
    
  r = rational_divide(rational_create(1, 2), rational_create(1, 4));
  ASSERT(r.numerator == 2 && r.denominator == 1,
         "1/2 / 1/4 = 2");

  // comparing
    
  ASSERT(rational_equals(rational_create(2, 4), rational_create(1, 2)),
         "2/4 equals 1/2");
  ASSERT(!rational_equals(rational_create(1, 2), rational_create(1, 3)),
         "1/2 not equal to 1/3");
  ASSERT(rational_compare(rational_create(1, 2), rational_create(1, 3)) > 0,
         "1/2 > 1/3");
  ASSERT(rational_compare(rational_create(1, 3), rational_create(1, 2)) < 0,
         "1/3 < 1/2");
  ASSERT(rational_compare(rational_create(1, 2), rational_create(2, 4)) == 0,
         "1/2 == 2/4");

  // printing
  
  char *str = rational_to_string(rational_create(3, 4));
  ASSERT_STRCMP(str, "3/4",
                "String representation of 3/4");
  free(str);
    
  str = rational_to_string(rational_create(5, 1));
  ASSERT_STRCMP(str, "5",
                "String representation of 5/1");
  free(str);
    
  return EXIT_SUCCESS;
}
