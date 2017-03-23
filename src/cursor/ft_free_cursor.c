/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cursor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:15:07 by aollivie          #+#    #+#             */
/*   Updated: 2017/03/23 15:15:26 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** free all command save in struct cursor
*/

int	ft_free_cursor(t_cursor *cursor)
{
	if (cursor->prompt)
	{
		free(cursor->prompt);
	}
	return (EXIT_SUCCESS);
}
