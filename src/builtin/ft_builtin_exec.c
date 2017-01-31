#include "project.h"

/**
 * exec a builtin in function of the index
 * return 0 if sucess 1 if error
 */
int  ft_builtin_exec(
  int index_builtin, char **tab_cmd, t_arr **env, int fd_stdout, int fd_stderr)
{
  if (!index_builtin)
  {
    return (EXIT_FAILURE);
  }
  // else if (index_builtin == B_ENV)
  // {
  //   ft_builtin_env(tab_cmd, env, fd_stdout, fd_stderr);
  // }
  else if (index_builtin == B_SETENV)
  {
    ft_builtin_setenv((const char **)tab_cmd, env, fd_stderr);
  }
  else if (index_builtin == B_UNSETENV)
  {
    ft_builtin_unsetenv((const char **)tab_cmd, env, fd_stderr);
  }
  else if (index_builtin == B_CD)
  {
    ft_builtin_cd((const char **)tab_cmd, env, fd_stderr);
  }
  else if (index_builtin == B_ECHO)
  {
    ft_builtin_echo((const char **)tab_cmd, env);
  }
  else if (index_builtin == B_EXIT)
  {
    ft_builtin_exit(tab_cmd, env);
  }
  return (EXIT_SUCCESS);
}
