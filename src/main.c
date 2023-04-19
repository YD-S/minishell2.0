
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	ft_init_global(envp);
	while (1)
	{
		line = ft_readline();
		add_history(line);
		ft_check_cmd(line);
	}
}
