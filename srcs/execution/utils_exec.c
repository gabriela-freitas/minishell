/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:50:22 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/30 22:51:35 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	ignores the ctrl+C signal during command execution
	so it's not interpreted twice,
	as for pressing ctrl+C when a command waits for input*/
void	sig_block(int sig)
{
	(void) sig;
	signal(SIGINT, SIG_IGN);
	base()->errnumb = 130;
}

/*	same as sig_block but adds a new line*/
void	sig_block_nl(int sig)
{
	(void) sig;
	signal(SIGINT, SIG_IGN);
	base()->errnumb = 130;
	printf("\n");
}

int	exec_setup_one(t_pipex *pipe)
{
	if (base()->num_pipes == 1)
	{
		if (!open_files(pipe))
			return (FALSE);
		if (pipe->fd[OUT] != STD)
			dup2(pipe->fd[OUT], STDOUT_FILENO);
		if (pipe->fd[IN] != STD)
			dup2(pipe->fd[IN], STDIN_FILENO);
		if (pipe->fd[OUT] != STD)
			close(pipe->fd[OUT]);
		if (pipe->fd[IN] != STD)
			close(pipe->fd[IN]);
	}
	return (TRUE);
}
