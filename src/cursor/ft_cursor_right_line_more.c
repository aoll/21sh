/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_right_line_more.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 10:42:00 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 11:25:40 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int  ft_cursor_right_line_more_print(
  t_cursor *cursor, t_arr *arr, void *ptr_tmp, int len_tmp)
{
  arr->ptr = (unsigned char *)ptr_tmp
  + arr->sizeof_elem * (cursor->index_line + 1);
  arr->length = len_tmp - (cursor->index_line + 1);
  ft_arr_print(arr);
  ft_term_apply_cmd(cursor->up, 1);
  ft_cursor_move_x(cursor->terminal_size.ws_col - 1, cursor->move_x);
  return (EXIT_SUCCESS);
}

static int  ft_cursor_right_line_more_print_end(
  t_cursor *cursor, t_arr *arr, void *ptr_tmp, int index_end_showed)
{
  arr->ptr = (unsigned char *)ptr_tmp
  + arr->sizeof_elem * (cursor->index_line + 2);
  arr->length = index_end_showed - cursor->index_line - 1;
  ft_arr_print(arr);
  ft_cursor_move_x(0, cursor->move_x);
  arr->ptr = (unsigned char *)ptr_tmp
  + arr->sizeof_elem * (cursor->index_line + 1);
  arr->length = 1;
  ft_arr_print(arr);
  ft_term_apply_cmd(cursor->up, 1);
  ft_cursor_move_x(cursor->terminal_size.ws_col - 1, cursor->move_x);
  return (EXIT_SUCCESS);
}

static int  ft_cursor_right_line_more_init(
  t_cursor *cursor, t_arr *arr, int *len_tmp, void **ptr_tmp)
{
  cursor->y_start++;
  ft_cursor_clear_all_screen(cursor, 1);
  ft_term_apply_cmd(cursor->up, cursor->terminal_size.ws_row - 1);
  ft_cursor_move_x(0, cursor->move_x);
  *len_tmp = arr->length;
  *ptr_tmp = arr->ptr;
  return (EXIT_SUCCESS);
}

static int  ft_cursor_right_line_more_init_index(
  t_cursor *cursor, t_arr *arr, int *index_end_showed, int *index_start_showed)
{
  *index_end_showed = ft_index_line_end_showed(cursor, arr);
  *index_start_showed = ft_index_line_start_showed(cursor, arr);
  arr->ptr = (unsigned char *)arr->ptr
  + arr->sizeof_elem * (*index_start_showed);
  arr->length = cursor->index_line + 1 - (*index_start_showed);
  ft_arr_print(arr);
  return (EXIT_SUCCESS);
}
/**
 * clean the screen
 * print the command with line + 1
 */
int  ft_cursor_right_line_more(t_cursor *cursor, t_arr *arr)
{
  int index_start_showed;
  int index_end_showed;
  void *ptr_tmp;
  int len_tmp;

  ft_cursor_right_line_more_init(cursor, arr, &len_tmp, &ptr_tmp);
  ft_cursor_right_line_more_init_index(
    cursor, arr, &index_end_showed, &index_start_showed);
  if ((cursor->index_line + 2) < len_tmp)
  {
    ft_cursor_right_line_more_print_end(cursor, arr, ptr_tmp, index_end_showed);
  }
  else if ((cursor->index_line + 1) < len_tmp)
  {
    ft_cursor_right_line_more_print(cursor, arr, ptr_tmp, len_tmp);
  }
  else if (cursor->index_line < len_tmp)
  {
    ft_cursor_right_line_more_up(cursor, ptr_tmp, arr);
  }
  arr->length = len_tmp;
  arr->ptr = ptr_tmp;
  return (EXIT_SUCCESS);
}
