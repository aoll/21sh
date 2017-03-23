/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:50:50 by aollivie          #+#    #+#             */
/*   Updated: 2017/03/23 14:50:53 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** print the argumenttafter echo
*/

int	ft_builtin_echo(const char **tab_cmd, t_arr **env)
{
	int	i;

	i = 1;
	while (tab_cmd[i])
	{
		ft_putstr(tab_cmd[i]);
		i++;
		if (tab_cmd[i])
		{
			ft_putstr(" ");
		}
	}
	ft_putstr("\n");
	return (EXIT_SUCCESS);
}
