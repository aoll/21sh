/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd_change_directory.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 13:24:00 by aollivie          #+#    #+#             */
/*   Updated: 2017/03/23 13:42:10 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int	ft_builtin_cd_change_directory_switch(char **path_absolute,
	const char *old_path, const char *new_path, int fd_stderr)
{
	int	err;

	if (!(*path_absolute = ft_builtin_cd_absolute_path(old_path, new_path)))
	{
		ft_putstr_fd("mysh: error malloc\n", fd_stderr);
		return (EXIT_FAILURE);
	}
	if ((err = ft_builtin_cd_is_existing_file(
		(const char *)*path_absolute, new_path, fd_stderr)))
	{
		free(*path_absolute);
		return (EXIT_FAILURE);
	}
	if ((err = chdir(*path_absolute)))
	{
		free(*path_absolute);
		ft_putstr_fd("mysh: permission denied: ", fd_stderr);
		ft_putstr_fd(new_path, fd_stderr);
		ft_putstr_fd("\n", fd_stderr);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_get_new_actual_pwd(
	char **new_actual_pwd, char **path_absolute, int fd_stderr)
{
	if (!(*new_actual_pwd = ft_strnew(1082)))
	{
		free(*path_absolute);
		ft_putstr_fd("mysh: error malloc\n", fd_stderr);
		return (EXIT_FAILURE);
	}
	if (!getcwd(*new_actual_pwd, 1082))
	{
		free(*new_actual_pwd);
		free(*path_absolute);
		ft_putstr_fd("mysh: error malloc\n", fd_stderr);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
** change the currenttdirectory of the actual processus
** if sucess settthe PWD and OLDPWD off the env
*/

int			ft_builtin_cd_change_directory(
	t_arr **env, const char *old_path, const char *new_path, int fd_stderr)
{
	char	*path_absolute;
	int		err;
	char	*new_actual_pwd;

	if (!new_path || !ft_strlen(new_path))
		return (EXIT_SUCCESS);
	if ((err = ft_builtin_cd_change_directory_switch(
		&path_absolute, old_path, new_path, fd_stderr)))
		return (EXIT_FAILURE);
	if ((err = ft_get_new_actual_pwd(
		&new_actual_pwd, &path_absolute, fd_stderr)))
		return (EXIT_FAILURE);
	ft_builtin_cd_set_env(env, "PWD", new_actual_pwd, fd_stderr);
	ft_builtin_cd_set_env(env, "OLDPWD", old_path, fd_stderr);
	free(path_absolute);
	free(new_actual_pwd);
	return (EXIT_SUCCESS);
}
