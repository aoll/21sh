/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 20:44:54 by alex              #+#    #+#             */
/*   Updated: 2017/04/19 21:10:20 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int	ft_read_exec_exit(
	t_cursor *cursor, t_list_arr *list_arr, struct termios *term)
{
	if (cursor->is_env)
	{
		ft_term_apply_cmd(cursor->mode_insertion_end, 1);
		if (ft_get_term_restore(term))
			return (EXIT_FAILURE);
	}
	ft_putstr("\n");
	signal(SIGINT, ft_signal_sigint_chariot);
	if (ft_fork_loop(&list_arr->env, list_arr->tab_cmds) == B_EXIT)
	{
		ft_term_apply_cmd(cursor->up, 1);
		ft_read_exit(list_arr, cursor, term);
		return (EXIT_SUCCESS);
	}
	return (-1);
}

static int	ft_read_exec_cmds(
	t_cursor *cursor, t_list_arr *list_arr, struct termios *term)
{
	signal(SIGINT, ft_signal_sigint_c);
	if (list_arr->tab_cmds)
	{
		if (list_arr->tab_cmds->length)
			ft_arr_free(ft_arr_pop(list_arr->tab_cmds, 0));
		if (list_arr->tab_cmds->ptr)
			free(list_arr->tab_cmds->ptr);
		free(list_arr->tab_cmds);
		list_arr->tab_cmds = NULL;
	}
	if (cursor->is_env)
	{
		ft_term_apply_cmd(cursor->mode_insertion, 1);
		term->c_lflag &= ~(ICANON);
		term->c_lflag &= ~(ECHO);
		if (tcsetattr(0, TCSADRAIN, term) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_read_exec(t_cursor *cursor, t_list_arr *list_arr, struct termios *term)
{
  int err;

	if (cursor->is_env)
		ft_cursor_end(cursor, list_arr->arr);
	list_arr->tab_cmds = ft_parse_line(list_arr->arr);
	if (list_arr->tab_cmds)
	{
		if ((err = ft_read_exec_exit(cursor, list_arr, term)) != -1)
			return (err);
		if ((err = ft_read_exec_cmds(cursor, list_arr, term)))
			return (err);
	}
	else
	{
		ft_putstr("\n");
	}
	ft_cursor_valide_line(cursor, &list_arr->history_line,
    &list_arr->current_line, &list_arr->arr);
	return (-1);
}
