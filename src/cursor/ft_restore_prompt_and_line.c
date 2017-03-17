/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restore_prompt_and_line.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 12:49:03 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 12:49:59 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** output the prompt and the line, from the start position with a clean empty
** line
** the cursor will be at the end of the line
*/

int	ft_restore_prompt_and_line(t_cursor *cursor, t_arr *arr)
{
	int				nb_char;

	if (!cursor)
	{
		return (EXIT_FAILURE);
	}
	ft_putstr(cursor->prompt);
	ft_arr_print(arr);
	return (EXIT_SUCCESS);
}
