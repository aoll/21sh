#include "project.h"

/**
 * separate the line on a multiple line whitout "free ;" (; not inside quote or
 * dquote)
 * return null if lien lenght == 0
 */
t_arr  *ft_parse_separate_cmd(t_arr *arr)
{
  t_arr *tab_cmds;
  t_arr *cmd;
  unsigned char *s_line;
  int index;
  bool dquote;
  bool quote;

  if (!arr->length)
  {
    return (NULL);
  }
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
    else if (*s_line != ';')
    {
      ft_arr_push(&cmd, ft_strdup((const char *)s_line), -1);
    }
    index++;
  }
  return (tab_cmds);
}

/**
 * pop usless space outside quote or dquote
 */
int  ft_parse_pop_space_inside(t_arr *arr)
{
  int index;
  unsigned char *s_line;
  bool dquote;
  bool quote;

  index = 0;
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
    if (!quote && !dquote && ft_isspace(*s_line))
    {
      if (index + 1 < (int)arr->length)
      {
        s_line = (unsigned char *)arr->ptr + (index + 1) * arr->sizeof_elem;
        s_line = *(unsigned char **)s_line;
        if (ft_isspace(*s_line))
        {
          free(ft_arr_pop(&arr, index));
        }
        else
        {
          index++;
        }
      }
      else
      {
        free(ft_arr_pop(&arr, index));
      }
    }
    else
    {
      index++;
    }
  }
  return (EXIT_SUCCESS);
}

/**
 * pop usles space on the begin of the command
 */
int  ft_parse_pop_prev_space(t_arr *arr)
{
  int index;
  unsigned char *s_line;

  index = 0;
  while (index < (int)arr->length)
  {
    s_line = (unsigned char *)arr->ptr + index * arr->sizeof_elem;
    s_line = *(unsigned char **)s_line;
    if (!ft_isspace(*s_line))
    {
      return (EXIT_SUCCESS);
    }
    else
    {
      free(ft_arr_pop(&arr, 0));
    }
  }

  return (EXIT_SUCCESS);
}

/**
 * itere every line and aply function who pop every usless space
 */
int  ft_parse_pop_space(t_arr *tab_cmds)
{
  int index;
  t_arr *cmd;

  index = 0;
  while (index < (int)tab_cmds->length)
  {
    cmd = *(t_arr **)((unsigned char *)tab_cmds->ptr + index * tab_cmds->sizeof_elem);
    ft_parse_pop_prev_space(cmd);
    ft_parse_pop_space_inside(cmd);
    if (!cmd->length)
    {
      ft_arr_free(ft_arr_pop(&tab_cmds, index));
    }
    index++;
  }

  return (EXIT_SUCCESS);
}


/**
 * parsing
 */
int  ft_parse_line(t_arr *arr)
{
  t_arr *tab_cmds;
  int index;
  t_arr *cmd;

  if (!(tab_cmds = ft_parse_separate_cmd(arr)))
  {
    return (EXIT_SUCCESS);
  }
  ft_parse_pop_space(tab_cmds);
  ft_putstr("\n");
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
