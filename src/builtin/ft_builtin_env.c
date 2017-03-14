/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:05:25 by alex              #+#    #+#             */
/*   Updated: 2017/03/10 10:42:30 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"


/*
 * print the env on a fd give in parameter
 */
static int  ft_builtin_env_print(t_arr *env, int fd_stdout)
{
  int i;
  t_kval *kval;

  i = 0;
  if (!env)
  {
    return (EXIT_SUCCESS);
  }
  while (i < (int)env->length)
  {
    kval = *(t_kval **)((unsigned char *)env->ptr + i * env->sizeof_elem);
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

/*
 * add or edit a var of the env
 */
int  ft_builtin_env_setenv(t_arr *env, char *var, int fd_stderr)
{
  char *cmd;
  char **tab_cmd;
  int i;

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
  i = -1;
  while (tab_cmd[++i])
    free(tab_cmd[i]);
  free(tab_cmd);
  return (EXIT_SUCCESS);
}


/*
 *
 */
int  ft_builtin_env_set_var_is_cmd(char **cmd, char ***tab_cmd)
{
  int len;
  char **tmp;

  len = ft_array_len((const void **)cmd);
  if (!(tmp = ft_array_str_new(len)))
  {
    return (EXIT_FAILURE);
  }
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


/*
 * free the kvals in a t_arr
 */
int  ft_builtin_env_free_kval(t_arr *env)
{
  void *kval;

  while (env->length)
  {
    kval = ft_arr_pop(env, 0);
    ft_kval_free(&kval);
  }
  return (EXIT_SUCCESS);
}


/*
 *
 */
int  ft_builtin_env_set_var_cmd(char **cmd, t_arr *env, bool *is_env_prev)
{
  if (!(ft_strcmp(*cmd, "-i")) && *is_env_prev)
  {
    ft_builtin_env_free_kval(env);
  }
  else if ((ft_strcmp(*cmd, "env")))
  {
    return (1);
  }
  *is_env_prev = true;
  return (EXIT_SUCCESS);
}


/*
 * free and print the env
 */
int  ft_builtin_env_print_free(char ***tab_cmd, t_arr *env, int fd_stdout)
{
  free(*tab_cmd);
  *tab_cmd = NULL;
  ft_builtin_env_print(env, fd_stdout);
  return (EXIT_SUCCESS);
}

/*
 *
 */
int  ft_builtin_env_print_init(char ***cmd, char ***tab_cmd, bool *is_env_prev)
{
  if (!tab_cmd)
    return (EXIT_FAILURE);
  *is_env_prev = false;
  *cmd = *tab_cmd;
  return (EXIT_SUCCESS);
}


/*
 * set a list off var in the env before execute a commande or print the new env
 */
int  ft_builtin_env_set_var(
  char ***tab_cmd, t_arr *env, int fd_stdout, int fd_stderr)
{
  char **cmd;
  bool is_env_prev;

  if (ft_builtin_env_print_init(&cmd, tab_cmd, &is_env_prev))
    return (EXIT_SUCCESS);
  while (*cmd)
  {
    if (ft_indexof_first_char(*cmd, '=') < 0)
    {
      if (ft_builtin_env_set_var_cmd(cmd, env, &is_env_prev))
        return (ft_builtin_env_set_var_is_cmd(cmd, tab_cmd));
    }
    else
    {
      ft_builtin_env_setenv(env, *cmd, fd_stderr);
      is_env_prev = false;
    }
    free(*cmd);
    cmd++;
  }
  ft_builtin_env_print_free(tab_cmd, env, fd_stdout);
  return (B_ENV);
}

/*
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
