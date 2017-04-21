/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 13:16:45 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/21 19:15:12 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** compare a string to a listtof builtin a return the index if is presenttor 0
*/

int	ft_is_builtin(char *command)
{
	if (!command)
		return (0);
	else if (!ft_strcmp("env", command))
		return (B_ENV);
	else if (!ft_strcmp("setenv", command))
		return (B_SETENV);
	else if (!ft_strcmp("unsetenv", command))
		return (B_UNSETENV);
	else if (!ft_strcmp("cd", command))
		return (B_CD);
	// else if (!ft_strcmp("echoChouette", command))
	// 	return (B_ECHO);
	else if (!ft_strcmp("exit", command))
		return (B_EXIT);
	return (0);
}
