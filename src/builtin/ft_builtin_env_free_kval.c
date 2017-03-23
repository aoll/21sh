/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env_free_kval.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:31:55 by aollivie          #+#    #+#             */
/*   Updated: 2017/03/23 14:32:43 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** free the kvals in a t_arr
*/

int	ft_builtin_env_free_kval(t_arr *env)
{
	void	*kval;

	while (env->length)
	{
		kval = ft_arr_pop(env, 0);
		ft_kval_free(&kval);
	}
	return (EXIT_SUCCESS);
}
