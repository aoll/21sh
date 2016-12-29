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


int  ft_son(char *path, char *cmd, char **envp, int i)
{
  char **tab_cmd = malloc(sizeof(char*) * 2);
  char **tab_path = malloc(sizeof(char*) * 2);
  int index;
  char *path_tmp;

  tab_path = ft_strsplit(path, ':');
  tab_cmd = ft_strsplit(cmd, ' ');
  index = 0;
  while (tab_path[i])
  {
    path_tmp = ft_strjoin(tab_path[index], "/");
    path_tmp = ft_strjoin(path_tmp, tab_cmd[0]);
    if (execve(path_tmp, tab_cmd, envp) != -1)
      break;
    index++;
  }
  // if (i == 3)
  //   execlp(cmd, cmd, "-e", (char *)0);
  // execlp(cmd, cmd, (char *)0);

  return (EXIT_SUCCESS);
}



int ft_fork(char **cmd, struct t_tube tab_tube[], int fd, char **env, char *path)
{
  int i;
  pid_t pid;
  int status;

  i = 0;

  while (i < 1)
  {
    if ((pid = create_process()) == -1)
    {
      return (EXIT_FAILURE);
    }
    if (!pid)
    {
      // if (i < 3)
      // {
      //   close(tab_tube[i].tube[0]);
      //   dup2(tab_tube[i].tube[1], 1);
      // }

      ft_son(path, cmd[i], env, i);
    }
    else if (pid)
    {
      // if (i < 3)
      // {
      //   wait(&status);
      //   close(tab_tube[i].tube[1]);
      //   dup2(tab_tube[i].tube[0], 0);
      // }
      // else
      // {
      //   wait(&status);
      // }
      wait(&status);
      i++;
    }
}




  return EXIT_SUCCESS;
}

/**
 * fork test
 */
int  ft_fork_test_save(char **env, t_arr *tab_cmds)
{
  char **cmd;
  struct t_tube tab_tube[3];
  int fd = 0;
  char *path;

  // fd = open("./toto_fork", O_RDWR | O_APPEND | O_CREAT, 0777);
  path = getenv("PATH");


  pipe(tab_tube[0].tube);
  pipe(tab_tube[1].tube);
  pipe(tab_tube[2].tube);
  cmd = malloc(sizeof(char *) * 4);
  cmd[0] = ft_strdup("ls -l");
  cmd[1] = ft_strdup("wc");
  cmd[2] = ft_strdup("wc");
  cmd[3] = ft_strdup("cat -e");
  cmd[4] = NULL;

  ft_fork(cmd, tab_tube, fd, env, path);
  // while (true)
  // {
  // }

  return (EXIT_SUCCESS);
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
 * fork
 */
int  ft_fork_test(char **env, t_arr *tab_cmds)
{
  int index;
  t_arr *cmd;
  int nb_pipe;
  char *command;

  index = 0;
  while (index < (int)tab_cmds->length)
  {

    cmd = *(t_arr **)((unsigned char *)tab_cmds->ptr + index * tab_cmds->sizeof_elem);
    nb_pipe = ft_fork_nb_pipe(cmd);
    command = ft_fork_str_from_arr(cmd);
    ft_putstr("\nnb_pipe: ");
    ft_putnbr(nb_pipe);
    ft_putstr("\ncmd: ");
    ft_putstr(command);
    ft_putstr("\n");
    index++;
  }
  ft_putstr("\n");
  return (EXIT_SUCCESS);
}
