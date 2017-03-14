#include "project.h"

/*
 * turn off all alternative mode
 */
int  ft_mode_basic_video(void)
{
  char *cmd;

  if ((cmd = tgetstr("me", NULL)) == NULL) //turn off alternative mode
    return (EXIT_FAILURE); //pas quiter le programme
  tputs(cmd, 0, &my_putchar);
  return (EXIT_SUCCESS);
}
