/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_create_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 12:46:21 by alex              #+#    #+#             */
/*   Updated: 2017/10/14 11:00:49 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"


void cleanup(int signal) {
	while (waitpid((pid_t) (-1), 0, WNOHANG) > 0) {}
}

/*
** create_process and exec commande
*/

int	ft_fork_create_process(
	t_fork *st_fork, t_arr_fd *arr_fd, t_tab_tube *array_tube, t_tube *tab_tube, char **cmd,  t_arr **env)
{
	pid_t			pid;
	int status;

	signal(SIGCHLD, cleanup);
	pid = 0;
	if ((pid = fork()) == -1)
	{
		return (EXIT_FAILURE);
	}
	if (!pid)
	{
		if (st_fork->nb_pipe && st_fork->i < st_fork->nb_pipe && !st_fork->err)
		{
			close(tab_tube[st_fork->i].tube[0]);
			dup2(tab_tube[st_fork->i].tube[1], 1);
		}
		ft_fork_pid_son(st_fork, arr_fd, array_tube);
		return (EXIT_FAILURE);
	}
	else if (pid)
	{
		if (st_fork->i < st_fork->nb_pipe)
		{
			st_fork->i++;
			ft_fork_re(cmd, tab_tube, env, st_fork, arr_fd);
		}
		// waitpid(-1, &status, WNOHANG | WUNTRACED);


		// wait(NULL);
		// if (st_fork->nb_pipe && st_fork->i < st_fork->nb_pipe && !st_fork->err)
		// {
		// 	close(tab_tube[st_fork->i].tube[1]);
		// 	// fdin = tab_tube[st_fork->i].tube[0];
		// 	dup2(tab_tube[st_fork->i].tube[0], 0);
		// }

		// st_fork->i++;
		// ft_fork_father(st_fork, tab_tube, array_tube, arr_fd);
	}
	if (st_fork->i < st_fork->nb_pipe)
		close(tab_tube[st_fork->i].tube[0]);
	return (EXIT_SUCCESS);
}
