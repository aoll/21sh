/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 09:31:13 by alex              #+#    #+#             */
/*   Updated: 2016/12/29 16:43:40 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    else if (*s_line == '\'' && !dquote)
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
 * replace space outside quote or dquote
 */
int  ft_parse_replace_space(t_arr *arr)
{
  int index;
  unsigned char *s_line;
  bool dquote;
  bool quote;

  dquote = false;
  quote = false;
  index = 0;
  while (index < (int)arr->length)
  {
    s_line = (unsigned char *)arr->ptr + index * arr->sizeof_elem;
    s_line = *(unsigned char **)s_line;
    if (*s_line == '"' && !quote)
    {
      *s_line = SPACE_SEPARATOR;
      dquote = !dquote;
    }
    else if (*s_line == '\'' && !dquote)
    {
      *s_line = SPACE_SEPARATOR;
      quote = !quote;
    }
    if (!quote && !dquote && ft_isspace(*s_line))
    {
      *s_line = SPACE_SEPARATOR;
    }
    index++;
  }
  return (EXIT_SUCCESS);
}

/**
 * replace all double left redirection outside quote and dquote
 */
int  ft_parse_replace_d_left_redirect(t_arr *arr)
{
  int index;
  unsigned char *s_line;
  bool dquote;
  bool quote;

  dquote = false;
  quote = false;
  index = 0;
  while (index < (int)arr->length)
  {
    s_line = (unsigned char *)arr->ptr + index * arr->sizeof_elem;
    s_line = *(unsigned char **)s_line;
    if (*s_line == '"' && !quote)
    {
      dquote = !dquote;
    }
    else if (*s_line == '\'' && !dquote)
    {
      quote = !quote;
    }
    if (!dquote && !quote)
    {
      if (*s_line == '<' && index + 1 < (int)arr->length)
      {
        s_line = (unsigned char *)arr->ptr + (index + 1) * arr->sizeof_elem;
        s_line = *(unsigned char **)s_line;
        if (*s_line == '<')
        {
          free(ft_arr_pop(&arr, index));
          *s_line = D_LEFT_REDIRECT;
        }
      }
    }
    index++;
  }
  return (EXIT_SUCCESS);
}
/**
 * replace all double right redirection outside quote and dquote
 */
int  ft_parse_replace_d_right_redirect(t_arr *arr)
{
  int index;
  unsigned char *s_line;
  bool dquote;
  bool quote;

  dquote = false;
  quote = false;
  index = 0;
  while (index < (int)arr->length)
  {
    s_line = (unsigned char *)arr->ptr + index * arr->sizeof_elem;
    s_line = *(unsigned char **)s_line;
    if (*s_line == '"' && !quote)
    {
      dquote = !dquote;
    }
    else if (*s_line == '\'' && !dquote)
    {
      quote = !quote;
    }
    if (!dquote && !quote)
    {
      if (*s_line == '>' && index + 1 < (int)arr->length)
      {
        s_line = (unsigned char *)arr->ptr + (index + 1) * arr->sizeof_elem;
        s_line = *(unsigned char **)s_line;
        if (*s_line == '>')
        {
          free(ft_arr_pop(&arr, index));
          *s_line = D_RIGHT_REDIRECT;
        }
      }
    }
    index++;
  }
  return (EXIT_SUCCESS);
}
/**
 * replace all simple right redirection outside quote and dquote
 */
int  ft_parse_replace_s_right_redirect(t_arr *arr)
{
  int index;
  unsigned char *s_line;
  bool dquote;
  bool quote;

  dquote = false;
  quote = false;
  index = 0;
  while (index < (int)arr->length)
  {
    s_line = (unsigned char *)arr->ptr + index * arr->sizeof_elem;
    s_line = *(unsigned char **)s_line;
    if (*s_line == '"' && !quote)
    {
      dquote = !dquote;
    }
    else if (*s_line == '\'' && !dquote)
    {
      quote = !quote;
    }
    if (!dquote && !quote && *s_line == '>')
    {
      *s_line = S_RIGHT_REDIRECT;
    }
    index++;
  }
  return (EXIT_SUCCESS);
}
/**
 * replace all simple left redirection outside quote and dquote
 */
