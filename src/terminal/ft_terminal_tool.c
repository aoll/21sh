/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal_tool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 13:49:35 by alex              #+#    #+#             */
/*   Updated: 2017/05/17 19:49:25 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_get_term(struct termios *term)
{
	char			*name_terminal;

	if (!(name_terminal = getenv("TERM")) || ft_strcmp(name_terminal, "xterm-256color")) //retour le nom du terminal
		return (EXIT_FAILURE);
	fprintf(stderr, "%s\n","term found" );
	if (tgetent(NULL, name_terminal) != 1) //check if name_terminal exist and if
		return (EXIT_FAILURE);   //the terminfo databbase could be found
	fprintf(stderr, "%s\n","tgetent found" );
	if (tcgetattr(0, term) == -1) // rempli la struct termios avec les
		return (-2);  // possibilités du terminal
	fprintf(stderr, "%s\n","tcgetattr found" );
	return (EXIT_SUCCESS);
}

int	ft_init_terminal(void)
{
	struct			termios term;

	if (ft_get_term(&term))
		return (EXIT_FAILURE);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_get_term_restore(struct termios *term)
{
	char			*name_terminal;

	term->c_lflag |= ICANON;
	term->c_lflag |= ECHO;
	if (tcsetattr(0, 0, term) == -1)
		return (-1);
	return (EXIT_SUCCESS);
}

/*
** Apply n time the command given in param
*/

int	ft_term_apply_cmd(char *cmd, int n)
{
	if (!cmd)
	{
		return (EXIT_FAILURE);
	}
	while (n)
	{
		tputs(cmd, 0, &my_putchar);
		n--;
	}
	return (EXIT_SUCCESS);
}

int	ft_cursor_move_x(int new_pos_x, char *cmd)
{
	if (!cmd)
	{
		return (EXIT_FAILURE);
	}
	tputs(tgoto(cmd, 0, new_pos_x), 0, &my_putchar);
	return (EXIT_SUCCESS);
}
