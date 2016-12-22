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


int  ft_son(char *cmd, int tube[], int i)
{

// else
// {
//   close(tube[1]);
//   dup2(tube[0], 0);
// }


  // else
  // {
  //   close(tube[1]);
  //   dup2(tube[0], 0);
  // }
  ft_putstr("son\n");

  execlp(cmd, cmd, (char *)0);

  return (EXIT_SUCCESS);
}

int  ft_pere(char *cmd, int tube[], int i)
{
  int status;

  // int i;
  pid_t pid;
  // int tube[2];


  wait(&status);
  close(tube[1]);
  dup2(tube[0], 0);

  pid = fork();
  if (!pid)
    execlp(cmd, cmd, (char *)0);
  if (pid)
    wait(&status);


  return (EXIT_SUCCESS);
}


int ft_fork(char **cmd, struct t_tube tab_tube[])
{
  int i;
  pid_t pid;
  int status;

  ft_putstr("fork\n");
  i = 0;
  while (i < 2)
  {
    if ((pid = create_process()) == -1)
    {
      return (EXIT_FAILURE);
    }
    if (!pid)
    {
      if (!i) {

      close(tab_tube[0].tube[0]);
      dup2(tab_tube[0].tube[1], 1);
    }
      ft_son(cmd[i], tab_tube[0].tube, i);
    }
    else if (pid)
    {
      if (!i)
      {
        wait(&status);
        close(tab_tube[0].tube[1]);
        dup2(tab_tube[0].tube[0], 0);
      }
      else
      {
        wait(&status);

      }
      i++;
      // ft_pere(cmd[1], tube, i);
    }
}




  return EXIT_SUCCESS;
}

/**
 * fork test
 */
int  ft_fork_test()
{
  char **cmd;
  struct t_tube tab_tube[2];



  // pipe(tube);
  pipe(tab_tube[0].tube);
  pipe(tab_tube[1].tube);
  cmd = malloc(sizeof(char *) * 4);
  cmd[0] = ft_strdup("ls");
  cmd[1] = ft_strdup("wc");
  cmd[2] = ft_strdup("wc");
  cmd[3] = NULL;

  ft_fork(cmd, tab_tube);
  while (true)
  {
  }

  return (EXIT_SUCCESS);
}
