/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd_absolute_path.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 13:21:40 by aollivie          #+#    #+#             */
/*   Updated: 2017/03/23 14:05:46 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** return a string with the absolute new path
** NULL in case of faillure
*/

char	*ft_builtin_cd_absolute_path(const char *old_path, const char *new_path)
{
	char	*path_tmp;
	char	*path_absolute;

	if (new_path[0] != '/')
	{
		if (!(path_tmp = ft_strjoin(old_path, "/")))
		{
			return (NULL);
		}
		if (!(path_absolute = ft_strjoin(path_tmp, new_path)))
		{
			free(path_tmp);
			return (NULL);
		}
		free(path_tmp);
	}
	else
	{
		if (!(path_absolute = ft_strdup(new_path)))
			return (NULL);
	}
	return (path_absolute);
}
