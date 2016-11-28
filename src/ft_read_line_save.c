#include "project.h"

void  ft_loop(void)
{
  char *line;
  int read;

  ft_putstr("$> ");
  while ((read = get_next_line(0, &line)))
  {
    if (line)
    {
      ft_putstr(line);
      ft_putstr("\n");
      free(line);
      line = NULL;
    }
    ft_putstr("$> ");

  }
  if (line)
  {
    // exec line;
    ft_putstr("\n");
    ft_putstr(line);
    free(line);
    line = NULL;
    ft_putstr("\n$> ");
  }
  ft_putchar('\n');
  return;
}


void  ft_read_line(void)
{
  ft_putstr("test du read_line\n");
  ft_loop();
  return;
}
