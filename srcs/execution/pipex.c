/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:45:57 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/18 15:14:32 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

 void pipex(int i)
{
	(void) i;
	int pid;

	pid = fork();
	if (pid < 0)
		printf("error\n");
	else if (pid == 0)
	{
		close(base()->pipe.pipe_fd[0]);
		dup2(base()->pipe.pipe_fd[1], STDOUT_FILENO);
		execute(base()->pipe.cmds[0], base()->pipe.pipe_fd[1]);
		exit(0);
	}
	else
	{
		close(base()->pipe.pipe_fd[1]);
		dup2(base()->pipe.pipe_fd[0], STDIN_FILENO);
		close(base()->pipe.pipe_fd[1]);
		execute(base()->pipe.cmds[1], base()->pipe.pipe_fd[0]);
		exit(0);
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
	pipe(base()->pipe.pipe_fd);
	pid = fork();
	if (pid < 0)
		printf("error\n");
	else if (pid == 0)
	{
		pipex(i);
	}
	else
	{
		close(base()->pipe.pipe_fd[0]);
		close(base()->pipe.pipe_fd[1]);
		waitpid(pid, NULL, 0);
	}
}

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
