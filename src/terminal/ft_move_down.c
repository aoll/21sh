#include "project.h"

/*
 * move the cursor to a one down line
 */
 int  ft_move_down(void)
 {
   char *cmd;

   if ((cmd = tgetstr("do", NULL)) == NULL) //move to the left
     return (EXIT_FAILURE); //pas quiter le programme
   tputs(cmd, 0, &my_putchar);
   return (EXIT_SUCCESS);
 }
