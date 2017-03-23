/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_check_is_builtin_exit.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 11:25:10 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 11:33:58 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_fork_check_is_builtin_exit(t_fork *st_fork, t_arr_fd *arr_fd)
{
	if ((st_fork->index_builtin = ft_is_builtin(st_fork->tab_cmd[0])))
	{
		if (st_fork->index_builtin == B_EXIT)
		{
			if (st_fork->env_copy)
			{
				ft_arr_free(st_fork->env_copy);
				st_fork->env_copy = NULL;
			}
			ft_array_free(&st_fork->envp);
			ft_arr_free_arr_fd(arr_fd);
			ft_array_free(&st_fork->tab_cmd);
			return (B_EXIT);
		}
	}
	return (EXIT_SUCCESS);
}
