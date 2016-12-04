/**
 * dup the selection in a new arr copy_line, and reprint the line without
 * the selection
 */
int  ft_cursor_cut(t_cursor *cursor, t_arr *arr, t_arr *select_line, t_arr **copy_line)
{
  int index;
  unsigned char *s_line;
  int nb_line_displayed;

  index = 0;
  ft_cursor_copy_line(cursor, select_line, copy_line);
  while (index < arr->length)
  {
    s_line = (unsigned char *)arr->ptr * arr->sizeof_elem * index;
    s_line = *(unsigned char **)s_line;
    if (s_line[5] == 1)
    {
      free(ft_arr_pop(&arr, index));
    }
    else
    {
      index++;
    }
  }
  
  return (EXIT_SUCCESS);
}
