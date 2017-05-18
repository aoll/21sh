/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_father.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 12:30:24 by alex              #+#    #+#             */
/*   Updated: 2017/05/18 14:11:28 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** processus father after a fork write in different tube for redirection and
** next command after pipe
*/

int	ft_fork_father(
	t_fork *st_fork, t_tube *tab_tube, t_tab_tube *array_tube, t_arr_fd *arr_fd)
{
	ft_fork_is_stdin_fd(st_fork, tab_tube, arr_fd, array_tube);
	if (st_fork->index_builtin > B_ENV)
	{
		ft_builtin_exec(
			st_fork,
			st_fork->env,
			array_tube->tube_fork_stdout_tmp[1],
			array_tube->tube_fork_stderr_tmp[1]);
	}
	// ft_putstr("\nmidlle dup \n");
	wait(&st_fork->status);
	// ft_putstr("\nmidlle -- dup \n");
	ft_fork_set_tube_father(st_fork, array_tube, tab_tube, arr_fd);
	// ft_putstr("\nmidlle ++ dup \n");
	if (st_fork->i < st_fork->nb_pipe && !st_fork->err)
	{
		// ft_putstr("\ndup 0\n");
		close(tab_tube[st_fork->i].tube[1]);
		dup2(tab_tube[st_fork->i].tube[0], 0);
	}
	ft_arr_close_arr_fd(arr_fd);
	while (arr_fd->arr_d_end_word->length)
		free(ft_arr_pop(arr_fd->arr_d_end_word, 0));
	st_fork->i++;
	// ft_putstr("\nby dup\n");
	return (EXIT_SUCCESS);
}
