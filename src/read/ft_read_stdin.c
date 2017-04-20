/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:19:13 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/20 11:33:31 by aollivie         ###   ########.fr       */
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
	struct			winsize terminal_size_old;
	struct termios	term;
	char			*line;
	t_list_arr		list_arr;
	int 			err;

	if ((err = ft_read_init_term(&term, &cursor)))
		return (EXIT_FAILURE);
	ft_init_init_term_arr(&list_arr, envp, &cursor, &terminal_size_old);
	while (1 == 1)
	{
		if (ft_check_loop(&terminal_size_old, &cursor, &list_arr))
			continue;
		if (cursor.is_env)
		{
			if ((err = ft_read_env(&cursor, &list_arr, &term)) == -1)
				continue;
			if (err != -2)
				return (err);
		}
		else
		{
			if ((err = ft_read_no_env(&cursor, &list_arr, &line, &term)) == -1)
				continue;
			else if (err == EXIT_SUCCESS)
			{
				return (EXIT_SUCCESS);
			}
		}
	}
	return (EXIT_SUCCESS);
}
