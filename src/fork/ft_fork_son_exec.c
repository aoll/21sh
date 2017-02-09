/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_son_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:49:12 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 17:02:48 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int  ft_fork_son_exec(char *path_cmd, char **tab_cmd, char **envp)
{
  ft_signal_restore();
  execve(path_cmd, tab_cmd, envp);
  return (EXIT_SUCCESS);
}
