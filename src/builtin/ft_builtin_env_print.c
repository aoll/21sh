/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:27:26 by aollivie          #+#    #+#             */
/*   Updated: 2017/03/23 14:27:28 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** print the env on a fd give in parameter
*/

int	ft_builtin_env_print(t_arr *env, int fd_stdout)
{
	int		i;
	t_kval	*kval;

	i = 0;
	if (!env)
	{
		return (EXIT_SUCCESS);
	}
	while (i < (int)env->length)
	{
		kval = *(t_kval **)((unsigned char *)env->ptr + i * env->sizeof_elem);
		ft_putstr_fd(kval->key, fd_stdout);
		ft_putstr_fd("=", fd_stdout);
		if (kval->value)
		{
			ft_putstr_fd(kval->value, fd_stdout);
		}
		ft_putstr_fd("\n", fd_stdout);
		i++;
	}
	return (EXIT_SUCCESS);
}
