/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cursor_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:13:44 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/20 12:38:55 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_init_cursor_cmd(t_cursor *cursor)
{
	cursor->up = tgetstr("up", NULL);
	cursor->down = tgetstr("do", NULL);
	cursor->left = tgetstr("le", NULL);
	cursor->right = tgetstr("nd", NULL);
	cursor->sup_char = tgetstr("dc", NULL);
	cursor->move_x = tgetstr("ch", NULL);
	cursor->clear_current_line = tgetstr("ce", NULL);
	cursor->clear_down = tgetstr("cd", NULL);
	cursor->mode_insertion = tgetstr("im", NULL);
	cursor->mode_insertion_end = tgetstr("ei", NULL);
	cursor->mode_basic_video = tgetstr("me", NULL);
	cursor->mode_reverse_video = tgetstr("mr", NULL);
	cursor->save_cursor_position = tgetstr("sc", NULL);
	cursor->restore_cursor_position = tgetstr("rc", NULL);
	cursor->scroll_down = tgetstr("sr", NULL);
	cursor->scroll_up = tgetstr("sf", NULL);
	cursor->left_corner_up = tgetstr("ho", NULL);
	cursor->left_corner_down = tgetstr("ll", NULL);
	cursor->clear_all_the_screen = tgetstr("cl", NULL);
	cursor->marge = tgetstr("am", NULL);
	return (EXIT_SUCCESS);
}
