#include "minishell.h"

int	exe_builtin(char **cmd)
{
	if (!ft_strncmp(cmd[0], "echo", 5))
		printf("%s\n", cmd[1]);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		cd(cmd[1]);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		pwd();
	else if (!ft_strncmp(cmd[0], "env", 4))
		print_env();
	else if (!ft_strncmp(cmd[0], "export", 7))
		export(cmd[1]);
	else if (!ft_strncmp(cmd[0], "exit", 6))
		return (0);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		unset(cmd[1]);
	else
		return (-1);
	return (0);
}

int ft_execve(char *path, char **cmd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
		execve(path, cmd, base()->env);
	else
	{
		waitpid(pid, NULL, 0);
		free(path);
		return (0);
	}
	return (0);
}

int	exe_cmd(char **cmd)
{
	int		i;
	char	*path;
	char	*path_aux;

	i = 0;
	while (base()->paths[i])
	{
		path_aux = ft_strjoin(base()->paths[i], "/");
		path = ft_strjoin(path_aux, cmd[0]);
		free(path_aux);
		if (!access(path, F_OK))
			return (ft_execve(path, cmd));
		free(path);
		i++;
	}
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

int execute(char **cmds)
{	
	if (exe_builtin(cmds) == 0)
		return (0);
	if (exe_cmd(cmds) == 0)
		return (0);
	else
		return (-1);
}
