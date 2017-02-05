/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 09:31:13 by alex              #+#    #+#             */
/*   Updated: 2017/02/05 20:08:22 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"


/**
 * replace all 2> and 2&> outside quote and dquote
 */
int  ft_parse_replace_sdterr_redirect(t_arr *arr)
{
  int index;
  char *s_line;
  char *s_prev_line;
  char *s_prev_prev_line;
  char *s_prev_prev_prev_line;
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
    if (!dquote && !quote && *s_line == S_RIGHT_REDIRECT)
    {
      if (index - 1 >= 0)
      {
        s_prev_line = *(char **)((unsigned char *)arr->ptr + (index - 1) * arr->sizeof_elem);
        if (*s_prev_line == '2')
        {

          if (index - 2 < 0)
          {
            *s_prev_line = ' ';
            *s_line = STDERR_REDIRECT;
            index++;
            continue;
          }
          else
          {
            s_prev_prev_line = *(char **)((unsigned char *)arr->ptr + (index - 2) * arr->sizeof_elem);
            if (ft_isspace(*s_prev_prev_line))
            {
              *s_prev_line = ' ';
              *s_line = STDERR_REDIRECT;
              index++;
              continue;
            }
          }
        }
        else if (*s_prev_line == '1')
        {
          if (index - 2 < 0)
          {
            *s_prev_line = ' ';
            // *s_line = STDERR_REDIRECT;
            index++;
            continue;
          }
          else
          {
            s_prev_prev_line = *(char **)((unsigned char *)arr->ptr + (index - 2) * arr->sizeof_elem);
            if (ft_isspace(*s_prev_prev_line))
            {
              *s_prev_line = ' ';
              // *s_line = STDERR_REDIRECT;
              index++;
              continue;
            }
          }
        }
        if (*s_prev_line == '&')
        {
          if (index - 2 >= 0)
          {
            s_prev_prev_line = *(char **)((unsigned char *)arr->ptr + (index - 2) * arr->sizeof_elem);
            if (*s_prev_prev_line == '2')
            {
              if (index - 3 < 0)
              {
                *s_line = STDERR_REDIRECT;
                *s_prev_line = ' ';
                *s_prev_prev_line = ' ';
                index++;
                continue;
              }
              else
              {
                s_prev_prev_prev_line = *(char **)((unsigned char *)arr->ptr + (index - 3) * arr->sizeof_elem);
                if (ft_isspace(*s_prev_prev_prev_line))
                {
                  *s_line = STDERR_REDIRECT;
                  *s_prev_line = ' ';
                  *s_prev_prev_line = ' ';
                  index++;
                  continue;
                }
              }
            }
            else if (*s_prev_prev_line == '1')
            {
              if (index - 3 < 0)
              {
                // *s_line = S_REDIRECT;
                *s_prev_line = ' ';
                *s_prev_prev_line = ' ';
                index++;
                continue;
              }
              else
              {
                s_prev_prev_prev_line = *(char **)((unsigned char *)arr->ptr + (index - 3) * arr->sizeof_elem);
                if (ft_isspace(*s_prev_prev_prev_line))
                {
                  // *s_line = STDERR_REDIRECT;
                  *s_prev_line = ' ';
                  *s_prev_prev_line = ' ';
                  index++;
                  continue;
                }
              }
            }
          }
        }

      }
    }
    index++;
  }
  return (EXIT_SUCCESS);
}
/**
 * replace all 2>> and 2&>> outside quote and dquote
 */
