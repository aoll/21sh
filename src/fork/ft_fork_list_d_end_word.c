/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_list_d_end_word.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 19:06:46 by alex              #+#    #+#             */
/*   Updated: 2017/02/07 19:07:03 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** if some D_LEFT_REDIRECT are present push in arr_d_end_word the string present
** for finish the read
*/

int	ft_fork_list_d_end_word(char **command, t_arr *arr_d_end_word)
{
	int				i;
	char			*end_word;
	char			*cmd;

	i = -1;
	cmd = *command;
	while (arr_d_end_word->length)
	{
		free(ft_arr_pop(arr_d_end_word, 0));
	}
	while (cmd[++i])
	{
		if (cmd[i] == D_LEFT_REDIRECT)
		{
			if (!(end_word = ft_fork_name_file(&cmd, i + 1)))
			{
			 return (EXIT_FAILURE);
			}
			ft_arr_push(arr_d_end_word, end_word, -1);
			cmd[i] = SPACE_SEPARATOR;
		}
	}
	return (EXIT_SUCCESS);
}
