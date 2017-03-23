/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_write_tube_stdin.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 17:28:58 by alex              #+#    #+#             */
/*   Updated: 2017/02/08 17:35:54 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_fork_write_tube_stdin(
	t_tube *tab_tube, t_tab_tube *array_tube, int i, int nb_pipe)
{
	char			*buff;
	int				rd;

	if (nb_pipe && i < nb_pipe)
	{
		buff = ft_strnew(1);
		while ((rd = read(tab_tube[i].tube[0], buff, 1)))
		{
			if (rd < 0)
				break ;
			write(array_tube->tube_fork_stdin[1], buff, 1);
		}
		ft_str_free(&buff);
	}
	return (EXIT_SUCCESS);
}
