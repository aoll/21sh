/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:19:13 by aollivie          #+#    #+#             */
/*   Updated: 2017/03/23 15:19:41 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int ft_read_stdin(char **envp)
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
