/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_set_env_copy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:39:08 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 13:41:23 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** init the env_copy by a dup to the env
** set the copy if is B_ENV
** create a char *env with the seted copy t_arr *st_fork.env_copy
*/

int	ft_fork_set_env_copy(t_fork *st_fork, t_arr *env, t_tab_tube *array_tube)
{
	ft_fork_init_env_copy(st_fork, env, array_tube);
	ft_array_free(&st_fork->envp);
	ft_fork_env_arr_to_tab_str(st_fork->env_copy, &st_fork->envp);
	return (EXIT_SUCCESS);
}
