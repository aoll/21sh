#include "project.h"

/**
 * Parsing section
 */
int  ft_parse_line(t_arr *arr)
{
  t_arr *tab_cmds;
  t_arr *cmd;
  unsigned char *s_line;
  int index;
  bool dquote;
  bool quote;

  if (!arr->length)
  {
    return (EXIT_SUCCESS);
  }
  ft_putstr("\n");
  index = 0;
  dquote = false;
  quote = false;
  tab_cmds = ft_arr_new(1, sizeof(t_arr *));
  cmd = ft_arr_new(1, sizeof(char *));
  ft_arr_push(&tab_cmds, cmd, 0);
  cmd->f_del = &ft_memdel;
  cmd->f_print = &ft_arr_putchar;
  while (index < (int)arr->length)
  {
    s_line = (unsigned char *)arr->ptr + index * arr->sizeof_elem;
    s_line = *(unsigned char **)s_line;
    if (*s_line == '"' && !quote)
    {
      dquote = !dquote;
    }

    if (*s_line == '\'' && !dquote)
    {
      quote = !quote;
    }
    if (*s_line == ';' && !dquote && !quote && index + 1 < (int)arr->length)
    {
      cmd = ft_arr_new(1, sizeof(char *));
      ft_arr_push(&tab_cmds, cmd, -1);
      cmd->f_del = &ft_memdel;
      cmd->f_print = &ft_arr_putchar;
    }
    else
    {
      ft_arr_push(&cmd, ft_strdup((const char *)s_line), -1);
    }
    index++;
  }
  index = 0;
  while (index < (int)tab_cmds->length)
  {
    cmd = *(t_arr **)((unsigned char *)tab_cmds->ptr + index * tab_cmds->sizeof_elem);
    ft_arr_print(cmd);
    ft_putstr("\n");
    index++;
  }
  ft_putstr("\n");
  ft_putstr("parsing start\n");
  return (EXIT_SUCCESS);
}
