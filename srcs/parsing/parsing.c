#include "minishell.h"

int	ft_is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (ECHO);
	if (!ft_strncmp(cmd, "cd", 3))
		return (CD);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (PWD);
	if (!ft_strncmp(cmd, "env", 4))
		return (ENV);
	if (!ft_strncmp(cmd, "export", 7))
		return (EXPORT);
	if (!ft_strncmp(cmd, "exit", 6))
		return (EXIT);
	if (!ft_strncmp(cmd, "unset", 6))
		return (UNSET);
	return (-1);
}

int	check_cmd(char *str)
{
	printf("%d\n", ft_is_builtin(str));
	printf("%s\n", getenv("PATH"));
	return (0);
}

//has more than 25 lines
void	parser(char *str)
{
	char	*args;
	char	*cmd;
	int		i;
	size_t	length;

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
	cmd = ft_substr(str, 0, i); //criar saida para erro do cmd
	check_cmd(cmd);
	while (str[i] && ft_isspace(str[++i]) == 1);
	args = ft_substr(str, i, length); //criar saida para erro do cmd
	printf("cmd = %s\n", cmd);
	printf("args = %s\n", args);
	free(cmd); //nao libertar se der erro
	free(args); // nao libertar se der erro
	return ;
}

