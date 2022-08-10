/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:45:57 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/10 23:01:36 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent_process(int i);

void	pipex(void)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < base()->pipe.num_cmds)
	{
		if (pipe(base()->pipe.pipe_fd) == -1)
		{
			// exit_message("Pipe didn't work");
			printf("Pipe didn't work\n");
			return ;
		}
		pid = fork();
		if (pid == -1)
		{
			// exit_message("Could not fork");
			printf("Could not fork");
			return ;
		}
		if (!pid)
			first_child_process(i);
		else
		{
			close(base()->pipe.pipe_fd[1]);
			close(base()->pipe.pipe_aux[0]);
			wait(NULL);
			if (i == base()->pipe.num_cmds - 1)
				break ;
			i++;
			parent_process(i);
		}
	}
}

/*execute first fork's parent process*/
static void	parent_process(int i)
{
	pid_t	pid;

	if (pipe(base()->pipe.pipe_aux) == -1)
	{
		// exit_message("Pipe aux didn't work");
		printf("Pipe aux didn't work\n");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		// exit_message("Could not fork");
		printf("Could not fork\n");
		return ;
	}
	if (!pid)
		second_child_process(i);
	else
	{
		close(base()->pipe.pipe_fd[0]);
		close(base()->pipe.pipe_aux[1]);
		wait(NULL);
	}
	return ;
}
