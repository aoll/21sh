#ifndef PROJECT_H
#define PROJECT_H



/*
** INCLUDE
*/

# include "libft.h"
#include <sys/ioctl.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <signal.h>
#include <sys/stat.h>


/**
 * DEFINE
 */

#define TABULATION_LEN 4
#define PADDING_BUFFER 30


#define SPACE_SEPARATOR       -1
#define D_LEFT_REDIRECT       -2
#define D_RIGHT_REDIRECT      -3
#define S_LEFT_REDIRECT       -4
#define S_RIGHT_REDIRECT      -5
#define PIPE                  -6
#define FILE_REDIRECT         -7
#define STDOUT_STDERR_REDIRECT -8
#define STDERR_REDIRECT       -9
#define D_STDERR_REDIRECT     -10


/**
 * STRUCT
 */

typedef struct s_cursor t_cursor;
struct  s_cursor
{
  char *prompt;
  size_t prompt_len;

  int pos_x;
  int pos_y;
  int index_line;
  int y_total;
  int y_start;
  int index_history;

  struct winsize terminal_size;

  bool is_select;

  bool quote;
  bool dquote;

  int prev_chariot;
  int chariot;

  char char_tmp; //inactive for the moment if for add_char_save with é à ù etc..

  char *up;
  char *down;
  char *left;
  char *right;
  char *move_x;
  char *sup_char;
  char *clear_down;
  char *mode_insertion;
  char *mode_insertion_end;
  char *mode_basic_video;
  char *mode_reverse_video;
  char *save_cursor_position;
  char *restore_cursor_position;
  char *scroll_up; // not use
  char *scroll_down;// not use
  char *left_corner_up;// not use
  char *left_corner_down;
  char *clear_current_line;
  char *marge;
  char *no_marge;

  char *clear_all_the_screen;
  int test;
};

typedef struct s_token t_token;
struct  s_token
{
  int  category;
  int  pipe[2];
  int  fd;
  char **cmd_args;
};
/**
 * PROTOTYPES
 */

/**
 * Action to the terminal with termcaps
 */
int  ft_cursor_move_x(int new_pos_x, char *cmd);
int  ft_term_apply_cmd(char *cmd, int n);
int  ft_terminal_winsize(struct winsize *terminal_size);
int  my_putchar(int c);

int  ft_sup_char(int n);
int  ft_move_up(void);
int  ft_move_down(void);
int  ft_move_left(void);
int  ft_move_right(void);
int  ft_move_x(int new_pos_x);
int  ft_cursor_save_position(void);
int  ft_cursor_restore_position(void);
int  ft_mode_reverse_video(void);
int  ft_mode_basic_video(void);
int  ft_mode_insertion(void);
int  ft_mode_insertion_end(void);
int  ft_clear_down(void);

/**
 * Function for t_arr
 */
 void  *ft_arr_strdup(const void *s, size_t n);
 void  ft_arr_putchar(const void *s);
/**
 * Action on the cursor
 */
int  ft_cursor_left(t_cursor *cursor, t_arr *arr);
int  ft_cursor_right(t_cursor *cursor, t_arr *arr);
int  ft_cursor_word_left(t_cursor *cursor, t_arr *arr);
int  ft_cursor_word_right(t_cursor *cursor, t_arr *arr);
int  ft_cursor_home(t_cursor *cursor, t_arr *arr);
int  ft_cursor_end(t_cursor *cursor, t_arr *arr);

int  ft_cursor_move_to_start(t_cursor *cursor, t_arr *arr);
int  ft_restore_prompt_and_line(t_cursor *cursor, t_arr *arr);
int  ft_cursor_move_to_index_line_from_start(t_cursor *cursor);

int  ft_cursor_clear_up(t_cursor *cursor);
int  ft_cursor_clear_down(t_cursor *cursor);
int  ft_cursor_clear_all_screen(t_cursor *cursor, int is_up); // very effective!!

int  ft_cursor_select_left(t_cursor *cursor, t_arr *arr, t_arr *select_line);
int  ft_cursor_select_right(t_cursor *cursor, t_arr *arr, t_arr *select_line);
int  ft_cursor_deselect_all(t_cursor *cursor, t_arr *arr, t_arr *select_line);


int  ft_cursor_del_or_suppr(t_cursor *cursor, t_arr *arr, int is_prev_char);


int  ft_cursor_add_char(t_cursor *cursor, t_arr *arr, char *buff);

int  ft_nb_char_between_two_chariot(t_arr *arr, int index);
int  ft_arr_index_line_start_showed(t_cursor *cursor, t_arr *arr, int line_off);

int  ft_index_line_start_showed(t_cursor *cursor, t_arr *arr);

int  ft_cursor_restore_index(t_cursor *cursor, t_arr *arr, int index);
int  ft_cursor_nb_line_displayed(t_cursor *cursor, t_arr *arr, int index_start_showed, int is_total);
int  ft_cursor_restore_y_x(t_cursor *cursor, t_arr *arr, int nb_line_displayed);
int  ft_cursor_resize(t_cursor *cursor, t_arr *arr, struct winsize *terminal_size_old);

int  ft_cursor_copy_line(t_cursor *cursor, t_arr *select_line, t_arr **copy_line);

int  ft_cursor_cut(t_cursor *cursor, t_arr *arr, t_arr *select_line, t_arr **copy_line);
int  ft_cursor_paste(t_cursor *cursor, t_arr *arr, t_arr *copy_line);

int  ft_cursor_up_line(t_cursor *cursor, t_arr *arr);
int  ft_cursor_down_line(t_cursor *cursor, t_arr *arr);
int  ft_cusor_clear_down_line(t_cursor *cursor, t_arr *arr);

int  ft_cursor_up_history_line(t_cursor *cursor, t_arr *history_line, t_arr **current_line, t_arr **arr);
int  ft_cursor_down_history_line(t_cursor *cursor, t_arr *history_line, t_arr **current_line, t_arr **arr);
int  ft_cursor_valide_line(t_cursor *cursor, t_arr **history_line, t_arr **current_line, t_arr **arr);

/**
 * Parsing section
 */
t_arr *ft_parse_line(t_arr *arr);
/**
 * fork test
 */
 #include <fcntl.h>
int  ft_fork_test(t_arr *env, t_arr *tab_cmds, char **envp);

void  ft_read_line(char **env);

t_kval  *ft_kval_init(const char *env_line);

t_arr  *ft_env_init(char **env);

void  ft_start(void);

# endif
