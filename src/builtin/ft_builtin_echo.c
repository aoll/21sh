#include "project.h"

/*
 * print the argument after echo
 */
int  ft_builtin_echo(const char **tab_cmd, t_arr **env)
{
  int i;

  i = 1;
  while (tab_cmd[i])
  {
    ft_putstr(tab_cmd[i]);
    i++;
    if (tab_cmd[i])
    {
      ft_putstr(" ");
    }
  }
  ft_putstr("\n");
  return (EXIT_SUCCESS);
}
