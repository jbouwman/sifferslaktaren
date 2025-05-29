#ifndef TEST_H
#define TEST_H

/*
 * Utilities for writing unit tests
 */

#define ASSERT(condition, message)                              \
  do {                                                          \
    if (!(condition)) {                                         \
      fprintf(stderr, "Test assertion failed: %s\n", message);  \
      return EXIT_FAILURE;                                      \
    }                                                           \
  } while (0)


#define ASSERT_STRCMP(actual, expected, message)                \
  do {                                                          \
    if (!actual || strcmp(actual, expected) != 0) {             \
      fprintf(stderr, "Test assertion failed: %s\n", message);  \
      fprintf(stderr, "  Expected: \"%s\"\n", expected);        \
      fprintf(stderr, "  Actual: \"%s\"\n",                     \
              (!actual ? "NULL" : actual));                     \
      return EXIT_FAILURE;                                      \
    }                                                           \
  } while (0)

#endif /* TEST_H */
