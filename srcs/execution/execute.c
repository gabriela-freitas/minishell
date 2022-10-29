/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:15:40 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/29 16:50:05 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*checks if cmd[0] is builtin and executes it, if not returns -1*/
static int	exe_builtin(char **cmd)
{
	if (!ft_strncmp(cmd[0], "echo", 5))
		ft_echo(cmd);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		cd(cmd);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		pwd();
	else if (!ft_strncmp(cmd[0], "env", 4))
		env(cmd);
	else if (!ft_strncmp(cmd[0], "export", 7))
		export(cmd);
	else if (!ft_strncmp(cmd[0], "exit", 6))
	{
		ft_exit(cmd);
		return (0);
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
	int		exit_status;
	char	**env;

	(void) fd;
	env = convert_env_list();
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		execve(path, cmd, env);
		exit(errno);
	}
	else
	{
		signal(SIGINT, sig_block_nl);
		waitpid(pid, &exit_status, 0);
		base()->errnumb = WEXITSTATUS(exit_status);
		free(path);
		free_split(env);
		return (0);
	}
	return (0);
}

/*tests if the list of commands can be executed with current paths,
	if yes, executes it, else it prints the error and exits*/
static int	exe_cmd(char **cmd, int fd)
{
	int		i;
	char	*path;
	char	*path_aux;

	i = 0;
	if (!access(cmd[0], X_OK))
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
	command_not_found(cmd[0]);
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
	{
		if (base()->errnumb == 13)
			command_not_found(cmds[0]);
		return (0);
	}
	else
		return (-1);
}

/*	checks if there's any pipe, if not executes the only read command
	if there's pipes, executes calls the function that executes them
*/
void	exec_all(void)
{
	if (base()->num_pipes == 1)
	{
		open_files(&base()->pipes[0]);
		/* DUP FILE DESCRIPTORS IF THERE'S A FILE FROM REDIRECTION */
		if (base()->pipes[0].fd[OUT] != STD)
		{
			dup2(base()->pipes[0].fd[OUT], STDOUT_FILENO);
		}
		if (base()->pipes[0].fd[IN] != STD)
		{
			dup2(base()->pipes[0].fd[IN], STDIN_FILENO);
		}
		if (base()->pipes[0].heredoc)
			close(((int *)base()->pipes[0].heredoc)[0]);
		/* DUP DONE */
		execute(&base()->pipes->cmds[0], -1);
		ft_putstr_fd(">>>>>>\n", 2);
		if (base()->pipes[0].fd[OUT] != STD)
		{
			close(base()->pipes[0].fd[OUT]);
		}
		if (base()->pipes[0].fd[IN] != STD)
		{
			close(base()->pipes[0].fd[IN]);
		}
	}
	else
		loop_pipex();
	free_command_line();
}
