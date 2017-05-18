/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_list_fd_tmp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 17:36:02 by alex              #+#    #+#             */
/*   Updated: 2017/05/18 15:33:52 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** create and test permission of file for cmd
*/

int	ft_fork_list_fd_tmp(char **cmd, t_arr_fd *arr_fd, char **error_ptr)
{
	int				i;
	int				*fd;
	int				err;

	i = 0;
	fd = NULL;
	while (cmd[i])
	{
		if ((err = ft_fork_list_fd(&cmd[i], arr_fd, error_ptr)))
		{
			ft_arr_close_arr_fd(arr_fd);
			return (EXIT_FAILURE);
		}
		i++;
	}
	ft_arr_close_arr_fd(arr_fd);
	return (EXIT_SUCCESS);
}
