/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_command_not_found.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 17:17:48 by alex              #+#    #+#             */
/*   Updated: 2017/02/08 17:19:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** if command not found print the correct message
*/

int	ft_fork_command_not_found(
	char ***tab_cmd, int index_builtin, t_arr_fd *arr_fd)
{
	if (!index_builtin)
	{
		ft_putstr_fd("21sh: command not found: ", STDERR);
		ft_putstr_fd(**tab_cmd, STDERR);
		ft_putstr_fd("\n", STDERR);
		ft_array_free(tab_cmd);
		ft_arr_free_arr_fd(arr_fd);
	}
	return (EXIT_SUCCESS);
}
