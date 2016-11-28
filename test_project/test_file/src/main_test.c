#include "test_project.h"

int   main(int ac, char **av, char **env)
{

  ft_putstr("\033[32mhello unit_test get started\n");
  ft_putstr("\033[0m");

  // ut_print();
  // ut_env(ac, av, env);
  // ut_free();

  // ut_arr();
  ut_read_line();

  (void)ac;
  (void)av;
  (void)env;
  return (0);
}
