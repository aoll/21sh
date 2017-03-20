/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 09:26:47 by alex              #+#    #+#             */
/*   Updated: 2017/03/20 09:26:48 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

#include <signal.h>

/*
** print the key
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

static int	ft_get_term(struct termios *term)
{
	char			*name_terminal;

	if (!(name_terminal = getenv("TERM"))) //retour le nom du terminal
		return (EXIT_FAILURE);
	if (tgetent(NULL, name_terminal) != 1) //check if name_terminal exist and if
		return (EXIT_FAILURE);   //the terminfo databbase could be found
	if (tcgetattr(0, term) == -1) // rempli la struct termios avec les
		return (EXIT_FAILURE);  // possibilités du terminal
	return (EXIT_SUCCESS);
}
int	ft_init_terminal(void)
{
	struct			termios term;

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

int	ft_get_term_restore(struct termios *term)
{
	char			*name_terminal;

	// if (!(name_terminal = getenv("TERM"))) //retour le nom du terminal
	// return (EXIT_FAILURE);
	// if (tgetent(NULL, name_terminal) != 1) //check if name_terminal exist and if
	// return (EXIT_FAILURE);   //the terminfo databbase could be found
	// if (tcgetattr(0, term) == -1) // rempli la struct termios avec les
	// return (EXIT_FAILURE);  // possibilités du terminal
	term->c_lflag |= ICANON;
	term->c_lflag |= ECHO;
	if (tcsetattr(0, 0, term) == -1)
		return (-1);
	return (EXIT_SUCCESS);
}

/*
** function for print some char * was stocked in a t_arr like elem
** is give for arr->f_print, print some elem
*/

