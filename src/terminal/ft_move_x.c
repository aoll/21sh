#include "project.h"

/**
 * move the cursor to a new position x
 */
int  ft_move_x(int new_pos_x)
{
  char *cmd;

  // if ((cmd = tgetstr("cr", NULL)) == NULL) //begin on the line
  if ((cmd = tgetstr("ch", NULL)) == NULL) //move to pos_x on the line
    return (EXIT_FAILURE);
  tputs(tgoto(cmd, 0, new_pos_x), 0, &my_putchar);
  return (EXIT_SUCCESS);
}
