#include <stdio.h>
#include <stdarg.h>

#define COLOR_BLACK "\033[30m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[325m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"
#define COLOR_L_GRAY "\033[90m"
#define COLOR_L_RED "\033[91m"
#define COLOR_L_GREEN "\033[92m"
#define COLOR_L_YELLOW "\033[93m"
#define COLOR_L_BLUE "\033[94m"
#define COLOR_L_MAGENTA "\033[95m"
#define COLOR_L_CYAN "\033[96m"
#define COLOR_L_WHITE "\033[97m"

void color_print(char Color, char* Text, ...){

  va_list args;

  va_start(args, Text);

  vprintf(Text, args);

  va_end(args);
}

void color_scan(char Color, char* Text, ...){
  va_list args;

  va_start(args, Text);

  vprintf(Text, args);

  va_end(args);
}
