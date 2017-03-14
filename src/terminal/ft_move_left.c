#include "project.h"

/*
 * move the cursor to a actual position x - 1 (left)
 */

int  ft_move_left(void)
{
  char *cmd;
  char *new;


  if ((cmd = tgetstr("le", NULL)) == NULL) //move to the left
    return (EXIT_FAILURE); //pas quiter le programme
  new = ft_strnew(ft_strlen(cmd) + PADDING_BUFFER);
  ft_bzero(new, ft_strlen(cmd) + PADDING_BUFFER);
  ft_memcpy(new, cmd, ft_strlen(cmd));
  tputs(new, 0, &my_putchar);
  return (EXIT_SUCCESS);
}
