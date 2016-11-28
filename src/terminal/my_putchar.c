#include "project.h"
/**
 * it's a function to give in parameter to the function who apply different
 * change to the terminal, like tputs()
 */
int  my_putchar(int c)
{
  write(1, &c, 1);
  return (0);
}
