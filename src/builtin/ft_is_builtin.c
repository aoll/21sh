#include "project.h"

/*
** compare a string to a listtof builtin a return the index if is presenttor 0 if no
*/

int	ft_is_builtin(char *command)
{
	if (!command)
		return (0);
	else if (!ft_strcmp("env", command))
		return (B_ENV);
	else if (!ft_strcmp("setenv", command))
		return (B_SETENV);
	else if (!ft_strcmp("unsetenv", command))
		return (B_UNSETENV);
	else if (!ft_strcmp("cd", command))
		return (B_CD);
	else if (!ft_strcmp("echo", command))
		return (B_ECHO);
	else if (!ft_strcmp("exit", command))
		return (B_EXIT);
	return (0);
}
