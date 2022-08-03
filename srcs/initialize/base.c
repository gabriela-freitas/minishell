#include "minishell.h"

void ini_paths(void)
{
	char *str;

	str = getenv("PATH");
	base()->paths = ft_split(str, ':');
}


void	base_free(void) //ir atualizando esta funcao a medida que adicionamos coisas no base
{
	env_free();
	//args_free();
	free_split(base()->paths);
}
