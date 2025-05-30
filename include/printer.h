#ifndef PRINTER_H
#define PRINTER_H

typedef enum {
  COLOR_BLACK,
  COLOR_RED,
  COLOR_GREEN,
  COLOR_YELLOW,
  COLOR_BLUE,
  COLOR_MAGENTA,
  COLOR_CYAN,
  COLOR_WHITE
} Color;

void print_color(const char *text, Color color);

#endif /* PRINTER_H */
