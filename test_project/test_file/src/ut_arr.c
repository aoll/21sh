#include "test_project.h"

void  ut_arr(void)
{


  t_arr *arr;
  // char *b ;
  char a ='a';
  char b = 'b';
  // char _b = 'b';
  // char c = 'c';
  // char d = 'd';
  // char e = 'e';
  // char f = 'f';
  // char g = 'g';
  // char h = 'h';
  // char i = 'i';
  // char j = 'j';
char *s;


  arr = ft_arr_new(1, sizeof(char));


  ft_arr_push(&arr, (void *)(SIZE_PTR)a, 0);
  ft_arr_push(&arr, (void *)(SIZE_PTR)b, 0);
  // ft_arr_push(&arr, (unsigned char *)a, 0);
  // ft_arr_push(&arr, (unsigned char *)b, 0);
  // ft_arr_push(&arr, &c, -1);
  // ft_arr_push(&arr, &d, -1);

  // ft_putchar((char)*((unsigned char *)arr->ptr)); ft_putchar('\n');
  //
  // arr->ptr += arr->sizeof_elem;
  // ft_putchar(*((char *)(unsigned char *)arr->ptr)); ft_putchar('\n');
  s = (char *)(unsigned char *)arr->ptr;
  ft_putstr(s);
  ft_putchar('\n');

  // t_arr *arr;
  // int a = 0;
  // int b = 1;
  // int c = 2;
  // int d = 3;
  // int e = 4;
  // int f = 5;
  // int g = 6;
  // int h = 42;
  // void *tmp;
  //
  // // int index;
  //
  // arr = ft_arr_new(1, sizeof(int));
  //
  // ft_arr_push(&arr, &a, -1);
  // ft_arr_push(&arr, &b, -1);
  // ft_arr_push(&arr, &c, -1);
  // ft_arr_push(&arr, &d, -1);
  // ft_arr_push(&arr, &e, -1);
  // ft_arr_push(&arr, &f, -1);
  // ft_arr_push(&arr, &g, -1);
  // ft_arr_push(&arr, &h, 0);
  // //
  // index = 7;
  // ft_putstr("indexof: elem = 7    :");
  // ft_putnbr(ft_arr_indexof(arr, &index));
  // ft_putchar('\n');

  // tmp = arr->ptr;
  // ft_putnbr(*((int *)arr->ptr));
  // arr->ptr += arr->sizeof_elem; ft_putchar('\n');
  //
  // ft_putnbr(*((int *)arr->ptr));
  // arr->ptr += arr->sizeof_elem; ft_putchar('\n');
  // ft_putnbr(*((int *)arr->ptr));
  // arr->ptr += arr->sizeof_elem; ft_putchar('\n');
  // ft_putnbr(*((int *)arr->ptr));
  // arr->ptr += arr->sizeof_elem; ft_putchar('\n');
  // ft_putnbr(*((int *)arr->ptr));
  // arr->ptr += arr->sizeof_elem; ft_putchar('\n');
  // ft_putnbr(*((int *)arr->ptr));
  // arr->ptr += arr->sizeof_elem; ft_putchar('\n');
  // ft_putnbr(*((int *)arr->ptr));ft_putchar('\n');
  // arr->ptr += arr->sizeof_elem;
  // ft_putnbr(*((int *)arr->ptr));ft_putchar('\n');

  // ft_putnbr(*((int *)ft_arr_pop(&arr, 0)));ft_putchar('\n');
  // ft_putnbr(*((int *)ft_arr_pop(&arr, 0)));ft_putchar('\n');
  // ft_putnbr(*((int *)ft_arr_pop(&arr, 0)));ft_putchar('\n');
  // ft_putnbr(*((int *)ft_arr_pop(&arr, 0)));ft_putchar('\n');
  // ft_putnbr(*((int *)ft_arr_pop(&arr, 0)));ft_putchar('\n');
  // ft_putnbr(*((int *)ft_arr_pop(&arr, 0)));ft_putchar('\n');
  // ft_putnbr(*((int *)ft_arr_pop(&arr, 0)));ft_putchar('\n');
  // ft_putnbr(*((int *)ft_arr_pop(&arr, 0)));ft_putchar('\n');



  // free(ft_arr_pop(&arr, 0));
  // free(ft_arr_pop(&arr, 0));
  // free(ft_arr_pop(&arr, 0));
  // free(ft_arr_pop(&arr, 0));
  // free(ft_arr_pop(&arr, 0));
  // free(ft_arr_pop(&arr, 0));
  // free(ft_arr_pop(&arr, 0));
  // free(ft_arr_pop(&arr, 0));

  // t_arr *arr;
  // char *s1;
  //
  //
  // arr  = ft_arr_new(2, sizeof(char *));
  // s1 = ft_strdup("hello ceci est un test un peu longt expres ");
  // char *s2 = ft_strdup("world");
  // char *s3 = ft_strdup(" pardon");
  // char *s4 = ft_strdup(" my french\n");
  // ft_arr_push(&arr, s1, -1);
  // ft_arr_push(&arr, s2, -1);
  // ft_arr_push(&arr, s3, -1);
  // ft_arr_push(&arr, s4, -1);

  // ft_putnbr(ft_arr_indexof(arr, cmp));
  // ft_putstr(*((char **)arr->ptr));ft_putchar('\n');
  // arr->ptr += arr->sizeof_elem;
  // ft_putstr(*((char **)arr->ptr));ft_putchar('\n');
  // arr->ptr += arr->sizeof_elem;
  // ft_putstr(*((char **)arr->ptr));ft_putchar('\n');
  // arr->ptr += arr->sizeof_elem;
  // ft_putstr(*((char **)arr->ptr));ft_putchar('\n');
  // arr->ptr += arr->sizeof_elem;

  // ft_putstr(((char *)ft_arr_pop(&arr, 0)));ft_putchar('\n');
  // ft_putstr(((char *)ft_arr_pop(&arr, 0)));ft_putchar('\n');
  // ft_putstr(((char *)ft_arr_pop(&arr, 0)));ft_putchar('\n');
  // ft_putstr(((char *)ft_arr_pop(&arr, 0)));ft_putchar('\n');
  // ft_putstr(((char *)ft_arr_pop(&arr, 0)));ft_putchar('\n');

  // free(((char *)ft_arr_pop(&arr, 0)));ft_putchar('\n');
  // free(((char *)ft_arr_pop(&arr, 0)));ft_putchar('\n');
  // free(((char *)ft_arr_pop(&arr, 0)));ft_putchar('\n');
  // free(((char *)ft_arr_pop(&arr, 0)));ft_putchar('\n');

  // free(arr->ptr);
  free(arr);
  printf("yolo tesh des arr\n");
  return;
}
