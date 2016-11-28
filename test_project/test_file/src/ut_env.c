#include "test_project.h"

// void  ft_arr_print(t_arr *arr)
// {
//   int i;
//   t_arr *tmp;
//   unsigned char *ptr;
//
//   tmp = arr;
//   ptr = tmp->ptr;
//   i = 0;
//   while (i < (int)tmp->length)
//   {
//     tmp->f_print(ptr);
//     ptr += tmp->sizeof_elem;
//     i++;
//   }
//   return;
// }

// void  ft_arr_free(t_arr *arr)
// {
//   int i;
//   t_arr *tmp;
//   unsigned char *ptr;
//
//   tmp = arr;
//   ptr = tmp->ptr;
//   i = 0;
//   while (i < (int)tmp->length)
//   {
//     tmp->f_del((void **)ptr);
//     ptr += tmp->sizeof_elem;
//     i++;
//   }
//   free(tmp->ptr);
//   free(tmp);
//   return;
// }

void  ut_init_env(int ac, char **av, char **env)
{
  t_arr *arr;

  ut_name_function_tested("ut_env");
  ut_name_function_tested("ft_env_init");

  arr = ft_env_init(ac, av, env);
  if (arr != NULL)
    ut_success();
  else
    ut_fail();
  printf("\n");

  ut_name_function_tested("ut_env");
  ut_name_function_tested("ft_arr_indexof");
  if (ft_arr_indexof(arr, "_") == 60)
    ut_success();
  else
    ut_fail();
  if (ft_arr_indexof(arr, "x_x") == -1)
    ut_success();
  else
    ut_fail();
  printf("\n");

  ft_arr_print(arr);
  ft_arr_free(arr);
  return;
}

void  ut_kval_init(void)
{
  t_kval *ptr;

  ut_name_function_tested("ut_env");
  ut_name_function_tested("ft_init_kval");

  ptr = ft_kval_init("PATH=hello/world");
  if (!ft_strcmp(ptr->key, "PATH"))
    ut_success();
  else
    ut_fail();
  if (!ft_strcmp(ptr->value, "hello/world"))
    ut_success();
  else
    ut_fail();
  ptr = ft_kval_init("PATH=");
  if (!ft_strcmp(ptr->key, "PATH"))
    ut_success();
  else
    ut_fail();
  if (!ft_strcmp(ptr->value, ""))
    ut_success();
  else
    ut_fail();

  ptr = ft_kval_init("PATHhello/world");
  if (ptr == NULL)
    ut_success();
  else
    ut_fail();
  ptr = ft_kval_init(NULL);
  if (ptr == NULL)
    ut_success();
  else
    ut_fail();

  printf("\n");

  return;
}



void  ut_env(int ac, char **av, char **env)
{
  // ut_kval_init();
  ut_init_env(ac, av, env);
  return;
}
