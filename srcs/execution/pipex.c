/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:45:57 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/20 17:40:59 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void close_pipes(int *pipes)
{
	int	i;
	int	pipe_nb;

	pipe_nb = (base()->pipe.num_cmds - 1) * 2;
	i = 0;
	while (i < pipe_nb)
	{
		close(pipes[i]);
		i++;
	}
}

static int	*pipe_ini(void)
{
	int	*pipes;
	int	i;

	pipes = malloc(sizeof(int) * (base()->pipe.num_cmds - 1) * 2);
	i = 0;
	while (i < (base()->pipe.num_cmds - 1) * 2)
	{
		pipe(pipes + i);
		i += 2;
	}
	return (pipes);
}

void	exec_pipe(int stdin_fd, int stdout_fd, int cmd, int *pipes)
{
	if (stdout_fd >= 0)
		dup2(stdout_fd, STDOUT_FILENO);
	if (stdin_fd >= 0)
		dup2(stdin_fd, STDIN_FILENO);
	close_pipes(pipes);
	execute(base()->pipe.cmds[cmd], -1);
	exit (0);
}

static void	loop_pipex(void)
{
	int	status;
	int	i;
	int	*pipes;

	pipes = pipe_ini();
	if (fork() == 0)
		exec_pipe(-1, pipes[1], 0, pipes);
	else
	{	
		i = 1;
		while (i < (base()->pipe.num_cmds) - 1)
		{
			if (fork() == 0)
				exec_pipe(pipes[(i - 1) * 2], pipes[(i - 1) * 2 + 3], i, pipes);
			else
				i++;
		}
	}
	if (fork() == 0)
		exec_pipe(pipes[(i - 1) * 2], -1, i, pipes);
	close_pipes(pipes);
	i = -1;
	while (++i < (base()->pipe.num_cmds))
		wait(&status);
	free(pipes);
}

void	control_pipex(void)
{
	if (base()->pipe.num_cmds == 1)
	{
		execute(base()->pipe.cmds[0], -1);
		return ;
	}
	loop_pipex();
}
