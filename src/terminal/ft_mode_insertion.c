#include "project.h"

/*
* autorize the insertion between caracteres x and x - 1, the cursor don't move
*/
int  ft_mode_insertion(void)
{
  char *cmd;

  if ((cmd = tgetstr("im", NULL)) == NULL)
  {
    return (EXIT_FAILURE);
  }
  tputs(cmd, 0, &my_putchar);
  return (EXIT_SUCCESS);
}
