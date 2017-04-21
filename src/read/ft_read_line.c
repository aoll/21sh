/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 09:26:47 by alex              #+#    #+#             */
/*   Updated: 2017/04/21 13:50:22 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
#include <signal.h>

/*
** function for print some char * was stocked in a t_arr like elem
** is give for arr->f_print, print some elem
*/

void ft_arr_putchar(const void *s)
{
	char			*s_line;

	if (!s)
	{
		return;
	}
	s_line = *(char **)s;
	if (!s_line)
	{
		return;
	}
	if (s_line[5] == 1)
	{
		ft_mode_reverse_video();
	}
	ft_putstr(*((char **)s));
	ft_mode_basic_video();
	return;
}

/*
** function for dup some char * was stocked in a t_arr like elem
** is give for arr->f_dup, dup some elem and return a void *
*/

void *ft_arr_strdup(const void *s, size_t n)
{
	void			*new;

	(void)n;
	if (!s)
	{
		return (NULL);
	}
	if (!(new = ft_strnew(8)))
	{
		return (NULL);
	}
	ft_memcpy(new, *((char **)s), 8);
	return (new);
}

/*
** return a fresh pointeur on a copy of a kval *
** in case of fail NULL is returned
*/

t_kval *ft_kval_dup(const t_kval *old)
{
	t_kval			*new;

	if (!(new = malloc(sizeof(t_kval))))
	{
		return (NULL);
	}
	new->key = NULL;
	new->value = NULL;
	ft_kval_set_key(new, old->key);
	ft_kval_set_value(new, old->value);
	return (new);
}

/*
** function for dup some kval * was stocked in a t_arr like elem
** is give for arr->f_dup, dup some elem and return a void *
*/

void *ft_arr_kvaldup(const void *s, size_t n)
{
	void			*new;

	(void)n;
	if (!s)
	{
		return (NULL);
	}
	new = ft_kval_dup(*((t_kval **)s));
	return (new);
}

int ft_read_line(char **env)
{
	ft_signal_init();
	return (ft_read_stdin(env));

}
