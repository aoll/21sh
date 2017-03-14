/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_check_d_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 18:43:45 by alex              #+#    #+#             */
/*   Updated: 2017/02/05 18:43:56 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * check if the the current char is a quote or a dquote
 * if is true set the bool quote and dquote
 */
int  ft_parse_check_d_quote(t_cmd_line *line)
{
  if (*line->s_line == '"' && !line->quote)
  {
    line->dquote = !line->dquote;
  }
  if (*line->s_line == '\'' && !line->dquote)
  {
    line->quote = !line->quote;
  }
  return (EXIT_SUCCESS);
}
