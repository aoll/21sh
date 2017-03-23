/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 13:16:21 by aollivie          #+#    #+#             */
/*   Updated: 2017/03/23 14:37:17 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_builtin_exit(char **tab_cmd, t_arr **env)
{
	ft_putstr("EXIT\n");
	return (EXIT_SUCCESS);
}
