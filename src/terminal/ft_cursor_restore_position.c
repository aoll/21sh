#include "project.h"

/**
 * String of commands to make the terminal restore the last saved cursor
 * position. If this capability is present, `sc' should be provided also.
 * Most terminals have neither.
 */

 int  ft_cursor_restore_position(void)
 {
   char *cmd;

   if ((cmd = tgetstr("rc", NULL)) == NULL)
     return (EXIT_FAILURE);

   tputs(cmd, 0, &my_putchar);
   return (EXIT_SUCCESS);
 }
