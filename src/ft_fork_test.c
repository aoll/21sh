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
int  ft_fork_env_arr_to_tab_str(t_arr *envp, char ***env_ptr)
{
  char **env;
  int index;
  t_kval *kv;
  int i;
  int index_i;
  int len;

  env = *env_ptr;
  if (!envp)
  {
    return (EXIT_FAILURE);
  }

  if (!(env = malloc(sizeof(char *) * (envp->length + 1))))
  {
    return (EXIT_FAILURE);
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
    i++;
    index_i = -1;
    len = ft_strlen(kv->value);
    while (++index_i <len)
    {
      env[index][i] = kv->value[index_i];
      i++;
    }
    index++;
  }
  *env_ptr = env;
  return (EXIT_SUCCESS);
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
  if (!(fd_ptr = malloc(sizeof(int))))
  {
    return (NULL);
  }
  *fd_ptr = -1;
  if (token == S_RIGHT_REDIRECT || token == STDOUT_STDERR_REDIRECT || token == STDERR_REDIRECT)
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
  else if (token == S_LEFT_REDIRECT)
  {
    if (*name_file == FILE_REDIRECT)
    {
      fd = ft_atoi(name_file + 1);
    }
    else
    {
      fd = open(name_file, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
    }
  }
  if (fd == -1)
  {
    free(fd_ptr);
    fd_ptr = NULL;
    return (NULL);
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
int  ft_fork_list_fd(char **command, t_arr *tab_fd_stdout, t_arr *tab_fd_stderr, t_arr *tab_fd_stdin)
{
  char *name_file;
  int i;
  int *fd;
  char *cmd;
  int *fd_err;
  int index;
  int *fd_tmp;
  int *fd_dup;
  struct stat buf;

  i = 0;
  cmd = *command;
  while (tab_fd_stdout->length)
  {
    fd = *(int **)(ft_arr_pop(&tab_fd_stdout, 0));
    if (*fd >= 0)
    {
      close(*fd);
    }
    free(fd);
  }
  while (tab_fd_stderr->length)
  {
    fd = *(int **)(ft_arr_pop(&tab_fd_stderr, 0));
    if (*fd >= 0)
    {
      close(*fd);
    }
    free(fd);
  }
  while (tab_fd_stdin->length)
  {
    fd = *(int **)(ft_arr_pop(&tab_fd_stdin, 0));
    if (*fd >= 0)
    {
      close(*fd);
    }
    free(fd);
  }
  while (cmd[i])
  {
    if (cmd[i] == D_LEFT_REDIRECT)
    {
      if (!(fd_dup = malloc(sizeof(int))))
      {
        return (EXIT_FAILURE);
      }
      *fd_dup = D_LEFT_REDIRECT;
      ft_arr_push(&tab_fd_stdin, fd_dup, -1);
    }
    else if (cmd[i] == S_RIGHT_REDIRECT || cmd[i] == D_RIGHT_REDIRECT || cmd[i] == STDOUT_STDERR_REDIRECT || cmd[i] == STDERR_REDIRECT || cmd[i] == D_STDERR_REDIRECT || cmd[i] == S_LEFT_REDIRECT)
    {

      if (!(name_file = ft_fork_name_file(&cmd, i + 1)))
      {

        return (EXIT_FAILURE);
      }
      fd = ft_fork_fd(name_file, cmd[i]);
      if (fd == NULL)
      {
        cmd[i] = SPACE_SEPARATOR;
        lstat(name_file, &buf);
        if (S_ISDIR(buf.st_mode))
        {
          ft_putstr("21sh: it is a directory: ");
        }
        else
        {
          ft_putstr("21sh: permission denied: ");
        }
        ft_putstr(name_file);
        ft_putstr("\n");
        free(name_file);
        i = 0;
        while (tab_fd_stdout->length)
        {
          fd = *(int **)(ft_arr_pop(&tab_fd_stdout, 0));
          if (*fd >= 0)
          {
            close(*fd);
          }
          free(fd);
        }
        while (tab_fd_stderr->length)
        {
          fd = *(int **)(ft_arr_pop(&tab_fd_stderr, 0));
          if (*fd >= 0)
          {
            close(*fd);
          }
          free(fd);
        }
        while (tab_fd_stdin->length)
        {
          fd = *(int **)(ft_arr_pop(&tab_fd_stdin, 0));
          if (*fd >= 0)
          {
            close(*fd);
          }
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
          ft_arr_push(&tab_fd_stdout, fd_dup, -1);
          index++;
        }
      }
      else if (*fd == -1)
      {
        while (index < (int)tab_fd_stdout->length)
        {
          fd_tmp = *(int **)((unsigned char *)tab_fd_stdout->ptr + index * tab_fd_stdout->sizeof_elem);
          if (!(fd_dup = malloc(sizeof(int))))
          {
            return (EXIT_FAILURE);
          }
          *fd_dup = *fd_tmp;
          ft_arr_push(&tab_fd_stderr, fd_dup, -1);
          index++;
        }
      }
      else if (cmd[i] == STDOUT_STDERR_REDIRECT || cmd[i] == STDERR_REDIRECT || cmd[i] == D_STDERR_REDIRECT)
      {
        ft_arr_push(&tab_fd_stderr, fd, -1);
        if (cmd[i] == STDOUT_STDERR_REDIRECT)
        {
          fd_err = malloc(sizeof(int));
          *fd_err = *fd;
          ft_arr_push(&tab_fd_stdout, fd_err, -1);
        }
      }
      else if (cmd[i] == S_RIGHT_REDIRECT || cmd[i] == D_RIGHT_REDIRECT)
      {
        ft_arr_push(&tab_fd_stdout, fd, -1);
      }
      else if (cmd[i] == S_LEFT_REDIRECT)
      {
        ft_arr_push(&tab_fd_stdin, fd, -1);
      }
      cmd[i] = SPACE_SEPARATOR;
    }
    i++;
  }
  // i = 0;
  // while (i < (int)tab_fd_stdout->length)
  // {
  //   fd = *(int **)((unsigned char *)tab_fd_stdout->ptr + i * tab_fd_stdout->sizeof_elem);
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

/**
 * if some D_LEFT_REDIRECT are present push in tab_d_end_word the string present
 * for finish the read
 */
int  ft_fork_list_d_end_word(char **command, t_arr *tab_d_end_word)
{
  int i;
  char *end_word;
  char *cmd;

  i = 0;
  cmd = *command;
  while (tab_d_end_word->length)
  {
    free(ft_arr_pop(&tab_d_end_word, 0));
  }

  while (cmd[i])
  {
    if (cmd[i] == D_LEFT_REDIRECT)
    {
      if (!(end_word = ft_fork_name_file(&cmd, i + 1)))
      {
        return (EXIT_FAILURE);
      }
      ft_arr_push(&tab_d_end_word, end_word, -1);
      cmd[i] = SPACE_SEPARATOR;
    }
    i++;
  }
  return (EXIT_SUCCESS);
}

int ft_fork(char **cmd, struct t_tube *tab_tube, t_arr **env, int nb_pipe)
{
  int i;
  pid_t pid;
  int status;
  int stdin_copy = dup(0);
  int stdout_copy = dup(1);
  int err;
  int index;
  int index_builtin;
  int tube_fork_stdout_tmp[2];
  int tube_fork_stderr_tmp[2];
  int tube_fork_stdout[2];
  int tube_fork_stderr[2];
  int tube_fork_stdin[2];
  int rd;
  int fd_tmp;
  int fd_tmp2;
  t_arr *tab_fd_stdout;
  t_arr *tab_fd_stderr;
  t_arr *tab_fd_stdin;
  int *fd;
  int len_stdin;
  int len_stderr;
  t_arr *tab_d_end_word;
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
  tab_d_end_word = ft_arr_new(1, sizeof(char *));
  tab_fd_stdout = ft_arr_new(1, sizeof(int *));
  tab_fd_stderr = ft_arr_new(1, sizeof(int *));
  tab_fd_stdin = ft_arr_new(1, sizeof(int *));
  i = 0;
  while (i < nb_pipe + 1)
  {
    if (i)
    {
      close(tube_fork_stdout[0]);
      close(tube_fork_stdout[1]);
      close(tube_fork_stderr[0]);
      close(tube_fork_stderr[1]);
      close(tube_fork_stdout_tmp[0]);
      close(tube_fork_stdout_tmp[1]);
      close(tube_fork_stderr_tmp[0]);
      close(tube_fork_stderr_tmp[1]);
      close(tube_fork_stdin[0]);
      close(tube_fork_stdin[1]);
    }
    pipe(tube_fork_stdin);
    pipe(tube_fork_stdout);
    pipe(tube_fork_stderr);
    pipe(tube_fork_stdout_tmp);
    pipe(tube_fork_stderr_tmp);
    index_builtin = false;
    err = 0;
    if ((err = ft_fork_list_fd(&cmd[i], tab_fd_stdout, tab_fd_stderr, tab_fd_stdin) ))
    {
      return (EXIT_FAILURE);
    }
    if ((err = ft_fork_list_d_end_word(&cmd[i], tab_d_end_word) ))
    {
      return (EXIT_FAILURE);
    }
    if (tab_cmd)
    {
      i_free = 0;
      while (tab_cmd[i_free])
      {
        if (tab_cmd[i_free])
        {
          free(tab_cmd[i_free]);
          tab_cmd[i_free] = NULL;
        }
        i_free++;
      }
      free(tab_cmd);
      tab_cmd = NULL;
    }

    if (!(tab_cmd = ft_strsplit(cmd[i], SPACE_SEPARATOR)))
    {
      break;
    }
    if (!tab_cmd[0])
    {

      break;
    }

    if (ft_is_builtin(tab_cmd[0]))
    {
      index_builtin = ft_is_builtin(tab_cmd[0]);
    }

    pid = 0;
    if (env_copy)
    {
      ft_arr_free(env_copy);
      env_copy = NULL;
    }

    env_copy = ft_arr_dup(*env);
    if (index_builtin == B_ENV)
    {
      index_builtin = ft_builtin_env(&tab_cmd, &env_copy, tube_fork_stdout_tmp[1], tube_fork_stderr_tmp[1]);
    }
    if (tab_cmd)
    {
      i_free = 0;
      while (tab_cmd[i_free])
      {
        i_free++;
      }
    }
    if (envp)
    {
      i_free = 0;
      while (envp[i_free])
      {
        if (envp[i_free])
        {
          free(envp[i_free]);
          envp[i_free] = NULL;
        }
        i_free++;
      }
      free(envp);
      envp = NULL;
    }
    ft_fork_env_arr_to_tab_str(env_copy, &envp);
    if ((pid = create_process()) == -1)
    {
      return (EXIT_FAILURE);
    }

    if (!pid)
    {
      if (tab_fd_stdin->length)
      {
        close(tube_fork_stdin[1]);
        dup2(tube_fork_stdin[0], 0);
      }
      close(tube_fork_stdout_tmp[0]);
      dup2(tube_fork_stdout_tmp[1], 1);
      close(tube_fork_stderr_tmp[0]);
      dup2(tube_fork_stderr_tmp[1], 2);


      path_tmp = NULL;
      if (!index_builtin && *tab_cmd)
      {
        index_path = ft_arr_indexof(env_copy, "PATH");
        if (index_path > 0 & index_path < (int)env_copy->length)
        {
          kval = *(t_kval **)((unsigned char *)env_copy->ptr + index_path *env_copy->sizeof_elem);
          path_ptr = kval->value;
        }
        else
        {
          path_ptr = ft_strnew(0);
        }
        if (tab_path)
        {
          i_free = 0;
          while (tab_path[i_free])
          {
            free(tab_path[i_free]);
            i_free++;
          }
          free(tab_path);
          tab_path = NULL;
        }

        tab_path = ft_strsplit(path_ptr, ':');
        if (path_ptr)
        {
          free(path_ptr);
          path_ptr = NULL;
        }
        // TODO segfault si !tab_cmd[0]
        index = 0;
        path_tmp = ft_strdup(*tab_cmd);
        while (tab_path[index] && (err = access(path_tmp, F_OK)) )
        {
          if (path_tmp)
          {
            free(path_tmp);
            path_tmp = NULL;
          }
          path_tmp_ptr = ft_strjoin(tab_path[index], "/");
          path_tmp = ft_strjoin(path_tmp_ptr, *tab_cmd);
          if (path_tmp_ptr)
          {
            free(path_tmp_ptr);
            path_tmp_ptr = NULL;
          }
          index++;
        }
        if (tab_path)
        {
          i_free = 0;
          while (tab_path[i_free])
          {
            free(tab_path[i_free]);
            i_free++;
          }
          free(tab_path);
          tab_path = NULL;
        }



      }

      if (!index_builtin && !err && *tab_cmd) // ?? index_builtin pour env
      {
        ft_son(path_tmp, tab_cmd, envp);
      }
      if (path_tmp)
      {
        free(path_tmp);
        path_tmp = NULL;
      }

      if (!index_builtin)
      {
        ft_putstr("21sh: command not found: ");
        ft_putstr(*tab_cmd);
        ft_putstr("\n");
      }
      exit(EXIT_SUCCESS);
    }
    else if (pid)
    {

      if (tab_fd_stdin->length)
      {
        // close(tube_fork_stdout_tmp[1]);
        if (nb_pipe)
        {
          buff = ft_strnew(1);
          while ((rd = read(tab_tube[i].tube[0], buff, 1)))
          {
            if (rd < 0)
            break;
            write(tube_fork_stdin[1], buff, 1);
          }
          free(buff);
          buff = NULL;
        }

        index = 0;
        while (index < (int)tab_fd_stdin->length)
        {
          fd = *(int **)((unsigned char *)tab_fd_stdin->ptr + index * tab_fd_stdin->sizeof_elem);
          rd = 0;
          buff = ft_strnew(1);

          if (*fd == D_LEFT_REDIRECT)
          {
            line = NULL;
            if (!tab_d_end_word->length)
            {
              index++;
              continue;
            }
            end_word = ft_arr_pop(&tab_d_end_word, 0);
            while (ft_strcmp(line, end_word) != 0 || tab_d_end_word->length)
            {
              if (ft_strcmp(line, end_word) == 0)
              {
                free(line);
                line = NULL;
                free(end_word);
                end_word = NULL;
                end_word = ft_arr_pop(&tab_d_end_word, 0);
              }
              if (line)
              {
                write(tube_fork_stdin[1], line, ft_strlen(line));
                *line = '\n';
                write(tube_fork_stdin[1], line, 1);
                free(line);
                line = NULL;
              }
              get_next_line(0, &line);
            }
            if (line)
            {
              free(line);
              line = NULL;
              free(end_word);
              end_word = NULL;
            }
          }
          else
          {
            while ((rd = read(*fd, buff, 1)))
            {
              if (rd < 0)
              break;
              write(tube_fork_stdin[1], buff, 1);
            }
          }

          index++;
        }

        if (buff)
        {
          free(buff);
          buff = NULL;
        }
        close(tube_fork_stdin[1]);
      }




      if (index_builtin > B_ENV)
      {
        ft_builtin_exec(index_builtin, tab_cmd, env, tube_fork_stdout_tmp[1], tube_fork_stderr_tmp[1]);
      }

      wait(&status);



      close(tube_fork_stdout_tmp[1]);
      close(tube_fork_stderr_tmp[1]);
      buff = ft_strnew(1);
      len_stdin = 0;
      while ((rd = read(tube_fork_stdout_tmp[0], buff, 1)))
      {
        if (rd < 0)
          break;
        write(tube_fork_stdout[1], buff, 1);
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
        buff = NULL;
      }
      buff = ft_strnew(len_stdin);
      close(tube_fork_stderr[1]);
      close(tube_fork_stdout[1]);
      while ((rd = read(tube_fork_stdout[0], buff, len_stdin)))
      {
        if (rd < 0)
          break;
        if (i < nb_pipe && !err)
        {
          write(tab_tube[i].tube[1], buff, len_stdin);
        }
        if (tab_fd_stdout->length)
        {
          ft_fork_write_list_fd(tab_fd_stdout, buff, len_stdin);
        }

        if (!tab_fd_stdout->length && i >= nb_pipe)
        {
          write(1, buff, len_stdin);
        }
      }

      if (buff)
      {
        free(buff);
        buff = NULL;
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
        buff = NULL;
      }

      if (i < nb_pipe && !err)
      {
        close(tab_tube[i].tube[1]);
        dup2(tab_tube[i].tube[0], 0);
      }




      while (tab_fd_stdout->length)
      {
        fd = (int *)(ft_arr_pop(&tab_fd_stdout, 0));
        if (*fd >= 0)
        {
          close(*fd);
        }
        free(fd);
      }
      while (tab_fd_stderr->length)
      {
        fd = (int *)(ft_arr_pop(&tab_fd_stderr, 0));
        if (*fd >= 0)
        {
          close(*fd);
        }
        free(fd);
      }
      while (tab_fd_stdin->length)
      {
        fd = (int *)(ft_arr_pop(&tab_fd_stdin, 0));
        if (*fd >= 0)
        {
          close(*fd);
        }
        free(fd);
      }
      while (tab_d_end_word->length)
      {
        free(ft_arr_pop(&tab_d_end_word, 0));
      }

      i++;
    }
  }
  dup2(stdin_copy, 0);
  dup2(stdout_copy, 1);
  close(stdin_copy);
  close(stdout_copy);

  if (env_copy)
  {
    ft_arr_free(env_copy);
    env_copy = NULL;
  }

  ft_arr_free(tab_fd_stdout);
  ft_arr_free(tab_fd_stderr);
  ft_arr_free(tab_fd_stdin);
  ft_arr_free(tab_d_end_word);
  if (envp)
  {
    i_free = 0;
    while (envp[i_free])
    {
      if (envp[i_free])
      {
        free(envp[i_free]);
        envp[i_free] = NULL;
      }
      i_free++;
    }
    free(envp);
    envp = NULL;
  }


  if (tab_cmd)
  {
    i_free = 0;
    while (tab_cmd[i_free])
    {
      free(tab_cmd[i_free]);
      i_free++;
    }
    if (tab_cmd)
      free(tab_cmd);
    tab_cmd = NULL;
  }
  if (tab_path)
  {
    i_free = 0;
    while (tab_path[i_free])
    {
      free(tab_path[i_free]);
      i_free++;
    }
    free(tab_path);
    tab_path = NULL;
  }

  if (path_tmp)
  {
    free(path_tmp);
    path_tmp = NULL;
  }
  if (path_tmp_ptr)
  {
    free(path_tmp_ptr);
    path_tmp_ptr = NULL;
  }
  if (buff)
  {
    free(buff);
    buff = NULL;
  }
  if (line)
  {
    free(line);
    line = NULL;
  }
  if (path_ptr)
  {
    free(path_ptr);
    path_ptr = NULL;
  }
  if (end_word)
  {
    free(end_word);
    end_word = NULL;
  }
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
  struct t_tube *tab_tube;
  int index;
  // char *path;
  int index_path;
  t_kval *kval;
  t_arr *env;
  int i;


  // path = NULL;
  env = *env_ptr;
  // index_path = ft_arr_indexof(env, "PATH");
  // if (index_path >= 0 && index_path < (int)env->length)
  // {
  //   kval = *(t_kval **)((unsigned char *)env->ptr + env->sizeof_elem * index_path);
  //   path = kval->value;
  // }
  // else
  // {
  //   path = ft_strnew(0);
  // }
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
    free(tab_tube);
    return (EXIT_FAILURE);
  }
  ft_fork(cmds, tab_tube, env_ptr, nb_pipe);
  i = 0;
  while (cmds[i])
  {
    free(cmds[i]);
    i++;
  }
  free(cmds);
  free(tab_tube);
  return (EXIT_SUCCESS);
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

  index = 0;
  cmd_str = NULL;
  while (index < (int)tab_cmds->length)
  {

    cmd = *(t_arr **)((unsigned char *)tab_cmds->ptr + index * tab_cmds->sizeof_elem);
    nb_pipe = ft_fork_nb_pipe(cmd);
    cmd_str = ft_fork_str_from_arr(cmd);
    ft_fork_split_pipe(cmd_str, nb_pipe, env);
    if (cmd_str)
    {
      free(cmd_str);
      cmd_str = NULL;
    }
    index++;
  }
  // ft_putstr("\n");
  return (EXIT_SUCCESS);
}
