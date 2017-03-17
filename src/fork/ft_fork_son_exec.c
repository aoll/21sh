/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_son_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:49:12 by alex              #+#    #+#             */
/*   Updated: 2017/02/10 11:24:09 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_fork_son_exec(char *path_cmd, char **tab_cmd, char **envp)
{
	execve(path_cmd, tab_cmd, envp);
	return (EXIT_SUCCESS);
}
