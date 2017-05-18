/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_pid_son.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 11:38:59 by alex              #+#    #+#             */
/*   Updated: 2017/05/18 11:20:56 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** is the processus son, set the tube for processus comminucation
** execute the command
*/

int	ft_fork_pid_son(t_fork *st_fork, t_arr_fd *arr_fd, t_tab_tube *array_tube)
{
	char	*path_tmp;
	int		re;

	re = 0;
	ft_signal_restore();
	// ft_putstr("\nson hy\n");
	ft_fork_set_tube(arr_fd, array_tube, st_fork->i, st_fork->nb_pipe);
	ft_fork_is_error_ptr(&st_fork->error_ptr, arr_fd);
	path_tmp = NULL;
	if (!st_fork->index_builtin && *st_fork->tab_cmd)
	{
		path_tmp = ft_fork_init_path(
			st_fork->env_copy, st_fork->tab_cmd, &st_fork->err);
	}
	if (!st_fork->index_builtin && !st_fork->err && *st_fork->tab_cmd)
		re = ft_fork_son_exec(path_tmp, st_fork->tab_cmd, st_fork->envp);
	ft_str_free(&path_tmp);
	if (re != B_ECHO)
		ft_fork_command_not_found(
			&st_fork->tab_cmd, st_fork->index_builtin, arr_fd);
	// ft_putstr("\nson by\n");
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
