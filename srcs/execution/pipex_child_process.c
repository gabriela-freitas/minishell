/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:48:52 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/12 19:20:26 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command(int read, int write, char **command);
void		first_child_process(int i);
void		second_child_process(int i);

// pipe[0] >> read
// pipe[1] >> write
/*execute command with execve*/
static void	exec_command(int read, int write, char **command)
{
	if (read != STDIN_FILENO)
	{
		if (dup2(read, STDIN_FILENO) == -1)
		{
			// exit_message("could not dup read fd");
			printf("could not dup read fd\n");
			return ;
		}
		close(read);
	}
	if (write != STDOUT_FILENO)
	{
		if (dup2(write, STDOUT_FILENO) == -1)
		{
			// exit_message("could not dup output fd");
			printf("could not dup output fd\n");
			return ;
		}
		close(write);
	}
	//execve(command[0], command, infos()->envp);
	//exit_message("exec did not work");
	if (execute(command) < 0)
		printf("execute did not work\n");
}

/* write process ::: will allways read either from pipe_aux[0] or from STDIN
	and write on pipe_fd[1]*/
void	first_child_process(int i)
{
	if (i == 0)
	{
		close(base()->pipe.pipe_fd[0]);
		exec_command(STDIN_FILENO, base()->pipe.pipe_fd[1],
			base()->pipe.cmds[i]);
	}
	else if (i == base()->pipe.num_cmds - 1)
	{
		close(base()->pipe.pipe_aux[1]);
		exec_command(base()->pipe.pipe_aux[0], STDOUT_FILENO,
			base()->pipe.cmds[i]);
	}
	else
	{
		close(base()->pipe.pipe_aux[1]);
		close(base()->pipe.pipe_fd[0]);
		exec_command(base()->pipe.pipe_aux[0],
			base()->pipe.pipe_fd[1], base()->pipe.cmds[i]);
	}
}

/*read process ::: will allways read pipe_fd[0]
	and write on pipe_aux[1] or STDOUT*/
void	second_child_process(int i)
{
	if (i == base()->pipe.num_cmds - 1)
	{
		close(base()->pipe.pipe_fd[1]);
		close(base()->pipe.pipe_aux[0]);
		exec_command(base()->pipe.pipe_fd[0], STDOUT_FILENO,
			base()->pipe.cmds[i]);
	}
	else
	{
		close(base()->pipe.pipe_fd[1]);
		close(base()->pipe.pipe_aux[0]);
		exec_command(base()->pipe.pipe_fd[0],
			base()->pipe.pipe_aux[1], base()->pipe.cmds[i]);
	}
}
