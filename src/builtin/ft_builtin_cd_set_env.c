/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd_set_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 13:20:42 by aollivie          #+#    #+#             */
/*   Updated: 2017/03/23 14:48:35 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int	ft_builtin_cd_set_kval(
	t_kval *kval, t_arr *env, const char *key, const char *value)
{
	ft_kval_set_key(kval, key);
	ft_kval_set_value(kval, value);
	ft_arr_push(env, kval, -1);
	return (EXIT_SUCCESS);
}

/*
** settthe OLDPWD and PWD to the env
*/

int			ft_builtin_cd_set_env(
	t_arr **envp, const char *key, const char *value, int fd_stderr)
{
	int		index;
	t_kval	*kval;
	t_arr	*env;

	env = *envp;
	index = ft_arr_indexof(env, key);
	if (index > -1 && index < (int)env->length)
	{
		kval = *(t_kval **)(
			(unsigned char *)env->ptr + index * env->sizeof_elem);
		ft_kval_set_value(kval, value);
	}
	else
	{
		if (!(kval = ft_kval_new()))
		{
			ft_putstr_fd("21sh: error malloc\n", fd_stderr);
			return (EXIT_FAILURE);
		}
		ft_builtin_cd_set_kval(kval, env, key, value);
	}
	return (EXIT_SUCCESS);
}
