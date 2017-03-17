/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_read_stdin_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 17:39:39 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 08:12:39 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
*
*/

static int	ft_fork_read_file(t_tab_tube *array_tube, int *fd)
{
	int				rd;
	char			*buff;

	buff = ft_strnew(1);
	while ((rd = read(*fd, buff, 1)))
	{
		if (rd < 0)
		break;
		write(array_tube->tube_fork_stdin[1], buff, 1);
	}
	ft_str_free(&buff);
	return (EXIT_SUCCESS);
}

static int	ft_fork_read_stdin_is_end_word(
	t_arr_fd *arr_fd, char **end_word, char **line)
{
	if (ft_strcmp(*line, *end_word) == 0)
	{
		ft_str_free(line);
		ft_str_free(end_word);
		*end_word = ft_arr_pop(arr_fd->arr_d_end_word, 0);
	}
	return (EXIT_SUCCESS);
}

static int	ft_fork_read_stdin(t_arr_fd *arr_fd, t_tab_tube *array_tube)
{
	char			*end_word;
	char			*line;

	line = NULL;
	end_word = ft_arr_pop(arr_fd->arr_d_end_word, 0);
	while (ft_strcmp(line, end_word) != 0 || arr_fd->arr_d_end_word->length)
	{
		ft_fork_read_stdin_is_end_word(arr_fd, &end_word, &line);
		if (line)
		{
			write(array_tube->tube_fork_stdin[1], line, ft_strlen(line));
			*line = '\n';
			write(array_tube->tube_fork_stdin[1], line, 1);
			ft_str_free(&line);
		}
		get_next_line(0, &line);
	}
	ft_str_free(&line);
	ft_str_free(&end_word);
	return (EXIT_SUCCESS);
}

int	ft_fork_read_stdin_file(t_arr_fd *arr_fd, t_tab_tube *array_tube)
{
	int				index;
	int				*fd;

	index = -1;
	while (++index < (int)arr_fd->arr_fd_stdin->length)
	{
		fd = *(int **)((unsigned char *)arr_fd->arr_fd_stdin->ptr
		+ index * arr_fd->arr_fd_stdin->sizeof_elem);
		if (*fd == D_LEFT_REDIRECT)
		{
			if (!arr_fd->arr_d_end_word->length)
			{
			 continue;
			}
			ft_fork_read_stdin(arr_fd, array_tube);
		}
		else
		{
			ft_fork_read_file(array_tube, fd);
		}
	}
	return (EXIT_SUCCESS);
}
