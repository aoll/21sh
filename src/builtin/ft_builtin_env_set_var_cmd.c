/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env_set_var_cmd.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:33:51 by aollivie          #+#    #+#             */
/*   Updated: 2017/03/23 14:33:58 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_builtin_env_set_var_cmd(char **cmd, t_arr *env, bool *is_env_prev)
{
	if (!(ft_strcmp(*cmd, "-i")) && *is_env_prev)
	{
		ft_builtin_env_free_kval(env);
	}
	else if ((ft_strcmp(*cmd, "env")))
	{
		return (1);
	}
	*is_env_prev = true;
	return (EXIT_SUCCESS);
}
