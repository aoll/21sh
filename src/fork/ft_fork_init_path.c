/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_init_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 16:24:59 by alex              #+#    #+#             */
/*   Updated: 2017/02/10 12:02:06 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 *
 */
static char  *ft_fork_init_path_ptr(t_arr *env_copy)
{
  t_kval *kval;
  int index_path;
  char *path_ptr;

  index_path = ft_arr_indexof(env_copy, "PATH");
  if (index_path > 0 & index_path < (int)env_copy->length)
  {
    kval = *(t_kval **)(
      (unsigned char *)env_copy->ptr + index_path *env_copy->sizeof_elem);
    if (!(path_ptr = ft_strdup(kval->value)))
    {
      path_ptr = ft_strnew(0);
    }
  }
  else
  {
    path_ptr = ft_strnew(0);
  }
  return (path_ptr);
}

char  *ft_fork_init_path(t_arr *env_copy, char **tab_cmd, int *err)
{
  char *path_ptr;
  char **tab_path;
  char *path_tmp;
  int index;

  path_ptr = ft_fork_init_path_ptr(env_copy);
  tab_path = ft_strsplit(path_ptr, ':');
  ft_str_free(&path_ptr);
  index = 0;
  path_tmp = ft_strdup(*tab_cmd);
  while (tab_path[index] && (*err = access(path_tmp, F_OK)) )
  {
    ft_str_free(&path_tmp);
    path_tmp = ft_strjoin(tab_path[index], "/");
    path_tmp = ft_strjoin_free(&path_tmp, *tab_cmd);
    index++;
  }
  ft_array_free(&tab_path);
  return (path_tmp);
}
