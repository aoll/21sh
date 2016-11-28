#include "project.h"

/**
 * output the prompt and the line, from the start position with a clean empty
 * line
 * the cursor will be at the end of the line
 */
int  ft_restore_prompt_and_line(t_cursor *cursor, t_arr *arr)
{
  int nb_char;

  if (!cursor)
  {
    return (EXIT_FAILURE);
  }
  ft_putstr(cursor->prompt);
  ft_arr_print(arr);
  return (0);
  cursor->index_line = arr->length;
  cursor->prev_chariot = cursor->chariot;
  cursor->pos_y = (cursor->prompt_len + arr->length) / cursor->terminal_size.ws_col;
  // cursor->pos_x = (cursor->prompt_len + arr->length) % cursor->terminal_size.ws_col;
  if (!cursor->pos_x)
  {
    ft_term_apply_cmd(cursor->down, 1);
  }
  if (cursor->prev_chariot)
  {
    nb_char = ft_nb_char_between_two_chariot(arr, arr->length - 1);
    if (nb_char >= cursor->terminal_size.ws_col)
    {
      nb_char %= cursor->terminal_size.ws_col;
    }
  }
  else
  {
    nb_char = (cursor->prompt_len + arr->length) % cursor->terminal_size.ws_col;
  }
  cursor->pos_x = nb_char;
  return (EXIT_SUCCESS);
}
