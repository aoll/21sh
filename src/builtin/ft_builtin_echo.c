/* ************************************************************************** */
/*                                      */
/*                            :::   ::::::::  */
/*  ft_builtin_echo.c                 :+:   :+:  :+:  */
/*                          +:+ +:+     +:+   */
/*  By: alex <alex@student.42.fr>         +#+ +:+    +#+    */
/*                        +#+#+#+#+#+  +#+      */
/*  Created: 2017/03/15 11:21:32 by alex       #+#  #+#       */
/*  Updated: 2017/03/15 11:27:54 by alex       ###  ########.fr    */
/*                                      */
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
