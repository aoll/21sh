#include "test_project.h"


void  free_test()
{
  void *tabb;
  t_kval *kv;
  t_kval *tmp;

  kv = malloc(sizeof(t_kval *));

  kv->key = ft_strdup("hello ");
  kv->value = ft_strdup("world\n");

  tabb = malloc(sizeof(* kv)); // pour une copie totale alloue la taille de la structure et pas seulement du poiteur sur la structure

  ft_putstr(kv->key);
  ft_putstr(kv->value);
  ft_putstr("----------\n");

  memcpy(tabb, kv, sizeof(* kv)); // pour une copie total de la structure obligé de copier la structure derefencé

  free(kv);  //le pointeur n'a plus d'utilité

  tmp = tabb;

  ft_putstr(tmp->key);
  ft_putstr(tmp->value);
  ft_putstr("----------\n");


  free(tmp->key); // c'est un poiteur de la structure, doit etre free
  free(tmp->value); // c'est encore un poiteur de la structure, doit etre free

  free(tabb); // le ptr doit etre free
  return;
}



void  ut_free(void)
{
  free_test();

  return;
}