int  ft_parse_replace_s_left_redirect(t_arr *arr)
{
  int index;
  unsigned char *s_line;
  bool dquote;
  bool quote;

  dquote = false;
  quote = false;
  index = 0;
  while (index < (int)arr->length)
  {
    s_line = (unsigned char *)arr->ptr + index * arr->sizeof_elem;
    s_line = *(unsigned char **)s_line;
    if (*s_line == '"' && !quote)
    {
      dquote = !dquote;
    }
    else if (*s_line == '\'' && !dquote)
    {
      quote = !quote;
    }
    if (!dquote && !quote && *s_line == '<')
    {
      *s_line = S_LEFT_REDIRECT;
    }
    index++;
  }
  return (EXIT_SUCCESS);
}
/**
 * replace all pipe outside quote and dquote
 */
int  ft_parse_replace_pipe(t_arr *arr)
{
  int index;
  unsigned char *s_line;
  bool dquote;
  bool quote;

  dquote = false;
  quote = false;
  index = 0;
  while (index < (int)arr->length)
  {
    s_line = (unsigned char *)arr->ptr + index * arr->sizeof_elem;
    s_line = *(unsigned char **)s_line;
    if (*s_line == '"' && !quote)
    {
      dquote = !dquote;
    }
    else if (*s_line == '\'' && !dquote)
    {
      quote = !quote;
    }
    if (!dquote && !quote && *s_line == '|')
    {
      *s_line = PIPE;
    }
    index++;
  }
  return (EXIT_SUCCESS);
}

/**
 * check if the token past in parameter in present in double succecsive
 * return 1 if is true or 0 if not
 */
int  ft_parse_check_double(t_arr *arr, int token)
{
  int index;
  char *s_line;
  bool dquote;
  bool quote;
  bool check;

  check = false;
  dquote = false;
  quote = false;
  index = 0;
  while (index < (int)arr->length)
  {
    s_line = *(char **)((unsigned char *)arr->ptr + index * arr->sizeof_elem);
    if (*s_line == '"' && !quote)
    {
      dquote = !dquote;
    }
    else if (*s_line == '\'' && !dquote)
    {
      quote = !quote;
    }
    if (!dquote && !quote)
    {
      if (check && token != PIPE)
      {
        if (*s_line == D_LEFT_REDIRECT || *s_line == D_RIGHT_REDIRECT
        || *s_line == S_LEFT_REDIRECT || *s_line == S_RIGHT_REDIRECT
        || *s_line == PIPE)
        {
          return (EXIT_FAILURE);
        }
      }
      if (*s_line == token)
      {
        if (check)
        {
          return (EXIT_FAILURE);
        }
        check = true;
      }
      else if (!ft_isspace(*s_line))
      {
        check = false;
      }
    }
    index++;
  }
  return (EXIT_SUCCESS);
}

/**
 * check if the charactere are only space
 * if a not space if found return 0
 */
int  ft_parse_is_only_space(t_arr *arr, int index)
{
  char *s_line;

  while (index < (int)arr->length)
  {
    s_line = *(char **)((unsigned char *)arr->ptr + index * arr->sizeof_elem);
    if (!ft_isspace(*s_line))
    {
      return (EXIT_SUCCESS);
    }
    index++;
  }
  return (EXIT_FAILURE);
}

/**
 * check if a token is not the end of the command (space not included)
 * return 1 if is true or 0 if not
 */
