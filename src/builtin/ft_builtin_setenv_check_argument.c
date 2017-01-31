#include "project.h"

/**
 * check the number of argument for setenv
 * if error print the adequat message
 * return 0 if is correct and 1 if != 2 (setenv including)
 */
int  ft_builtin_setenv_check_argument(const char ** tab_cmd, char *cmd)
{
  size_t arr_len;

  arr_len = ft_array_len((const void **)tab_cmd);
  if (!arr_len || arr_len < 2)
  {
    ft_putstr("21sh: ");
    ft_putstr(cmd);
    ft_putstr(" to few arguments\n");
    return (EXIT_FAILURE);
  }
  else if (arr_len > 2)
  {
    ft_putstr("21sh: ");
    ft_putstr(cmd);
    ft_putstr(" too many arguments\n");
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}
