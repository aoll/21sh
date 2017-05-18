/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_split_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:52:41 by alex              #+#    #+#             */
/*   Updated: 2017/05/18 18:12:30 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** split the command line with the PIPE
** create a array of tube[2]
*/

static int	ft_init_tab_tube(t_tube **tab_tube_ptr, int nb_pipe)
{
	t_tube			*tab_tube;
	int				index;

	tab_tube = *tab_tube_ptr;
	tab_tube = NULL;
	if (nb_pipe)
	{
		if (!(tab_tube = malloc(sizeof(t_tube) * nb_pipe)))
		{
			return (EXIT_FAILURE);
		}
		index = 0;
		while (index < nb_pipe)
		{
			pipe(tab_tube[index].tube);
			index++;
		}
	}
	*tab_tube_ptr = tab_tube;
	return (EXIT_SUCCESS);
}

int			ft_fork_split_pipe(char *str, int nb_pipe, t_arr **env_ptr)
{
	char			**cmds;
	t_tube			*tab_tube;
	t_arr			*env;
	int				i_return;

	env = *env_ptr;
	if (ft_init_tab_tube(&tab_tube, nb_pipe))
	{
		return (EXIT_FAILURE);
	}
	if (!(cmds = ft_strsplit(str, PIPE)))
	{
		if (tab_tube)
			free(tab_tube);
		return (EXIT_FAILURE);
	}
	i_return = ft_fork(cmds, tab_tube, env_ptr, nb_pipe);
	ft_array_free(&cmds);
	if (tab_tube)
		free(tab_tube);
	return (i_return);
}
