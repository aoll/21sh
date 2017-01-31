#include "project.h"


/**
 * print the env on a fd give in parameter
 */
static int  ft_builtin_env_print(t_arr *env, int fd_stdout)
{
  int i;
  t_kval *kval;

  i = 0;
  while (i < (int)env->length)
  {
    kval = *(t_kval **) ((unsigned char *)env->ptr + i * env->sizeof_elem);
    ft_putstr_fd(kval->key, fd_stdout);
    ft_putstr_fd("=", fd_stdout);
    ft_putstr_fd(kval->value, fd_stdout);
    ft_putstr_fd("\n", fd_stdout);
    i++;
  }
  return (EXIT_SUCCESS);
}

/**
 *
 */
int  ft_builtin_env(char **tab_cmd, t_arr **env, int fd_stdout, int fd_stderr)
{
  if (!tab_cmd[1])
  {
    ft_builtin_env_print(*env, fd_stdout);
    return (EXIT_SUCCESS);
  }
  return (EXIT_SUCCESS);
}