int  ft_parse_replace_sdterr_double_redirect(t_arr *arr)
{
  int index;
  char *s_line;
  char *s_prev_line;
  char *s_prev_prev_line;
  char *s_prev_prev_prev_line;
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
    if (!dquote && !quote && *s_line == D_RIGHT_REDIRECT)
    {
      if (index - 1 >= 0)
      {
        s_prev_line = *(char **)((unsigned char *)arr->ptr + (index - 1) * arr->sizeof_elem);
        if (*s_prev_line == '2')
        {

          if (index - 2 < 0)
          {
            *s_prev_line = ' ';
            *s_line = D_STDERR_REDIRECT;
            index++;
            continue;
          }
          else
          {
            s_prev_prev_line = *(char **)((unsigned char *)arr->ptr + (index - 2) * arr->sizeof_elem);
            if (ft_isspace(*s_prev_prev_line))
            {
              *s_prev_line = ' ';
              *s_line = D_STDERR_REDIRECT;
              index++;
              continue;
            }
          }
        }
        else if (*s_prev_line == '1')
        {
          if (index - 2 < 0)
          {
            *s_prev_line = ' ';
            // *s_line = STDERR_REDIRECT;
            index++;
            continue;
          }
          else
          {
            s_prev_prev_line = *(char **)((unsigned char *)arr->ptr + (index - 2) * arr->sizeof_elem);
            if (ft_isspace(*s_prev_prev_line))
            {
              *s_prev_line = ' ';
              // *s_line = STDERR_REDIRECT;
              index++;
              continue;
            }
          }
        }
        if (*s_prev_line == '&')
        {
          if (index - 2 >= 0)
          {
            s_prev_prev_line = *(char **)((unsigned char *)arr->ptr + (index - 2) * arr->sizeof_elem);
            if (*s_prev_prev_line == '2')
            {
              if (index - 3 < 0)
              {
                *s_line = D_STDERR_REDIRECT;
                *s_prev_line = ' ';
                *s_prev_prev_line = ' ';
                index++;
                continue;
              }
              else
              {
                s_prev_prev_prev_line = *(char **)((unsigned char *)arr->ptr + (index - 3) * arr->sizeof_elem);
                if (ft_isspace(*s_prev_prev_prev_line))
                {
                  *s_line = D_STDERR_REDIRECT;
                  *s_prev_line = ' ';
                  *s_prev_prev_line = ' ';
                  index++;
                  continue;
                }
              }
            }
            else if (*s_prev_prev_line == '1')
            {
              if (index - 3 < 0)
              {
                // *s_line = D_STDERR_REDIRECT;
                *s_prev_line = ' ';
                *s_prev_prev_line = ' ';
                index++;
                continue;
              }
              else
              {
                s_prev_prev_prev_line = *(char **)((unsigned char *)arr->ptr + (index - 3) * arr->sizeof_elem);
                if (ft_isspace(*s_prev_prev_prev_line))
                {
                  // *s_line = D_STDERR_REDIRECT;
                  *s_prev_line = ' ';
                  *s_prev_prev_line = ' ';
                  index++;
                  continue;
                }
              }
            }
          }
        }

      }
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
  int index_tmp;

  check = false;
  dquote = false;
  quote = false;
  index = 0;
  while (index < (int)arr->length)
  {
    s_line = *(char **)((unsigned char *)arr->ptr + index * arr->sizeof_elem);
    if (*s_line == PIPE && !index && token == PIPE)
    {
      return (EXIT_FAILURE);
    }
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
      if (check)
      {
        if (*s_line == D_LEFT_REDIRECT || *s_line == D_RIGHT_REDIRECT
        || *s_line == S_LEFT_REDIRECT || *s_line == S_RIGHT_REDIRECT
        || *s_line == PIPE)
        {
          if (*s_line != PIPE && token == PIPE)
          {
            free(ft_arr_pop(&arr, index_tmp));
            index -= 1;
          }
          else
          {
            return (EXIT_FAILURE);
          }
        }
      }
      if (*s_line == token)
      {
        index_tmp = index;
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
      || *s_line == PIPE || *s_line == STDOUT_STDERR_REDIRECT
      || *s_line == STDERR_REDIRECT || *s_line == D_STDERR_REDIRECT)
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
 * check if a token is not the end of the command (space not included)
 * return 1 if is true or 0 if not
 */
int  ft_parse_check_file_redirect(t_arr *arr)
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
      if (*s_line == FILE_REDIRECT)
      {
        if (index + 1 < (int)arr->length)
        {
          s_line = *(char **)((unsigned char *)arr->ptr + (index + 1) * arr->sizeof_elem);
          if (*s_line == D_LEFT_REDIRECT)
          {
            ft_putstr_fd("\n21sh: parse error near `>'", STDERR);
            return (EXIT_FAILURE);
          }
          if (ft_isspace(*s_line))
          {
            ft_putstr_fd("\n21sh: parse error near `&'", STDERR);
            return (EXIT_FAILURE);
          }
        }
        else
        {
          ft_putstr_fd("\n21sh: parse error near `\\n'", STDERR);
          return (EXIT_FAILURE);
        }
        if (index - 1 >= 0)
        {
          s_line = *(char **)((unsigned char *)arr->ptr + (index - 1) * arr->sizeof_elem);
          if (ft_isspace(*s_line))
          {
            ft_putstr_fd("\n21sh: parse error near `&'", STDERR);
            return (EXIT_FAILURE);
          }
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
    ft_putstr_fd("\n21sh: parse error near `<'", STDERR);
    return (EXIT_FAILURE);
  }
  else if ((err = ft_parse_check_double(cmd, D_LEFT_REDIRECT)))
  {
    ft_putstr_fd("\n21sh: parse error near `<'", STDERR);
    return (EXIT_FAILURE);
  }
  else if ((err = ft_parse_check_double(cmd, S_RIGHT_REDIRECT)))
  {
    ft_putstr_fd("\n21sh: parse error near `>'", STDERR);
    return (EXIT_FAILURE);
  }
  else if ((err = ft_parse_check_double(cmd, D_RIGHT_REDIRECT)))
  {
    ft_putstr_fd("\n21sh: parse error near `>'", STDERR);
    return (EXIT_FAILURE);
  }
  else if ((err = ft_parse_check_double(cmd, STDOUT_STDERR_REDIRECT)))
  {
    ft_putstr_fd("\n21sh: parse error near `>'", STDERR);
    return (EXIT_FAILURE);
  }
  else if ((err = ft_parse_check_double(cmd, PIPE)))
  {
    ft_putstr_fd("\n21sh: parse error near `|'", STDERR);
    return (EXIT_FAILURE);
  }
  else if ((err = ft_parse_check_end_space(cmd)))
  {
    ft_putstr_fd("\n21sh: parse error near `\\n'", STDERR);
    return (EXIT_FAILURE);
  }
  else if ((err = ft_parse_check_file_redirect(cmd)))
  {
    // ft_putstr("\n21sh: parse error near `&'");
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
    if ((err = ft_parse_check_double_redirect(cmd)))
    {
      ft_putstr_fd("\n21sh: parse error near `&'", STDERR);
      return (EXIT_FAILURE);
    }

    ft_parse_replace_sdterr_redirect(cmd);
    ft_parse_replace_sdterr_double_redirect(cmd);
    ft_parse_replace_stdin_sdterr_redirect(cmd);
    ft_parse_replace_file_redirect(cmd);

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
  int err;
  // int index;
  // t_arr *cmd;

  if (!(tab_cmds = ft_parse_separate_cmd(arr)))
  {
    return (NULL);
  }
  if ((err = ft_parse_pop_and_replace_and_check_error(tab_cmds)))
  {
    //TODO free t_arr * t_arr *
    return (NULL);
  }
  return (tab_cmds);
}
