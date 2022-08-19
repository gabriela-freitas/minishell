/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:45:57 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/19 20:47:32 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void child3(int pipe_i, int cmd_i)
{
	if (cmd_i == 0)
	{
		close(base()->pipe.pipe_fd[pipe_i][0]);
		dup2(base()->pipe.pipe_fd[pipe_i][1], STDOUT_FILENO);
	}
	else if (cmd_i == base()->pipe.num_cmds - 1)
	{
		close(base()->pipe.pipe_fd[pipe_i][1]);
		dup2(base()->pipe.pipe_fd[pipe_i][0], STDIN_FILENO);
	}
	else
	{
		close(base()->pipe.pipe_fd[pipe_i - 1][1]);
		dup2(base()->pipe.pipe_fd[pipe_i - 1][0], STDIN_FILENO);
		close(base()->pipe.pipe_fd[pipe_i][0]);
		dup2(base()->pipe.pipe_fd[pipe_i][1], STDOUT_FILENO);
	}
	execute(base()->pipe.cmds[cmd_i], base()->pipe.pipe_fd[pipe_i][1]);
	exit(0);
	
}

 void pipex(int i)
{
	int pid;

	pid = fork();
	if (pid < 0)
		printf("error\n");
	else if (pid == 0)
	{
		child3(i, i);
	}
	else
	{
		child3(i, i + 1);
	}
	exit(0);
}

void loop_pipex(void)
{
	int i;
	int pid;

	i = 0;
	while (i < base()->pipe.num_cmds - 1)
	{
		pid = fork();
		if (pid < 0)
			printf("Error\n");
		else if (pid == 0)
			pipex(i);
		else
		{
			// close(base()->pipe.pipe_fd[i][0]);
			// close(base()->pipe.pipe_fd[i][1]);
			waitpid(pid, NULL, 0);
			exit(0);
		}
		i++;
	}
}

void control_pipex(int i)
{
	(void) i;
	int pid;

	if (base()->pipe.num_cmds == 1)
	{
		execute(base()->pipe.cmds[0], -1);
		return ;
	}
	i = 0;
	base()->pipe.pipe_fd = malloc(sizeof(int *) * base()->pipe.num_cmds);
	while (i < base()->pipe.num_cmds - 1)
	{
		base()->pipe.pipe_fd[i] = malloc(sizeof(int) * 2);
		pipe(base()->pipe.pipe_fd[i]);
		i++;
	}
	pid = fork();
	if (pid < 0)
		printf("error\n");
	else if (pid == 0)
	{
		loop_pipex();
	}
	else
	{
		i = 0;
		while (i < base()->pipe.num_cmds - 1)
		{
			close(base()->pipe.pipe_fd[i][0]);
			close(base()->pipe.pipe_fd[i][1]);
			i++;
		}
		waitpid(pid, NULL, 0);
	}
}



// void child2(int i) //i = num_pipe - 1
// {
// 	close(base()->pipe.pipe_fd[0][1]);
// 	dup2(base()->pipe.pipe_fd[0][0], STDIN_FILENO);
// 	close(base()->pipe.pipe_fd[0][1]);
// 	execute(base()->pipe.cmds[i], base()->pipe.pipe_fd[0][0]);
// 	exit(0);
// }

// void	child1(int i) // i = 0
// {
// 	close(base()->pipe.pipe_fd[0][0]);
// 	dup2(base()->pipe.pipe_fd[0][1], STDOUT_FILENO);
// 	execute(base()->pipe.cmds[i], base()->pipe.pipe_fd[0][1]);
// 	exit(0);
// }

// void pipex(int i)
// {
// 	// (void) i;
// 	int fd[2];
// 	int pid;

// 	pipe(fd);
// 	pid = fork();
// 	if (pid < 0)
// 		printf("error\n");
// 	else if (pid == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		execute(base()->pipe.cmds[0], fd[1]);
// 		exit(0);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[1]);
// 		execute(base()->pipe.cmds[1], fd[0]);
// 		exit(0);
// 	}
// }
