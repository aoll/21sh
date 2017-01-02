#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/* Pour le type pid_t */
#include <sys/types.h>
/* Pour wait() */
#include <sys/wait.h>
/* Pour perror() et errno */
#include <errno.h>

struct t_tube
{
  int tube[2];
};

/* La fonction create_process duplique le processus appelant et retourne
   le PID du processus fils ainsi créé */
pid_t create_process(void)
{
    /* On crée une nouvelle valeur de type pid_t */
    pid_t pid;

    /* On fork() tant que l'erreur est EAGAIN */
    do {
	pid = fork();
    } while ((pid == -1) && (errno == EAGAIN));

    /* On retourne le PID du processus ainsi créé */
    return pid;
}

/**
 * return a new pointeur to a char **
 */
char  **ft_fork_env_arr_to_tab_str(t_arr *envp)
{
  char **env;
  int index;
  t_kval *kv;
  int i;
  int len;

  if (!envp)
  {
    return (NULL);
  }
  if ((env = malloc(sizeof(char *) * (envp->length + 1))))
  {
    return (NULL);
  }
  env[envp->length] = NULL;
  index = 0;
  while (index < (int)envp->length)
  {
    kv = *(t_kval **)((unsigned char *)envp->ptr + index * envp->sizeof_elem);
    env[index] = ft_strnew(ft_strlen(kv->key) + ft_strlen(kv->value) + 1);
    i = -1;
    len = ft_strlen(kv->key);
    while (++i < len)
    {
      env[index][i] = kv->key[i];
    }
    env[index][i] = '=';
    i = 0;
    len = ft_strlen(kv->value);
    while (++i < len)
    {
      env[index][i] = kv->value[i];
    }
    index++;
  }
  return (env);
}


int  ft_son(char *path_cmd, char **tab_cmd, char **envp)
{

  execve(path_cmd, tab_cmd, envp);

  return (EXIT_SUCCESS);
}

