/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_init_term_arr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:32:23 by alex              #+#    #+#             */
/*   Updated: 2017/04/19 16:32:44 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_init_init_term_arr(
	t_list_arr *list_arr, char **envp,
	t_cursor *cursor, struct winsize *terminal_size_old)
{
	ft_init_list_arr(list_arr, envp);
	ft_init_cursor_position(cursor);
	ft_terminal_winsize(&(cursor->terminal_size));
	ft_putstr(cursor->prompt);
	ft_terminal_winsize(terminal_size_old);
	ft_terminal_winsize(&(cursor->terminal_size));
	return (EXIT_SUCCESS);
}
