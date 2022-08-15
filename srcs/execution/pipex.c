/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:45:57 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/15 14:42:12 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	parent_process(int i);

// pipe[0] >> read
// pipe[1] >> write
void	pipex(int i)
{
	if (base()->pipe.num_cmds == 1)
	{
		execute(base()->pipe.cmds[0]);
		return ;
	}
	while (++i < base()->pipe.num_cmds)
	{
		if (pipe(base()->pipe.pipe_fd) == -1)
		{
			// exit_message("Pipe didn't work");
			printf("Pipe didn't work\n");
			return ;
		}
		//close(base()->pipe.pipe_aux[1]);
		if (i == 0)
			close(base()->pipe.pipe_fd[0]);
		first_child_process(i);
		// close(base()->pipe.pipe_fd[1]);
		if (i == base()->pipe.num_cmds - 1)
			break ;
		i++;
		if (pipe(base()->pipe.pipe_aux) == -1)
		{
			// exit_message("Pipe aux didn't work");
			printf("Pipe aux didn't work\n");
			return ;
		}
		// close(base()->pipe.pipe_aux[0]);
		second_child_process(i);
		// close(base()->pipe.pipe_aux[1]);
		// close(base()->pipe.pipe_fd[0]);
	}
}