int  ft_parse_check_end_space(t_arr *arr)
{
  int index;
  char *s_line;
  bool dquote;
  bool quote;

  dquote = false;
  quote = false;
  index = 0;
  while (index < (int)arr->length)
  {
    s_line = *(char **)((unsigned char *)arr->ptr + index * arr->sizeof_elem);
    if (*s_line == '"' && !quote)
    {
      dquote = !dquote;
    }
    else if (*s_line == '\'' && !dquote)
    {
      quote = !quote;
    }
    if (!dquote && !quote)
    {
      if (*s_line == D_LEFT_REDIRECT || *s_line == D_RIGHT_REDIRECT
      || *s_line == S_LEFT_REDIRECT || *s_line == S_RIGHT_REDIRECT
      || *s_line == PIPE)
      {
        if (ft_parse_is_only_space(arr, index + 1))
        {
          return (EXIT_FAILURE);
        }
      }
    }
    index++;
  }
  return (EXIT_SUCCESS);
}

/**
 * iter every line and apply a batery of function to check the good grammar
 * of different command
 */
int  ft_parse_check_error(t_arr *cmd)
{
  int err;

  if ((err = ft_parse_check_double(cmd, S_LEFT_REDIRECT)))
  {
    ft_putstr("\n21sh: parse error near `<'");
    return (EXIT_FAILURE);
  }
  else if ((err = ft_parse_check_double(cmd, D_LEFT_REDIRECT)))
  {
    ft_putstr("\n21sh: parse error near `<'");
    return (EXIT_FAILURE);
  }
  else if ((err = ft_parse_check_double(cmd, S_RIGHT_REDIRECT)))
  {
    ft_putstr("\n21sh: parse error near `>'");
    return (EXIT_FAILURE);
  }
  else if ((err = ft_parse_check_double(cmd, D_RIGHT_REDIRECT)))
  {
    ft_putstr("\n21sh: parse error near `>'");
    return (EXIT_FAILURE);
  }
  else if ((err = ft_parse_check_double(cmd, PIPE)))
  {
    ft_putstr("\n21sh: parse error near `|'");
    return (EXIT_FAILURE);
  }
  else if ((err = ft_parse_check_end_space(cmd)))
  {
    ft_putstr("\n21sh: parse error near `\\n'");
    return (EXIT_FAILURE);
  }


  return (EXIT_SUCCESS);
}

/**
 * itere every line and aply function who pop every usless space
 *
 */
int  ft_parse_pop_and_replace_and_check_error(t_arr *tab_cmds)
{
  int index;
  t_arr *cmd;
  int err;

  index = 0;
  while (index < (int)tab_cmds->length)
  {
    cmd = *(t_arr **)((unsigned char *)tab_cmds->ptr + index * tab_cmds->sizeof_elem);
    ft_parse_pop_prev_space(cmd);
    ft_parse_pop_space_inside(cmd);
    ft_parse_replace_d_left_redirect(cmd);
    ft_parse_replace_d_right_redirect(cmd);
    ft_parse_replace_s_left_redirect(cmd);
    ft_parse_replace_s_right_redirect(cmd);
    ft_parse_replace_pipe(cmd);
    if ((err = ft_parse_check_error(cmd)))
    {
      return (EXIT_FAILURE);
    }
    ft_parse_replace_space(cmd);
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
t_arr  *ft_parse_line(t_arr *arr)
{
  t_arr *tab_cmds;
  int index;
  t_arr *cmd;
  int err;

  if (!(tab_cmds = ft_parse_separate_cmd(arr)))
  {
    return (NULL);
  }
  if ((err = ft_parse_pop_and_replace_and_check_error(tab_cmds)))
  {
    //TODO free t_arr * t_arr *
    return (NULL);
  }
  // ft_putstr("\n");
  // index = 0;
  // while (index < (int)tab_cmds->length)
  // {
  //   cmd = *(t_arr **)((unsigned char *)tab_cmds->ptr + index * tab_cmds->sizeof_elem);
  //   ft_arr_print(cmd);
  //   ft_putstr("\n");
  //   index++;
  // }
  // ft_putstr("\n");
  // ft_putstr("parsing start\n");
  return (tab_cmds);
}
