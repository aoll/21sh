#include "test_project.h"

void  ut_print(void)
{
  ft_start();
  ut_name_function_tested("ut_print");
  ut_name_function_tested("ft_start");
  ut_success();
  ut_fail();
  printf("\n");
  return;
}
