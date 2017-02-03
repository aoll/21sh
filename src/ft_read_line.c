#include "project.h"

#include <signal.h>
/**
 * print the key
 */
int  ft_print_key(char *buff)
{
  ft_putchar('\n');
  ft_putnbr(buff[0]);
  ft_putchar('\n');
  ft_putnbr(buff[1]);
  ft_putchar('\n');
  ft_putnbr(buff[2]);
  ft_putchar('\n');
  ft_putnbr(buff[3]);
  ft_putchar('\n');
  ft_putnbr(buff[4]);
  ft_putchar('\n');
  ft_putnbr(buff[5]);
  ft_putchar('\n');
  ft_putnbr(buff[6]);
  ft_putchar('\n');
  ft_putnbr(buff[7]);
  ft_putchar('\n');
  ft_bzero(buff, 8);
  return (EXIT_SUCCESS);
}

static int  ft_get_term(struct termios *term)
{
  char *name_terminal;

  if (!(name_terminal = getenv("TERM"))) //retour le nom du terminal
    return (EXIT_FAILURE);
  if (tgetent(NULL, name_terminal) != 1) //check if name_terminal exist and if
    return (EXIT_FAILURE);            //the terminfo databbase could be found
  if (tcgetattr(0, term) == -1) // rempli la struct termios avec les
    return (EXIT_FAILURE);       // possibilités du terminal
  return (EXIT_SUCCESS);
}
int  ft_init_terminal(void)
{
  struct termios term;

  if (ft_get_term(&term))
    return (EXIT_FAILURE);

  term.c_lflag &= ~(ICANON);
  term.c_lflag &= ~(ECHO);
  // term.c_cc[VMIN] = 0;
  // term.c_cc[VTIME] = 1;


  if (tcsetattr(0, TCSADRAIN, &term) == -1)
  {
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}

int  ft_get_term_restore(struct termios *term)
{
  char *name_terminal;

  // if (!(name_terminal = getenv("TERM"))) //retour le nom du terminal
  //   return (EXIT_FAILURE);
  // if (tgetent(NULL, name_terminal) != 1) //check if name_terminal exist and if
  //   return (EXIT_FAILURE);            //the terminfo databbase could be found
  // if (tcgetattr(0, term) == -1) // rempli la struct termios avec les
  //    return (EXIT_FAILURE);       // possibilités du terminal
  term->c_lflag |= ICANON;
  term->c_lflag |=  ECHO;
  if (tcsetattr(0, 0, term) == -1)
    return (-1);
  return (EXIT_SUCCESS);
}

/*
** function for print some char * was stocked in a t_arr like elem
** is give for arr->f_print, print some elem
*/
void  ft_arr_putchar(const void *s)
{
  unsigned char *s_line_u;
  char *s_line;


  s_line_u = *((unsigned char **)s);
  s_line = (char *)s_line_u;
  if (!s_line)
  {
    return;
  }
  if (s_line[5] == 1)
  {
    ft_mode_reverse_video();
  }
  ft_putstr(*((char **)s));
  if (s_line[5] == 1)
  {
  }
  ft_mode_basic_video();
  return;
}
/*
** function for dup some char * was stocked in a t_arr like elem
** is give for arr->f_dup, dup some elem and return a void *
*/
void  *ft_arr_strdup(const void *s, size_t n)
{
  void *new;

  (void)n;
  if (!s)
  {
    return (NULL);
  }
  new = ft_strdup(*((char **)s));
  return (new);
}

/**
 * return a fresh pointeur on a copy of a kval *
 * in case of fail NULL is returned
 */
t_kval  *ft_kval_dup(const t_kval *old)
{
  t_kval *new;

  if (!(new = malloc(sizeof(t_kval))))
  {
    return (NULL);
  }
  new->key = NULL;
  new->value = NULL;
  ft_kval_set_key(new, old->key);
  ft_kval_set_value(new, old->value);
  return (new);
}

/*
** function for dup some kval * was stocked in a t_arr like elem
** is give for arr->f_dup, dup some elem and return a void *
*/
void  *ft_arr_kvaldup(const void *s, size_t n)
{
  void *new;

  (void)n;
  if (!s)
  {
    return (NULL);
  }
  new = ft_kval_dup(*((t_kval **)s));
  return (new);
}

/**
 *  Apply n time the command given in param
 */
int  ft_term_apply_cmd(char *cmd, int n)
{
  if (!cmd)
  {
    return (EXIT_FAILURE);
  }
  while (n)
  {
    tputs(cmd, 0, &my_putchar);
    n--;
  }
  return (EXIT_SUCCESS);
}

/**
 * move the cursor to a new position x
 */
int  ft_cursor_move_x(int new_pos_x, char *cmd)
{
  if (!cmd)
  {
    return (EXIT_FAILURE);
  }
  tputs(tgoto(cmd, 0, new_pos_x), 0, &my_putchar);
  return (EXIT_SUCCESS);
}

/**
 * PADDING_BUFFER
 */
char *ft_cmd(char *cmd)
{
  // // return (ft_strjoin("1.3*5", cmd));
  // char *new;
  //
  // new = ft_strnew(ft_strlen(cmd) + PADDING_BUFFER);
  // ft_bzero(new, ft_strlen(cmd) + PADDING_BUFFER);
  // ft_memcpy(new, cmd, ft_strlen(cmd));
  return (cmd);
}

int  ft_init_cursor_cmd(t_cursor *cursor)
{
  // cursor->up = tgetstr("sr", NULL);
  cursor->up = ft_cmd(tgetstr("up", NULL));
  cursor->down = ft_cmd(tgetstr("do", NULL));
  cursor->left = ft_cmd(tgetstr("le", NULL));
  cursor->right = ft_cmd(tgetstr("nd", NULL));
  cursor->sup_char = ft_cmd(tgetstr("dc", NULL));
  cursor->move_x = tgetstr("ch", NULL);
  cursor->clear_current_line = ft_cmd(tgetstr("ce", NULL)); //ce
  cursor->clear_down = ft_cmd(tgetstr("cd", NULL));
  cursor->mode_insertion = tgetstr("im", NULL);
  cursor->mode_insertion_end = ft_cmd(tgetstr("ei", NULL));
  cursor->mode_basic_video = ft_cmd(tgetstr("me", NULL));
  cursor->mode_reverse_video = ft_cmd(tgetstr("mr", NULL));
  cursor->save_cursor_position = ft_cmd(tgetstr("sc", NULL));
  cursor->restore_cursor_position = ft_cmd(tgetstr("rc", NULL));
  cursor->scroll_down = ft_cmd(tgetstr("sr", NULL));
  cursor->scroll_up = ft_cmd(tgetstr("sf", NULL));
  cursor->left_corner_up = ft_cmd(tgetstr("ho", NULL));
  cursor->left_corner_down = ft_cmd(tgetstr("ll", NULL));
  cursor->clear_all_the_screen = tgetstr("cl", NULL);
  cursor->marge = tgetstr("am", NULL);

  return (EXIT_SUCCESS);
}

/**
 * free all command save in struct cursor
 */
int  ft_free_cursor(t_cursor *cursor)
{
  if (cursor->prompt)
  {
    free(cursor->prompt);
  }
  // free(cursor->up);
  // free(cursor->down);
  // free(cursor->left);
  // free(cursor->right);
  // free(cursor->sup_char);
  // free(cursor->move_x);
  // free(cursor->clear_current_line);
  // free(cursor->clear_down);
  // free(cursor->mode_insertion);
  // free(cursor->mode_insertion_end);
  // free(cursor->mode_basic_video);
  // free(cursor->mode_reverse_video);
  // free(cursor->save_cursor_position);
  // free(cursor->restore_cursor_position);
  // free(cursor->scroll_down);
  // free(cursor->scroll_up);
  // free(cursor->left_corner_up);
  // free(cursor->left_corner_down);
  // free(cursor->clear_all_the_screen);
  // free(cursor->marge);
  return (EXIT_SUCCESS);
}

/**
 * init the cursor position
 */
int  ft_init_cursor_position(t_cursor *cursor)
{
  cursor->prompt = ft_strdup("\033[32m$> \033[0m");
  cursor->pos_y = 0;
  // cursor->prompt_len = ft_strlen(cursor->prompt);
  cursor->prompt_len = 3;
  cursor->pos_x = cursor->prompt_len;
  cursor->index_line = 0;
  cursor->dquote = false;
  cursor->quote = false;
  cursor->prev_chariot = 0;
  cursor->chariot = 0;
  cursor->y_total = 1;
  cursor->y_start = 0;
  cursor->index_history = 0;
  cursor->test = 0;

  return (EXIT_SUCCESS);
}




int  read_stdin(char **envp)
{
  t_cursor cursor;
  char *buff;
  int rd;
  int nb_char;
  t_arr *select_line;
  t_arr *copy_line;
  // int cursor.index_history;
  struct winsize terminal_size_old;
  t_arr *history_line;
  t_arr *current_line;
  t_arr *arr;
  t_arr *current_line_free;
  t_arr *tab_cmds;
  t_arr *env;
  struct termios term;
  char *line;

  cursor.is_env = false;
  // if (ft_get_term(&term))
  // {
  //   cursor.is_env = false;
  // }
  // else
  // {
  //   cursor.is_env = true;
  //   term.c_lflag &= ~(ICANON);
  //   term.c_lflag &= ~(ECHO);
  //   if (tcsetattr(0, TCSADRAIN, &term) == -1)
  //   {
  //     return (EXIT_FAILURE);
  //   }
  //
  //   ft_init_cursor_cmd(&cursor);
  // }


  env = ft_env_init(envp);
  history_line = ft_arr_new(1, sizeof(t_arr *));
  current_line = ft_arr_new(1, sizeof(t_arr *));
  ft_arr_push(&history_line, current_line, 0);
  arr = ft_arr_new(1, sizeof(char *));
  ft_arr_push(&current_line, arr, 0);
  arr->f_print = &ft_arr_putchar;
  arr->f_dup_elem = &ft_arr_strdup;


  ft_init_cursor_position(&cursor);
  //chaque apel a malloc doit etre proteger soit dit au passage!!!
  ft_terminal_winsize(&(cursor.terminal_size)); // a checker le retour
  ft_putnbr(cursor.terminal_size.ws_col);
  ft_putstr("-");
  ft_putnbr(cursor.terminal_size.ws_row);
  ft_putchar('\n');
  // history_line->f_print = &ft_arr_print; // mal construit !! doit eux pouvoir prendre des void
  // history_line->f_dup_elem = &ft_arr_dup; //mal construit !! doit eux meme pouvoir prendre des void
  select_line = ft_arr_new(1, sizeof(char *));
  copy_line = NULL;
  select_line->f_print = &ft_arr_putchar;
  select_line->f_dup_elem = &ft_arr_strdup;
  // ft_arr_push(&history_line, arr, 0);
  nb_char = cursor.prompt_len;

  buff = ft_strnew(8); //need 3 but we are never to sure
  ft_bzero(buff, 8);
  ft_cursor_save_position();
  ft_putstr(cursor.prompt);
  ft_terminal_winsize(&terminal_size_old); // a checker le retour
  ft_terminal_winsize(&(cursor.terminal_size)); // a checker le retour
  while (1 == 1)
  {

    ft_terminal_winsize(&terminal_size_old); // a checker le retour
    if (cursor.terminal_size.ws_col != terminal_size_old.ws_col || cursor.terminal_size.ws_row != terminal_size_old.ws_row)
    {
      ft_cursor_resize(&cursor, arr, &terminal_size_old);
    }
    if (cursor.is_env)
    {
      if ((rd = read(0, buff, 8)) > 0)
      {
        // ft_print_key(buff);
        // continue;
        cursor.is_select = false;
        // cursor.prompt_len = ft_strlen(cursor.prompt); // maybe one function with the adress of promt a the change is do it only if a change has be do it an not a check every loop


        if (!(ft_read_parse((const char *)buff, &cursor, &arr, history_line, current_line, select_line, copy_line)))
        {
          ft_bzero(buff, 8);
          continue;
        }
        else if (!(ft_read_parse_eof(&buff, &cursor, arr, history_line, current_line, copy_line, select_line, &term, env, false)))
        {
          return (EXIT_SUCCESS);
        }
        //enter
        else if (!cursor.dquote && !cursor.quote && buff[0] == 10 && !buff[1] && !buff[2] && !buff[3] && !buff[4] && !buff[5] && !buff[6]  && !buff[7])
        {
          /**
          * next step push arr dans arr :p :p
          * and not free actual but only a new
          * and maybe , yes only maybe exec the line ??
          */
          // tab_cmds = NULL;
          if (cursor.is_env)
          {
            ft_cursor_end(&cursor, arr);
          }
          if (tab_cmds)
          {
            //TODO free tab_cmds
          }
          tab_cmds = ft_parse_line(arr);
          if (tab_cmds)
          {
            if (cursor.is_env)
            {
              ft_term_apply_cmd(cursor.mode_insertion_end, 1);
              if (ft_get_term_restore(&term))
              return (EXIT_FAILURE);
            }
            ft_putstr("\n");
            ft_fork_test(&env, tab_cmds);
            if (cursor.is_env)
            {
              ft_term_apply_cmd(cursor.mode_insertion, 1);
              term.c_lflag &= ~(ICANON);
              term.c_lflag &= ~(ECHO);
              if (tcsetattr(0, TCSADRAIN, &term) == -1)
              {
                return (EXIT_FAILURE);
              }
            }
            // ft_init_terminal();
            // ft_putstr("\n");
          }
          else
          {
            ft_putstr("\n");
          }
          ft_cursor_valide_line(&cursor, &history_line, &current_line, &arr);


        }


        else //everithing else the previous command and past cmd - v
        {
          ft_cursor_add_char(&cursor, arr, buff);
        }

        // delete all char reverse video and normal and rewrite in normal video
        if (!cursor.is_select && select_line->length && arr->length && cursor.is_env)
        {
          ft_cursor_deselect_all(&cursor, arr, select_line);
        }

        ft_bzero(buff, 8);

      }

    }
    else
    {
      // line = ft_strnew(BUFF_SIZE);
      line = NULL;
      if (get_next_line(0, &line))
      {
        while (arr->length)
        {
          free(ft_arr_pop(&arr, 0));
        }
        ft_arr_str(arr, line);
        if (line)
        {
          free(line);
          line = NULL;
        }
        tab_cmds = ft_parse_line(arr);
        if (tab_cmds)
        {
          ft_fork_test(&env, tab_cmds);
        }
        else
        {
          ft_putstr("\n");
        }
        if (tab_cmds)
        {
          if (tab_cmds->length)
          {
            ft_arr_free(ft_arr_pop(&tab_cmds, 0));

          }
          if (tab_cmds->ptr)
          {
            free(tab_cmds->ptr);
          }
          free(tab_cmds);
          tab_cmds = NULL;
        }
        ft_putstr(cursor.prompt);

      }
      else
      {
        if (line)
        {
          free(line);
          line = NULL;
        }
        if (!(ft_read_parse_eof(&buff, &cursor, arr, history_line, current_line, copy_line, select_line, &term, env, true)))
        {
          return (EXIT_SUCCESS);
        }
        return (EXIT_SUCCESS);
      }
      if (line)
      {
        free(line);
        line = NULL;
      }
    }
  }
  return (EXIT_SUCCESS);
}







void  ft_loop(char **env)
{

  // ft_init_terminal();

  read_stdin(env);
  return;
}


void  ft_read_line(char **env)
{
  ft_putstr("test du read_line\n");
  ft_loop(env);
  return;
}
