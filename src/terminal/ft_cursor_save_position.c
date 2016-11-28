#include "project.h"

/**
 * String of commands to make the terminal save the current cursor position.
 * Only the last saved position can be used. If this capability is present,
 * `rc' should be provided also. Most terminals have neither.
 */
 int  ft_cursor_save_position(void)
 {
   char *cmd;

   if ((cmd = tgetstr("sc", NULL)) == NULL)
     return (EXIT_FAILURE);
   tputs(cmd, 0, &my_putchar);
   return (EXIT_SUCCESS);
 }
