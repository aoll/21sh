#include "project.h"

/*
 *
 */
int  ft_builtin_exit(char **tab_cmd, t_arr **env)
{
  ft_putstr("EXIT\n");
  return (EXIT_SUCCESS);
}
