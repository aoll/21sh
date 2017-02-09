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


int  ft_son(char *path_cmd, char **tab_cmd, char **envp)
{
  execve(path_cmd, tab_cmd, envp);
  return (EXIT_SUCCESS);
}









int ft_fork(char **cmd, t_tube *tab_tube, t_arr **env, int nb_pipe)
{
  // int st_fork.i;
  pid_t pid;
  int status;
  int stdin_copy = dup(0);
  int stdout_copy = dup(1);
  // int st_fork.st_fork.err;
  int index;
  int index_builtin;

  t_tab_tube array_tube;


  t_arr_fd arr_fd;

  int *fd;
  int len_stdout;
  int len_stderr = 0;
  int index_end_word;
  int index_path;
  t_kval *kval;
  t_arr *env_ptr;
  int i_free;
  char *path_tmp;
  char *path_tmp_ptr;
  char *buff;
  char *line;
  char *end_word;
  char *path_ptr;

  char **envp;
  char **tab_cmd;
  char **tab_path;
  t_arr *env_copy;
  char **cmd_tmp;
  char *error_ptr;

  int err_fd;

  t_fork st_fork;

  env_copy = NULL;

  path_tmp = NULL;
  path_tmp_ptr = NULL;
  buff = NULL;
  line = NULL;
  path_ptr = NULL;
  end_word = NULL;

  tab_cmd = NULL;
  tab_path = NULL;
  envp = NULL;
  /* init arr_fd */
//
  st_fork.nb_pipe = nb_pipe;
  if ((st_fork.err = ft_fork_init_arr_fd(&arr_fd)))
  {
    return (EXIT_FAILURE);
  }
  /* end */
  st_fork.i = 0;
  err_fd = 0;
  cmd_tmp = NULL;
  error_ptr = NULL;
  /* open file for all pipe */
  cmd_tmp = ft_array_str_dup((const char **)cmd);
  err_fd = ft_fork_list_fd_tmp(cmd_tmp, &arr_fd, &error_ptr);
  ft_str_free(&error_ptr);
  ft_array_free(&cmd_tmp);

  /* end */
  while (st_fork.i < st_fork.nb_pipe + 1)
  {
    /* close tube_tmp */
    if (st_fork.i)
    {
      ft_fork_close_array_tube(&array_tube);
    }
    /* end */
    /*pipe tmp */
    ft_fork_pipe_array_tube(&array_tube);

    /* end */
    index_builtin = false;
    st_fork.err = 0;

    /* check error for open file */
    ft_str_free(&error_ptr);
    st_fork.err = ft_fork_list_fd(&cmd[st_fork.i], &arr_fd, &error_ptr);
    /* end */
    /* init arr_fd.arr_d_end_word */
    if ((st_fork.err = ft_fork_list_d_end_word(&cmd[st_fork.i], arr_fd.arr_d_end_word) ))
    {
      return (EXIT_FAILURE);
    }
    /* end */
    /* free tab_cmd  and init it*/
    ft_array_free(&tab_cmd);
    if (!(tab_cmd = ft_strsplit(cmd[st_fork.i], SPACE_SEPARATOR)))
    {
      break;
    }
    if (!tab_cmd[0])
    {
      break;
    }
    /* end */

    /*check if cmd is a builtin */
    // if (ft_is_builtin(tab_cmd[0]))
    if ((index_builtin = ft_is_builtin(tab_cmd[0])))
    {
      if (index_builtin == B_EXIT)
      {
        if (env_copy)
        {
          ft_arr_free(env_copy);
          env_copy = NULL;
        }
        ft_array_free(&envp);
        ft_arr_free_arr_fd(&arr_fd);
        ft_array_free(&tab_cmd);
        return (B_EXIT);
      }
    }
    /* end */
    pid = 0;

    /* dup t_arr *env */
    if (env_copy)
    {
      ft_arr_free(env_copy);
      env_copy = NULL;
    }

    env_copy = ft_arr_dup(*env);
    /* end */

    /* if B_ENV set the copy of th env */
    if (index_builtin == B_ENV)
    {
      index_builtin = ft_builtin_env(&tab_cmd, &env_copy, array_tube.tube_fork_stdout_tmp[1], array_tube.tube_fork_stderr_tmp[1]);
    }
    /* end */

    /* create a char *env with the seted copy t_arr *env_copy*/
    ft_array_free(&envp);
    ft_fork_env_arr_to_tab_str(env_copy, &envp);
    /*end */

    /* create_process */
    if ((pid = create_process()) == -1)
    {
      return (EXIT_FAILURE);
    }
    /*end */
    if (!pid)
    {
      /* son */
      /* case read file */
      ft_fork_set_tube(&arr_fd, &array_tube, st_fork.i, st_fork.nb_pipe);
      /* end */
      /*case error open file */
      ft_fork_is_error_ptr(&error_ptr, &arr_fd);
      /* end */

      path_tmp = NULL;
      /* case not index_builtin && *tab_cmd */
      if (!index_builtin && *tab_cmd)
      {
        path_tmp = ft_fork_init_path(env_copy, tab_cmd, &st_fork.err);
      }
      /*end */

      /* exec */
      if (!index_builtin && !st_fork.err && *tab_cmd)
      {
        ft_son(path_tmp, tab_cmd, envp);
      }
      /*end */

      /* case cmd not found or builtin */
      ft_fork_command_not_found(&tab_cmd, index_builtin, &arr_fd);
      /*end */
      exit(EXIT_SUCCESS);
      /* end son */
    }
    else if (pid)
    {
      /* father */

      /* case arr_fd_stdin to read file or STDIN */
      if (arr_fd.arr_fd_stdin->length)
      {

        /* st_fork.nb_pipe */
        ft_fork_write_tube_stdin(tab_tube, &array_tube, st_fork.i, st_fork.nb_pipe);
        /* end */
        /* read the list of file or the STDIN */
        ft_fork_read_stdin_file(&arr_fd, &array_tube);
        //ft_fork_read_stdin_file()
        /* end */
        ft_str_free(&buff);
        close(array_tube.tube_fork_stdin[1]);
      }

      /*end */

      /*builtin*/
      if (index_builtin > B_ENV)
      {
        ft_builtin_exec(index_builtin, tab_cmd, env, array_tube.tube_fork_stdout_tmp[1], array_tube.tube_fork_stderr_tmp[1]);
      }
      /*end*/
      wait(&status);



      close(array_tube.tube_fork_stdout_tmp[1]);
      close(array_tube.tube_fork_stderr_tmp[1]);

      /* write on tab_tube STDIN && SDTERR */
      // une fonction pour les deux renvoyant un int
      st_fork.len_stdout = ft_fork_write_tube(array_tube.tube_fork_stdout[1], array_tube.tube_fork_stdout_tmp[0]);
      st_fork.len_stderr = ft_fork_write_tube(array_tube.tube_fork_stderr[1], array_tube.tube_fork_stderr_tmp[0]);

      /*end*/


      close(array_tube.tube_fork_stderr[1]);
      close(array_tube.tube_fork_stdout[1]);

      ft_fork_write_fd_stdout(&array_tube, tab_tube, &arr_fd, &st_fork);
      ft_fork_write_fd_stderr(&array_tube, &arr_fd, &st_fork);

      if (st_fork.i < st_fork.nb_pipe && !st_fork.err)
      {
        close(tab_tube[st_fork.i].tube[1]);
        dup2(tab_tube[st_fork.i].tube[0], 0);
      }



      ft_arr_close_arr_fd(&arr_fd);

      /*free arr->ptr*/
      while (arr_fd.arr_d_end_word->length)
      {
        free(ft_arr_pop(arr_fd.arr_d_end_word, 0));
      }
      /*end*/
      /*end */
      st_fork.i++;

    }

  }
  /*retablie les flux*/
  dup2(stdin_copy, 0);
  dup2(stdout_copy, 1);
  close(stdin_copy);
  close(stdout_copy);
  /*end*/
  /*free env_copy*/
  if (env_copy)
  {
    ft_arr_free(env_copy);
    env_copy = NULL;
  }
  /*end*/
  ft_arr_close_arr_fd(&arr_fd); //?
  /*free arr_fd*/
  ft_arr_free_arr_fd(&arr_fd);
  /*end*/
  /*free array*/
  ft_array_free(&envp);
  /*end */

  /*free array*/
  ft_array_free(&tab_cmd);
  ft_array_free(&tab_path);
  /*end*/
  /*free str*/
  ft_str_free(&path_tmp);
  ft_str_free(&path_tmp_ptr);
  ft_str_free(&buff);
  ft_str_free(&line);
  ft_str_free(&path_ptr);
  ft_str_free(&end_word);
  ft_str_free(&error_ptr);
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
