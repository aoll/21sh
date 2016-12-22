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

  while (i < 4)
  {
    if ((pid = create_process()) == -1)
    {
      return (EXIT_FAILURE);
    }
    if (!pid)
    {
      if (i < 3)
      {
        close(tab_tube[i].tube[0]);
        dup2(tab_tube[i].tube[1], 1);
      }

      ft_son(path, cmd[i], env, i);
    }
    else if (pid)
    {
      if (i < 3)
      {
        wait(&status);
        close(tab_tube[i].tube[1]);
        dup2(tab_tube[i].tube[0], 0);
      }
      else
      {
        wait(&status);
      }
      wait(&status);
      i++;
    }
}




  return EXIT_SUCCESS;
}

/**
 * fork test
 */
int  ft_fork_test(char **env)
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
  cmd[0] = ft_strdup("ls - l");
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
