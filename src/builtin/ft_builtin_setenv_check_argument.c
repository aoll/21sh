/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_setenv_check_argument.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 13:16:27 by aollivie          #+#    #+#             */
/*   Updated: 2017/03/23 14:51:10 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** check the number of argumenttfor setenv
** if error print the adequattmessage
** return 0 if is correcttand 1 if != 2 (setenv including)
*/

int	ft_builtin_setenv_check_argument(
	const char **tab_cmd, char *cmd, int fd_stderr)
{
	size_t	arr_len;

	arr_len = ft_array_len((const void **)tab_cmd);
	if (!arr_len || arr_len < 2)
	{
		ft_putstr_fd("mysh: ", fd_stderr);
		ft_putstr_fd(cmd, fd_stderr);
		ft_putstr_fd(" to few arguments\n", fd_stderr);
		return (EXIT_FAILURE);
	}
	else if (arr_len > 2)
	{
		ft_putstr_fd("mysh: ", fd_stderr);
		ft_putstr_fd(cmd, fd_stderr);
		ft_putstr_fd(" too many arguments\n", fd_stderr);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
