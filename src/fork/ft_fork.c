/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:46:59 by alex              #+#    #+#             */
/*   Updated: 2017/05/16 08:28:06 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int	ft_fork_is_exit(
	t_fork *st_fork, t_arr *env, t_tab_tube *array_tube, t_arr_fd *arr_fd)
{
	if (ft_fork_check_is_builtin_exit(st_fork, arr_fd) == B_EXIT)
		return (B_EXIT);
	ft_fork_set_env_copy(st_fork, env, array_tube);
	if (ft_fork_check_is_builtin_exit(st_fork, arr_fd) == B_EXIT)
		return (B_EXIT);
	return (EXIT_SUCCESS);
}

int			ft_fork(char **cmd, t_tube *tab_tube, t_arr **env, int nb_pipe)
{
	t_tab_tube		array_tube;
	t_arr_fd		arr_fd;
	t_fork			st_fork;

	ft_fork_init_st_fork(&st_fork, env);
	if ((st_fork.err = ft_fork_init_loop(
		&st_fork, &arr_fd, (const char **)cmd, nb_pipe)))
		return (EXIT_FAILURE);
	while (st_fork.i < st_fork.nb_pipe + 1)
	{
		if ((st_fork.err = ft_fork_set_tube_fd(
			&st_fork, &array_tube, &arr_fd, &cmd[st_fork.i])))
			return (EXIT_FAILURE);
		if ((st_fork.err = ft_fork_init_tab_cmd(&st_fork, cmd[st_fork.i])))
			break ;
		if (ft_fork_is_exit(&st_fork, *env, &array_tube, &arr_fd) == B_EXIT)
			return (B_EXIT);
		if ((st_fork.err = ft_fork_create_process(
			&st_fork, &arr_fd, &array_tube, tab_tube)))
			return (EXIT_FAILURE);
	}
	return (ft_fork_free_st_fork_and_arr_fd(&st_fork, &arr_fd));
}
