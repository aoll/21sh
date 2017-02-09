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


int  ft_fork_son_exec(char *path_cmd, char **tab_cmd, char **envp)
{
  execve(path_cmd, tab_cmd, envp);
  return (EXIT_SUCCESS);
}









int ft_fork(char **cmd, t_tube *tab_tube, t_arr **env, int nb_pipe)
{
  t_tab_tube array_tube;
  t_arr_fd arr_fd;
  t_fork st_fork;

  st_fork.env_copy = NULL;
  st_fork.tab_cmd = NULL;
  st_fork.envp = NULL;
  st_fork.error_ptr = NULL;
  st_fork.env = env;
  st_fork.stdin_copy = dup(STDIN);
  st_fork.stdout_copy = dup(STDOUT);
  st_fork.stderr_copy = dup(STDERR);
  /* init loop */
  if ((st_fork.err = ft_fork_init_loop(
    &st_fork, &arr_fd, (const char **)cmd, nb_pipe)))
  {
    return (EXIT_FAILURE);
  }
  /* end */
  while (st_fork.i < st_fork.nb_pipe + 1)
  {
    if ((st_fork.err = ft_fork_set_tube_fd(
      &st_fork, &array_tube, &arr_fd, &cmd[st_fork.i])))
    {
      return (EXIT_FAILURE);
    }
    /* end */
    /* free st_fork.tab_cmd  and init it*/
    ft_array_free(&st_fork.tab_cmd);
    if (!(st_fork.tab_cmd = ft_strsplit(cmd[st_fork.i], SPACE_SEPARATOR)))
    {
      break;
    }
    if (!st_fork.tab_cmd[0])
    {
      break;
    }
    /* end */

    /*check if cmd is a builtin */
    // if (ft_is_builtin(st_fork.tab_cmd[0]))
    if (ft_fork_check_is_builtin_exit(&st_fork, &arr_fd) == B_EXIT)
    {
      return (B_EXIT);
    }

    /* end */

    /* dup t_arr *env */
    if (st_fork.env_copy)
    {
      ft_arr_free(st_fork.env_copy);
      st_fork.env_copy = NULL;
    }

    st_fork.env_copy = ft_arr_dup(*env);
    /* end */

    /* if B_ENV set the copy of th env */
    if (st_fork.index_builtin == B_ENV)
    {
      st_fork.index_builtin = ft_builtin_env(
        &st_fork.tab_cmd,
        &st_fork.env_copy,
        array_tube.tube_fork_stdout_tmp[1],
        array_tube.tube_fork_stderr_tmp[1]);
    }
    /* end */

    /* create a char *env with the seted copy t_arr *st_fork.env_copy*/
    ft_array_free(&st_fork.envp);
    ft_fork_env_arr_to_tab_str(st_fork.env_copy, &st_fork.envp);
    /*end */

    /* create_process */
    if ((st_fork.err = ft_fork_create_process(
      &st_fork, &arr_fd, &array_tube, tab_tube)))
    {
      return (EXIT_FAILURE);
    }
  }
  /*retablie les flux*/
  dup2(st_fork.stdin_copy, STDIN);
  dup2(st_fork.stdout_copy, STDOUT);
  dup2(st_fork.stderr_copy, STDERR);
  close(st_fork.stdin_copy);
  close(st_fork.stdout_copy);
  close(st_fork.stderr_copy);
  /*end*/
  /*free st_fork.env_copy*/
  if (st_fork.env_copy)
  {
    ft_arr_free(st_fork.env_copy);
    st_fork.env_copy = NULL;
  }
  /*end*/
  ft_arr_close_arr_fd(&arr_fd); //?
  /*free arr_fd*/
  ft_arr_free_arr_fd(&arr_fd);
  /*end*/
  /*free array*/
  ft_array_free(&st_fork.envp);
  /*end */
  /*free array*/
  ft_array_free(&st_fork.tab_cmd);
  /*end*/
  /*free str*/

  ft_str_free(&st_fork.error_ptr);
  /*end*/
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
int  ft_fork_split_pipe(char *str, int nb_pipe, t_arr **env_ptr)
{
  char **cmds;
  t_tube *tab_tube;
  int index;
  int index_path;
  t_kval *kval;
  t_arr *env;
  int j;
  int i_return;

  env = *env_ptr;
  tab_tube = NULL;
  if (nb_pipe)
  {
    if (!(tab_tube = malloc(sizeof(t_tube) * nb_pipe)))
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
    free(tab_tube);
    return (EXIT_FAILURE);
  }
  i_return = ft_fork(cmds, tab_tube, env_ptr, nb_pipe);
  j = 0;
  while (cmds[j])
  {
    free(cmds[j]);
    j++;
  }
  free(cmds);
  free(tab_tube);
  return (i_return);
}


/**
 * fork
 */
int  ft_fork_test(t_arr **env, t_arr *tab_cmds)
{
  int index;
  t_arr *cmd;
  int nb_pipe;
  char *cmd_str;
  int i_return;

  index = 0;
  cmd_str = NULL;
  while (index < (int)tab_cmds->length)
  {

    cmd = *(t_arr **)((unsigned char *)tab_cmds->ptr + index * tab_cmds->sizeof_elem);
    nb_pipe = ft_fork_nb_pipe(cmd);
    cmd_str = ft_fork_str_from_arr(cmd);
    i_return = ft_fork_split_pipe(cmd_str, nb_pipe, env);
    if (cmd_str)
    {
      free(cmd_str);
      cmd_str = NULL;
    }
    if (i_return == B_EXIT)
    {
      return (i_return);
    }
    index++;
  }
  return (EXIT_SUCCESS);
}
