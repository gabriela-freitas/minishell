/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:15:40 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/17 21:42:54 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*checks if cmd[0] is builtin and executes it, if not returns -1*/
static int	exe_builtin(char **cmd)
{
	if (!ft_strncmp(cmd[0], "echo", 5))
		ft_echo(cmd);
	else if (!ft_strncmp(cmd[0], "cd", 3)) //rever este builtin
		cd(cmd[1]);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		pwd();
	else if (!ft_strncmp(cmd[0], "env", 4))
		print_env();
	else if (!ft_strncmp(cmd[0], "export", 7))
		export(cmd);
	else if (!ft_strncmp(cmd[0], "exit", 6))
	{
		ft_exit(cmd);
		return (0); //GABI ft_exit(0);
	}
	else if (!ft_strncmp(cmd[0], "unset", 6))
		unset(cmd);
	else
		return (-1);
	return (0);
}

/*executes the list of commands, and avoids the program to exit*/
static int	ft_execve(char *path, char **cmd, int fd)
{
	int		pid;
	char	**env;
	(void) fd;

	env = convert_env_list();
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		execve(path, cmd, env);
		// write(2, "error in execve\n", 17);
	}
	else
	{
		// close(fd);
		waitpid(pid, NULL, 0);
		// wait(NULL);
		// write(2, "in parent process of ft_execve\n", 31);
		free(path);
		free_split(env);
		return (0);
	}
	return (0);
}

/*tests if the list of commands can be executed with current paths,
	if yes, executes it, else it prints the error and exits*/
int	exe_cmd(char **cmd, int fd)
{
	int		i;
	char	*path;
	char	*path_aux;

	i = 0;
	if (!access(cmd[0], F_OK))
		return (ft_execve(ft_strdup(cmd[0]), cmd, fd));
	while (base()->paths && base()->paths[i])
	{
		path_aux = ft_strjoin(base()->paths[i], "/");
		path = ft_strjoin(path_aux, cmd[0]);
		free(path_aux);
		if (!access(path, F_OK))
			return (ft_execve(path, cmd, fd));
		free(path);
		i++;
	}
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

/*Executes the list if commands*/
int	execute(char **cmds, int fd)
{
	if (fd >= 0)
		close(fd);
	if (exe_builtin(cmds) == 0)
		return (0);
	if (exe_cmd(cmds, fd) == 0)
		return (0);
	else
		return (-1);
}
