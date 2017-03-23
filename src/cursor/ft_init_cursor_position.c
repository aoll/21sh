/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cursor_position.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:16:05 by aollivie          #+#    #+#             */
/*   Updated: 2017/03/23 15:16:24 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** init the cursor position
*/

int	ft_init_cursor_position(t_cursor *cursor)
{
	cursor->prompt = ft_strdup("\033[32m$> \033[0m");
	cursor->pos_y = 0;
	cursor->prompt_len = 3;
	cursor->pos_x = cursor->prompt_len;
	cursor->index_line = 0;
	cursor->dquote = false;
	cursor->quote = false;
	cursor->prev_chariot = 0;
	cursor->chariot = 0;
	cursor->y_total = 1;
	cursor->y_start = 0;
	cursor->index_history = 0;
	cursor->test = 0;
	return (EXIT_SUCCESS);
}
