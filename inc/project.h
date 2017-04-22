/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 13:17:39 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/22 11:46:55 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*
** GLOBAL
*/

int g_is_ctrl_c_father;

/*
** STRUCT
*/

typedef struct s_cursor t_cursor;
struct  s_cursor
{
	bool			is_env;
	char			*prompt;
	size_t			prompt_len;
	int				pos_x;
	int				pos_y;
	int				index_line;
	int				y_total;
	int				y_start;
	int				index_history;
	struct winsize	terminal_size;
	bool			is_select;
	bool			quote;
	bool			dquote;
	int				prev_chariot;
	int				chariot;
	char			char_tmp;
	char			*up;
	char			*down;
	char			*left;
	char			*right;
	char			*move_x;
	char			*sup_char;
	char			*clear_down;
	char			*mode_insertion;
	char			*mode_insertion_end;
	char			*mode_basic_video;
	char			*mode_reverse_video;
	char			*save_cursor_position;
	char			*restore_cursor_position;
	char			*scroll_up;
	char			*scroll_down;
	char			*left_corner_up;
	char			*left_corner_down;
	char			*clear_current_line;
	char			*marge;
	char			*no_marge;
	char			*clear_all_the_screen;
	int			test;
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

typedef struct s_list_arr t_list_arr;
struct s_list_arr
{
	t_arr *arr;
	char *buff;
	t_arr *copy_line;
	t_arr *env;
	t_arr *current_line;
	t_arr *history_line;
	t_arr *select_line;
	t_arr *tab_cmds;
};

typedef struct s_read t_read;
struct	s_read
{
	t_cursor		cursor;
	struct			winsize terminal_size_old;
	struct termios	term;
	char			*line;
	t_list_arr		list_arr;
	int 			err;
};

/*
** PROTOTYPES
 */

/*
** Action on the signal
*/

int  ft_signal_init(void);
int  ft_signal_restore(void);
void  ft_signal_sigint_c(int num_sig);
void  ft_signal_sigint_chariot(int num_sig);
void  ft_signal_sigint_not_env(int num_sig);
/*
** Action to the terminal with termcaps
*/
int	ft_get_term(struct termios *term);
int	ft_init_terminal(void);

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
int  ft_mode_reverse_video(void);
int  ft_mode_basic_video(void);
int  ft_mode_insertion(void);
int  ft_mode_insertion_end(void);

/*
** Function for t_arr
*/
 void  *ft_arr_strdup(const void *s, size_t n);
 void  ft_arr_putchar(const void *s);
 int  ft_check_is_char(t_arr *arr, char c);

/*
** Functions for read the key
*/
int	ft_read_env(t_cursor *cursor, t_list_arr *list_arr, struct termios *term);
int	ft_read_no_env(
	t_cursor *cursor, t_list_arr *list_arr, char **line, struct termios *term);
int	ft_read_end(
	t_cursor *cursor, t_list_arr *list_arr, struct termios *term, char **line);
int	ft_read_get(
	t_cursor *cursor, t_list_arr *list_arr, char **line, bool quote);
int	ft_read_exec(t_cursor *cursor, t_list_arr *list_arr, struct termios *term);
int	ft_init_list_arr(t_list_arr *list_arr, char **envp);
int	ft_check_loop(
	struct winsize *terminal_size_old, t_cursor *cursor, t_list_arr *list_arr);
int	ft_init_init_term_arr(
	t_list_arr *list_arr, char **envp,
t_cursor *cursor, struct winsize *terminal_size_old);
int	ft_read_exit(t_list_arr *list_arr, t_cursor *cursor, struct termios *term);
int	ft_read_deselect(t_list_arr *list_arr, t_cursor *cursor);
int ft_read_stdin(char **envp);
int  ft_read_ctrl_c_not_env(t_cursor *cursor, t_arr *arr);
int  ft_read_ctrl_c_env(t_cursor *cursor, t_arr *arr);
int  ft_read_parse(const char *buff, t_cursor *cursor, t_list_arr *list_arr);

int  ft_read_parse_eof(t_cursor *cursor, t_list_arr *list_arr,
  struct termios *term, bool option);


int  ft_read_parse_shift(
  const char *buff, t_cursor *cursor, t_arr *arr, t_arr **select_line);
int  ft_read_parse_ctrl(const char *buff, t_cursor *cursor, t_arr *arr);

int  ft_read_parse_arrow(
  const char *buff, t_cursor *cursor, t_list_arr *list_arr);

int  ft_read_parse_home_end(const char *buff, t_cursor *cursor, t_arr *arr);
int  ft_read_parse_ctrl_arrow(const char *buff, t_cursor *cursor, t_arr *arr);


/*
** Action on the cursor
*/
int	ft_init_cursor_position(t_cursor *cursor);
int	ft_init_cursor_cmd(t_cursor *cursor);
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
int  ft_fork_init_st_fork(t_fork *st_fork, t_arr **env);
int  ft_fork_back_std(t_fork *st_fork);
int  ft_fork_free_st_fork_and_arr_fd(t_fork *st_fork, t_arr_fd *arr_fd);
int  ft_fork_init_tab_cmd(t_fork *st_fork, char *cmd);
int  ft_fork_init_env_copy(t_fork *st_fork, t_arr *env, t_tab_tube *array_tube);
int  ft_fork_set_env_copy(t_fork *st_fork, t_arr *env, t_tab_tube *array_tube);
int ft_fork(char **cmd, t_tube *tab_tube, t_arr **env, int nb_pipe);
int  ft_fork_son_exec(char *path_cmd, char **tab_cmd, char **envp);
int  ft_fork_nb_pipe(t_arr *arr);
char  *ft_fork_str_from_arr(t_arr *arr);
int  ft_fork_split_pipe(char *str, int nb_pipe, t_arr **env_ptr);

int  ft_cursor_valide_line_init_cursor_prompt(
  t_cursor *cursor, int len_history);
int  ft_cursor_valide_line_with_line(
  t_arr  *tmp_arr, t_arr *tmp_current_line, t_arr *tmp_history_line);
int  ft_cursor_valide_line_without_line(t_arr *tmp_history_line);
int  ft_cursor_clear_up(t_cursor *cursor);
int  ft_cursor_clear_down(t_cursor *cursor);
int  ft_arr_add_char(t_cursor *cursor, t_arr *arr, char c, int is_tab);
int  ft_arr_index_line_start_showed(t_cursor *cursor, t_arr *arr, int line_off);
int  ft_cursor_print_char(t_cursor *cursor, char c, t_arr *arr);
int  ft_cursor_print_chariot(t_cursor *cursor, t_arr *arr);
int  ft_cursor_print_overide_line(t_cursor *cursor, t_arr *arr);
int  ft_cusor_clear_down_line(t_cursor *cursor, t_arr *arr);
int  ft_cursor_left_tab(t_cursor *cursor, int same_line);
int  ft_cursor_left_same_line(t_cursor *cursor, unsigned char *s_line);
int  ft_nb_char_between_two_chariot(t_arr *arr, int index);
int  ft_cursor_left_chariot(t_cursor *cursor, t_arr *arr);
int  ft_cursor_index_prev_line_end(t_cursor *cursor, t_arr *arr, int start);
int  ft_cursor_nb_line_displayed(
  t_cursor *cursor, t_arr *arr, int index_start_showed, int is_total);
int  ft_cursor_restore_y_x(t_cursor *cursor, t_arr *arr, int nb_line_displayed);
int  ft_cursor_right_tab(t_cursor *cursor, int same_line);
int  ft_cursor_right_chariot(t_cursor *cursor);
int  ft_cursor_right_same_line(t_cursor *cursor, t_arr *arr,
  unsigned char *s_line);
int  ft_clear_up_from_bottom(t_cursor *cursor);
int  ft_index_line_end_showed(t_cursor *cursor, t_arr *arr);
int  ft_index_line_start_showed(t_cursor *cursor, t_arr *arr);
int  ft_cursor_right_line_more(t_cursor *cursor, t_arr *arr);
int  ft_cursor_right_line_more_up(
  t_cursor *cursor, void *ptr_tmp, t_arr *arr);
int  ft_cursor_y_screen(t_cursor *cursor, t_arr *arr);
int  ft_cursor_select_overide_tab(t_cursor *cursor, t_arr *arr,
  t_arr *select_line, int is_will_reverse);
int  ft_cursor_select_overide_char(t_cursor *cursor, t_arr *arr,
  t_arr *select_line, int is_will_reverse);

/*
** Parsing section
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
int  ft_fork_loop(t_arr **env, t_arr *tab_cmds);
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

/*
** builtin
*/

int  ft_is_builtin(char *command);
int  ft_builtin_exec(
  t_fork *st_fork, t_arr **env, int fd_stdout, int fd_stderr);
int  ft_builtin_env(char ***tab_cmd, t_arr **env, int fd_stdout, int fd_stderr);
int  ft_builtin_setenv(const char **tab_cmd, t_arr **env, int fd_stderr);
int  ft_builtin_unsetenv(const char **tab_cmd, t_arr **env, int fd_stderr);
int  ft_builtin_cd(const char **tab_cmd, t_arr **env, int fd_stderr);
int  ft_builtin_echo(char **tab_cmd, t_arr **env);
int  ft_builtin_exit(char **tab_cmd, t_arr **env);
int  ft_builtin_setenv_check_argument(
  const char ** tab_cmd, char *cmd, int fd_stderr);

int	ft_read_line(char **env);

t_kval  *ft_kval_init(const char *env_line);

t_arr  *ft_env_init(char **env);
int	ft_builtin_cd_set_env(
	t_arr **envp, const char *key, const char *value, int	fd_stderr);
char *ft_builtin_cd_absolute_path(const char *old_path, const char *new_path);
int	ft_builtin_cd_is_existing_file(
	const char *path_absolute, const char *new_path, int	fd_stderr);
int	ft_builtin_cd_change_directory(
	t_arr **env, const char *old_path, const char *new_path, int fd_stderr);
int	ft_builtin_env_print(t_arr *env, int fd_stdout);
int	ft_builtin_env_setenv(t_arr *env, char *var, int fd_stderr);
int	ft_builtin_env_set_var_is_cmd(char **cmd, char ***tab_cmd);
int	ft_builtin_env_free_kval(t_arr *env);
int	ft_builtin_env_set_var_cmd(char **cmd, t_arr *env, bool *is_env_prev);
int	ft_free_name_value(char **name, char **value);

# endif
