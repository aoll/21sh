#include "project.h"

/*
 * String of commands to clear the line the cursor is on, and all the lines
 * below it, down to the bottom of the screen. This command string should be
 * used only with the cursor in column zero; their effect is undefined
 * if the cursor is elsewhere.
 */
 int  ft_clear_down(void)
 {
   char *cmd;

   if ((cmd = tgetstr("cd", NULL)) == NULL)
   {
     return (EXIT_FAILURE);
   }
   tputs(cmd, 0, &my_putchar);
   return (EXIT_SUCCESS);
 }
