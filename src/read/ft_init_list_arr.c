/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_list_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:02:32 by alex              #+#    #+#             */
/*   Updated: 2017/04/19 16:02:54 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
**  init list_arr
*/

int	ft_init_list_arr(t_list_arr *list_arr, char **envp)
{
	list_arr->env = ft_env_init(envp);
	list_arr->history_line = ft_arr_new(1, sizeof(t_arr *));
	list_arr->current_line = ft_arr_new(1, sizeof(t_arr *));
	ft_arr_push(list_arr->history_line, list_arr->current_line, 0);
	list_arr->arr = ft_arr_new(1, sizeof(char *));
	ft_arr_push(list_arr->current_line, list_arr->arr, 0);
	list_arr->arr->f_print = &ft_arr_putchar;
	list_arr->arr->f_dup_elem = &ft_arr_strdup;
	list_arr->select_line = ft_arr_new(1, sizeof(char *));
	list_arr->copy_line = NULL;
	list_arr->select_line->f_print = &ft_arr_putchar;
	list_arr->select_line->f_dup_elem = &ft_arr_strdup;
	list_arr->buff = ft_strnew(8);
	ft_bzero(list_arr->buff, 8);
	return (EXIT_SUCCESS);
}
