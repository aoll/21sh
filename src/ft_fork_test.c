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


int  ft_son(char *path_cmd, char **tab_cmd, char **envp, int i)
{
  // char **tab_cmd = malloc(sizeof(char*) * 2);
  // char **tab_path = malloc(sizeof(char*) * 2);

  execve(path_cmd, tab_cmd, envp);

  // ft_putstr("\n21sh: command not found: ");
  // ft_putstr(tab_cmd[0]);
  // ft_putstr("\n");
  // if (i == 3)
  //   execlp(cmd, cmd, "-e", (char *)0);
  // execlp(cmd, cmd, (char *)0);

  return (EXIT_SUCCESS);
}



int ft_fork(char **cmd, struct t_tube *tab_tube, int fd, char **env, char *path, int nb_pipe)
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

  tab_path = ft_strsplit(path, ':');
  i = 0;
  while (i < nb_pipe + 1)
  {
    err = 0;
    tab_cmd = ft_strsplit(cmd[i], SPACE_SEPARATOR);
    index = 0;
    path_tmp = ft_strdup(tab_cmd[0]);
    while (tab_path[index] && (err = access(path_tmp, F_OK)) )
    {
      path_tmp = ft_strjoin(tab_path[index], "/");
      path_tmp = ft_strjoin(path_tmp, tab_cmd[0]);
      index++;
    }
    if (err)
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
      if (!err)
      {
        ft_son(path_tmp, tab_cmd, env, i);
      }
    }
    else if (pid)
    {
      if (!err)
      {
        if (i < nb_pipe)
        {
          wait(&status);
          close(tab_tube[i].tube[1]);
          dup2(tab_tube[i].tube[0], 0);
        }
        else
        {
          wait(&status);
        }
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
int  ft_fork_split_pipe(char *str, int nb_pipe, char **env)
{
  char **cmds;
  struct t_tube *tab_tube;
  int index;
  char *path;

  path = getenv("PATH");
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
int  ft_fork_test(char **env, t_arr *tab_cmds)
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
