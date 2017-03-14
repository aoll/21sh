#include "project.h"

/*
 * every output after this function will be in reverse mode video
 */
int  ft_mode_reverse_video(void)
{
  char *cmd;

  if ((cmd = tgetstr("mr", NULL)) == NULL) //enter reverse mode video
    return (EXIT_FAILURE); //pas quiter le programme
  tputs(cmd, 0, &my_putchar);
  return (EXIT_SUCCESS);
}
