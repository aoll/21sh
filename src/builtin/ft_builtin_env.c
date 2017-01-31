#include "project.h"

/**
 *
 */
int  ft_builtin_env(char **tab_cmd, t_arr **env)
{
  if (!tab_cmd[1])
  {
    ft_arr_print(*env);
    return (EXIT_SUCCESS);
  }
  return (EXIT_SUCCESS);
}
