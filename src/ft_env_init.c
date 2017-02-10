#include "project.h"

void  ft_kval_print(const void *ptr)
{
  t_kval *tmp;

  tmp = *((t_kval **)ptr);
  ft_putstr(tmp->key);
  ft_putstr("=");
  ft_putstr(tmp->value);
  ft_putstr("\n");
  return;
}

t_kval  *ft_kval_init(const char *env_line)
{
  t_kval  *new;
  int     index_separator;
  int     len;

  if (!env_line)
    return (NULL);
  if ((index_separator = ft_indexof_first_char(env_line, '=')) < 0)
    return (NULL);
  if (!(new = ft_kval_new()))
    return (NULL);
  len = ft_strlen(env_line);
  new->key = ft_strsub(env_line, 0, index_separator);
  new->value = ft_strsub(env_line, index_separator + 1, len);

  return (new);
}


t_arr  *ft_env_init(char **env)
{
  size_t length;
  t_arr *arr;

  arr = NULL;
  length = ft_array_len((const void **)env);
  length = length > 0 ? length : 1;
  if (!(arr = ft_arr_new(length, sizeof(t_kval*))))
    return (NULL);
  arr->f_print = &ft_kval_print;
  arr->f_cmp = &ft_kval_cmp_key;
  arr->f_del = &ft_kval_free;
  arr->f_dup_elem = &ft_arr_kvaldup;
  if (!env)
    return (arr);
  if (!*env)
    return (arr);
  while (*env)
  {
      ft_arr_push(arr, ft_kval_init(*env), -1);
      env++;
  }
  return (arr);
}
