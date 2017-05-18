/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_check_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:17:21 by alex              #+#    #+#             */
/*   Updated: 2017/03/15 21:48:58 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** iter every line and apply a batery of function to check the good grammar
** of different command
*/

static int	ft_parse_check_error_redirect(t_arr *cmd)
{
	int				err;

	if ((err = ft_parse_check_double(cmd, S_LEFT_REDIRECT)))
	{
		ft_putstr_fd("\nmysh: parse error near `<'", STDERR);
		return (EXIT_FAILURE);
	}
	else if ((err = ft_parse_check_double(cmd, D_LEFT_REDIRECT)))
	{
		ft_putstr_fd("\nmysh: parse error near `<'", STDERR);
		return (EXIT_FAILURE);
	}
	else if ((err = ft_parse_check_double(cmd, S_RIGHT_REDIRECT)))
	{
		ft_putstr_fd("\nmysh: parse error near `>'", STDERR);
		return (EXIT_FAILURE);
	}
	else if ((err = ft_parse_check_double(cmd, D_RIGHT_REDIRECT)))
	{
		ft_putstr_fd("\nmysh: parse error near `>'", STDERR);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_parse_check_error_stdout_sdterr_pipe(t_arr *cmd)
{
	int				err;

	if ((err = ft_parse_check_double(cmd, STDOUT_STDERR_REDIRECT)))
	{
		ft_putstr_fd("\nmysh: parse error near `>'", STDERR);
		return (EXIT_FAILURE);
	}
	else if ((err = ft_parse_check_double(cmd, PIPE)))
	{
		ft_putstr_fd("\nmysh: parse error near `|'", STDERR);
		return (EXIT_FAILURE);
	}
	else if ((err = ft_parse_check_end_space(cmd)))
	{
		ft_putstr_fd("\nmysh: parse error near `\\n'", STDERR);
		return (EXIT_FAILURE);
	}
	else if ((err = ft_parse_check_file_redirect(cmd)))
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			ft_parse_check_error(t_arr *cmd)
{
	int				err;

	if ((err = ft_parse_check_error_redirect(cmd)))
	{
		return (EXIT_FAILURE);
	}
	if ((err = ft_parse_check_error_stdout_sdterr_pipe(cmd)))
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
