/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env_set_var_is_cmd.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:30:08 by aollivie          #+#    #+#             */
/*   Updated: 2017/03/23 14:30:10 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_builtin_env_set_var_is_cmd(char **cmd, char ***tab_cmd)
{
	int		len;
	char	**tmp;

	len = ft_array_len((const void **)cmd);
	if (!(tmp = ft_array_str_new(len)))
	{
		return (EXIT_FAILURE);
	}
	len = 0;
	while (*cmd)
	{
		tmp[len] = ft_strdup(*cmd);
		free(*cmd);
		cmd++;
		len++;
	}
	free(*tab_cmd);
	*tab_cmd = tmp;
	return (EXIT_SUCCESS);
}
