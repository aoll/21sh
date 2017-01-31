#include "project.h"

/**
 * compare a string to a list of builtin a return the index if is present or 0 if not
 */
int  ft_is_builtin(char *command)
{
  if (!command)
    return (0);
  else if (!ft_strcmp("env", command))
    return (B_ENV);
  else if (!ft_strcmp("setenv", command))
    return (B_SETENV);
  else if (!ft_strcmp("unsetenv", command))
    return (B_UNSETENV);
  else if (!ft_strcmp("cd", command))
    return (B_CD);
  else if (!ft_strcmp("echo", command))
    return (B_ECHO);
  return (0);
}
