/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:45:57 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/31 17:31:04 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	auxiliar function that closes all pipes */
static void	close_pipes(int *pipes)
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

/*	initializes one pipe for each | on input
	there are 2 enterings for each pipe,
	so we have to alloc 2 * number of pipes
*/
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

/*	executes the command in the position cmd, reading from stdin_fd and
	writing in stdout_fd if this fd are -1 it reads and writes on
	STDIN_FILENO, STDOUT_FILENO all pipes are closed to prevent the
	program to be waiting forever
*/
void	exec_pipe(int stdin_fd, int stdout_fd, int cmd, int *pipes)
{
	if (stdout_fd >= 0)
		dup2(stdout_fd, STDOUT_FILENO);
	if (stdin_fd >= 0)
		dup2(stdin_fd, STDIN_FILENO);
	close_pipes(pipes);
	execute(base()->pipe.cmds[cmd], -1);
	exit (base()->errnumb);
}

/*	executes a list of commands delimited by pipes
*/
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
	{
		wait(&status);
		base()->errnumb = WEXITSTATUS(status);
	}
	free(pipes);
}

/*	checks if there's any pipe, if not executes the only read command
	if there's pipes, executes calls the function that executes them
*/
void	exec_all(void)
{
	if (base()->pipe.num_cmds == 1)
		execute(base()->pipe.cmds[0], -1);
	else
		loop_pipex();
	free_command_line();
}
