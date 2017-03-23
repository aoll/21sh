/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_name_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:39:57 by aollivie          #+#    #+#             */
/*   Updated: 2017/03/23 14:40:18 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** free name and value
*/

int	ft_free_name_value(char **name, char **value)
{
	if (*name)
	{
		free(*name);
	}
	if (*value)
	{
		free(*value);
	}
	return (EXIT_SUCCESS);
}
