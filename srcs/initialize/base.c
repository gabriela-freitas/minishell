#include "minishell.h"

void ini_paths(void)
{
	char	*paths;

	paths = getenv("PATH");
	base()->paths = ft_split(paths, ':');
	base()->home = getenv("HOME");
}


void	base_free(void) //ir atualizando esta funcao a medida que adicionamos coisas no base
{
	env_free();
	//args_free();
	free_split(base()->paths);
	ft_lstclear(&base()->cmds, free);
}
