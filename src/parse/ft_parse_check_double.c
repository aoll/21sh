/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_check_double.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 11:33:13 by alex              #+#    #+#             */
/*   Updated: 2017/03/18 10:16:31 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** check if the token past in parameter in present in double succecsive
** return 1 if is true or 0 if not
*/

static int	ft_parse_check_double_pop(
	t_cmd_line *line, t_arr **arr, int token, int index_tmp)
{
	if (line->check)
	{
		if (*line->s_line == D_LEFT_REDIRECT
			|| *line->s_line == D_RIGHT_REDIRECT
			|| *line->s_line == S_LEFT_REDIRECT
			|| *line->s_line == S_RIGHT_REDIRECT
			|| *line->s_line == PIPE)
		{
			if (*line->s_line != PIPE && token == PIPE)
			{
			 free(ft_arr_pop(*arr, index_tmp));
			 line->index -= 1;
			}
			else
			{
			 return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

static int	ft_parse_check_double_set_check(
	t_cmd_line *line, int token, int *index_tmp)
{
	if (*line->s_line == token)
	{
		*index_tmp = line->index;
		if (line->check)
		{
			return (EXIT_FAILURE);
		}
		line->check = true;
	}
	else if (!ft_isspace(*line->s_line))
	{
		line->check = false;
	}
	return (EXIT_SUCCESS);
}

static int	ft_parse_check_double_check_error(
	t_cmd_line *line, t_arr **arr, int token, int *index_tmp)
{
	int				err;

	if (!line->dquote && !line->quote)
	{
		if (line->check)
		{
			if ((err = ft_parse_check_double_pop(line, arr, token, *index_tmp)))
			{
			 return (EXIT_FAILURE);
			}
		}
		if ((err = ft_parse_check_double_set_check(
			line, token, index_tmp)))
			{
			 return (EXIT_FAILURE);
			}
	}
	return (EXIT_SUCCESS);
}

int	ft_parse_check_double(t_arr *arr, int token)
{
	int				index_tmp;
	t_cmd_line		line;
	int				err;

	ft_parse_init_cmd_line(&line);
	while (line.index < (int)arr->length)
	{
		line.s_line = *(char **)(
			(unsigned char *)arr->ptr + line.index * arr->sizeof_elem);
		if (*line.s_line == PIPE && !line.index && token == PIPE)
		{
			return (EXIT_FAILURE);
		}
		ft_parse_check_d_quote(&line);
		if ((err = ft_parse_check_double_check_error(
			&line, &arr, token, &index_tmp)))
		{
			return (EXIT_FAILURE);
		}
		line.index++;
	}
	return (EXIT_SUCCESS);
}
