#include "minishell.h"

//has more than 25 lines
void	parser(char *str)
{
	char	**cmd;
	int		i;
	size_t	length;

	cmd = NULL;
	cmd = malloc(sizeof(char*) * 2);
	if (!str)
		return ;
	length = ft_strlen(str);
	while (*str && ft_isspace(*str) == 1)
		str++;
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == 0)
			i++;
		else
			break ;
	}
	cmd[0] = ft_substr(str, 0, i); //criar saida para erro do cmd
	while (str[i] && ft_isspace(str[++i]) == 1);
	cmd[1] = ft_substr(str, i, length); //criar saida para erro do cmd
	// printf("cmd = %s\n", cmd[0]);
	// printf("args = %s\n", cmd[1]);
	execute(cmd);
	free(cmd[0]);
	free(cmd[1]);
	free(cmd); //nao libertar se der erro
	return ;
}
