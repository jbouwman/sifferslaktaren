#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "printer.h"

int has_color(void) {
  const char *term = getenv("TERM");
  // "isatty" is short for "is connected to a teletypewriter"
  if (!isatty(STDOUT_FILENO) || term == NULL) {
    return 0;
  }
  return strstr(term, "xterm") != NULL;
}

void print_color(const char *s, Color c) {
  int color = has_color();
  if (color)
    printf("\033[%dm", c + 30);
  printf("%s", s);
  if (color)
    printf("\033[0m");
}
