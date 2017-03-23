/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_env_arr_to_tab_str.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 10:39:19 by alex              #+#    #+#             */
/*   Updated: 2017/03/17 12:08:31 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** return a new pointeur to a char **
*/

static int	ft_fork_env_arr_to_tab_str_init(t_arr *envp, char ***env_ptr)
{
	char			**env;

	env = *env_ptr;
	if (!envp)
	{
		return (EXIT_FAILURE);
	}
	if (!(env = malloc(sizeof(char *) * (envp->length + 1))))
	{
		return (EXIT_FAILURE);
	}
	env[envp->length] = NULL;
	*env_ptr = env;
	return (EXIT_SUCCESS);
}

static int	ft_fork_env_arr_to_tab_str_set_tab(
	t_kval *kv, char ***env_ptr, int index)
{
	char			**env;
	int				i;
	int				len;
	int				index_i;

	env = *env_ptr;
	env[index] = ft_strnew(ft_strlen(kv->key) + ft_strlen(kv->value) + 1);
	i = -1;
	len = ft_strlen(kv->key);
	while (++i < len)
		env[index][i] = kv->key[i];
	env[index][i] = '=';
	i++;
	index_i = -1;
	len = ft_strlen(kv->value);
	while (++index_i < len)
	{
		env[index][i] = kv->value[index_i];
		i++;
	}
	return (EXIT_SUCCESS);
}

int			ft_fork_env_arr_to_tab_str(t_arr *envp, char ***env_ptr)
{
	char			**env;
	int				index;
	t_kval			*kv;
	int				err;

	if ((err = ft_fork_env_arr_to_tab_str_init(envp, env_ptr)))
	{
		return (EXIT_FAILURE);
	}
	env = *env_ptr;
	index = 0;
	while (index < (int)envp->length)
	{
		kv = *(t_kval **)(
			(unsigned char *)envp->ptr + index * envp->sizeof_elem);
		ft_fork_env_arr_to_tab_str_set_tab(kv, &env, index);
		index++;
	}
	*env_ptr = env;
	return (EXIT_SUCCESS);
}
