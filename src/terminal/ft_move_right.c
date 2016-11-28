#include "project.h"

/**
 *  move the cursor to a actual position x + 1 (right)
 */
int  ft_move_right(void)
{
  char *cmd;

  if ((cmd = tgetstr("nd", NULL)) == NULL)
    return (EXIT_FAILURE);
  tputs(cmd, 0, &my_putchar);
  return (EXIT_SUCCESS);
}
