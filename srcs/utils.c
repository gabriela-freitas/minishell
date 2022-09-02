/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:09:23 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/02 11:30:14 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Function used to print errors in parsing: exit errors, parsing pipes
	and unfinished quotes. It also updates the errnumb*/
void	parse_error_message(char *cmd, char *error, int error_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	base()->errnumb = error_code;
}

/*Function to print errors during execution*/
void	error_message(char *cmd, char *arg, char *error, int error_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	base()->errnumb = error_code;
}

/*	Prints the error for command not found
	and updates the error number accordingly*/
void	command_not_found(char *cmd)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	base()->errnumb = 127;
}

/*	ignores the ctrl+C signal during command execution
	so it's not interpreted twice,
	as for pressing ctrl+C when a command waits for input*/
void	sig_block(int sig)
{
	(void) sig;
	signal(SIGINT, SIG_IGN);
	base()->errnumb = 130;
	printf("\n");
}
