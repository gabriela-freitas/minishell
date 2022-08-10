/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:48:52 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/10 23:05:44 by gafreita         ###   ########.fr       */
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
	if (dup2(read, STDIN_FILENO) == -1)
	{
		// exit_message("could not dup read fd");
		printf("could not dup read fd\n");
		return ;
	}
	if (dup2(write, STDOUT_FILENO) == -1)
	{
		// exit_message("could not dup output fd");
		printf("could not dup output fd\n");
		return ;
	}
	//execve(command[0], command, infos()->envp);
	//exit_message("exec did not work");
	if (!execute(command) < 0)
		printf("exec did not work\n");
}

/* write process ::: will allways read either from pipe_aux[0] or from infile
	and write on pipe_fd[1]*/
void	first_child_process(int i)
{
	if (i == 0)
		exec_command(STDIN_FILENO, base()->pipe.pipe_fd[1],
			base()->pipe.cmds[i]);
	else if (i == base()->pipe.num_cmds - 1)
		exec_command(base()->pipe.pipe_aux[0], STDOUT_FILENO,
			base()->pipe.cmds[i]);
	else
		exec_command(base()->pipe.pipe_aux[0],
			base()->pipe.pipe_fd[1], base()->pipe.cmds[i]);
}

/*read process ::: will allways read pipe_fd[0]
	and write on pipe_aux[1] or outfile*/
void	second_child_process(int i)
{
	if (i == base()->pipe.num_cmds - 1)
		exec_command(base()->pipe.pipe_fd[0], STDOUT_FILENO,
			base()->pipe.cmds[i]);
	else
		exec_command(base()->pipe.pipe_fd[0],
			base()->pipe.pipe_aux[1], base()->pipe.cmds[i]);
}
