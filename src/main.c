/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 09:27:27 by alex              #+#    #+#             */
/*   Updated: 2017/03/20 09:27:28 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int   main(int ac, char **av, char **env)
{
	ft_putstr("hello let's begin new project\n");
	ft_read_line(env);
	(void)ac;
	(void)av;
	(void)env;
	return (EXIT_SUCCESS);
}
