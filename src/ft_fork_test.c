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

/**
 * return a name file
 */
char  *ft_fork_name_file(char **command, int i)
{
  int index;
  char *name_file;
  char *cmd;

  cmd = *command;
  name_file = NULL;
  while (cmd[i])
  {
    if (cmd[i] != SPACE_SEPARATOR)
    {
      break;
    }
    i++;
  }
  index = i;
  while (cmd[index])
  {
    if (cmd[index] == SPACE_SEPARATOR)
    {
      break;
    }
    index++;
  }
  if (!(name_file = ft_strsub(cmd, i, index - i)))
  {
    return (NULL);
  }
  while (i < index)
  {
    cmd[i] = SPACE_SEPARATOR;
    i++;
  }
  // index--;

  return (name_file);
}

/**
 *  return a case of sucess a fd with the good permission
 * -1 if error like not have the permission
 */
int  *ft_fork_fd(char *name_file, int token)
{
  int fd;
  int *fd_ptr;

  fd = -1;
  fd_ptr = malloc(sizeof(int));
  *fd_ptr = -1;
  if (token == S_RIGHT_REDIRECT || token == STDIN_STDERR_REDIRECT || token == STDERR_REDIRECT)
  {
    if (*name_file == FILE_REDIRECT)
    {
      fd = ft_atoi(name_file + 1);

    }
    else
    {
      fd = open(name_file, O_CREAT|O_RDWR|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
    }
  }
  else if (token == D_RIGHT_REDIRECT || token == D_STDERR_REDIRECT)
  {
    if (*name_file == FILE_REDIRECT)
    {
      fd = ft_atoi(name_file + 1);
    }
    else
    {
      fd = open(name_file, O_CREAT|O_RDWR|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
    }
  }
  if (fd == -1)
  {
    free(fd_ptr);
    fd_ptr = NULL;
  }
  if (fd == 1 || fd == 2)
  {
    fd *= -1;
  }
  *fd_ptr = fd;
  return (fd_ptr);
}

/**
 * in case in sucess return EXIT_SUCCESS else EXIT_FAILURE
 * give a list of fd with good right and position cursor
 * error if the file can be open
 */
int  ft_fork_list_fd(char **command, t_arr *tab_fd_stdin, t_arr *tab_fd_stderr)
{
  char *name_file;
  int i;
  int *fd;
  char *cmd;
  int *fd_err;
  int index;
  int *fd_tmp;
  int *fd_dup;

  i = 0;
  cmd = *command;
  while (tab_fd_stdin->length)
  {
    fd = *(int **)(ft_arr_pop(&tab_fd_stdin, 0));
    close(*fd);
    free(fd);
  }
  while (tab_fd_stderr->length)
  {
    fd = *(int **)(ft_arr_pop(&tab_fd_stderr, 0));
    close(*fd);
    free(fd);
  }
  while (cmd[i])
  {
    if (cmd[i] == S_RIGHT_REDIRECT || cmd[i] == D_RIGHT_REDIRECT || cmd[i] == STDIN_STDERR_REDIRECT || cmd[i] == STDERR_REDIRECT || cmd[i] == D_STDERR_REDIRECT)
    {

      if (!(name_file = ft_fork_name_file(&cmd, i + 1)))
      {

        return (EXIT_FAILURE);
      }
      fd = ft_fork_fd(name_file, cmd[i]);
      if (fd == NULL)
      {
        cmd[i] = SPACE_SEPARATOR;
        ft_putstr("\n21sh: permission denied: ");
        ft_putstr(name_file);
        ft_putstr("\n");
        free(name_file);
        i = 0;
        while (tab_fd_stdin->length)
        {
          fd = *(int **)(ft_arr_pop(&tab_fd_stdin, 0));
          close(*fd);
          free(fd);
        }
        while (tab_fd_stderr->length)
        {
          fd = *(int **)(ft_arr_pop(&tab_fd_stderr, 0));
          close(*fd);
          free(fd);
        }
        return (EXIT_FAILURE);
      }
      free(name_file);
      index = 0;
      if (*fd == -2)
      {
        while (index < (int)tab_fd_stderr->length)
        {
          fd_tmp = *(int **)((unsigned char *)tab_fd_stderr->ptr + index * tab_fd_stderr->sizeof_elem);
          if (!(fd_dup = malloc(sizeof(int))))
          {
            return (EXIT_FAILURE);
          }
          *fd_dup = *fd_tmp;
          ft_arr_push(&tab_fd_stdin, fd_dup, -1);
          index++;
        }
      }
      else if (*fd == -1)
      {
        while (index < (int)tab_fd_stdin->length)
        {
          fd_tmp = *(int **)((unsigned char *)tab_fd_stdin->ptr + index * tab_fd_stdin->sizeof_elem);
          if (!(fd_dup = malloc(sizeof(int))))
          {
            return (EXIT_FAILURE);
          }
          *fd_dup = *fd_tmp;
          ft_arr_push(&tab_fd_stderr, fd_dup, -1);
          index++;
        }
      }
      else if (cmd[i] == STDIN_STDERR_REDIRECT || cmd[i] == STDERR_REDIRECT || cmd[i] == D_STDERR_REDIRECT)
      {
        ft_arr_push(&tab_fd_stderr, fd, -1);
        if (cmd[i] == STDIN_STDERR_REDIRECT)
        {
          fd_err = malloc(sizeof(int));
          *fd_err = *fd;
          ft_arr_push(&tab_fd_stdin, fd_err, -1);
        }
      }
      else if (cmd[i] == S_RIGHT_REDIRECT || cmd[i] == D_RIGHT_REDIRECT)
      {
        ft_arr_push(&tab_fd_stdin, fd, -1);
      }
      cmd[i] = SPACE_SEPARATOR;
    }
    i++;
  }
  // i = 0;
  // while (i < (int)tab_fd_stdin->length)
  // {
  //   fd = *(int **)((unsigned char *)tab_fd_stdin->ptr + i * tab_fd_stdin->sizeof_elem);
  //   // ft_putstr("\nfdp: ");
  //   // ft_putnbr(*fd);
  //   // ft_putstr("\n");
  //   i++;
  // }
  return (EXIT_SUCCESS);
}

/**
 * write on a list of fd
 */
int  ft_fork_write_list_fd(t_arr *arr, char *buff, int len)
{
  int index;
  int *fd;

  index = 0;
  while (index < (int)arr->length)
  {
    fd = *(int **)((unsigned char *)arr->ptr + index * arr->sizeof_elem);
    write(*fd, buff, len);
    index++;
  }
  return (EXIT_SUCCESS);
}

int ft_fork(char **cmd, struct t_tube *tab_tube, t_arr *env, char *path, int nb_pipe)
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
  int tube_fork_stdin_tmp[2];
  int tube_fork_stderr_tmp[2];
  int tube_fork_stdin[2];
  int tube_fork_stderr[2];
  char *buff;
  int rd;
  int fd_tmp;
  int fd_tmp2;
  t_arr *tab_fd_stdin;
  t_arr *tab_fd_stderr;
  int *fd;
  int len_stdin;
  int len_stderr;


  tab_fd_stdin = ft_arr_new(1, sizeof(int *));
  tab_fd_stderr = ft_arr_new(1, sizeof(int *));
  tab_path = ft_strsplit(path, ':');
  i = 0;
  // ft_putstr("\ncmd:");
  // ft_putstr(cmd[i]);
  // ft_putstr(";\n");
  // return(1);
  while (i < nb_pipe + 1)
  {
    if (i)
    {
      close(tube_fork_stdin[0]);
      close(tube_fork_stdin[1]);
      close(tube_fork_stderr[0]);
      close(tube_fork_stderr[1]);
      close(tube_fork_stdin_tmp[0]);
      close(tube_fork_stdin_tmp[1]);
      close(tube_fork_stderr_tmp[0]);
      close(tube_fork_stderr_tmp[1]);
    }
    pipe(tube_fork_stdin);
    pipe(tube_fork_stderr);
    pipe(tube_fork_stdin_tmp);
    pipe(tube_fork_stderr_tmp);
    builtin = false;
    err = 0;
    if ((err = ft_fork_list_fd(&cmd[i], tab_fd_stdin, tab_fd_stderr) ))
    {
      return (EXIT_FAILURE);
    }

    if (!(tab_cmd = ft_strsplit(cmd[i], SPACE_SEPARATOR)) && !tab_cmd[1])
    {
      break;
      // return (EXIT_FAILURE);
    }
    if (!ft_strcmp("env", tab_cmd[0]))
    {
      builtin = true;
    }
    if (!builtin && *tab_cmd)
    {
      // TODO segfault si !tab_cmd[0]
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
      // if (i < nb_pipe && !err)
      // {
        // close(tab_tube[i].tube[0]);
        // dup2(tab_tube[i].tube[1], 1);

      close(tube_fork_stdin_tmp[0]);
      dup2(tube_fork_stdin_tmp[1], 1);

      close(tube_fork_stderr_tmp[0]);
      dup2(tube_fork_stderr_tmp[1], 2);


      // }
      if (builtin)
      {
        ft_arr_print(env);
      }
      else if (!err && *tab_cmd)
      {
        ft_son(path_tmp, tab_cmd, envp);
      }
      exit(EXIT_SUCCESS);
    }
    else if (pid)
    {

      wait(&status);



      close(tube_fork_stdin_tmp[1]);
      close(tube_fork_stderr_tmp[1]);
      buff = ft_strnew(1);
      len_stdin = 0;
      while ((rd = read(tube_fork_stdin_tmp[0], buff, 1)))
      {
        if (rd < 0)
          break;
        write(tube_fork_stdin[1], buff, 1);
        len_stdin++;
      }
      len_stderr = 0;
      while ((rd = read(tube_fork_stderr_tmp[0], buff, 1)))
      {
        if (rd < 0)
          break;
        write(tube_fork_stderr[1], buff, 1);
        len_stderr++;
      }





      if (buff)
      {
        free(buff);
      }
      buff = ft_strnew(len_stdin);
      close(tube_fork_stderr[1]);
      close(tube_fork_stdin[1]);
      while ((rd = read(tube_fork_stdin[0], buff, len_stdin)))
      {
        if (rd < 0)
          break;
        if (i < nb_pipe && !err)
        {
          write(tab_tube[i].tube[1], buff, len_stdin);
        }
        if (tab_fd_stdin->length)
        {
          ft_fork_write_list_fd(tab_fd_stdin, buff, len_stdin);
        }

        if (!tab_fd_stdin->length && i >= nb_pipe)
        {
          write(1, buff, len_stdin);
        }
      }

      if (buff)
      {
        free(buff);
      }
      buff = ft_strnew(len_stderr);
      while ((rd = read(tube_fork_stderr[0], buff, len_stderr)) )
      {
        if (rd < 0)
          break;

        if (tab_fd_stderr->length)
        {
          ft_fork_write_list_fd(tab_fd_stderr, buff, len_stderr);
        }
        else if (!tab_fd_stderr->length)
        {
          write(2, buff, len_stderr);
        }
      }
      if (buff)
      {
        free(buff);
      }

      if (i < nb_pipe && !err)
      {
        close(tab_tube[i].tube[1]);
        dup2(tab_tube[i].tube[0], 0);
      }




      while (tab_fd_stdin->length)
      {
        fd = (int *)(ft_arr_pop(&tab_fd_stdin, 0));
        close(*fd);
        free(fd);
      }
      while (tab_fd_stderr->length)
      {
        fd = (int *)(ft_arr_pop(&tab_fd_stderr, 0));
        close(*fd);
        free(fd);
      }

      /* enabled */
      // close(tube_fork_stdin[0]);
      // pipe(tube_fork_stdin);
      // wait(&status);
      // if (i < nb_pipe && !err)
      // {
      //   buff = ft_strnew(1);
      //
      //   close(tab_tube[i].tube[1]);
      //   while ((rd = read(tab_tube[i].tube[0], buff, 1)) )
      //   {
      //     if (rd < 0)
      //       break;
      //     write(1, buff, 1);
      //     ft_fork_write_list_fd(tab_fd_stdin, buff);
      //     write(tube_fork_stdin[1], buff, 1);
      //   }
      //   ft_putstr("\n------------------------------------------------------\n");
      //   close(tube_fork_stdin[1]);
      //   dup2(tube_fork_stdin[0], 0);

        // close(tab_tube[i].tube[1]);
        //
        // dup2(tab_tube[i].tube[0], 0);
      // }
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
  ft_fork(cmds, tab_tube, env, path, nb_pipe);

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
