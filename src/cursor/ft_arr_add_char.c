/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_add_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 11:51:54 by aollivie          #+#    #+#             */
/*   Updated: 2017/03/15 17:42:42 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** add a char to arr a marke if is a element to a tabulation
*/

int	ft_arr_add_char(t_cursor *cursor, t_arr *arr, char c, int is_tab)
{
	char *char_line;

	if (c == '"' && !cursor->quote)
	{
		cursor->dquote = !cursor->dquote;
	}
	if (c == '\'' && !cursor->dquote)
	{
		cursor->quote = !cursor->quote;
	}
	char_line = ft_strnew(8);
	ft_bzero(char_line, 8);
	*char_line = c;
	char_line[4] = is_tab;
	ft_arr_push(arr, char_line, cursor->index_line);
	cursor->index_line++;
	return (EXIT_SUCCESS);
}
