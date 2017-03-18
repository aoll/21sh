/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_init_cmd_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 18:22:22 by alex              #+#    #+#             */
/*   Updated: 2017/02/06 11:47:05 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** init a t_cmd_line with
** init a index to 0 and two bool to false
*/

int	ft_parse_init_cmd_line(t_cmd_line *line)
{
	line->index = 0;
	line->quote = false;
	line->dquote = false;
	line->check = false;
	return (EXIT_SUCCESS);
}
