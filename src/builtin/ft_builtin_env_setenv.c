/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env_setenv.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:29:11 by aollivie          #+#    #+#             */
/*   Updated: 2017/03/23 14:29:18 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** add or edit a var of the env
*/

int	ft_builtin_env_setenv(t_arr *env, char *var, int fd_stderr)
{
	char	*cmd;
	char	**tab_cmd;
	int		i;

	if (!(cmd = ft_strjoin("setenv ", var)))
	{
		ft_putstr_fd("21sh: error malloc\n", STDERR);
		return (EXIT_FAILURE);
	}
	if (!(tab_cmd = ft_strsplit(cmd, ' ')))
	{
		ft_putstr_fd("21sh: error malloc\n", STDERR);
		return (EXIT_FAILURE);
	}
	ft_builtin_setenv((const char **)tab_cmd, &env, fd_stderr);
	free(cmd);
	i = -1;
	while (tab_cmd[++i])
		free(tab_cmd[i]);
	free(tab_cmd);
	return (EXIT_SUCCESS);
}
