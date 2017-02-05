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
    if (kval->value)
    {
      ft_putstr_fd(kval->value, fd_stdout);
    }
    ft_putstr_fd("\n", fd_stdout);
    i++;
  }
  return (EXIT_SUCCESS);
}

/**
 * add or edit a var of the env
 */
int  ft_builtin_env_setenv(t_arr *env, char *var, int fd_stderr)
{
  char *cmd;
  char **tab_cmd;
  int i;

  i = 0;
  if (!(cmd = ft_strjoin("setenv ", var)))
  {
    ft_putstr_fd("21sh: error malloc\n", STDERR);
    return (EXIT_FAILURE);
  }
  if (!(tab_cmd = ft_strsplit(cmd, ' ')))
  {
    ft_putstr_fd("21sh: error malloc\n", STDERR);
    return (EXIT_FAILURE);
  }
  ft_builtin_setenv((const char **)tab_cmd, &env, fd_stderr);
  free(cmd);
  while (tab_cmd[i])
  {
    free(tab_cmd[i]);
    i++;
  }
  free(tab_cmd);
  return (EXIT_SUCCESS);
}

/**
 * set a list off var in the env before execute a commande or print the new env
 */
int  ft_builtin_env_set_var(char ***tab_cmd, t_arr *env, int fd_stdout, int fd_stderr)
{
  char **cmd;
  int index_separator;
  bool is_env_prev;
  void *kval;
  char **tmp;
  int len;

  is_env_prev = false;
  index_separator = 0;
  cmd = *tab_cmd;
  while (*cmd)
  {
    index_separator = ft_indexof_first_char(*cmd, '=');
    if (index_separator < 0)
    {
      if (!(ft_strcmp(*cmd, "env")))
      {
        is_env_prev = true;
        free(*cmd);
        cmd++;
        continue;
      }
      else if (!(ft_strcmp(*cmd, "-i")) && is_env_prev)
      {
        //TODO free chaque element
        while (env->length)
        {
          kval = ft_arr_pop(&env, 0);
          ft_kval_free(&kval);
          // ft_putstr("\nvalue:");
          // ft_putstr(kval->value);
          // ft_putstr(".\n");
        }
        is_env_prev = true;
        free(*cmd);
        cmd++;
        continue;
      }
      else
      {
        // tmp = ft_array_str_dup((const char **)cmd); ??????????????
        len = ft_array_len((const void **)cmd);
        tmp = malloc(sizeof(char *) * (len + 1));
        tmp[len] = NULL;
        len = 0;
        while (*cmd)
        {
          tmp[len] = ft_strdup(*cmd);
          free(*cmd);
          cmd++;
          len++;
        }
        free(*tab_cmd);
        *tab_cmd = tmp;
        return (EXIT_SUCCESS);
      }
    }
    ft_builtin_env_setenv(env, *cmd, fd_stderr);
    free(*cmd);
    cmd++;
    is_env_prev = false;
  }
  // *tab_cmd = cmd;
  free(*tab_cmd);
  *tab_cmd = NULL;
  ft_builtin_env_print(env, fd_stdout);
  return (B_ENV);
}

/**
 * if not other arguments for env, print the env
 * else set the variable for a temporaire env before execute a commande
 * if not commande print the new env
 * env -i env = NULL
 * env -u "VAR_NAME" unsetenv the var
 */
int  ft_builtin_env(char ***tab_cmd, t_arr **env, int fd_stdout, int fd_stderr)
{
  char **cmd;

  cmd = *tab_cmd;
  if (!cmd[1])
  {
    ft_builtin_env_print(*env, fd_stdout);
    return (B_ENV);
  }
  else
  {
    return (ft_builtin_env_set_var(tab_cmd, *env, fd_stdout, fd_stderr));
  }
  return (EXIT_SUCCESS);
}