int ft_fork(char **cmd, struct t_tube *tab_tube, int fd, t_arr *env, char *path, int nb_pipe)
{
  int i;
  pid_t pid;
  int status;
  int stdin_copy = dup(0);
  int stdout_copy = dup(1);
  char **tab_path;
  char **tab_cmd;
  int err;
  int index;
  char *path_tmp;
  bool builtin;
  char **envp;
  int tube_fork[2];
  int fd1;
  int fd2;
  char *buff;
  int rd;
  int fd_tmp;
  int fd_tmp2;

  fd1 = open("test1", O_CREAT|O_RDWR|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
  pipe(tube_fork);
  tab_path = ft_strsplit(path, ':');
  i = 0;
  while (i < nb_pipe + 1)
  {
    builtin = false;
    err = 0;
    tab_cmd = ft_strsplit(cmd[i], SPACE_SEPARATOR);
    if (!ft_strcmp("env", tab_cmd[0]) && !tab_cmd[1])
    {
      builtin = true;
    }
    if (!builtin)
    {
      envp = ft_fork_env_arr_to_tab_str(env);
      index = 0;
      path_tmp = ft_strdup(tab_cmd[0]);
      while (tab_path[index] && (err = access(path_tmp, F_OK)) )
      {
        path_tmp = ft_strjoin(tab_path[index], "/");
        path_tmp = ft_strjoin(path_tmp, tab_cmd[0]);
        index++;
      }
    }
    if (err && !builtin)
    {
      ft_putstr("21sh: command not found: ");
      ft_putstr(tab_cmd[0]);
      ft_putstr("\n");
      i++;
      continue;
    }
    if ((pid = create_process()) == -1)
    {
      return (EXIT_FAILURE);
    }
    if (!pid)
    {
      if (i < nb_pipe && !err)
      {
        close(tab_tube[i].tube[0]);
        dup2(tab_tube[i].tube[1], 1);

      }
      if (builtin)
      {
        ft_arr_print(env);
      }
      else if (!err)
      {
        ft_son(path_tmp, tab_cmd, envp);
      }
      exit(EXIT_SUCCESS);
    }
    else if (pid)
    {
      pipe(tube_fork);
      wait(&status);
      if (i < nb_pipe && !err)
      {
        buff = ft_strnew(1);

        close(tab_tube[i].tube[1]);
        while ((rd = read(tab_tube[i].tube[0], buff, 1)) )
        {
          if (rd < 0)
            break;
          write(1, buff, 1);
          write(tube_fork[1], buff, 1);
        }
        ft_putstr("\n------------------------------------------------------\n");
        close(tube_fork[1]);
        dup2(tube_fork[0], 0);

        // close(tab_tube[i].tube[1]);
        //
        // dup2(tab_tube[i].tube[0], 0);
      }
      i++;
    }
  }
  dup2(stdin_copy, 0);
  dup2(stdout_copy, 1);
  close(stdin_copy);
  close(stdout_copy);
  return EXIT_SUCCESS;
}

/**
 * return the number of pipe
 */
int  ft_fork_nb_pipe(t_arr *arr)
{
  int index;
  int nb_pipe;
  char *s_line;

  index = 0;
  nb_pipe = 0;
  while (index < (int)arr->length)
  {
    s_line = *(char **)((unsigned char *)arr->ptr + index * arr->sizeof_elem);
    if (*s_line == PIPE)
    {
      nb_pipe++;
    }
    index++;
  }
  return (nb_pipe);
}

/**
 * return a new string with the element of a t_arr
 */
char*  ft_fork_str_from_arr(t_arr *arr)
{
  char *str;
  int index;
  char *s_line;

  if (!(str = ft_strnew((int)arr->length)))
    return (NULL);
  index = 0;
  while (index < (int)arr->length)
  {
    s_line = *(char **)((unsigned char *)arr->ptr + index * arr->sizeof_elem);
    str[index] = *s_line;
    index++;
  }
  return (str);
}

/**
 * split the command line with the PIPE
 * create a array of tube[2]
 */
int  ft_fork_split_pipe(char *str, int nb_pipe, t_arr *env)
{
  char **cmds;
  struct t_tube *tab_tube;
  int index;
  char *path;
  int index_path;
  t_kval *kval;

  // path = getenv("PATH");
  path = NULL;
  index_path = ft_arr_indexof(env, "PATH");
  if (index_path >= 0 && index_path < (int)env->length)
  {
    kval = *(t_kval **)((unsigned char *)env->ptr + env->sizeof_elem * index_path);
    path = kval->value;
  }
  tab_tube = NULL;
  if (nb_pipe)
  {
    if (!(tab_tube = malloc(sizeof(struct t_tube) * nb_pipe)))
    {
      return (EXIT_FAILURE);
    }
    index = 0;
    while (index < nb_pipe)
    {
      pipe(tab_tube[index].tube);
      index++;
    }
  }

  if (!(cmds = ft_strsplit(str, PIPE)))
  {
    return (EXIT_FAILURE);
  }
  ft_fork(cmds, tab_tube, 0, env, path, nb_pipe);

  return (EXIT_SUCCESS);
}


/**
 * fork
 */
int  ft_fork_test(t_arr *env, t_arr *tab_cmds)
{
  int index;
  t_arr *cmd;
  int nb_pipe;
  char *cmd_str;

  index = 0;
  while (index < (int)tab_cmds->length)
  {

    cmd = *(t_arr **)((unsigned char *)tab_cmds->ptr + index * tab_cmds->sizeof_elem);
    nb_pipe = ft_fork_nb_pipe(cmd);
    cmd_str = ft_fork_str_from_arr(cmd);
    ft_fork_split_pipe(cmd_str, nb_pipe, env);

    index++;
  }
  // ft_putstr("\n");
  return (EXIT_SUCCESS);
}
