/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:45:57 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/17 22:06:38 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	child1(char **cmds, int fd[2])
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	execute(cmds, fd[1]);
	exit(0);
}

int	child2(char **cmds, int fd[2])
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	execute(cmds, fd[0]);
	exit(0);
}

void pipex(int i)
{
	(void) i;
	int fd[2];
	int pid;

	pipe(fd);
	pid = fork();
	if (pid < 0)
		printf("error\n");
	else if (pid == 0)
	{
		child1(base()->pipe.cmds[0], fd);
	}
	else
	{
		child2(base()->pipe.cmds[1], fd);	
	}
}


void control_pipex(int i)
{
	int pid;

	pid = fork();
	if (pid < 0)
		printf("error\n");
	else if (pid == 0)
	{
		pipex(i);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

	


// // static void	parent_process(int i);

// // pipe[0] >> read
// // pipe[1] >> write
// void	pipex(int i)
// {
// 	(void) i;
// 	pid_t pid;

// 	if (base()->pipe.num_cmds == 1)
// 	{
// 		execute(base()->pipe.cmds[0], -1);
// 		return ;
// 	}
// 	if (pipe(base()->pipe.pipe_fd) == -1)
// 	{
// 		printf("Pipe didn't work\n");
// 		return ;
// 	}
// 	pid = fork();
// 	if (!pid)
// 	{
// 		close(base()->pipe.pipe_fd[0]); //fechando o que n vou usar
// 		dup2(base()->pipe.pipe_fd[1], STDOUT_FILENO); //dup the write part to stdout
// 		write(2, "before cmd 1>>>>\n", 18);
// 		execute(base()->pipe.cmds[0], base()->pipe.pipe_fd[1]); //executar e fechar o que ja dei dup
// 		write(2, "after cmd 1>>>>>\n", 18);
// 		close(base()->pipe.pipe_fd[1]); //fechando o q n vou usar "so that it no longer refers to any file and may be reused"
// 		dup2(base()->pipe.pipe_fd[0], STDIN_FILENO); //dup the read part to stdin
// 		write(2, "before cmd 2>>>>>\n", 18);
// 		execute(base()->pipe.cmds[1], base()->pipe.pipe_fd[0]); //executar e fechar o q dei dup
// 		write(2, "after cmd 2>>>>>\n", 18);
// 	}
// 	else
// 	{
// 		close(base()->pipe.pipe_fd[1]);
// 		close(base()->pipe.pipe_fd[0]);
// 		waitpid(pid, NULL, 0);
// 	}
// 	return ;
// }
// 	// while (++i < base()->pipe.num_cmds)
// 	// {
// 	// 	if (pipe(base()->pipe.pipe_fd) == -1)
// 	// 	{
// 	// 		// exit_message("Pipe didn't work");
// 	// 		printf("Pipe didn't work\n");
// 	// 		return ;
// 	// 	}
// 	// 	//close(base()->pipe.pipe_aux[1]);
// 	// 	if (i == 0)
// 	// 		close(base()->pipe.pipe_fd[0]);
// 	// 	first_child_process(i);
// 	// 	// close(base()->pipe.pipe_fd[1]);
// 	// 	if (i == base()->pipe.num_cmds - 1)
// 	// 		break ;
// 	// 	i++;
// 	// 	if (pipe(base()->pipe.pipe_aux) == -1)
// 	// 	{
// 	// 		// exit_message("Pipe aux didn't work");
// 	// 		printf("Pipe aux didn't work\n");
// 	// 		return ;
// 	// 	}
// 	// 	// close(base()->pipe.pipe_aux[0]);
// 	// 	second_child_process(i);
// 	// 	// close(base()->pipe.pipe_aux[1]);
// 	// 	// close(base()->pipe.pipe_fd[0]);
// 	// }
