#include "project.h"

/**
 * delete n character from the current cursor's position
 */
int  ft_sup_char(int n)
{
  char *cmd;
  char *new;

  if ((cmd = tgetstr("dc", NULL)) == NULL) //sup one caracter from the cursor position
    return (EXIT_FAILURE); //pas quiter le programme
  new = ft_strnew(ft_strlen(cmd) + PADDING_BUFFER);
  ft_bzero(new, ft_strlen(cmd) + PADDING_BUFFER );
  ft_memcpy(new, cmd, ft_strlen(cmd));
  while (n--) {
    // tputs(cmd, 0, &my_putchar);
    tputs(new, 0, &my_putchar);
  }
  return (EXIT_SUCCESS);
}
