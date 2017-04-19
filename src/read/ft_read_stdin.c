/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:19:13 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/19 17:05:44 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_read_init_term(struct termios *term, t_cursor *cursor)
{
	int err;

	cursor->is_env = false;
	if ((err = ft_get_term(term)))
	{
		cursor->is_env = false;
		signal(SIGINT, ft_signal_sigint_not_env);
	}
	else
	{
		cursor->is_env = true;
		term->c_lflag &= ~(ICANON);
		term->c_lflag &= ~(ECHO);
		term->c_cc[VMIN] = 0;
		term->c_cc[VTIME] = 1;
		if (tcsetattr(0, TCSADRAIN, term) == -1)
		{
			return (EXIT_FAILURE);
		}
		ft_init_cursor_cmd(cursor);
	}
	return (EXIT_SUCCESS);
}

int ft_read_stdin(char **envp)
{
	t_cursor		cursor;

	int					rd;

	struct			winsize terminal_size_old;
	struct termios	term;
	char			*line;
	t_list_arr		list_arr;
	int 			err;

	if ((err = ft_read_init_term(&term, &cursor)))
	{
		return (EXIT_FAILURE);
	}
	ft_init_init_term_arr(&list_arr, envp, &cursor, &terminal_size_old);
	while (1 == 1)
	{
		if (ft_check_loop(&terminal_size_old, &cursor, &list_arr))
		{
			continue;
		}
		if (cursor.is_env)
		{
			if ((rd = read(0, list_arr.buff, 8)) > 0)
			{
				cursor.is_select = false;
				if (!(ft_read_parse((const char *)list_arr.buff, &cursor, &list_arr)))
				{
					ft_read_deselect(&list_arr, &cursor);
					continue;
				}
				else if (!(ft_read_parse_eof(&cursor, &list_arr, &term, false)))
				{
					return (EXIT_SUCCESS);
				}
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
						if (ft_fork_loop(&list_arr.env, list_arr.tab_cmds) == B_EXIT)
						{
							ft_read_exit(&list_arr, &cursor, &term);
							return (EXIT_SUCCESS);
						}
						ft_putstr("\n");
						signal(SIGINT, ft_signal_sigint_chariot);
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
				else
				{
					ft_cursor_add_char(&cursor, list_arr.arr, list_arr.buff);
				}
				if (!cursor.is_select && list_arr.select_line->length && list_arr.arr->length)
				{
					ft_cursor_deselect_all(&cursor, list_arr.arr, list_arr.select_line);
				}
				ft_bzero(list_arr.buff, 8);
			}
		}
		else
		{
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
