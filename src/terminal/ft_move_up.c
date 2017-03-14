#include "project.h"

/*
 * move the cursor to a one up line
 */
 int  ft_move_up(void)
 {
   char *cmd;

   if ((cmd = tgetstr("up", NULL)) == NULL) //move to the left
     return (EXIT_FAILURE); //pas quiter le programme
   tputs(cmd, 0, &my_putchar);
   return (EXIT_SUCCESS);
 }
