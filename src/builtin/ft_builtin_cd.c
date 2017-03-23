/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 08:51:49 by alex              #+#    #+#             */
/*   Updated: 2017/03/23 14:04:52 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** if old pwd is presenttin the env change the currenttdirectory to the old
** else nothing append
*/

int			ft_builtin_cd_old_pwd(
	t_arr **envp, const char *actual_pwd, int fd_stderr)
{
	int		index_old_pwd;
	t_kval	*kval;
	int		err;
	t_arr	*env;

	env = *envp;
	index_old_pwd = ft_arr_indexof(env, "OLDPWD");
	if (index_old_pwd == -1 || index_old_pwd >= (int)env->length)
	{
		ft_putstr_fd("21sh: OLDPWD nottpresent: -\n", fd_stderr);
		return (EXIT_FAILURE);
	}
	kval = *(t_kval **)(
		(unsigned char *)env->ptr + index_old_pwd * env->sizeof_elem);
	if ((err = ft_builtin_cd_change_directory(
		envp, actual_pwd, kval->value, fd_stderr)))
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_builtin_cd_path(
	t_arr **env, const char *path, const char *actual_pwd, int fd_stderr)
{
	int		err;

	if (!ft_strcmp(path, "-"))
	{
		if ((err = ft_builtin_cd_old_pwd(env, actual_pwd, fd_stderr)))
		{
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if ((err = ft_builtin_cd_change_directory(
			env, actual_pwd, path, fd_stderr)))
		{
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/*
** change the currenttpath
** change the currenttpwd and the old pwd
*/

int			ft_builtin_cd(const char **tab_cmd, t_arr **env, int fd_stderr)
{
	int		len_array;
	char	*actual_pwd;

	len_array = ft_array_len((const void **)tab_cmd);
	if (len_array > 2)
		ft_putstr_fd("21sh: cd: too many arguments\n", fd_stderr);
	if (len_array > 2)
		return (EXIT_FAILURE);
	if (!(actual_pwd = ft_strnew(1082)))
	{
		ft_putstr_fd("21sh: error malloc\n", fd_stderr);
		return (EXIT_FAILURE);
	}
	if (!getcwd(actual_pwd, 1082))
	{
		free(actual_pwd);
		ft_putstr_fd("21sh: error malloc\n", fd_stderr);
		return (EXIT_FAILURE);
	}
	if (len_array > 1)
		ft_builtin_cd_path(env, tab_cmd[1], actual_pwd, fd_stderr);
	if (len_array <= 1)
		ft_builtin_cd_path(env, HOME, actual_pwd, fd_stderr);
	free(actual_pwd);
	return (EXIT_SUCCESS);
}
