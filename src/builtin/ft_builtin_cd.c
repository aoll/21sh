#include "project.h"

/**
 * set the OLDPWD and PWD to the env
 */
// int  ft_builtin_cd_set_env(t_arr *envp, const char *old_path, const char *new_path)
int  ft_builtin_cd_set_env(t_arr **envp, const char *key, const char *value, int fd_stderr)
{
  int index;
  t_kval *kval;
  t_arr *env;

  env = *envp;
  index = ft_arr_indexof(env, key);
  if (index > -1 && index < (int)env->length)
  {
    kval = *(t_kval **)((unsigned char *)env->ptr + index * env->sizeof_elem);
    ft_kval_set_value(kval, value);
  }
  else
  {
    if (!(kval = ft_kval_new()))
    {
      ft_putstr_fd("21sh: error malloc\n", fd_stderr);
      return (EXIT_FAILURE);
    }
    ft_kval_set_key(kval, key);
    ft_kval_set_value(kval, value);
    ft_arr_push(&env, kval, -1);
  }
  return (EXIT_SUCCESS);
}

/**
 * return a string with the absolute new path
 * NULL in case of faillure
 */
char  *ft_builtin_cd_absolute_path(const char *old_path, const char *new_path)
{
  char *path_tmp;
  char *path_absolute;

  if (new_path[0] != '/')
  {
    if (!(path_tmp = ft_strjoin(old_path, "/")))
    {
      return (NULL);
    }
    if (!(path_absolute = ft_strjoin(path_tmp, new_path)))
    {
      free(path_tmp);
      return (NULL);
    }
    free(path_tmp);
  }
  else
  {
    if (!(path_absolute = ft_strdup(new_path)))
    {
      return (NULL);
    }
  }
  return (path_absolute);
}

/**
 * check if the file exist
 * 0 if succed or 1 if faillure
 */
int  ft_builtin_cd_is_existing_file(
  const char *path_absolute, const char *new_path, int fd_stderr)
{
  int err;

  if ((err = access(path_absolute, F_OK)))
  {
    ft_putstr_fd("21sh: cd no file: ", fd_stderr);
    ft_putstr_fd(new_path, fd_stderr);
    ft_putstr_fd("\n", fd_stderr);
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}

/**
 * change the current directory of the actual processus
 * if sucess set the PWD and OLDPWD off the env
 */
int  ft_builtin_cd_change_directory(
  t_arr **env, const char *old_path, const char *new_path, int fd_stderr)
{
  char *path_absolute;
  int err;
  char *new_actual_pwd;

  if (!new_path || !ft_strlen(new_path))
  {
    return (EXIT_SUCCESS);
  }
  if (!(path_absolute = ft_builtin_cd_absolute_path(old_path, new_path)))
  {
    ft_putstr_fd("21sh: error malloc\n", fd_stderr);
    return (EXIT_FAILURE);
  }
  if ((err = ft_builtin_cd_is_existing_file(
    (const char *)path_absolute, new_path, fd_stderr)))
  {
    free(path_absolute);
    return (EXIT_FAILURE);
  }
  if ((err = chdir(path_absolute)))
  {
    free(path_absolute);
    ft_putstr_fd("21sh: permission denied: ", fd_stderr);
    ft_putstr_fd(new_path, fd_stderr);
    ft_putstr_fd("\n", fd_stderr);
    return (EXIT_FAILURE);
  }
  if (!(new_actual_pwd = ft_strnew(1082)))
  {
    free(path_absolute);
    ft_putstr_fd("21sh: error malloc\n", fd_stderr);
    return (EXIT_FAILURE);
  }
  if (!getcwd(new_actual_pwd, 1082))
  {
    free(new_actual_pwd);
    free(path_absolute);
    ft_putstr_fd("21sh: error malloc\n", fd_stderr);
    return (EXIT_FAILURE);
  }
  ft_builtin_cd_set_env(env, "PWD", new_actual_pwd, fd_stderr);
  ft_builtin_cd_set_env(env, "OLDPWD", old_path, fd_stderr);
  free(path_absolute);
  free(new_actual_pwd);
  return (EXIT_SUCCESS);
}


/**
 * if old pwd is present in the env change the current directory to the old
 * else nothing append
 */
int  ft_builtin_cd_old_pwd(t_arr **envp, const char *actual_pwd, int fd_stderr)
{
  int index_old_pwd;
  t_kval *kval;
  int err;
  t_arr *env;

  env = *envp;
  index_old_pwd = ft_arr_indexof(env, "OLDPWD");
  if (index_old_pwd == -1 || index_old_pwd >= (int)env->length)
  {
    ft_putstr_fd("21sh: OLDPWD not present: -\n", fd_stderr);
    return (EXIT_FAILURE);
  }
  kval = *(t_kval **)(
    (unsigned char *)env->ptr + index_old_pwd * env->sizeof_elem);
  if ((err = ft_builtin_cd_change_directory(envp, actual_pwd, kval->value, fd_stderr)))
  {
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}

/**
 *
 */
static int  ft_builtin_cd_path(
  t_arr **env, const char *path, const char *actual_pwd, int fd_stderr)
{
  int err;

  if (!ft_strcmp(path, "-"))
  {
    if ((err = ft_builtin_cd_old_pwd(env, actual_pwd, fd_stderr)))
    {
      return (EXIT_FAILURE);
    }
  }
  else
  {
    if ((err = ft_builtin_cd_change_directory(env, actual_pwd, path, fd_stderr)))
    {
      return (EXIT_FAILURE);
    }
  }
  return (EXIT_SUCCESS);
}

/**
 * change the current path
 * change the current pwd and the old pwd
 */
int  ft_builtin_cd(const char **tab_cmd, t_arr **env, int fd_stderr)
{
  int len_array;
  char *actual_pwd;

  len_array = ft_array_len((const void **)tab_cmd);
  if (len_array > 2)
  {
    ft_putstr_fd("21sh: cd: too many arguments\n", fd_stderr);
    return (EXIT_FAILURE);
  }
  if (!(actual_pwd = ft_strnew(1082)))
  {
    ft_putstr_fd("21sh: error malloc\n", fd_stderr);
    return (EXIT_FAILURE);
  }
  if (!getcwd(actual_pwd, 1082))
  {
    free(actual_pwd);
    ft_putstr_fd("21sh: error malloc\n", fd_stderr);
    return (EXIT_FAILURE);
  }
  if (len_array > 1)
  {
    ft_builtin_cd_path(env, tab_cmd[1], actual_pwd, fd_stderr);
  }
  else
  {
    ft_builtin_cd_path(env, HOME, actual_pwd, fd_stderr);
  }
  free(actual_pwd);
  return (EXIT_SUCCESS);
}