void ft_arr_putchar(const void *s)
{
	char			*s_line;

	if (!s)
	{
		return;
	}
	s_line = *(char **)s;
	if (!s_line)
	{
		return;
	}
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

void *ft_arr_strdup(const void *s, size_t n)
{
	void			*new;

	(void)n;
	if (!s)
	{
		return (NULL);
	}
	if (!(new = ft_strnew(8)))
	{
		return (NULL);
	}
	ft_memcpy(new, *((char **)s), 8);
	// new = ft_strdup(*((char **)s));
	return (new);
}

/*
** return a fresh pointeur on a copy of a kval *
** in case of fail NULL is returned
*/

t_kval *ft_kval_dup(const t_kval *old)
{
	t_kval			*new;

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

void *ft_arr_kvaldup(const void *s, size_t n)
{
	void			*new;

	(void)n;
	if (!s)
	{
		return (NULL);
	}
	new = ft_kval_dup(*((t_kval **)s));
	return (new);
}

/*
** Apply n time the command given in param
*/

int	ft_term_apply_cmd(char *cmd, int n)
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

/*
** move the cursor to a new position x
*/

int	ft_cursor_move_x(int new_pos_x, char *cmd)
{
	if (!cmd)
	{
		return (EXIT_FAILURE);
	}
	tputs(tgoto(cmd, 0, new_pos_x), 0, &my_putchar);
	return (EXIT_SUCCESS);
}

int	ft_init_cursor_cmd(t_cursor *cursor)
{
	cursor->up = tgetstr("up", NULL);
	cursor->down = tgetstr("do", NULL);
	cursor->left = tgetstr("le", NULL);
	cursor->right = tgetstr("nd", NULL);
	cursor->sup_char = tgetstr("dc", NULL);
	cursor->move_x = tgetstr("ch", NULL);
	cursor->clear_current_line = tgetstr("ce", NULL); //e
	cursor->clear_down = tgetstr("cd", NULL);
	cursor->mode_insertion = tgetstr("im", NULL);
	cursor->mode_insertion_end = tgetstr("ei", NULL);
	cursor->mode_basic_video = tgetstr("me", NULL);
	cursor->mode_reverse_video = tgetstr("mr", NULL);
	cursor->save_cursor_position = tgetstr("sc", NULL);
	cursor->restore_cursor_position = tgetstr("rc", NULL);
	cursor->scroll_down = tgetstr("sr", NULL);
	cursor->scroll_up = tgetstr("sf", NULL);
	cursor->left_corner_up = tgetstr("ho", NULL);
	cursor->left_corner_down = tgetstr("ll", NULL);
	cursor->clear_all_the_screen = tgetstr("cl", NULL);
	cursor->marge = tgetstr("am", NULL);
	return (EXIT_SUCCESS);
}

/*
** free all command save in struct cursor
*/

int	ft_free_cursor(t_cursor *cursor)
{
	if (cursor->prompt)
	{
		free(cursor->prompt);
	}
	return (EXIT_SUCCESS);
}

/*
** init the cursor position
*/

int	ft_init_cursor_position(t_cursor *cursor)
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


int read_stdin(char **envp)
{
	t_cursor		cursor;

	int				rd;

	struct			winsize terminal_size_old;
	struct			termios term;
	char			*line;
	t_list_arr		list_arr;

	cursor.is_env = false;
	if (ft_get_term(&term))
	{
		cursor.is_env = false;
		signal(SIGINT, ft_signal_sigint_not_env);
	}
	else
	{
		cursor.is_env = true;
		term.c_lflag &= ~(ICANON);
		term.c_lflag &= ~(ECHO);
		term.c_cc[VMIN] = 0;
		term.c_cc[VTIME] = 1;
		if (tcsetattr(0, TCSADRAIN, &term) == -1)
		{
			return (EXIT_FAILURE);
		}
		ft_init_cursor_cmd(&cursor);
	}

	list_arr.env = ft_env_init(envp);
	list_arr.history_line = ft_arr_new(1, sizeof(t_arr *));
	list_arr.current_line = ft_arr_new(1, sizeof(t_arr *));
	ft_arr_push(list_arr.history_line, list_arr.current_line, 0);
	list_arr.arr = ft_arr_new(1, sizeof(char *));
	ft_arr_push(list_arr.current_line, list_arr.arr, 0);
	list_arr.arr->f_print = &ft_arr_putchar;
	list_arr.arr->f_dup_elem = &ft_arr_strdup;

	ft_init_cursor_position(&cursor);
	//chaque apel a malloc doit etre proteger soit dit au passage!!!
	ft_terminal_winsize(&(cursor.terminal_size)); // a checker le retour

	list_arr.select_line = ft_arr_new(1, sizeof(char *));
	list_arr.copy_line = NULL;
	list_arr.select_line->f_print = &ft_arr_putchar;
	list_arr.select_line->f_dup_elem = &ft_arr_strdup;

	list_arr.buff = ft_strnew(8);
	ft_bzero(list_arr.buff, 8);
	ft_cursor_save_position();
	ft_putstr(cursor.prompt);
	ft_terminal_winsize(&terminal_size_old); // a checker le retour
	ft_terminal_winsize(&(cursor.terminal_size)); // a checker le retour
	while (1 == 1)
	{

		ft_terminal_winsize(&terminal_size_old); // a checker le retour
		if (cursor.terminal_size.ws_col != terminal_size_old.ws_col || cursor.terminal_size.ws_row != terminal_size_old.ws_row)
		{
			ft_cursor_resize(&cursor, list_arr.arr, &terminal_size_old);
		}
		if (g_is_ctrl_c_father)
		{
			if (cursor.is_env)
			{
				ft_read_ctrl_c_env(&cursor, list_arr.arr);
				ft_cursor_valide_line(&cursor, &list_arr.history_line, &list_arr.current_line, &list_arr.arr);
				ft_bzero(list_arr.buff, 8);
				continue;
			}
		}
		if (cursor.is_env)
		{
			if ((rd = read(0, list_arr.buff, 8)) > 0)
			{
				// ft_print_key(list_arr.buff);
				// continue;
				cursor.is_select = false;
				if (!(ft_read_parse((const char *)list_arr.buff, &cursor, &list_arr)))
				{
				ft_bzero(list_arr.buff, 8);
				if (!cursor.is_select && list_arr.select_line->length && list_arr.arr->length)
				{
					ft_cursor_deselect_all(&cursor, list_arr.arr, list_arr.select_line);
				}
				continue;
				}
				else if (!(ft_read_parse_eof(&cursor, &list_arr, &term, false)))
				{
				return (EXIT_SUCCESS);
				}
				//enter
				else if ((!cursor.dquote && !cursor.quote && list_arr.buff[0] == 10 && !list_arr.buff[1] && !list_arr.buff[2] && !list_arr.buff[3] && !list_arr.buff[4] && !list_arr.buff[5] && !list_arr.buff[6] && !list_arr.buff[7]))
				{
				if (cursor.is_env)
				{
					ft_cursor_end(&cursor, list_arr.arr);
				}
				list_arr.tab_cmds = ft_parse_line(list_arr.arr);
				if (list_arr.tab_cmds)
				{
					if (cursor.is_env)
					{
					ft_term_apply_cmd(cursor.mode_insertion_end, 1);
					if (ft_get_term_restore(&term))
					return (EXIT_FAILURE);
					}
					ft_putstr("\n");
					signal(SIGINT, ft_signal_sigint_chariot);
					if (ft_fork_loop(&list_arr.env, list_arr.tab_cmds) == B_EXIT)
					{
					if (list_arr.tab_cmds)
					{
					 if (list_arr.tab_cmds->length)
					 {
					 ft_arr_free(ft_arr_pop(list_arr.tab_cmds, 0));
					 }
					 if (list_arr.tab_cmds->ptr)
					 {
					 free(list_arr.tab_cmds->ptr);
					 }
					 free(list_arr.tab_cmds);
					 list_arr.tab_cmds = NULL;
					}
					ft_read_parse_eof(&cursor, &list_arr, &term, true);
					return (EXIT_SUCCESS);
					}
					signal(SIGINT, ft_signal_sigint_c);
					if (list_arr.tab_cmds)
					{
					if (list_arr.tab_cmds->length)
					{
					 ft_arr_free(ft_arr_pop(list_arr.tab_cmds, 0));
					}
					if (list_arr.tab_cmds->ptr)
					{
					 free(list_arr.tab_cmds->ptr);
					}
					free(list_arr.tab_cmds);
					list_arr.tab_cmds = NULL;
					}
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

				}
				else
				{
					ft_putstr("\n");
				}
				ft_cursor_valide_line(&cursor, &list_arr.history_line, &list_arr.current_line, &list_arr.arr);
				}
				else //everithing else the previous command and past cmd - v
				{
				ft_cursor_add_char(&cursor, list_arr.arr, list_arr.buff);
				}
				// delete all char reverse video and normal and rewrite in normal video
				if (!cursor.is_select && list_arr.select_line->length && list_arr.arr->length)
				{
				ft_cursor_deselect_all(&cursor, list_arr.arr, list_arr.select_line);
				}
				ft_bzero(list_arr.buff, 8);
			}
		}
		else
		{
			// line = ft_strnew(BUFF_SIZE);
			line = NULL;
			if (g_is_ctrl_c_father)
			{
				g_is_ctrl_c_father = 0;
				ft_str_free(&line);
				continue;
			}
			if (get_next_line(0, &line))
			{
				while (list_arr.arr->length)
				{
				free(ft_arr_pop(list_arr.arr, 0));
				}
				ft_arr_str(list_arr.arr, line);
				if (line)
				{
				free(line);
				line = NULL;
				}
				list_arr.tab_cmds = ft_parse_line(list_arr.arr);
				if (list_arr.tab_cmds)
				{
				ft_fork_loop(&list_arr.env, list_arr.tab_cmds);
				}
				if (list_arr.tab_cmds)
				{
				if (list_arr.tab_cmds->length)
				{
					ft_arr_free(ft_arr_pop(list_arr.tab_cmds, 0));
				}
				if (list_arr.tab_cmds->ptr)
				{
					free(list_arr.tab_cmds->ptr);
				}
				free(list_arr.tab_cmds);
				list_arr.tab_cmds = NULL;
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
				if (!(ft_read_parse_eof(&cursor, &list_arr, &term, true)))
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



void ft_loop(char **env)
{

	read_stdin(env);
	return;
}

void ft_read_line(char **env)
{
	ft_signal_init();
	ft_loop(env);
	return;
}
