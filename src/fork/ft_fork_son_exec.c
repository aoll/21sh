/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_son_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:49:12 by alex              #+#    #+#             */
/*   Updated: 2017/04/24 22:17:31 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_fork_son_exec(char *path_cmd, char **tab_cmd, char **envp)
{
	int i;
	char *tmp;

	i = 0;
	if (!ft_strcmp(tab_cmd[0], "echo"))
	{
		ft_builtin_echo(tab_cmd, NULL);
		return (B_ECHO);
	}
	while (tab_cmd[i])
	{
		if (tab_cmd[i][0] == '"' || tab_cmd[i][0] == '\'')
		{
			tmp = ft_strsub(tab_cmd[i], 1, ft_strlen(tab_cmd[i]) - 2 );
			free(tab_cmd[i]);
			tab_cmd[i] = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
	execve(path_cmd, tab_cmd, envp);
	return (EXIT_SUCCESS);
}
