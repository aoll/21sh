#include "project.h"

#include <signal.h>

/*
** function for print some char * was stocked in a t_arr like elem
** is give for arr->f_print, print some elem
*/
void  ft_arr_putchar(const void *s)
{
  unsigned char *s_line;

  s_line = *((unsigned char **)s);

  if (s_line[5] == 1)
  {
    ft_mode_reverse_video();
  }
  ft_putstr(*((char **)s));
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
  new = ft_strdup(*((char **)s));
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
  cursor->prompt = ft_strdup("$> ");
  cursor->pos_y = 0;
  cursor->prompt_len = ft_strlen(cursor->prompt);
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
  int index_history_free;
  int index_current_free;
  t_arr *current_line_free;
  t_arr *tab_cmds;
  t_arr *env;


  env = ft_env_init(envp);
  history_line = ft_arr_new(1, sizeof(t_arr *));
  current_line = ft_arr_new(1, sizeof(t_arr *));
  ft_arr_push(&history_line, current_line, 0);
  arr = ft_arr_new(1, sizeof(char *));
  ft_arr_push(&current_line, arr, 0);
  arr->f_print = &ft_arr_putchar;
  arr->f_dup_elem = &ft_arr_strdup;


  ft_init_cursor_position(&cursor);
  ft_init_cursor_cmd(&cursor);
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
    if ((rd = read(0, buff, 8)) > 0)
    {

      // ft_putchar('\n');
      // ft_putnbr(buff[0]);
      // ft_putchar('\n');
      // ft_putnbr(buff[1]);
      // ft_putchar('\n');
      // ft_putnbr(buff[2]);
      // ft_putchar('\n');
      // ft_putnbr(buff[3]);
      // ft_putchar('\n');
      // ft_putnbr(buff[4]);
      // ft_putchar('\n');
      // ft_putnbr(buff[5]);
      // ft_putchar('\n');
      // ft_putnbr(buff[6]);
      // ft_putchar('\n');
      // ft_putnbr(buff[7]);
      // ft_putchar('\n');
      // ft_bzero(buff, 8);
      // continue;
      cursor.is_select = false;
      cursor.prompt_len = ft_strlen(cursor.prompt); // maybe one function with the adress of promt a the change is do it only if a change has be do it an not a check every loop
      if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59 && buff[4] == 50 && buff[5] == 68 && !buff[6] && !buff[7]) // shift + left //done
      {
        cursor.is_select = true;
        if (cursor.index_line > 0 && arr->length)
        {
          ft_cursor_select_left(&cursor, arr, select_line);
        }
      }
      else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59 && buff[4] == 50 && buff[5] == 67 && !buff[6] && !buff[7]) // shift + right //done
      {
        cursor.is_select = true;
        if (cursor.index_line < (int)arr->length)
        {
          ft_cursor_select_right(&cursor, arr, select_line);
        }
      }
      else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59 && buff[4] == 53 && buff[5] == 65 && !buff[6] && !buff[7]) // ctrl + up //done
      {
        ft_cursor_up_line(&cursor, arr);

      }
      else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59 && buff[4] == 53 && buff[5] == 66 && !buff[6] && !buff[7]) // ctrl + down //done
      {
        ft_cursor_down_line(&cursor, arr);
      }

      // up or down or key left or right
      else if (buff[0] == 27 && buff[1] == 91 && (buff[2] == 65 || buff[2] == 66 || buff[2] == 67 || buff[2] == 68) && !buff[3] && !buff[4] && !buff[5] && !buff[6] && !buff[7])
      {
        // up
        if (buff[2] == 65 && cursor.index_history - 1 >= 0)
        {
          ft_cursor_up_history_line(&cursor, history_line, &current_line, &arr);
        }
        else if (buff[2] == 66 && cursor.index_history  +  1 < (int)history_line->length)
        {
          ft_cursor_down_history_line(&cursor, history_line, &current_line, &arr);
        }
        // for key left check if the prev char is a tab and consequently move the time nescessary
        else if (buff[1] == 91 && buff[2] == 68) //key left
        {
          ft_cursor_left(&cursor, arr);
        }
        // for key right check if the next char is a tab and consequently move the time nescessary
        else if (buff[1] == 91 && buff[2] == 67)// && (cursor.pos_x + 1) <= nb_char) //key right
        {
          ft_cursor_right(&cursor, arr);
        }
      }
      else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 72 && !buff[3] && !buff[4] && !buff[5] && !buff[6] && !buff[7]) //key home //done
      {
        ft_cursor_home(&cursor, arr);
      }
      else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 70 && !buff[3] && !buff[4] && !buff[5] && !buff[6] && !buff[7]) //key end //done
      {
        ft_cursor_end(&cursor, arr);
      }

      else if (buff[0] == 4 && !buff[1] && !buff[2] && !buff[3] && !buff[4] && !buff[5] && !buff[6] && !buff[7]) //ctrl-d eof //doone
      {
        // si une ligne de commande est en cours exec ligne; ft_putstr("$> ");
        ft_free_cursor(&cursor);
        if (select_line)
        {
          ft_arr_free(select_line);
        }
        if (copy_line)
        {
          ft_arr_free(copy_line);
        }
        index_history_free = 0;
        while (index_history_free < (int)history_line->length)
        {
          current_line_free = *((t_arr **)((unsigned char *)history_line->ptr + index_history_free * history_line->sizeof_elem));
          index_current_free = 0;
          while (index_current_free < (int)current_line_free->length)
          {
            ft_arr_free(ft_arr_pop(&current_line_free, index_current_free));
          }
          ft_arr_free(ft_arr_pop(&history_line, index_history_free));
          // index_history_free++;
        }
        ft_arr_free(history_line);
        free(buff);
        buff = NULL;
        ft_putchar('\n');

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
        // ft_putstr("\n");
        // ft_putstr("@< ");
        // ft_arr_print(arr);
        // ft_putstr("       cursor.is_select: ");
        // ft_arr_print(select_line);
        // ft_putchar('\n');
        // ft_arr_push(&history_line, arr, -1);
        // ft_putstr("\ncursor.index_line: ");
        // ft_putnbr(cursor.index_line);
        // ft_putstr(" y_total: ");
        // ft_putnbr(cursor.y_total);
        // ft_putstr(" cursor.pos_x: ");
        // ft_putnbr(cursor.pos_x);
        // ft_putstr(" cursor.pos_y:");
        // ft_putnbr(cursor.pos_y);
        // ft_putstr(" cursor.y_start:");
        // ft_putnbr(cursor.y_start);
        // ft_putstr("\n");
        //
        tab_cmds = NULL;
        ft_cursor_end(&cursor, arr);
        if (tab_cmds)
        {
          //TODO free tab_cmds
        }
        tab_cmds = ft_parse_line(arr);
        if (tab_cmds)
        {
          ft_putstr("\n");
          ft_fork_test(env, tab_cmds);
          // ft_putstr("\n");
        }
        else
        {
          ft_putstr("\n");
        }
        ft_cursor_valide_line(&cursor, &history_line, &current_line, &arr);


      }

      //Del
      else if (buff[0] == 127 && !buff[1] && !buff[2] && !buff[3] && !buff[4] && !buff[5] && !buff[6]  && !buff[7]) //del //done
      {
        if (cursor.index_line > 0)
        {
          ft_cursor_del_or_suppr(&cursor, arr, 1);
        }
      }

      else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 51 && buff[3] == 126 && !buff[4] && !buff[5] && !buff[6]  && !buff[7]) //sup //done si le cursor se trouve sur char et pas avant ou apres
      {
        if (arr->length && cursor.index_line < (int)arr->length)
        {
          ft_cursor_del_or_suppr(&cursor, arr, 0);
        }
      }
      // ctrl + left arrow // done
      else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59 && buff[4] == 53 && buff[5] == 68 && !buff[6] && !buff[7]) // ctrl + left arrow //done
      {
        // if (cursor.pos_x - 1 >= 3)
        if (cursor.index_line > 0)
        {
          ft_cursor_word_left(&cursor, arr);
        }

      }
      // ctrl + right arrow // done
      else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59 && buff[4] == 53 && buff[5] == 67 && !buff[6] && !buff[7]) // ctrl + right arrow //done
      {
        if (cursor.index_line < (int)arr->length)
        {
          ft_cursor_word_right(&cursor, arr);
        }
      }
      //ctrl + x //cut // done
      else if (buff[0] == 24 && !buff[1] && !buff[2] && !buff[3] && !buff[4] && !buff[5] && !buff[6] && !buff[7])
      {
        // peut se resumer par un appel a copie comme ctrl + w
        cursor.is_select = false;
        if (select_line->length)
        {
          ft_cursor_cut(&cursor, arr, select_line, &copy_line);
        }

      }
      //ctrl + w // copy //done
      else if (buff[0] == 23 && !buff[1] && !buff[2] && !buff[3] && !buff[4] && !buff[5] && !buff[6] && !buff[7])
      {
        cursor.is_select = true;
        if (select_line->length)
        {
          ft_cursor_copy_line(&cursor, select_line, &copy_line);
        }

      }
      //ctrl + v // paste //done
      else if (buff[0] == 22 && !buff[1] && !buff[2] && !buff[3] && !buff[4] && !buff[5] && !buff[6] && !buff[7])
      {
        if (copy_line->length)
        {
          ft_cursor_paste(&cursor, arr, copy_line);
          continue;

        }
      }



      else //everithing else the previous command and past cmd - v
      {
        ft_cursor_add_char(&cursor, arr, buff);
      }

      // delete all char reverse video and normal and rewrite in normal video
      if (!cursor.is_select && select_line->length && arr->length)
      {
        ft_cursor_deselect_all(&cursor, arr, select_line);
      }

      ft_bzero(buff, 8);
      // free(buff);
      // buff = NULL;
    }
  }
  return (EXIT_SUCCESS);
}

int  ft_get_term(struct termios *term)
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
  // struct termios term_save; // la copier au debut pour une restauration futur

  if (ft_get_term(&term))
    return (EXIT_FAILURE);

  term.c_lflag &= ~(ICANON);
  term.c_lflag &= ~(ECHO);
  term.c_cc[VMIN] = 0;
  term.c_cc[VTIME] = 1;


  if (tcsetattr(0, TCSADRAIN, &term) == -1)
  {
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}

void  edit_cursor(t_cursor *cursor)
{
  cursor->pos_x = 42;
  return;
}

void  test_struc(void)
{
  t_cursor cursor;

  cursor.pos_x = 1;
  ft_putstr("init: \n"); ft_putnbr(cursor.pos_x); ft_putstr("\n");

  edit_cursor(&cursor);

  ft_putstr("after edit: \n"); ft_putnbr(cursor.pos_x); ft_putstr("\n");

  return;
}



void  ft_loop(char **env)
{

  ft_init_terminal();

  read_stdin(env);
  return;
}


void  ft_read_line(char **env)
{
  ft_putstr("test du read_line\n");
  ft_loop(env);
  return;
}
