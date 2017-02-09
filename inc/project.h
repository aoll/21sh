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

#define B_ENV                   1
#define B_SETENV                2
#define B_UNSETENV              3
#define B_CD                    4
#define B_ECHO                  5
#define B_EXIT                  6

#define HOME                    "/home/alex"
/**
 * STRUCT
 */

typedef struct s_cursor t_cursor;
struct  s_cursor
{
  bool is_env;

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

typedef struct s_cmd_line t_cmd_line;
struct  s_cmd_line
{
  int index;
  char *s_line;
  bool dquote;
  bool quote;
  bool check;
};

typedef struct s_tube t_tube;
struct s_tube
{
  int tube[2];
};

typedef struct s_fork t_fork;
struct s_fork
{
  int i;
  int nb_pipe;
  int err;
  int len_stdout;
  int len_stderr;
  int index_builtin;
  char *error_ptr;
  t_arr *env_copy;
  char **tab_cmd;
  char **envp;
  int status;
  t_arr **env;
  int stdin_copy;
  int stdout_copy;
  int stderr_copy;

};

typedef struct s_arr_fd t_arr_fd;
struct s_arr_fd
{
  t_arr *arr_fd_stdout;
  t_arr *arr_fd_stderr;
  t_arr *arr_fd_stdin;
  t_arr *arr_d_end_word;
};

typedef struct s_tab_tube t_tab_tube;
struct s_tab_tube
{
  int tube_fork_stdout_tmp[2];
  int tube_fork_stderr_tmp[2];
  int tube_fork_stdout[2];
  int tube_fork_stderr[2];
  int tube_fork_stdin[2];
};

/**
 * PROTOTYPES
 */

/**
 * Action to the terminal with termcaps
 */
int  ft_get_term_restore(struct termios *term);

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
  * Functions for read the key
  */
  int  ft_read_parse(
    const char *buff, t_cursor *cursor, t_arr **arr_ptr, t_arr *history_line, t_arr **current_line, t_arr **select_line, t_arr **copy_line);
  int  ft_read_parse_eof(char **buff, t_cursor *cursor, t_arr *arr, t_arr *history_line, t_arr *current_line, t_arr *copy_line, t_arr *select_line, struct termios *term, t_arr *env, bool option);
/**
 * Action on the cursor
 */
int  ft_free_cursor(t_cursor *cursor);
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
int  ft_cursor_nb_line_displayed(
  t_cursor *cursor, t_arr *arr, int index_start_showed, int is_total);
int  ft_cursor_restore_y_x(t_cursor *cursor, t_arr *arr, int nb_line_displayed);
int  ft_cursor_resize(
  t_cursor *cursor, t_arr *arr, struct winsize *terminal_size_old);

int  ft_cursor_copy_line(
  t_cursor *cursor, t_arr *select_line, t_arr **copy_line);

int  ft_cursor_cut(
  t_cursor *cursor, t_arr *arr, t_arr *select_line, t_arr **copy_line);
int  ft_cursor_paste(t_cursor *cursor, t_arr *arr, t_arr *copy_line);

int  ft_cursor_up_line(t_cursor *cursor, t_arr *arr);
int  ft_cursor_down_line(t_cursor *cursor, t_arr *arr);
int  ft_cusor_clear_down_line(t_cursor *cursor, t_arr *arr);

int  ft_cursor_up_history_line(
  t_cursor *cursor, t_arr *history_line, t_arr **current_line, t_arr **arr);
int  ft_cursor_down_history_line(
  t_cursor *cursor, t_arr *history_line, t_arr **current_line, t_arr **arr);
int  ft_cursor_valide_line(
  t_cursor *cursor, t_arr **history_line, t_arr **current_line, t_arr **arr);

/**
 * Parsing section
 */
t_arr *ft_parse_line(t_arr *arr);
t_arr  *ft_parse_separate_cmd(t_arr *arr);
int  ft_parse_init_cmd_line(t_cmd_line *line);
int  ft_parse_init_new_arr_line(t_arr **arr);
int  ft_parse_check_d_quote(t_cmd_line *line);
int  ft_parse_pop_space_inside(t_arr *arr);
int  ft_parse_pop_prev_space(t_arr *arr);
int  ft_parse_replace_space(t_arr *arr);
int  ft_parse_replace_d_left_redirect(t_arr *arr);
int  ft_parse_replace_d_right_redirect(t_arr *arr);
int  ft_parse_replace_s_right_redirect(t_arr *arr);
int  ft_parse_replace_s_left_redirect(t_arr *arr);
int  ft_parse_replace_pipe(t_arr *arr);
int  ft_parse_replace_file_redirect(t_arr *arr);
int  ft_parse_check_double_redirect(t_arr *arr);
int  ft_parse_replace_stdin_sdterr_redirect(t_arr *arr);
int  ft_parse_replace_sdterr_redirect(t_arr *arr);
int  ft_parse_replace_prev_line_stderr(
  t_cmd_line *line, char **s_prev_line, char *s_prev_prev_line, t_arr *arr);
int  ft_parse_replace_prev_line_stdout(
  t_cmd_line *line, char **s_prev_line, char *s_prev_prev_line, t_arr *arr);
int  ft_parse_replace_prev_prev_set_line(
  t_cmd_line *line, char **s_prev_line, char **s_prev_prev_line);
int  ft_parse_replace_prev_prev_line_stderr(
  t_cmd_line *line, char **s_prev_line, char **s_prev_prev_line, t_arr *arr);
int  ft_parse_replace_prev_prev_line_stdout(
  t_cmd_line *line, char **s_prev_line, char **s_prev_prev_line, t_arr *arr);
int  ft_parse_replace_sdterr_double_redirect(t_arr *arr);
int  ft_parse_replace_stderr_double_prev_line(
  t_cmd_line *line, char **s_prev_line, char *s_prev_prev_line, t_arr *arr);
int  ft_parse_replace_stdout_double_prev_line(
  t_cmd_line *line, char **s_prev_line, char *s_prev_prev_line, t_arr *arr);
int  ft_replace_double_stderr_prev_prev_set_line(
  t_cmd_line *line, char **s_prev_line, char **s_prev_prev_line);
int  ft_parse_replace_stderr_double_prev_prev_line(
  t_cmd_line *line, char **s_prev_line, char **s_prev_prev_line, t_arr *arr);
int  ft_parse_replace_stdout_double_prev_prev_line(
  t_cmd_line *line, char **s_prev_line, char **s_prev_prev_line, t_arr *arr);
int  ft_parse_check_double(t_arr *arr, int token);
int  ft_parse_is_only_space(t_arr *arr, int index);
int  ft_parse_check_end_space(t_arr *arr);
int  ft_parse_check_file_redirect(t_arr *arr);
int  ft_parse_check_error(t_arr *cmd);
int  ft_parse_pop_and_replace_and_check_error(t_arr *tab_cmds);
/**
 * fork test
 */
#include <fcntl.h>
#include <sys/wait.h>
int  ft_fork_test(t_arr **env, t_arr *tab_cmds);
char  *ft_fork_name_file(char **command, int i);
int  ft_fork_env_arr_to_tab_str(t_arr *envp, char ***env_ptr);
int  *ft_fork_fd(char *name_file, int token);

int  ft_fork_list_fd(char **command, t_arr_fd *arr_fd, char **error_ptr);
int  ft_fork_list_fd_null(
  char **cmd, int i, char **name_file, char **error_ptr);
int  ft_fork_fd_from_name(int **fd, char **command, char **error_ptr, int i);
int  ft_fork_list_fd_dup(t_arr *dst, const t_arr *src);
int  ft_fork_list_fd_stderr(
  t_arr *arr_fd_stderr, t_arr *arr_fd_stdout, int **fd_ptr, int c);
int  ft_fork_list_fd_left_redirect(t_arr *arr_fd_stdin);
int  ft_arr_close_arr_fd(t_arr_fd *arr_fd);

int  ft_arr_free_arr_fd(t_arr_fd *arr_fd);
int  ft_fork_list_fd_tmp(char **cmd, t_arr_fd *arr_fd, char **error_ptr);
int  ft_fork_write_list_fd(t_arr *arr, char *buff, int len);
int  ft_fork_list_d_end_word(char **command, t_arr *arr_d_end_word);

int  ft_fork_init_arr_fd(t_arr_fd *arr_fd);
int  ft_fork_pipe_array_tube(t_tab_tube *array_tube);
int  ft_fork_close_array_tube(t_tab_tube *array_tube);
int  ft_fork_set_tube(
  t_arr_fd *arr_fd, t_tab_tube *array_tube, int i, int nb_pipe);
int  ft_fork_is_error_ptr(char **error_ptr, t_arr_fd *arr_fd);
char  *ft_fork_init_path(t_arr *env_copy, char **tab_cmd, int *err);
int  ft_fork_command_not_found(
  char ***tab_cmd, int index_builtin, t_arr_fd *arr_fd);
int  ft_fork_write_tube_stdin(
  t_tube *tab_tube, t_tab_tube *array_tube, int i, int nb_pipe);
int  ft_fork_read_stdin_file(t_arr_fd *arr_fd, t_tab_tube *array_tube);
int  ft_fork_write_tube(int dst_fd, int src_fd);
int  ft_fork_write_fd_stdout(
  t_tab_tube *array_tube, t_tube *tab_tube, t_arr_fd *arr_fd, t_fork *st_fork);
int  ft_fork_write_fd_stderr(
  t_tab_tube *array_tube, t_arr_fd *arr_fd, t_fork *st_fork);
int  ft_fork_open_file(const char **cmd, t_arr_fd *arr_fd);
int  ft_fork_init_loop(
  t_fork *st_fork, t_arr_fd *arr_fd, const char **cmd, int nb_pipe);
int  ft_fork_set_tube_fd(
  t_fork *st_fork, t_tab_tube *array_tube, t_arr_fd *arr_fd, char **cmd);
int  ft_fork_check_is_builtin_exit(t_fork *st_fork, t_arr_fd *arr_fd);
int  ft_fork_pid_son(t_fork *st_fork, t_arr_fd *arr_fd, t_tab_tube *array_tube);
int  ft_fork_son_exec(char *path_cmd, char **tab_cmd, char **envp);
int  ft_fork_is_stdin_fd(
  t_fork *st_fork, t_tube *tab_tube, t_arr_fd *arr_fd, t_tab_tube *array_tube);
int  ft_fork_set_tube_father(
  t_fork *st_fork, t_tab_tube *array_tube, t_tube *tab_tube, t_arr_fd *arr_fd);
int  ft_fork_father(
  t_fork *st_fork, t_tube *tab_tube, t_tab_tube *array_tube, t_arr_fd *arr_fd);
int  ft_fork_create_process(
  t_fork *st_fork, t_arr_fd *arr_fd, t_tab_tube *array_tube, t_tube *tab_tube);

/**
 * builtin
 */
int  ft_is_builtin(char *command);
int  ft_builtin_exec(
  t_fork *st_fork, t_arr **env, int fd_stdout, int fd_stderr);
int  ft_builtin_env(char ***tab_cmd, t_arr **env, int fd_stdout, int fd_stderr);
int  ft_builtin_setenv(const char **tab_cmd, t_arr **env, int fd_stderr);
int  ft_builtin_unsetenv(const char **tab_cmd, t_arr **env, int fd_stderr);
int  ft_builtin_cd(const char **tab_cmd, t_arr **env, int fd_stderr);
int  ft_builtin_echo(const char **tab_cmd, t_arr **env);
int  ft_builtin_exit(char **tab_cmd, t_arr **env);
int  ft_builtin_setenv_check_argument(
  const char ** tab_cmd, char *cmd, int fd_stderr);

void  ft_read_line(char **env);

t_kval  *ft_kval_init(const char *env_line);

t_arr  *ft_env_init(char **env);

void  ft_start(void);

# endif
