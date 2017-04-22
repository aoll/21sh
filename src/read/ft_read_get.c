/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 09:45:16 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/22 11:55:21 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static ft_arr_add(t_list_arr *list_arr, char **line)
{
	ft_arr_str(list_arr->arr, *line);
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	return (EXIT_SUCCESS);
}

int	ft_read_get(t_cursor *cursor, t_list_arr *list_arr, char **line, bool quote)
{
	if (quote)
		return (ft_arr_add(list_arr, line));
	while (list_arr->arr->length)
		free(ft_arr_pop(list_arr->arr, 0));
	ft_arr_str(list_arr->arr, *line);
	if (*line)
		free(*line);
	*line = NULL;
	list_arr->tab_cmds = ft_parse_line(list_arr->arr);
	if (list_arr->tab_cmds)
		ft_fork_loop(&list_arr->env, list_arr->tab_cmds);
	if (list_arr->tab_cmds)
	{
		if (list_arr->tab_cmds->length)
			ft_arr_free(ft_arr_pop(list_arr->tab_cmds, 0));
		if (list_arr->tab_cmds->ptr)
			free(list_arr->tab_cmds->ptr);
		free(list_arr->tab_cmds);
		list_arr->tab_cmds = NULL;
	}
	ft_putstr(cursor->prompt);
	return (EXIT_SUCCESS);
}
