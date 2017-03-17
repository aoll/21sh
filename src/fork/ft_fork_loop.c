/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 14:13:55 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 14:17:16 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** fork
*/

int	ft_fork_loop(t_arr **env, t_arr *tab_cmds)
{
	int				index;
	t_arr			*cmd;
	char			*cmd_str;
	int				i_return;

	index = 0;
	cmd_str = NULL;
	while (index < (int)tab_cmds->length)
	{
		cmd = *(t_arr **)(
			(unsigned char *)tab_cmds->ptr + index * tab_cmds->sizeof_elem);
		cmd_str = ft_fork_str_from_arr(cmd);
		i_return = ft_fork_split_pipe(cmd_str, ft_fork_nb_pipe(cmd), env);
		ft_str_free(&cmd_str);
		if (i_return == B_EXIT)
		{
			return (i_return);
		}
		index++;
	}
	return (EXIT_SUCCESS);
}
