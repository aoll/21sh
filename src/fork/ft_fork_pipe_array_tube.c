/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_pipe_array_tube.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:14:23 by alex              #+#    #+#             */
/*   Updated: 2017/02/08 15:16:27 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** pipe a liste of tube from a struct
*/

int	ft_fork_pipe_array_tube(t_tab_tube *array_tube)
{
	pipe(array_tube->tube_fork_stdin);
	pipe(array_tube->tube_fork_stdout);
	pipe(array_tube->tube_fork_stderr);
	pipe(array_tube->tube_fork_stdout_tmp);
	pipe(array_tube->tube_fork_stderr_tmp);
	return (EXIT_SUCCESS);
}
