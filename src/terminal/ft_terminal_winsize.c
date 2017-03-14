#include "project.h"
/*
 * take the adress of a struct winsize and if success git it the informations
 * of the terminal size
 */
int ft_terminal_winsize(struct winsize *terminal_size)
{
  if (ioctl(STDIN_FILENO,TIOCGWINSZ, (char*) terminal_size) < 0)
  {
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}
