/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd_is_existing_file.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 13:22:43 by aollivie          #+#    #+#             */
/*   Updated: 2017/03/23 13:22:45 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** check if the file exis
** 0 if succed or 1 if faillure
*/
int	ft_builtin_cd_is_existing_file(
	const char *path_absolute, const char *new_path, int	fd_stderr)
{
	int	err;

	if ((err = access(path_absolute, F_OK)))
	{
	 ft_putstr_fd("21sh: cd no file: ", fd_stderr);
	 ft_putstr_fd(new_path, fd_stderr);
	 ft_putstr_fd("\n", fd_stderr);
	 return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
