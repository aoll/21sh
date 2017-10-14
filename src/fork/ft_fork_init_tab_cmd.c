/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_init_tab_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:27:10 by alex              #+#    #+#             */
/*   Updated: 2017/10/11 12:23:44 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** init a char ** by split with SPACE_SEPARATOR
*/

int	ft_fork_init_tab_cmd(t_fork *st_fork, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	ft_array_free(&st_fork->tab_cmd);
	if (!(st_fork->tab_cmd = ft_strsplit(cmd, SPACE_SEPARATOR)))
		return (EXIT_FAILURE);
	if (!st_fork->tab_cmd[0])
		return (EXIT_FAILURE);
	while (st_fork->tab_cmd[i])
	{
		if (st_fork->tab_cmd[i][0] == '"' || st_fork->tab_cmd[i][0] == '\'')
		{
			tmp = ft_strsub(
				st_fork->tab_cmd[i], 1, ft_strlen(st_fork->tab_cmd[i]) - 2);
			free(st_fork->tab_cmd[i]);
			st_fork->tab_cmd[i] = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
