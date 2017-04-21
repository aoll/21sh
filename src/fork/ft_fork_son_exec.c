/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_son_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:49:12 by alex              #+#    #+#             */
/*   Updated: 2017/04/21 19:29:12 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_fork_son_exec(char *path_cmd, char **tab_cmd, char **envp)
{
	if (!ft_strcmp(tab_cmd[0], "echo"))
	{
		ft_builtin_echo(tab_cmd, NULL);
		return (B_ECHO);
	}
	execve(path_cmd, tab_cmd, envp);
	return (EXIT_SUCCESS);
}
