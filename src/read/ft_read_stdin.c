/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:19:13 by aollivie          #+#    #+#             */
/*   Updated: 2017/05/17 19:52:31 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int	ft_read_init_term(struct termios *term, t_cursor *cursor)
{
	int err;

	cursor->is_env = false;
	if ((err = ft_get_term(term)))
	{
		if (err == -2)
			exit(0);
		fprintf(stderr, "%s\n", "is_env false" );
		cursor->is_env = false;
		signal(SIGINT, ft_signal_sigint_not_env);
	}
	else
	{
		fprintf(stderr, "%s\n", "is_env true" );
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
	
	fprintf(stderr, "%s\n", "is_env" );
	return (EXIT_SUCCESS);
}

static int	ft_read_stdin_loop(
	t_cursor *cursor, t_list_arr *list_arr, struct termios *term, char **line)
{
	int err;

	if (cursor->is_env)
	{
		if ((err = ft_read_env(cursor, list_arr, term)) == -1)
			return (-1);
		if (err != -2)
			return (err);
	}
	else
	{
		if ((err = ft_read_no_env(
			cursor, list_arr, line, term)) == -1)
			return (-1);
		if (err == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	}
	return (-1);
}

int			ft_read_stdin(char **envp)
{
	t_read r;

	if ((r.err = ft_read_init_term(&r.term, &r.cursor)))
		return (EXIT_FAILURE);
	ft_init_init_term_arr(&r.list_arr, envp, &r.cursor, &r.terminal_size_old);
	while (1 == 1)
	{
		if (ft_check_loop(&r.terminal_size_old, &r.cursor, &r.list_arr))
			continue;
		if ((r.err = ft_read_stdin_loop(
			&r.cursor, &r.list_arr, &r.term, &r.line)) != -1)
			return (r.err);
	}
	return (EXIT_SUCCESS);
}
