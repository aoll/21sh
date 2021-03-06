/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unsetenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 13:16:41 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/21 15:24:16 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** pop and free the kval
*/

static int	ft_builtin_unsetenv_pop_key(t_arr **env, int index)
{
	t_kval *kval;

	kval = ft_arr_pop(*env, index);
	if (kval->key)
	{
		free(kval->key);
	}
	if (kval->value)
	{
		free(kval->value);
	}
	if (kval)
	{
		free(kval);
	}
	return (EXIT_SUCCESS);
}

/*
** if the var is presenttin the env ittwill be delete else sucess is returned
** and the env stay the same
*/

int			ft_builtin_unsetenv(
	const char **tab_cmd, t_arr **env, int fd_stderr)
{
	int		err;
	int		index;
	t_arr	*envp;

	envp = *env;
	if ((err = ft_builtin_setenv_check_argument(
		tab_cmd, "unsetenv", fd_stderr)))
	{
		return (EXIT_FAILURE);
	}
	index = ft_arr_indexof((const t_arr *)envp, (const void *)tab_cmd[1]);
	if (index >= 0 && index < (int)envp->length)
	{
		ft_builtin_unsetenv_pop_key(env, index);
	}
	return (EXIT_SUCCESS);
}
