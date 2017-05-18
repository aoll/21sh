/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:50:50 by aollivie          #+#    #+#             */
/*   Updated: 2017/05/18 17:58:07 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int	ft_echo_check_quote(char c, bool *dquote, bool *quote)
{
	if (c == '\'' && !*dquote)
	{
		*quote = !*quote;
		return (1);
	}
	if (c == '"' && !*quote)
	{
		*dquote = !*dquote;
		return (1);
	}
	return (EXIT_SUCCESS);
}

static int	ft_echo_print(char *s)
{
	bool quote;
	bool dquote;

	quote = false;
	dquote = false;
	while (*s)
	{
		if (ft_echo_check_quote(*s, &dquote, &quote))
		{
			s++;
			continue;
		}
		ft_putchar(*s);
		s++;
	}
	return (EXIT_SUCCESS);
}

/*
** print the argumenttafter echo
*/

int			ft_builtin_echo(char **tab_cmd, t_arr **env)
{
	int	i;

	(void)env;
	i = 1;
	while (tab_cmd[i])
	{
		ft_echo_print(tab_cmd[i]);
		i++;
		if (tab_cmd[i])
		{
			ft_putstr(" ");
		}
	}
	ft_putstr("\n");
	return (EXIT_SUCCESS);
}
