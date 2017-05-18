/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_setenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 13:16:35 by aollivie          #+#    #+#             */
/*   Updated: 2017/05/18 17:59:18 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** settname and value if = is presen
** print the adequate message
** return if no error 0 and 1 if error
*/

static int	ft_builtin_setenv_set_name_value(
	const char *s, char **name, char **value, int fd_stderr)
{
	int	index;

	index = ft_indexof_first_char(s, '=');
	if (index <= 0)
		ft_putstr_fd("mysh: setenv bad argument\n", fd_stderr);
	if (index <= 0)
		return (EXIT_FAILURE);
	if (!(*name = ft_strsub(s, 0, index)))
	{
		ft_putstr_fd("mysh: error malloc\n", fd_stderr);
		return (EXIT_FAILURE);
	}
	if (index + 1 < (int)ft_strlen(s))
	{
		if (!(*value = ft_strsub(s, index + 1, ft_strlen(s) - index + 1)))
		{
			free(*name);
			ft_putstr_fd("mysh: error malloc\n", fd_stderr);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/*
** add a new var to the env
** return EXIT_SUCCESS or EXIT_FAILURE
*/

static int	ft_builtin_setenv_add_var(
	t_arr **env, const char *name, const char *value)
{
	t_kval	*kval;
	int		err;

	if (!(kval = ft_kval_new()))
	{
		return (EXIT_FAILURE);
	}
	if ((err = ft_kval_set_key(kval, name)))
	{
		return (EXIT_FAILURE);
	}
	if ((err = ft_kval_set_value(kval, value)))
	{
		return (EXIT_FAILURE);
	}
	if ((err = ft_arr_push(*env, kval, -1)))
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
** edittthe value of a presenttvar in env
*/

static int	ft_builtin_setenv_edit_var(
	int index, t_arr **envp, const char *name, const char *value)
{
	t_kval	*kval;
	t_arr	*env;
	int		err;

	(void)name;
	env = *envp;
	kval = *(t_kval **)((unsigned char *)env->ptr + index * env->sizeof_elem);
	if (!value)
	{
		err = ft_kval_set_value(kval, "");
	}
	else
	{
		err = ft_kval_set_value(kval, value);
	}
	return (err);
}

/*
** add or editta variable to the env
** return EXIT_SUCCESS or EXIT_FAILURE
*/

static int	ft_builtin_setenv_add_or_edit_var(
	t_arr **env_ptr, const char *name, const char *value)
{
	int		index;
	int		err;
	t_arr	*env;

	env = *env_ptr;
	index = ft_arr_indexof((const t_arr *)env, (const void *)name);
	if (index < 0)
	{
		if ((err = ft_builtin_setenv_add_var(env_ptr, name, value)))
		{
			return (EXIT_FAILURE);
		}
	}
	else if (index < (int)env->length)
	{
		if ((err = ft_builtin_setenv_edit_var(index, env_ptr, name, value)))
		{
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/*
** change or add a env variable
** 0 if succes
** 1 if error
*/

int			ft_builtin_setenv(const char **tab_cmd, t_arr **env, int fd_stderr)
{
	int		err;
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	if ((err = ft_builtin_setenv_check_argument(tab_cmd, "setenv", fd_stderr)))
	{
		return (EXIT_FAILURE);
	}
	if ((err = ft_builtin_setenv_set_name_value(
		(const char *)tab_cmd[1], &name, &value, fd_stderr)))
	{
		return (EXIT_FAILURE);
	}
	if ((err = ft_builtin_setenv_add_or_edit_var(
		env, (const char *)name, (const char *)value)))
	{
		ft_free_name_value(&name, &value);
		ft_putstr_fd("mysh: error malloc\n", fd_stderr);
		return (EXIT_FAILURE);
	}
	ft_free_name_value(&name, &value);
	return (EXIT_SUCCESS);
}
