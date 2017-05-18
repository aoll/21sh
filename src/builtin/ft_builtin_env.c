/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 09:05:25 by alex              #+#    #+#             */
/*   Updated: 2017/05/18 15:25:41 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** free and print the env
*/

static int	ft_builtin_env_print_free(
	char ***tab_cmd, t_arr *env, int fd_stdout)
{
	free(*tab_cmd);
	*tab_cmd = NULL;
	ft_builtin_env_print(env, fd_stdout);
	return (EXIT_SUCCESS);
}

static int	ft_builtin_env_print_init(
	char ***cmd, char ***tab_cmd, bool *is_env_prev)
{
	if (!tab_cmd)
		return (EXIT_FAILURE);
	*is_env_prev = false;
	*cmd = *tab_cmd;
	return (EXIT_SUCCESS);
}

/*
** setta listtoff var in the env before execute a commande or print the new env
*/

static int	ft_builtin_env_set_var(
	char ***tab_cmd, t_arr *env, int fd_stdout, int fd_stderr)
{
	char	**cmd;
	bool	is_env_prev;

	if (ft_builtin_env_print_init(&cmd, tab_cmd, &is_env_prev))
		return (EXIT_SUCCESS);
	while (*cmd)
	{
		if (ft_indexof_first_char(*cmd, '=') < 0)
		{
			if (ft_builtin_env_set_var_cmd(cmd, env, &is_env_prev))
				return (ft_builtin_env_set_var_is_cmd(cmd, tab_cmd));
		}
		else
		{
			ft_builtin_env_setenv(env, *cmd, fd_stderr);
			is_env_prev = false;
		}
		free(*cmd);
		cmd++;
	}
	ft_builtin_env_print_free(tab_cmd, env, fd_stdout);
	return (B_ENV);
}

/*
** if nottother arguments for env, print the env
** else settthe variable for a temporaire env before execute a commande
** if nottcommande print the new env
** env -i env = NULL
** env -u "VAR_NAME" unsetenv the var
*/

int			ft_builtin_env(
	char ***tab_cmd, t_arr **env, int fd_stdout, int fd_stderr)
{
	char	**cmd;

	cmd = *tab_cmd;
	if (!cmd[1])
	{
		ft_builtin_env_print(*env, fd_stdout);
		return (B_ENV);
	}
	else
	{
		return (ft_builtin_env_set_var(tab_cmd, *env, fd_stdout, fd_stderr));
	}
	return (EXIT_SUCCESS);
}
