#include "minishell.h"

void execute_echo(char **args)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "-n") != 0)
		{
			if (i < ft_charpplen(args) - 1)
				ft_printf("%s ", args[i]);
			else
				ft_printf("%s", args[i]);
		}
		else
			option = 1;
		i++;
	}
	if (!option)
		ft_printf("\n");
}